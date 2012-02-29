/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#include "scgwindow.h"

#include <QToolBar>
#include <QApplication>
#include <QClipboard>
#include <QAction>
#include <QUndoStack>
#include <QComboBox>
#include <QLineEdit>
#include <QMimeData>
#include <QActionGroup>
#include <QBoxLayout>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QDebug>

#include "scglayoutmanager.h"
#include "scgarrangervertical.h"
#include "scgarrangerhorizontal.h"
#include "scgarrangergrid.h"
#include "scgarrangertuple.h"
#include "scgplugin.h"

#include "scgfindwidget.h"
#include "scgview.h"
#include "scgminimap.h"
#include "gwf/gwffileloader.h"
#include "gwf/gwffilewriter.h"
#include "gwf/gwfobjectinforeader.h"
#include "scgtemplateobjectbuilder.h"
#include "config.h"
#include "scgundoview.h"


const QString SCgWindow::SupportedPasteMimeType = "text/KBE-gwf";

const QStringList SCgWindow::mScales = QStringList()<< "25" << "50"
                                                    << "75" << "100"
                                                    << "125" << "150"
                                                    << "175" << "200";
const int SCgWindow::mScaleChangeStep = 25;

SCgWindow::SCgWindow(const QString& _windowTitle, QWidget *parent) :
    QWidget(parent),
    mView(0),
    mZoomFactorLine(0),
    mMinimap(0),
    mUndoView(0),
    mFindWidget(0),
    mToolBar(0),
    mUndoStack(0),
//    mViewMenu(0),
    mEditMenu(0),
    mActionUndo(0),
    mActionRedo(0),
    mActionFind(0)//,
//    mActionMinMap(0)
{

    setObjectName(QString((quint32)this));

    mUndoStack = new QUndoStack(this);
    /////////////////////////////////////////////////
    //Creating main environment
    mView = new SCgView(0, this);
    mView->setScene(new SCgScene(mUndoStack, mView));
    mView->setSceneRect(0, 0, 1000, 1000);

    mFindWidget = new SCgFindWidget(this);
    connect(mFindWidget, SIGNAL(findNext()), this, SLOT(findNext()));
    connect(mFindWidget, SIGNAL(findPrevious()), this, SLOT(findPrevious()));
    connect(mFindWidget, SIGNAL(find(QString)), this, SLOT(findTextChanged(QString)));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(mView);
    layout->addWidget(mFindWidget);

    setLayout(layout);

    setAttribute(Qt::WA_DeleteOnClose);
    connect(mUndoStack, SIGNAL(cleanChanged(bool)), this, SLOT(stackCleanStateChanged(bool)));

    /////////////////////////////////////////////////

    // Create widgets, which will be added into dock area of main window.
    createWidgetsForDocks();

    createActions();

    createToolBar();
}

SCgWindow::~SCgWindow()
{
    delete mToolBar;
    delete mView;
    delete mUndoView;
    delete mMinimap;
    delete mFindWidget;
    delete mUndoStack;
}

QUndoStack* SCgWindow::undoStack() const
{
    return mUndoStack;
}

void SCgWindow::createActions()
{
    mActionFind = new QAction(findIcon("edit-find.png"), tr("&Find by Identifier..."), this);
    mActionFind->setShortcuts(QKeySequence::Find);
    mActionFind->setIcon(QIcon::fromTheme("edit-find", findIcon("edit-find.png")));
    connect(mActionFind, SIGNAL(triggered()), this, SLOT(showTextSearch()));

    mActionUndo = mUndoStack->createUndoAction(this, tr("Undo"));//new QAction(tr("Undo"),this);
    mActionUndo->setEnabled(false);
    mActionUndo->setShortcut(QKeySequence::Undo);
    mActionUndo->setIcon(QIcon::fromTheme("edit-undo", findIcon("edit-undo.png")));

    mActionRedo = mUndoStack->createRedoAction(this, tr("Redo"));//new QAction(tr("Redo"),this);
    mActionRedo->setEnabled(false);
    mActionRedo->setShortcut(QKeySequence::Redo);
    mActionRedo->setIcon(QIcon::fromTheme("edit-redo", findIcon("edit-redo.png")));

//    mActionMinMap = new QAction(tr("Minimap"), this);
//    mActionMinMap->setCheckable(true);
//    mActionMinMap->setShortcuts();
//    fi.setFile();
//    mActionMinMap->setIcon(QIcon(fi.absoluteFilePath()));
//    connect(mActionMinMap, SIGNAL(triggered(bool)), this, SLOT(setVisibleMinMap(bool)));
}

void SCgWindow::createWidgetsForDocks()
{
    //Creating widgets for docks
    mMinimap = new SCgMinimap(mView, mView->viewport());
    mMinimap->setWindowTitle(tr("Mini map"));
    mMinimap->setObjectName("Mini map");

    mUndoView = new SCgUndoView(this);
    mUndoView->setStack(mUndoStack);
    mUndoView->setWindowTitle(tr("History"));
    mUndoView->setObjectName("History");

    //Register this widgets
    mWidgetsForDocks.push_back(mUndoView);
    mWidgetsForDocks.push_back(mMinimap);
}


void SCgWindow::createToolBar()
{
    mToolBar = new QToolBar(this);

    mToolBar->setIconSize(QSize(42, 32));

    QActionGroup* group = new QActionGroup(mToolBar);

    // Select mode
    QAction *action = new QAction(findIcon("tool-select.png"), tr("Selection mode(1)"), mToolBar);
    action->setCheckable(true);
    action->setChecked(true);
    action->setShortcut(QKeySequence(tr("1", "Selection mode")));
    group->addAction(action);
    mToolBar->addAction(action);
    mMode2Action[SCgScene::Mode_Select] = action;
    connect(action, SIGNAL(triggered()), this, SLOT(onSelectMode()));

    //Pair creation mode
    action = new QAction(findIcon("tool-pair.png"), tr("Pair creation mode(2)"), mToolBar);
    action->setCheckable(true);
    action->setShortcut(QKeySequence(tr("2", "Pair creation mode")));
    group->addAction(action);
    mToolBar->addAction(action);
    mMode2Action[SCgScene::Mode_Pair] = action;
    connect(action, SIGNAL(triggered()), this, SLOT(onPairMode()));

    //Bus creation mode
    action = new QAction(findIcon("tool-bus.png"), tr("Bus creation mode(3)"), mToolBar);
    action->setCheckable(true);
    action->setShortcut(QKeySequence(tr("3", "Bus creation mode")));
    group->addAction(action);
    mToolBar->addAction(action);
    mMode2Action[SCgScene::Mode_Bus] = action;
    connect(action, SIGNAL(triggered()), this, SLOT(onBusMode()));

    //Contour creation mode
    action = new QAction(findIcon("tool-contour.png"), tr("Contour creation mode(4)"), mToolBar);
    action->setCheckable(true);
    action->setShortcut(QKeySequence(tr("4", "Contour creation mode")));
    group->addAction(action);
    mToolBar->addAction(action);
    mMode2Action[SCgScene::Mode_Contour] = action;
    connect(action, SIGNAL(triggered()), this, SLOT(onContourMode()));
    //
    mToolBar->addSeparator();
    //
    //Grid alignment
    action = new QAction(findIcon("tool-align-grid.png"), tr("Grid alignment (5)"), mToolBar);
    action->setCheckable(false);
    action->setShortcut(QKeySequence(tr("5", "Grid alignment")));
    mToolBar->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(onGridAlignment()));

    // tuple alignment
    action = new QAction(findIcon("tool-align-tuple.png"), tr("Tuple alignment (6)"), mToolBar);
    action->setCheckable(false);
    action->setShortcut(QKeySequence(tr("6", "Tuple alignment")));
    mToolBar->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(onTupleAlignment()));

    //Vertical alignment
    action = new QAction(findIcon("tool-align-vert.png"), tr("Vertical alignment (7)"), mToolBar);
    action->setCheckable(false);
    action->setShortcut(QKeySequence(tr("7", "Vertical alignment")));
    mToolBar->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(onVerticalAlignment()));

    //Horizontal alignment
    action = new QAction(findIcon("tool-align-horz.png"), tr("Horizontal alignment (8)"), mToolBar);
    action->setCheckable(false);
    action->setShortcut(QKeySequence(tr("8", "Horizontal alignment")));
    mToolBar->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(onHorizontalAlignment()));

    //
    mToolBar->addSeparator();
    //
    //Zoom in
    action = new QAction(findIcon("tool-zoom-in.png"), tr("Zoom in(+)"), mToolBar);
    action->setCheckable(false);
    action->setShortcut(QKeySequence(tr("+", "Zoom in")));
    mToolBar->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(onZoomIn()));

    //Scale combobox
    QComboBox* b = new QComboBox(mToolBar);
    b->setEditable(true);
    b->setInsertPolicy(QComboBox::NoInsert);
    b->addItems(SCgWindow::mScales);
    b->setCurrentIndex(mScales.indexOf("100"));
    mZoomFactorLine = b->lineEdit();
    mZoomFactorLine->setInputMask("D90%");
    mToolBar->addWidget(b);
    connect(mZoomFactorLine, SIGNAL(textChanged(const QString&)), mView, SLOT(setScale(const QString&)));
    connect(mView, SIGNAL(scaleChanged(qreal)), this, SLOT(onViewScaleChanged(qreal)));

    //Zoom out
    action = new QAction(findIcon("tool-zoom-out.png"), tr("Zoom out(-)"), mToolBar);
    action->setCheckable(false);
    action->setShortcut(QKeySequence(tr("-", "Zoom out")));
    mToolBar->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(onZoomOut()));


    mToolBar->setWindowTitle(tr("SCg Tools"));
}

QIcon SCgWindow::findIcon(const QString &iconName) const
{
    return QIcon(":/media/icons/" + iconName);
}

QIcon SCgWindow::icon() const
{
    return findIcon("mime_type.png");
}

bool SCgWindow::loadFromFile(const QString &fileName)
{
    GWFFileLoader loader;

    if (loader.load(fileName, mView->scene()))
    {
        mFileName = fileName;
        setWindowTitle(mFileName + "[*]");
        return true;
    }else
        return false;
}

bool SCgWindow::saveToFile(const QString &fileName)
{
    GWFFileWriter writer;

    if (writer.save(fileName, mView->scene()))
    {
        mFileName = fileName;
        setWindowTitle(mFileName + "[*]");
        mUndoStack->setClean();
        return true;
    }else
        return false;
}

void SCgWindow::_update()
{
    if (mView->cacheMode() != QGraphicsView::CacheNone)
        mView->resetCachedContent();

    mView->repaint();
}

void SCgWindow::onSelectMode()
{
    static_cast<SCgScene*>(mView->scene())->setEditMode(SCgScene::Mode_Select);
    mView->viewport()->setCursor(Qt::ArrowCursor);
    mView->setDragMode(QGraphicsView::RubberBandDrag);
}

void SCgWindow::onPairMode()
{
    static_cast<SCgScene*>(mView->scene())->setEditMode(SCgScene::Mode_Pair);
    mView->viewport()->setCursor(Qt::UpArrowCursor);
    mView->setDragMode(QGraphicsView::NoDrag);
}

void SCgWindow::onBusMode()
{
    static_cast<SCgScene*>(mView->scene())->setEditMode(SCgScene::Mode_Bus);
    mView->viewport()->setCursor(Qt::CrossCursor);
    mView->setDragMode(QGraphicsView::NoDrag);
}

void SCgWindow::onContourMode()
{
    static_cast<SCgScene*>(mView->scene())->setEditMode(SCgScene::Mode_Contour);
    mView->viewport()->setCursor(Qt::CrossCursor);
    mView->setDragMode(QGraphicsView::NoDrag);
}

void SCgWindow::onGridAlignment()
{
    SCgLayoutManager::instance().arrange(mView, SCgGridArranger::Type);
}

void SCgWindow::onTupleAlignment()
{
    SCgLayoutManager::instance().arrange(mView, SCgTupleArranger::Type);
}

void SCgWindow::onVerticalAlignment()
{
    SCgLayoutManager::instance().arrange(mView, SCgVerticalArranger::Type);
}

void SCgWindow::onHorizontalAlignment()
{
    SCgLayoutManager::instance().arrange(mView, SCgHorizontalArranger::Type);
}

void SCgWindow::onZoomIn()
{
    int oldScale = mZoomFactorLine->text().remove('%').toInt();
    int newScale = oldScale + mScaleChangeStep;

    if(newScale > int(maxScale*100))
        newScale = int(maxScale*100);

    mZoomFactorLine->setText(QString::number(newScale));
}

void SCgWindow::onZoomOut()
{
    int oldScale = mZoomFactorLine->text().remove('%').toInt();
    int newScale = oldScale - mScaleChangeStep;

    if(newScale < int(minScale*100))
        newScale = int(minScale*100);

    mZoomFactorLine->setText(QString::number(newScale));
}

void SCgWindow::onViewScaleChanged(qreal newScale)
{
    qreal oldScale = mZoomFactorLine->text().remove('%').toDouble() / 100;
    if (newScale != oldScale)
        mZoomFactorLine->setText(QString::number(int(newScale*100)));
}

void SCgWindow::cut() const
{
    copy();
    static_cast<SCgScene*>(mView->scene())->deleteSelObjectsCommand();
}

void SCgWindow::copy() const
{
    QByteArray copiedData;
    GwfStreamWriter writer(&copiedData);
    ////////////////////////////////////
    writer.startWriting();

    QList<QGraphicsItem *>  items = mView->scene()->selectedItems();
    if (items.isEmpty())
        return;

    foreach (QGraphicsItem *item, items)
        if(SCgObject::isSCgObjectType(item->type()) )
            writer.writeObject(static_cast<SCgObject*>(item));

    writer.finishWriting();
    ///////////////////////////////////
    QMimeData* d = new QMimeData();

    d->setData(SupportedPasteMimeType, copiedData);
    QApplication::clipboard()->setMimeData(d);

}

void SCgWindow::paste() const
{
    const QMimeData* data = QApplication::clipboard()->mimeData();
    if(data->hasFormat(SupportedPasteMimeType))
    {
        QDomDocument document;

        if (!document.setContent(data->data(SupportedPasteMimeType)))
            return;

        // Read document
        GwfObjectInfoReader reader;
        if (! reader.read(document))
            return;

        //Place objects to scene
        TemplateSCgObjectsBuilder objectBuilder(mView->scene());
        objectBuilder.buildObjects(reader.objectsInfo());

        static_cast<SCgScene*>(mView->scene())->pasteTemplate(objectBuilder.objects());
    }
}

void SCgWindow::deleteSelected()
{

}

void SCgWindow::showTextSearch()
{
    mFindWidget->show();
}

void SCgWindow::findNext()
{
    find(mFindWidget->text(), true);
}

void SCgWindow::findPrevious()
{
    find(mFindWidget->text(), false);
}

void SCgWindow::findTextChanged(const QString &ttf)
{
    find(ttf, true, true);
}

void SCgWindow::find(const QString &ttf, bool forward, bool checkCurrent)
{
    mFindWidget->setTextWrappedVisible(false);

    SCgScene *scene = dynamic_cast<SCgScene*>(mView->scene());

    Q_ASSERT(scene);

    SCgScene::FindFlags flg = 0;

    if(forward)
        flg |= SCgScene::FindForward;

    if(checkCurrent)
        flg |= SCgScene::CheckCurrent;

    if(mFindWidget->caseSensitive())
        flg |= SCgScene::CaseSensitive;

    SCgObject* found = scene->find(ttf, flg);
    if(!found)
    {
        if(forward)
            scene->setCursorPos(scene->sceneRect().topLeft());
        else
            scene->setCursorPos(scene->sceneRect().bottomRight());
        found = scene->find(ttf, flg);
        if(found)
            mFindWidget->setTextWrappedVisible(true);
    }

    if (!mFindWidget->isVisible())
        mFindWidget->show();

    if (!found && ttf.isEmpty())
        mFindWidget->setPalette(true);
    else
        mFindWidget->setPalette(found);

    if(found)
    {
        mView->ensureVisible(found, 300, 300);
        mView->scene()->clearSelection();
        found->setSelected(true);
        scene->setCursorPos(found->sceneBoundingRect().topLeft());
    }
}

void SCgWindow::activate(QMainWindow *window)
{
    EditorInterface::activate(window);

    createMenu();
    QList<QAction*> allMenus = window->menuBar()->actions();
    window->menuBar()->insertMenu(allMenus.at(1), mEditMenu);

    QToolBar *tool_bar = toolBar();
    if (tool_bar != 0)
    {
        window->addToolBar(Qt::LeftToolBarArea, tool_bar);
        tool_bar->show();
    }
    mUndoStack->setActive(true);
}

void SCgWindow::deactivate(QMainWindow *window)
{
    EditorInterface::deactivate(window);
    deleteMenu();

    window->removeToolBar(toolBar());
    mUndoStack->setActive(false);
}

QWidget* SCgWindow::widget()
{
    return this;
}

QToolBar* SCgWindow::toolBar()
{
    return mToolBar;
}

QList<QWidget*> SCgWindow::widgetsForDocks()
{
    return mWidgetsForDocks;
}

bool SCgWindow::isSaved() const
{
    return mUndoStack->isClean();
}

QStringList SCgWindow::supportedFormatsExt() const
{
    QStringList res;
    res << "gwf";
    return res;
}

void SCgWindow::createMenu()
{
    Q_ASSERT(!mEditMenu);

    mEditMenu = new QMenu(tr("Edit"), this);
    mEditMenu->addAction(mActionUndo);
    mEditMenu->addAction(mActionRedo);
    mEditMenu->addSeparator()->setParent(mEditMenu);
    mEditMenu->addAction(mActionFind);

    mEditMenu->addActions(mView->actions());


//
//    mViewMenu = new QMenu(tr("View"), this);
//    mViewMenu ->addAction(mActionMinMap);
}

void SCgWindow::deleteMenu()
{
    Q_ASSERT(mEditMenu);
    delete mEditMenu;
//    delete mViewMenu;
//    mViewMenu = 0;
    mEditMenu = 0;
}

void SCgWindow::stackCleanStateChanged(bool value)
{
    emitEvent(EditorObserverInterface::ContentChanged);
}


// ---------------------
SCgWindowFactory::SCgWindowFactory(QObject *parent) :
    QObject(parent)
{

}

SCgWindowFactory::~SCgWindowFactory()
{
}

const QString& SCgWindowFactory::name() const
{
    static QString name = "scg";
    return name;
}

EditorInterface* SCgWindowFactory::createInstance()
{
    return new SCgWindow("");
}

QStringList SCgWindowFactory::supportedFormatsExt()
{
    QStringList res;
    res << "gwf";
    return res;
}
