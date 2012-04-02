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
#include "mainwindow.h"
#include "scgview.h"
#include "scgnode.h"
#include "scgpair.h"
#include "scgbus.h"
#include "scgcontour.h"
#include "scgcontentchangedialog.h"
#include "scgwindow.h"

#include <math.h>
#include <QUrl>
#include <QContextMenuEvent>
#include <QMenu>
#include <QKeyEvent>
#include <QScrollBar>
#include <QDialog>
#include <QLabel>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QLayout>
#include <QUndoStack>
#include <QCompleter>
#include <QFileInfo>

SCgView::SCgView(QWidget *parent, SCgWindow *window) :
    QGraphicsView(parent),
    mContextMenu(0),
    mContextObject(0),
    mWindow(window),
    isSceneRectControlled(false)
{
    setCacheMode(CacheNone);//CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setResizeAnchor(AnchorViewCenter);
    setOptimizationFlag(DontAdjustForAntialiasing);
    setDragMode(QGraphicsView::RubberBandDrag);
    setAcceptDrops(true);
    connect(mWindow->undoStack(), SIGNAL(indexChanged(int)), this, SLOT(updateActionsState(int)) );
    craeteActions();
}

SCgView::~SCgView()
{
    if (mContextMenu)   delete mContextMenu;
    mContextObject = 0;
}

void SCgView::craeteActions()
{
    QAction* sep = new QAction(this);
    sep->setSeparator(true);
    mActionsList.append(sep);

    mActionChangeContent = new QAction(mWindow->findIcon("edit-content-change.png"),tr("Set content"),mWindow);
    mActionChangeContent->setShortcut(QKeySequence( tr("C") ));
    connect(mActionChangeContent, SIGNAL(triggered()), this, SLOT(changeContent()));

    mActionShowContent = new QAction(tr("Show content"),mWindow);
    mActionShowContent->setCheckable(true);
    mActionShowContent->setShortcut(QKeySequence( tr("H") ));
    connect(mActionShowContent, SIGNAL(triggered(bool)), this, SLOT(setContentVisible(bool)));

    mActionDeleteContent = new QAction(mWindow->findIcon("edit-content-delete.png"),tr("Delete content"),mWindow);
    mActionDeleteContent->setShortcut(QKeySequence( tr("D") ));
    connect(mActionDeleteContent, SIGNAL(triggered()), this, SLOT(deleteContent()));

    mActionChangeIdtf = new QAction(mWindow->findIcon("edit-change-idtf.png"),tr("Change identifier"),mWindow);
    mActionChangeIdtf->setShortcut(QKeySequence( tr("I") ));
    connect(mActionChangeIdtf, SIGNAL(triggered()), this, SLOT(changeIdentifier()));

    mActionDelete = new QAction(QIcon::fromTheme("edit-delete", mWindow->findIcon("edit-delete.png")),tr("Delete"),mWindow);
    mActionDelete->setShortcut(QKeySequence::Delete);
    connect(mActionDelete, SIGNAL(triggered()), this, SLOT(deleteSelected()));

    mActionContourDelete = new QAction(mWindow->findIcon("edit-delete.png"),tr("Delete contour"),mWindow);
    mActionContourDelete->setShortcut( QKeySequence(tr("Backspace")) );
    connect(mActionContourDelete, SIGNAL(triggered()), this, SLOT(deleteJustContour()));

    mActionCopy = new QAction(QIcon::fromTheme("edit-copy", mWindow->findIcon("edit-copy.png")), tr("Copy"),this);
    mActionCopy->setShortcut(QKeySequence::Copy);
    connect(mActionCopy, SIGNAL(triggered()), mWindow, SLOT(copy()));

    mActionCut = new QAction(QIcon::fromTheme("edit-cut", mWindow->findIcon("edit-cut.png")),tr("Cut"),this);
    mActionCut->setShortcut(QKeySequence::Cut);
    connect(mActionCut, SIGNAL(triggered()), mWindow, SLOT(cut()));

    mActionPaste = new QAction(QIcon::fromTheme("edit-paste", mWindow->findIcon("edit-paste.png")), tr("Paste"),this);
    mActionPaste->setShortcut(QKeySequence::Paste);
    connect(mActionPaste, SIGNAL(triggered()), mWindow, SLOT(paste()));

    mActionSelect_All = new QAction(QIcon::fromTheme("edit-select-all", mWindow->findIcon("edit-select-all.png")), tr("Select All"),this);
    mActionSelect_All->setShortcut(QKeySequence::SelectAll);
    connect(mActionSelect_All, SIGNAL(triggered()), this, SLOT(selectAllCommand()));


    mActionsList.append(mActionChangeContent);
    mActionsList.append(mActionShowContent);
    mActionsList.append(mActionDeleteContent);

    sep = new QAction(this);
    sep->setSeparator(true);
    mActionsList.append(sep);

    mActionsList.append(mActionChangeIdtf);

    sep = new QAction(this);
    sep->setSeparator(true);
    mActionsList.append(sep);

    mActionsList.append(mActionCopy);
    mActionsList.append(mActionCut);
    mActionsList.append(mActionPaste);

    sep = new QAction(this);
    sep->setSeparator(true);
    mActionsList.append(sep);

    mActionsList.append(mActionSelect_All);

    sep = new QAction(this);
    sep->setSeparator(true);
    mActionsList.append(sep);

    mActionsList.append(mActionContourDelete);
    mActionsList.append(mActionDelete);
}

void SCgView::updateActionsState(int idx)
{
    mContextObject = 0;

    QList <QGraphicsItem*> items = scene()->selectedItems();
    if(items.size() == 1)
        if(SCgObject::isSCgObjectType(items.first()->type()))
            mContextObject = static_cast<SCgObject*>(items.first());

    if(mContextObject && mContextObject->type() == SCgNode::Type)
    {
        mActionChangeContent->setEnabled(true);
        mActionChangeContent->setVisible(true);
        SCgNode *node = static_cast<SCgNode*>(mContextObject);

        bool isContentData = node->isContentData();
        if(isContentData)
        {
            mActionChangeContent->setText(tr("Change content"));

            mActionShowContent->setChecked(node->isContentVisible());
        }
        else
            mActionChangeContent->setText(tr("Set content"));

        mActionDeleteContent->setEnabled(isContentData);
        mActionDeleteContent->setVisible(isContentData);

        mActionShowContent->setEnabled(isContentData);
        mActionShowContent->setVisible(isContentData);

    }else
    {
        mActionChangeContent->setEnabled(false);
        mActionChangeContent->setVisible(false);
        mActionShowContent->setEnabled(false);
        mActionShowContent->setVisible(false);
        mActionDeleteContent->setEnabled(false);
        mActionDeleteContent->setVisible(false);
    }

    mActionChangeIdtf->setEnabled(mContextObject);
    mActionChangeIdtf->setVisible(mContextObject);

    mActionContourDelete->setEnabled(mContextObject && mContextObject->type() == SCgContour::Type);
    mActionContourDelete->setVisible(mContextObject && mContextObject->type() == SCgContour::Type);

    bool isAnySelected = !scene()->selectedItems().isEmpty();
    mActionDelete->setEnabled(isAnySelected);
    mActionCut->setEnabled(isAnySelected);
    mActionCopy->setEnabled(isAnySelected);
}

QList<QAction*> SCgView::actions() const
{
    return mActionsList;
}

void SCgView::contextMenuEvent(QContextMenuEvent *event)
{
    // get scg-object under mouse
    QPointF mousePos = mapToScene(event->pos());/* +
                                QPointF(horizontalScrollBar()->value(), verticalScrollBar()->value()) -
                                scene()->sceneRect().topLeft();*/

    SCgObject *object = static_cast<SCgScene*>(scene())->objectAt(mousePos);

    // create context menu
    if (mContextMenu)
    {
        delete mContextMenu;
        mContextMenu = 0;
    }

    // selection by right mouse click
    if(object && !object->isSelected())
    {
        scene()->clearSelection();
        object->setSelected(true);
    }

    // create new context menu
    mContextMenu = new QMenu(this);

    if (mContextObject)
    {
        // creating menu actions depending on object type
        if (mContextObject->type() == SCgNode::Type || mContextObject->type() == SCgPair::Type)
        {
            // type changing
            QMenu *menu = mContextMenu->addMenu(tr("Change type"));

            connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(changeType(QAction*)));

            QMenu* constSub = menu->addMenu(tr("Const"));
            QMenu* varSub = menu->addMenu(tr("Var"));

            QString stype;
            SCgAlphabet::SCgObjectTypesMap types;
            SCgAlphabet::SCgObjectTypesMap::const_iterator iter;

            if (mContextObject->type() == SCgNode::Type)
                stype = "node";
            else if (mContextObject->type() == SCgPair::Type)
                stype = "pair";

            SCgAlphabet::getInstance().getObjectTypes(stype, SCgAlphabet::Const, types);
            for (iter = types.begin(); iter != types.end(); ++iter)
                constSub->addAction(iter.value(), iter.key())->setData(QVariant(iter.key()));
            types.clear();
            SCgAlphabet::getInstance().getObjectTypes(stype, SCgAlphabet::Var, types);
            for (iter = types.begin(); iter != types.end(); ++iter)
                varSub->addAction(iter.value(), iter.key())->setData(QVariant(iter.key()));
            types.clear();
        }
    }
    mContextMenu->addActions(mActionsList);

    QPoint menuPos;
    if (mContextObject) {
        QPoint itemPos;
        if (mContextObject->type() == SCgPair::Type || mContextObject->type() == SCgBus::Type)
            itemPos = mapFromParent(mContextObject->boundingRect().center().toPoint());
        else
            itemPos = mContextObject->scenePos().toPoint();
        menuPos = mapToGlobal(itemPos);
    }
    else
        menuPos = event->globalPos();
    mContextMenu->exec(menuPos);
}

void SCgView::selectAllCommand() const
{
    QList<QGraphicsItem*> list = items();
    QList<QGraphicsItem*>::iterator it = list.begin();
    for(; it != list.end(); ++it)
        (*it)->setSelected(true);
}

void SCgView::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);
}

void SCgView::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsView::keyReleaseEvent(event);
}

void SCgView::mouseMoveEvent (QMouseEvent * event)
{
    if(event->buttons() & Qt::MidButton)
    {
        viewport()->setCursor(Qt::ClosedHandCursor);
        QScrollBar *hBar = horizontalScrollBar();
        QScrollBar *vBar = verticalScrollBar();
        QPoint delta = event->pos() - mPrevMousePos;
        hBar->setValue(hBar->value() + (isRightToLeft() ? delta.x() : -delta.x()));
        vBar->setValue(vBar->value() - delta.y());
        mPrevMousePos = event->pos();
    }

    QGraphicsView::mouseMoveEvent(event);
}


void SCgView::mousePressEvent (QMouseEvent * event)
{
    if(event->button() == Qt::MidButton)
    {
        viewport()->setCursor(Qt::OpenHandCursor);
        mPrevMousePos = event->pos();
    }
    else
        QGraphicsView::mousePressEvent(event);
}

void SCgView::mouseReleaseEvent (QMouseEvent * event)
{
    if(event->button() == Qt::MidButton)
    {
        viewport()->setCursor(Qt::ArrowCursor);
        mPrevMousePos = event->pos();
    }
    else
        QGraphicsView::mouseReleaseEvent(event);
}


void SCgView::dragEnterEvent(QDragEnterEvent *evt)
{
    evt->acceptProposedAction();
}

void SCgView::dragLeaveEvent(QDragLeaveEvent *evt)
{
    evt->accept();
}

void SCgView::dragMoveEvent(QDragMoveEvent *evt)
{
    evt->acceptProposedAction();
}

void SCgView::dropEvent(QDropEvent *event)
{
    QGraphicsView::dropEvent(event);
    event->acceptProposedAction();
}

void SCgView::wheelEvent(QWheelEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier)
        setScale(pow(2.0, event->delta() / 280.0));
    else
        QGraphicsView::wheelEvent(event);
}

void SCgView::deleteSelected()
{
    static_cast<SCgScene*>(scene())->deleteSelObjectsCommand();
}

void SCgView::deleteJustContour()
{
    Q_ASSERT(mContextObject && mContextObject->type() == SCgContour::Type);

    SCgContour *contour = static_cast<SCgContour*>(mContextObject);
    static_cast<SCgScene*>(scene())->deleteContourCommand(contour);
}

void SCgView::changeIdentifier()
{
    Q_ASSERT(mContextObject);

    QDialog dialog(this);
    dialog.setWindowTitle(tr("Change identifier"));

    QLabel* label = new QLabel(tr("New identifier:"),&dialog);
    QLineEdit* lineEdit = new QLineEdit(&dialog);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                       | QDialogButtonBox::Cancel);
    buttonBox->setParent(&dialog);

    connect(buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(buttonBox);

    QCompleter *completer = new QCompleter(static_cast<SCgScene*>(scene())->idtfList(), &dialog);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    lineEdit->setCompleter(completer);
    QString oldIdtf = mContextObject->idtfValue();

    lineEdit->setText(oldIdtf);
    lineEdit->selectAll();

    dialog.setLayout(layout);
    lineEdit->setFocus();

    if (dialog.exec())
    {
        QString newIdtf = lineEdit->text();
        if(oldIdtf != newIdtf)
            static_cast<SCgScene*>(scene())->changeIdtfCommand(mContextObject, newIdtf);
    }
}

void SCgView::changeType(QAction *action)
{
    Q_ASSERT(mContextObject);

    static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject, action->data().toString());
}

void SCgView::changeContent()
{
    Q_ASSERT(mContextObject && mContextObject->type() == SCgNode::Type);
    SCgNode *node = static_cast<SCgNode*>(mContextObject);
    SCgContentChangeDialog dlg(node, this);

    if (dlg.exec() == QDialog::Accepted)
    {
        SCgContent::ContInfo info;
        dlg.contentInfo(info);
        if (node->contentType() != SCgContent::Empty || info.type != SCgContent::Empty)
            static_cast<SCgScene*>(scene())->changeContentDataCommand(node, info);
    }
}

void SCgView::setContentVisible(bool visibility)
{
    Q_ASSERT(mContextObject && mContextObject->type() == SCgNode::Type);

    SCgNode *node = static_cast<SCgNode*>(mContextObject);

    if(visibility != node->isContentVisible())
        static_cast<SCgScene*>(scene())->changeContentVisibilityCommand(node, visibility);
}

void SCgView::deleteContent()
{
    Q_ASSERT(mContextObject && mContextObject->type() == SCgNode::Type);

    SCgNode* node = static_cast<SCgNode*> (mContextObject);
    SCgContent::ContInfo empty;
    static_cast<SCgScene*>(scene())->changeContentDataCommand(node, empty);
}

void SCgView::setScale(const QString& sc)
{
    QTransform t = transform();
    //Default transform
    t.reset();

    //Getting percent value
    QString str = sc;
    str.remove("%");
    double d = str.toDouble()/100.0;

    //Checking if value d in proper range
    if (d < SCgWindow::minScale)
        d = SCgWindow::minScale;
    else
        if (d > SCgWindow::maxScale)
            d = SCgWindow::maxScale;

    //Setting transformation
    setTransform(t.scale(d,d),false);

    emit(scaleChanged(transform().mapRect(QRectF(0, 0, 1, 1)).width()));
}

void SCgView::setScale(qreal scaleFactor)
{
    // Factor, that will be set.
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

    if (factor < SCgWindow::minScale || factor > SCgWindow::maxScale)
    {
        // current zoom factor.
        qreal currFacror = transform().mapRect(QRectF(0, 0, 1, 1)).width();

        if (factor < SCgWindow::minScale)
            factor = SCgWindow::minScale;
        else
            factor = SCgWindow::maxScale;
        // calculates factor, that fit in proper range(0.2 .. 9.99)
        scaleFactor = factor / currFacror;
    }

    scale(scaleFactor, scaleFactor);

    emit(scaleChanged(factor));
}

void SCgView::setScene(SCgScene* scene)
{
    QGraphicsView::setScene(scene);
    connect(scene, SIGNAL(sceneRectChanged(const QRectF&)), this, SLOT(updateSceneRect(const QRectF&)) );
    connect(scene, SIGNAL(selectionChanged()), this, SLOT(updateActionsState()) );
    connect(scene, SIGNAL(editModeChanged(int)), this, SLOT(editModeChanged(int)));
    updateActionsState();
}

void SCgView::updateSceneRect(const QRectF& rect)
{
    if(!isSceneRectControlled && !sceneRect().contains(rect))
        isSceneRectControlled = true;

    if(isSceneRectControlled)
    {
        QPointF topLeft = mapToScene(0,0);
        QPointF bottomRight = mapToScene(viewport()->width(),viewport()->height());
        QRectF vis(topLeft,bottomRight);
        QRectF result = rect.adjusted(-100,-100,100,100).unite(vis).unite(sceneRect());
        setSceneRect(result);

        emit sceneRectChanged(result);
    }
}

void SCgView::editModeChanged(int mode)
{
    setContextMenuPolicy(mode == SCgScene::Mode_Select ? Qt::DefaultContextMenu : Qt::NoContextMenu);
}
