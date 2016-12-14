/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "mainwindow.h"
#include "scgview.h"
#include "scgnode.h"
#include "scgpair.h"
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
#include <QGroupBox>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QIcon>
#include <QWidget>
#include <QLabel>
#include <QMessageBox>

SCgView::SCgView(QWidget *parent, SCgWindow *window) :
    mActionChangeConstPair(0),
    mActionChangeVarPair(0),
    mActionChangeConstNode(0),
    mActionChangeVarNode(0),
    QGraphicsView(parent),
    mActionChangeContent(0),
    mActionShowContent(0),
    mActionShowAllContent(0),
    mActionHideAllContent(0),
    mActionDeleteContent(0),
    mActionChangeIdtf(0),
    mActionDelete(0),
    mActionContourDelete(0),
    mActionSwapPairOrient(0),
    mActionCopy(0),
    mActionCut(0),
    mActionPaste(0),
    mActionSelectAll(0),
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
    createActions();
}

SCgView::~SCgView()
{
    if (mContextMenu)   delete mContextMenu;
    mContextObject = 0;
}

void SCgView::createActions()
{
    QAction* sep = new QAction(this);
    sep->setSeparator(true);
    mActionsList.append(sep);

    mActionChangeContent = new QAction(mWindow->findIcon("edit-content-change.png"),tr("Set content"),mWindow);
    mActionChangeContent->setShortcut(QKeySequence( tr("C") ));
    mWindow->addAction(mActionChangeContent);
    connect(mActionChangeContent, SIGNAL(triggered()), this, SLOT(changeContent()));

    mActionShowContent = new QAction(tr("Show content"),mWindow);
    mActionShowContent->setCheckable(true);
    mActionShowContent->setShortcut(QKeySequence( tr("H") ));
    mWindow->addAction(mActionShowContent);
    connect(mActionShowContent, SIGNAL(triggered(bool)), this, SLOT(setContentVisible(bool)));

    mActionShowAllContent = new QAction(tr("Show all content"), mWindow);
    connect(mActionShowAllContent, SIGNAL(triggered(bool)), this, SLOT(setContentVisible(bool)));

    mActionHideAllContent = new QAction(tr("Hide all content"), mWindow);
    connect(mActionHideAllContent, SIGNAL(triggered(bool)), this, SLOT(setContentVisible(bool)));

    mActionDeleteContent = new QAction(mWindow->findIcon("edit-content-delete.png"), tr("Delete content"), mWindow);
    mActionDeleteContent->setShortcut(QKeySequence( tr("D") ));
    mWindow->addAction(mActionDeleteContent);
    connect(mActionDeleteContent, SIGNAL(triggered()), this, SLOT(deleteContent()));

    mActionChangeIdtf = new QAction(mWindow->findIcon("edit-change-idtf.png"), tr("Change identifier"), mWindow);
    mActionChangeIdtf->setShortcut(QKeySequence( tr("I") ));
    mWindow->addAction(mActionChangeIdtf);
    connect(mActionChangeIdtf, SIGNAL(triggered()), this, SLOT(changeIdentifier()));

    mActionDelete = new QAction(QIcon::fromTheme("edit-delete", mWindow->findIcon("edit-delete.png")), tr("Delete"), mWindow);
    mActionDelete->setShortcut(QKeySequence::Delete);
    mWindow->addAction(mActionDelete);
    connect(mActionDelete, SIGNAL(triggered()), this, SLOT(deleteSelected()));

    mActionContourDelete = new QAction(mWindow->findIcon("edit-delete.png"), tr("Delete contour"), mWindow);
    mActionContourDelete->setShortcut( QKeySequence(tr("Backspace")) );
    mWindow->addAction(mActionContourDelete);
    connect(mActionContourDelete, SIGNAL(triggered()), this, SLOT(deleteJustContour()));

    mActionSwapPairOrient = new QAction(mWindow->findIcon("edit-swap-pair.png"), tr("Swap orientation"), mWindow);
    mActionSwapPairOrient->setShortcut( QKeySequence(tr("S")));
    mWindow->addAction(mActionSwapPairOrient);
    connect(mActionSwapPairOrient, SIGNAL(triggered()), this, SLOT(swapPairOrient()));

    mActionCopy = new QAction(QIcon::fromTheme("edit-copy", mWindow->findIcon("edit-copy.png")), tr("Copy"),this);
    mActionCopy->setShortcut(QKeySequence::Copy);
    mWindow->addAction(mActionCopy);
    connect(mActionCopy, SIGNAL(triggered()), mWindow, SLOT(copy()));

    mActionCut = new QAction(QIcon::fromTheme("edit-cut", mWindow->findIcon("edit-cut.png")), tr("Cut"),this);
    mActionCut->setShortcut(QKeySequence::Cut);
    mWindow->addAction(mActionCut);
    connect(mActionCut, SIGNAL(triggered()), mWindow, SLOT(cut()));

    mActionPaste = new QAction(QIcon::fromTheme("edit-paste", mWindow->findIcon("edit-paste.png")), tr("Paste"),this);
    mActionPaste->setShortcut(QKeySequence::Paste);
    mWindow->addAction(mActionPaste);
    connect(mActionPaste, SIGNAL(triggered()), mWindow, SLOT(paste()));

    mActionSelectAll = new QAction(QIcon::fromTheme("edit-select-all", mWindow->findIcon("edit-select-all.png")), tr("Select All"),this);
    mActionSelectAll->setShortcut(QKeySequence::SelectAll);
    mWindow->addAction(mActionSelectAll);
    connect(mActionSelectAll, SIGNAL(triggered()), this, SLOT(selectAllCommand()));

    mActionChangeConstPair=new QAction(tr("Change const pair"),mWindow);
    mActionChangeConstPair->setShortcut(QKeySequence( tr("Alt+T") ));
    connect(mActionChangeConstPair, SIGNAL(triggered()), this, SLOT(changeConstPair()));

    mActionChangeVarPair=new QAction(tr("Change variant pair"),mWindow);
    mActionChangeVarPair->setShortcut(QKeySequence( tr("Alt+P") ));
    connect(mActionChangeVarPair, SIGNAL(triggered()), this, SLOT(changeVarPair()));

    mActionChangeConstNode=new QAction(tr("Change const node"),mWindow);
    mActionChangeConstNode->setShortcut(QKeySequence( tr("Alt+C") ));
    connect(mActionChangeConstNode, SIGNAL(triggered()), this, SLOT(changeConstNode()));

    mActionChangeVarNode=new QAction(tr("Change variant node"),mWindow);
    mActionChangeVarNode->setShortcut(QKeySequence( tr("Alt+S") ));
    connect(mActionChangeVarNode, SIGNAL(triggered()), this, SLOT(changeVarNode()));




    mActionsList.append(mActionChangeContent);
    mActionsList.append(mActionShowContent);
    mActionsList.append(mActionShowAllContent);
    mActionsList.append(mActionHideAllContent);
    mActionsList.append(mActionDeleteContent);

    sep = new QAction(this);
    sep->setSeparator(true);
    mActionsList.append(sep);

    mActionsList.append(mActionChangeIdtf);
    mActionsList.append(mActionSwapPairOrient);

    sep = new QAction(this);
    sep->setSeparator(true);
    mActionsList.append(sep);

    mActionsList.append(mActionCopy);
    mActionsList.append(mActionCut);
    mActionsList.append(mActionPaste);

    sep = new QAction(this);
    sep->setSeparator(true);
    mActionsList.append(sep);

    mActionsList.append(mActionSelectAll);

    sep = new QAction(this);
    sep->setSeparator(true);
    mActionsList.append(sep);

    mActionsList.append(mActionContourDelete);
    mActionsList.append(mActionDelete);
    mActionsList.append(mActionChangeConstPair);
    mActionsList.append(mActionChangeVarPair);
    mActionsList.append(mActionChangeConstNode);
    mActionsList.append(mActionChangeVarNode);


}

void SCgView::updateActionsState(int idx)
{
    Q_UNUSED(idx);

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

    bool pairType = (mContextObject != 0) && (mContextObject->type() == SCgPair::Type);

    mActionSwapPairOrient->setEnabled(pairType);
    mActionSwapPairOrient->setVisible(pairType);

    mActionChangeIdtf->setEnabled(mContextObject);
    mActionChangeIdtf->setVisible(mContextObject);

    mActionContourDelete->setEnabled(mContextObject && mContextObject->type() == SCgContour::Type);
    mActionContourDelete->setVisible(mContextObject && mContextObject->type() == SCgContour::Type);

    bool isAnySelected = !scene()->selectedItems().isEmpty();
    mActionDelete->setEnabled(isAnySelected);
    mActionCut->setEnabled(isAnySelected);
    mActionCopy->setEnabled(isAnySelected);

    mActionChangeConstPair->setEnabled(isAnySelected);
    mActionChangeVarPair->setEnabled(isAnySelected);
    mActionChangeConstNode->setEnabled(isAnySelected);
    mActionChangeVarNode->setEnabled(isAnySelected);


    //check for showed/hidden contents
    items = scene()->items();
    SCgNode *node = 0;
    bool oneContentShowed = false, oneContentHidden = false;
    for(int i = 0; i < items.size(); ++i)
    {
        node = qgraphicsitem_cast<SCgNode*>(items.at(i));
        if (node && node->isContentVisible())
            oneContentShowed = true;
        else if (node && !node->isContentVisible() && node->isContentData())
            oneContentHidden = true;
    }
    mActionShowAllContent->setEnabled(oneContentHidden);
    mActionHideAllContent->setEnabled(oneContentShowed);
}

QList<QAction*> SCgView::actions() const
{
    return mActionsList;
}

void SCgView::contextMenuEvent(QContextMenuEvent *event)
{
    if (event->reason() == QContextMenuEvent::Keyboard || event->reason() == QContextMenuEvent::Other)
        return;
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
    mContextMenu = new QMenu;

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

            SCgAlphabet::getInstance().getObjectTypes(stype, SCgAlphabet::ConstUnknown, types);
            for (iter = types.begin(); iter != types.end(); ++iter)
                menu->addAction(iter.value(), iter.key())->setData(QVariant(iter.key()));
            types.clear();
        }
    }
    mContextMenu->addActions(mActionsList);

    mContextMenu->exec(event->globalPos());
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

void SCgView::swapPairOrient()
{
    Q_ASSERT(mContextObject && mContextObject->type() == SCgPair::Type);

    SCgPair *pair = static_cast<SCgPair*>(mContextObject);
    static_cast<SCgScene*>(scene())->swapPairOrientCommand(pair);
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

void SCgView::changeConstPair(){

    if(mContextObject && mContextObject->type() == SCgPair::Type){

    Q_ASSERT(mContextObject);

    QDialog dialogConstPair(this);
    QSize size(24,24);
    dialogConstPair.setWindowTitle("Change constant Pair");
    SCgAlphabet sc;

    QGroupBox *groupBox = new QGroupBox(tr("Константные sc.g-дуги"));

         QRadioButton *radioConstPair1 = new QRadioButton("pair/const/-/-/noorien");
         QRadioButton *radioConstPair2 = new QRadioButton("pair/const/-/-/orient");
         QRadioButton *radioConstPair3 = new QRadioButton("pair/const/fuz/perm/orient/accessory");
         QRadioButton *radioConstPair4 = new QRadioButton("pair/const/fuz/temp/orient/accessory");
         QRadioButton *radioConstPair5 = new QRadioButton("pair/const/neg/perm/orient/accessory");
         QRadioButton *radioConstPair6 = new QRadioButton("pair/const/neg/temp/orient/accessory");
         QRadioButton *radioConstPair7 = new QRadioButton("pair/const/pos/perm/orient/accessory");
         QRadioButton *radioConstPair8 = new QRadioButton("pair/const/pos/temp/orient/accessory");

         radioConstPair1->setChecked(true);
         radioConstPair1->setIcon(sc.createPairIcon(size,"pair/const/-/-/noorien"));
         radioConstPair2->setIcon(sc.createPairIcon(size,"pair/const/-/-/orient"));
         radioConstPair3->setIcon(sc.createPairIcon(size,"pair/const/fuz/perm/orient/accessory"));
         radioConstPair4->setIcon(sc.createPairIcon(size,"pair/const/fuz/temp/orient/accessory"));
         radioConstPair5->setIcon(sc.createPairIcon(size,"pair/const/neg/perm/orient/accessory"));
         radioConstPair6->setIcon(sc.createPairIcon(size,"pair/const/neg/temp/orient/accessory"));
         radioConstPair7->setIcon(sc.createPairIcon(size,"pair/const/pos/perm/orient/accessory"));
         radioConstPair8->setIcon(sc.createPairIcon(size,"pair/const/pos/temp/orient/accessory"));

         QVBoxLayout *vbox = new QVBoxLayout;

         vbox->addWidget(radioConstPair1);
         vbox->addWidget(radioConstPair2);
         vbox->addWidget(radioConstPair3);
         vbox->addWidget(radioConstPair4);
         vbox->addWidget(radioConstPair5);
         vbox->addWidget(radioConstPair6);
         vbox->addWidget(radioConstPair7);
         vbox->addWidget(radioConstPair8);

         vbox->addStretch(1);
         groupBox->setLayout(vbox);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                       | QDialogButtonBox::Cancel);
    buttonBox->setParent(&dialogConstPair);

    connect(buttonBox, SIGNAL(accepted()), &dialogConstPair, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), &dialogConstPair, SLOT(reject()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(groupBox);
    layout->addWidget(buttonBox);

    dialogConstPair.setLayout(layout);

if(dialogConstPair.exec())
   {
    if(radioConstPair1->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"pair/const/-/-/noorien");
    else if(radioConstPair2->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"pair/const/-/-/orient");
    else if(radioConstPair3->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"pair/const/fuz/perm/orient/accessory");
    else if(radioConstPair4->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"pair/const/fuz/temp/orient/accessory");
    else if(radioConstPair5->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"pair/const/neg/perm/orient/accessory");
    else if(radioConstPair6->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"pair/const/neg/temp/orient/accessory");
    else if(radioConstPair7->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"pair/const/pos/perm/orient/accessory");
    else if(radioConstPair8->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"pair/const/pos/temp/orient/accessory");

    }
    }else{
        QMessageBox msgBox;

        msgBox.setText("Воспользуйтесь сочетанием клавиш Alt+S(вариативные узлы)\nили Alt+C(константные узлы) ");

        msgBox.exec();

    }

}

void SCgView::changeVarPair(){
    if(mContextObject && mContextObject->type() == SCgPair::Type){
    Q_ASSERT(mContextObject);

    QDialog dialogVarPair(this);
    QSize size(24,24);
    dialogVarPair.setWindowTitle("Change variant Pair");
    SCgAlphabet sc;

    QGroupBox *groupBox = new QGroupBox(tr("Вариативные sc.g-дуги"));

         QRadioButton *radioVarPair1 = new QRadioButton("pair/var/-/-/noorien");
         QRadioButton *radioVarPair2 = new QRadioButton("pair/var/-/-/orient");
         QRadioButton *radioVarPair3 = new QRadioButton("pair/var/fuz/perm/orient/accessory");
         QRadioButton *radioVarPair4 = new QRadioButton("pair/var/fuz/temp/orient/accessory");
         QRadioButton *radioVarPair5 = new QRadioButton("pair/var/neg/perm/orient/accessory");
         QRadioButton *radioVarPair6 = new QRadioButton("pair/var/neg/temp/orient/accessory");
         QRadioButton *radioVarPair7 = new QRadioButton("pair/var/pos/perm/orient/accessory");
         QRadioButton *radioVarPair8 = new QRadioButton("pair/var/pos/temp/orient/accessory");

         radioVarPair1->setChecked(true);
         radioVarPair1->setIcon(sc.createPairIcon(size,"pair/var/-/-/noorien"));
         radioVarPair2->setIcon(sc.createPairIcon(size,"pair/var/-/-/orient"));
         radioVarPair3->setIcon(sc.createPairIcon(size,"pair/var/fuz/perm/orient/accessory"));
         radioVarPair4->setIcon(sc.createPairIcon(size,"pair/var/fuz/temp/orient/accessory"));
         radioVarPair5->setIcon(sc.createPairIcon(size,"pair/var/neg/perm/orient/accessory"));
         radioVarPair6->setIcon(sc.createPairIcon(size,"pair/var/neg/temp/orient/accessory"));
         radioVarPair7->setIcon(sc.createPairIcon(size,"pair/var/pos/perm/orient/accessory"));
         radioVarPair8->setIcon(sc.createPairIcon(size,"pair/var/pos/temp/orient/accessory"));

         QVBoxLayout *vbox = new QVBoxLayout;

         vbox->addWidget(radioVarPair1);
         vbox->addWidget(radioVarPair2);
         vbox->addWidget(radioVarPair3);
         vbox->addWidget(radioVarPair4);
         vbox->addWidget(radioVarPair5);
         vbox->addWidget(radioVarPair6);
         vbox->addWidget(radioVarPair7);
         vbox->addWidget(radioVarPair8);

         vbox->addStretch(1);
         groupBox->setLayout(vbox);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                       | QDialogButtonBox::Cancel);
    buttonBox->setParent(&dialogVarPair);

    connect(buttonBox, SIGNAL(accepted()), &dialogVarPair, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), &dialogVarPair, SLOT(reject()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(groupBox);
    layout->addWidget(buttonBox);

    dialogVarPair.setLayout(layout);

if(dialogVarPair.exec())
   {
    if(radioVarPair1->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"pair/var/-/-/noorien");
    else if(radioVarPair2->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"pair/var/-/-/orient");
    else if(radioVarPair3->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"pair/var/fuz/perm/orient/accessory");
    else if(radioVarPair4->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"pair/var/fuz/temp/orient/accessory");
    else if(radioVarPair5->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"pair/var/neg/perm/orient/accessory");
    else if(radioVarPair6->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"pair/var/neg/temp/orient/accessory");
    else if(radioVarPair7->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"pair/var/pos/perm/orient/accessory");
    else if(radioVarPair8->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"pair/var/pos/temp/orient/accessory");

    }
    }else{
        QMessageBox msgBox;

        msgBox.setText("Воспользуйтесь сочетанием клавиш Alt+S(вариативные узлы)\nили Alt+C(константные узлы) ");

        msgBox.exec();

    }

}
void SCgView::changeConstNode(){
    if(mContextObject && mContextObject->type() == SCgNode::Type){
    Q_ASSERT(mContextObject);

    QDialog dialogConstNode(this);
    QSize size(24,24);
    dialogConstNode.setWindowTitle("Change const Node");
    SCgAlphabet sc;

    QGroupBox *groupBox = new QGroupBox(tr("Константные sc.g-узлы"));

         QRadioButton *radioConstNode1 = new QRadioButton("node/const/general");
         QRadioButton *radioConstNode2 = new QRadioButton("node/const/abstract");
         QRadioButton *radioConstNode3 = new QRadioButton("node/const/material");
         QRadioButton *radioConstNode4 = new QRadioButton("node/const/struct");
         QRadioButton *radioConstNode5 = new QRadioButton("node/const/tuple");
         QRadioButton *radioConstNode6 = new QRadioButton("node/const/role");
         QRadioButton *radioConstNode7 = new QRadioButton("node/const/relation");
         QRadioButton *radioConstNode8 = new QRadioButton("node/const/group");

         radioConstNode1->setChecked(true);
         radioConstNode1->setIcon(sc.createNodeIcon(size,sc.Const,sc.StructType_General));
         radioConstNode2->setIcon(sc.createNodeIcon(size,sc.Const,sc.StructType_Abstract));
         radioConstNode3->setIcon(sc.createNodeIcon(size,sc.Const,sc.StructType_Material));
         radioConstNode4->setIcon(sc.createNodeIcon(size,sc.Const,sc.StructType_Struct));
         radioConstNode5->setIcon(sc.createNodeIcon(size,sc.Const,sc.StructType_Tuple));
         radioConstNode6->setIcon(sc.createNodeIcon(size,sc.Const,sc.StructType_Role));
         radioConstNode7->setIcon(sc.createNodeIcon(size,sc.Const,sc.StructType_Relation));
         radioConstNode8->setIcon(sc.createNodeIcon(size,sc.Const,sc.StructType_Group));

         QVBoxLayout *vbox = new QVBoxLayout;

         vbox->addWidget(radioConstNode1);
         vbox->addWidget(radioConstNode2);
         vbox->addWidget(radioConstNode3);
         vbox->addWidget(radioConstNode4);
         vbox->addWidget(radioConstNode5);
         vbox->addWidget(radioConstNode6);
         vbox->addWidget(radioConstNode7);
         vbox->addWidget(radioConstNode8);

         vbox->addStretch(1);
         groupBox->setLayout(vbox);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                       | QDialogButtonBox::Cancel);
    buttonBox->setParent(&dialogConstNode);

    connect(buttonBox, SIGNAL(accepted()), &dialogConstNode, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), &dialogConstNode, SLOT(reject()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(groupBox);
    layout->addWidget(buttonBox);

    dialogConstNode.setLayout(layout);

if(dialogConstNode.exec())
   {
    if(radioConstNode1->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"node/const/general");
    else if(radioConstNode2->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"node/const/abstract");
    else if(radioConstNode3->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"node/const/material");
    else if(radioConstNode4->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"node/const/struct");
    else if(radioConstNode5->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"node/const/tuple");
    else if(radioConstNode6->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"node/const/role");
    else if(radioConstNode7->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"node/const/relation");
    else if(radioConstNode8->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"node/const/group");

    }
    }else{
        QMessageBox msgBox;

        msgBox.setText("Воспользуйтесь сочетанием клавиш Alt+T(константные дуги)\nили Alt+P(вариативные дуги) ");

        msgBox.exec();

    }


}
void SCgView::changeVarNode(){
    if(mContextObject && mContextObject->type() == SCgNode::Type){
    Q_ASSERT(mContextObject);

    QDialog dialogVarNode(this);
    QSize size(24,24);
    dialogVarNode.setWindowTitle("Change variant Node");
    SCgAlphabet sc;

    QGroupBox *groupBox = new QGroupBox(tr("Вариативные sc.g-узлы"));

         QRadioButton *radioVarNode1 = new QRadioButton("node/var/general");
         QRadioButton *radioVarNode2 = new QRadioButton("node/var/abstract");
         QRadioButton *radioVarNode3 = new QRadioButton("node/var/material");
         QRadioButton *radioVarNode4 = new QRadioButton("node/var/struct");
         QRadioButton *radioVarNode5 = new QRadioButton("node/var/tuple");
         QRadioButton *radioVarNode6 = new QRadioButton("node/var/role");
         QRadioButton *radioVarNode7 = new QRadioButton("node/var/relation");
         QRadioButton *radioVarNode8 = new QRadioButton("node/var/group");

         radioVarNode1->setChecked(true);
         radioVarNode1->setIcon(sc.createNodeIcon(size,sc.Var,sc.StructType_General));
         radioVarNode2->setIcon(sc.createNodeIcon(size,sc.Var,sc.StructType_Abstract));
         radioVarNode3->setIcon(sc.createNodeIcon(size,sc.Var,sc.StructType_Material));
         radioVarNode4->setIcon(sc.createNodeIcon(size,sc.Var,sc.StructType_Struct));
         radioVarNode5->setIcon(sc.createNodeIcon(size,sc.Var,sc.StructType_Tuple));
         radioVarNode6->setIcon(sc.createNodeIcon(size,sc.Var,sc.StructType_Role));
         radioVarNode7->setIcon(sc.createNodeIcon(size,sc.Var,sc.StructType_Relation));
         radioVarNode8->setIcon(sc.createNodeIcon(size,sc.Var,sc.StructType_Group));

         QVBoxLayout *vbox = new QVBoxLayout;

         vbox->addWidget(radioVarNode1);
         vbox->addWidget(radioVarNode2);
         vbox->addWidget(radioVarNode3);
         vbox->addWidget(radioVarNode4);
         vbox->addWidget(radioVarNode5);
         vbox->addWidget(radioVarNode6);
         vbox->addWidget(radioVarNode7);
         vbox->addWidget(radioVarNode8);

         vbox->addStretch(1);
         groupBox->setLayout(vbox);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                       | QDialogButtonBox::Cancel);
    buttonBox->setParent(&dialogVarNode);

    connect(buttonBox, SIGNAL(accepted()), &dialogVarNode, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), &dialogVarNode, SLOT(reject()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(groupBox);
    layout->addWidget(buttonBox);

    dialogVarNode.setLayout(layout);

if(dialogVarNode.exec())
   {
    if(radioVarNode1->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"node/var/general");
    else if(radioVarNode2->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"node/var/abstract");
    else if(radioVarNode3->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"node/var/material");
    else if(radioVarNode4->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"node/var/struct");
    else if(radioVarNode5->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"node/var/tuple");
    else if(radioVarNode6->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"node/var/role");
    else if(radioVarNode7->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"node/var/relation");
    else if(radioVarNode8->isChecked())
        static_cast<SCgScene*>(scene())->changeObjectTypeCommand(mContextObject,"node/var/group");

    }
    }else{
        QMessageBox msgBox;

        msgBox.setText("Воспользуйтесь сочетанием клавиш Alt+T(константные дуги)\nили Alt+P(вариативные дуги) ");

        msgBox.exec();

    }

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
    QAction* _sender = static_cast<QAction*>(sender());
    if (_sender == mActionShowContent)
    {
        Q_ASSERT(mContextObject && mContextObject->type() == SCgNode::Type);

        SCgNode *node = static_cast<SCgNode*>(mContextObject);

        if(visibility != node->isContentVisible())
            static_cast<SCgScene*>(scene())->changeContentVisibilityCommand(node, visibility);
    }
    else if (_sender == mActionShowAllContent)
    {
        static_cast<SCgScene*>(scene())->changeContentVisibilityCommand(0, true, true);
    }
    else if(_sender == mActionHideAllContent)
    {
        static_cast<SCgScene*>(scene())->changeContentVisibilityCommand(0, false, true);
    }
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
        QPointF bottomRight = mapToScene(viewport()->width(), viewport()->height());
        QRectF vis(topLeft, bottomRight);
        QRectF result = rect.adjusted(-100, -100, 100, 100).united(vis).united(sceneRect());
        setSceneRect(result);

        emit sceneRectChanged(result);
    }
}

void SCgView::editModeChanged(int mode)
{
    setContextMenuPolicy(mode == SCgScene::Mode_Select ? Qt::DefaultContextMenu : Qt::NoContextMenu);
}
