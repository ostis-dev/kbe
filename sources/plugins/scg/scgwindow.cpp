/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
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
#include <QToolButton>
#include <QFileDialog>

#include "scglayoutmanager.h"
#include "arrangers/scgarrangervertical.h"
#include "arrangers/scgarrangerhorizontal.h"
#include "arrangers/scgarrangergrid.h"
#include "arrangers/scgarrangertuple.h"

#include "select/scgselectinputoutput.h"
#include "select/scgselectsubgraph.h"

#include "scgplugin.h"
#include "scgexportimage.h"

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
const qreal SCgWindow::minScale = 0.20;
const qreal SCgWindow::maxScale = 9.99;

SCgWindow::SCgWindow(const QString& _windowTitle, QWidget *parent)
    : QWidget(parent)
    , mView(0)
    , mScene(0)
    , mZoomFactorLine(0)
    , mMinimap(0)
    , mUndoView(0)
    , mFindWidget(0)
    , mToolBar(0)
    , mUndoStack(0)
    , mEditMenu(0)
    , mActionUndo(0)
    , mActionRedo(0)
    , mActionFind(0)
{
    Q_UNUSED(_windowTitle);

    mUndoStack = new QUndoStack(this);
    /////////////////////////////////////////////////
    //Creating main environment
    mView = new SCgView(0, this);
    mScene = new SCgScene(mUndoStack, mView);
    mView->setScene(mScene);
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
    this->addAction(mActionFind);
    connect(mActionFind, SIGNAL(triggered()), this, SLOT(showTextSearch()));

    mActionUndo = mUndoStack->createUndoAction(this, tr("Undo"));//new QAction(tr("Undo"),this);
    mActionUndo->setEnabled(false);
    mActionUndo->setShortcut(QKeySequence::Undo);
    this->addAction(mActionUndo);
    mActionUndo->setIcon(QIcon::fromTheme("edit-undo", findIcon("edit-undo.png")));

    mActionRedo = mUndoStack->createRedoAction(this, tr("Redo"));//new QAction(tr("Redo"),this);
    mActionRedo->setEnabled(false);
    mActionRedo->setShortcut(QKeySequence::Redo);
    this->addAction(mActionRedo);
    mActionRedo->setIcon(QIcon::fromTheme("edit-redo", findIcon("edit-redo.png")));
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

    mToolBar->setIconSize(QSize(32, 32));

    QActionGroup* group = new QActionGroup(mToolBar);

    // Select mode
    QAction *action = new QAction(findIcon("tool-select.png"), tr("Selection mode"), mToolBar);
    action->setCheckable(true);
    action->setChecked(true);
    action->setShortcut(QKeySequence(tr("1", "Selection mode")));
    group->addAction(action);
    mToolBar->addAction(action);
    mMode2Action[SCgScene::Mode_Select] = action;
    connect(action, SIGNAL(triggered()), this, SLOT(onSelectMode()));

    //Pair creation mode
    action = new QAction(findIcon("tool-pair.png"), tr("Pair creation mode"), mToolBar);
    action->setCheckable(true);
    action->setShortcut(QKeySequence(tr("2", "Pair creation mode")));
    group->addAction(action);
    mToolBar->addAction(action);
    mMode2Action[SCgScene::Mode_Pair] = action;
    connect(action, SIGNAL(triggered()), this, SLOT(onPairMode()));

    //Bus creation mode
    action = new QAction(findIcon("tool-bus.png"), tr("Bus creation mode"), mToolBar);
    action->setCheckable(true);
    action->setShortcut(QKeySequence(tr("3", "Bus creation mode")));
    group->addAction(action);
    mToolBar->addAction(action);
    mMode2Action[SCgScene::Mode_Bus] = action;
    connect(action, SIGNAL(triggered()), this, SLOT(onBusMode()));

    //Contour creation mode
    action = new QAction(findIcon("tool-contour.png"), tr("Contour creation mode"), mToolBar);
    action->setCheckable(true);
    action->setShortcut(QKeySequence(tr("4", "Contour creation mode")));
    group->addAction(action);
    mToolBar->addAction(action);
    mMode2Action[SCgScene::Mode_Contour] = action;
    connect(action, SIGNAL(triggered()), this, SLOT(onContourMode()));
    //
    mToolBar->addSeparator();
    //

    // align group button
    QToolButton *alignButton = new QToolButton(mToolBar);
    alignButton->setIcon(findIcon("tool-align.png"));
    alignButton->setPopupMode(QToolButton::InstantPopup);
    alignButton->setToolTip(tr("Alignment"));
    mToolBar->addWidget(alignButton);

    //Grid alignment
    action = new QAction(findIcon("tool-align-grid.png"), tr("Grid alignment"), mToolBar);
    action->setCheckable(false);
    action->setShortcut(QKeySequence(tr("5", "Grid alignment")));
    alignButton->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(onGridAlignment()));

    // tuple alignment
    action = new QAction(findIcon("tool-align-tuple.png"), tr("Tuple alignment"), mToolBar);
    action->setCheckable(false);
    action->setShortcut(QKeySequence(tr("6", "Tuple alignment")));
    alignButton->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(onTupleAlignment()));

    //Vertical alignment
    action = new QAction(findIcon("tool-align-vert.png"), tr("Vertical alignment"), mToolBar);
    action->setCheckable(false);
    action->setShortcut(QKeySequence(tr("7", "Vertical alignment")));
    alignButton->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(onVerticalAlignment()));

    //Horizontal alignment
    action = new QAction(findIcon("tool-align-horz.png"), tr("Horizontal alignment"), mToolBar);
    action->setCheckable(false);
    action->setShortcut(QKeySequence(tr("8", "Horizontal alignment")));
    alignButton->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(onHorizontalAlignment()));

    // selection group button
    QToolButton *selectButton = new QToolButton(mToolBar);
    selectButton->setIcon(findIcon("tool-select-group.png"));
    selectButton->setPopupMode(QToolButton::InstantPopup);
    selectButton->setToolTip(tr("Selection group"));
    mToolBar->addWidget(selectButton);

    // input/output selection
    action = new QAction(findIcon("tool-select-inout.png"), tr("Select input/output"), mToolBar);
    action->setCheckable(false);
    selectButton->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(onSelectInputOutput()));

    // sbgraph selection
    action = new QAction(findIcon("tool-select-subgraph.png"), tr("Select subgraph"), mToolBar);
    action->setCheckable(false);
    selectButton->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(onSelectSubgraph()));

    mToolBar->addSeparator();

    action = new QAction(findIcon("tool-export-image.png"), tr("Export image"), mToolBar);
    action->setCheckable(false);
    action->setShortcut(QKeySequence(tr("0", "Export image")));
    mToolBar->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(onExportImage()));

    //
    mToolBar->addSeparator();
    //
    //Zoom in
    action = new QAction(findIcon("tool-zoom-in.png"), tr("Zoom in"), mToolBar);
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
    action = new QAction(findIcon("tool-zoom-out.png"), tr("Zoom out"), mToolBar);
    action->setCheckable(false);
    action->setShortcut(QKeySequence(tr("-", "Zoom out")));
    mToolBar->addAction(action);
    connect(action, SIGNAL(triggered()), this, SLOT(onZoomOut()));

    mToolBar->setWindowTitle(tr("SCg Tools"));
    mToolBar->setObjectName("SCgMainToolBar");

    //! @bug toolbar state is not saved
    mToolBar->setMovable(false);
}

QIcon SCgWindow::findIcon(const QString &iconName)
{
    return QIcon(":/scg/media/icons/" + iconName);
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
        setWindowTitle(mFileName);
        emitEvent(EditorObserverInterface::ContentLoaded);
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
        setWindowTitle(mFileName);
        mUndoStack->setClean();
        emitEvent(EditorObserverInterface::ContentSaved);

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

void SCgWindow::onSelectInputOutput()
{
    SCgSelectInputOutput select;
    select.doSelection(mScene);
}

void SCgWindow::onSelectSubgraph()
{
    SCgSelectSubGraph select;
    select.doSelection(mScene);
}

void SCgWindow::onExportImage()
{

    QFileDialog::Options options;
    options |= QFileDialog::DontUseNativeDialog;
    QMap<QString, QString> filtersMap;

    SCgExportImage exportImage;
    QString selectedFilter;
    QString formatsStr, fmt;

    QStringList formats = exportImage.supportedFormats();
    foreach(fmt, formats)
    {
        QString filter = tr("%1 image (*.%1)").arg(fmt);
        formatsStr += filter + ";;";
        filtersMap[filter] = fmt;
    }
    formatsStr = formatsStr.left(formatsStr.length() - 2);

    QString fileName = QCoreApplication::applicationDirPath() + "/" + currentFileName();
    fileName = QFileDialog::getSaveFileName(this,
                                           tr("Export file to ..."),
                                           fileName,
                                           formatsStr,
                                           &selectedFilter,
                                           options);

    if (fileName.length() > 0)
    {
        QFileInfo info(fileName);

        if (info.suffix().isEmpty())
            fileName += "." + filtersMap[selectedFilter];
        else
        {
            // replace suffix if it not in selected filter
            if (info.suffix() != filtersMap[selectedFilter])
                fileName = fileName.left(fileName.size() - info.suffix().size()) + filtersMap[selectedFilter];
        }
        exportImage.doExport(mScene, fileName);
    }
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
    static_cast<SCgScene*>(mView->scene())->setEditMode(SCgScene::Mode_InsertTemplate);
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
}

void SCgWindow::deleteMenu()
{
    Q_ASSERT(mEditMenu);

    delete mEditMenu;
    mEditMenu = 0;
}

void SCgWindow::stackCleanStateChanged(bool value)
{
    Q_UNUSED(value);
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

QIcon SCgWindowFactory::icon() const
{
    return SCgWindow::findIcon("mime_type.png");
}
