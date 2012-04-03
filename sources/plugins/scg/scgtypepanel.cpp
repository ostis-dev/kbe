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

#include "scgtypepanel.h"
#include "scgobject.h"
#include "scgnode.h"
#include "scgpair.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QAction>
#include <QActionGroup>
#include <QToolBar>
#include <QVBoxLayout>

SCgTypePanel::SCgTypePanel(QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    QGraphicsProxyWidget(parent, wFlags)
{
    setFlags(ItemIsSelectable | ItemIsFocusable |ItemIsPanel);
    mOpacityTimer = new QTimer;
    mOpacityTimer->setInterval(250);
    connect(mOpacityTimer, SIGNAL(timeout()), this, SLOT(updateOpacity()));

    mNodeBars = new QWidget;
    mPairBars = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    ///========================================
    QToolBar *editBar = new QToolBar;
    QActionGroup *group = new QActionGroup(editBar);
    QAction *action = new QAction(QIcon(), tr("Not defined"), group);
    action->setCheckable(true);
    action->setData("3|not_define");
    action->setShortcut(QKeySequence(tr("Alt+0")));
    group->addAction(action);
    editBar->addAction(action);
    mTypeChangeActionsList.append(action);

    action = new QAction(QIcon(), tr("General node"), group);
    action->setCheckable(true);
    action->setData("3|general_node");
    action->setShortcut(QKeySequence(tr("Alt+1")));
    group->addAction(action);
    editBar->addAction(action);
    mTypeChangeActionsList.append(action);

    action = new QAction(QIcon(), tr("Abstract node"), group);
    action->setCheckable(true);
    action->setData("3|abstract");
    action->setShortcut(QKeySequence(tr("Alt+2")));
    group->addAction(action);
    editBar->addAction(action);
    mTypeChangeActionsList.append(action);

    action = new QAction(QIcon(), tr("Abstract extended node"), group);
    action->setCheckable(true);
    action->setData("3|abstractExt");
    action->setShortcut(QKeySequence(tr("Alt+3")));
    group->addAction(action);
    editBar->addAction(action);
    mTypeChangeActionsList.append(action);

    action = new QAction(QIcon(), tr("Nopredmet node"), group);
    action->setCheckable(true);
    action->setData("3|nopredmet");
    action->setShortcut(QKeySequence(tr("Alt+4")));
    group->addAction(action);
    editBar->addAction(action);
    mTypeChangeActionsList.append(action);

    action = new QAction(QIcon(), tr("Tuple"), group);
    action->setCheckable(true);
    action->setData("3|tuple");
    action->setShortcut(QKeySequence(tr("Alt+5")));
    group->addAction(action);
    editBar->addAction(action);
    mTypeChangeActionsList.append(action);

    action = new QAction(QIcon(), tr("Role node"), group);
    action->setCheckable(true);
    action->setData("3|role");
    action->setShortcut(QKeySequence(tr("Alt+6")));
    group->addAction(action);
    editBar->addAction(action);
    mTypeChangeActionsList.append(action);

    action = new QAction(QIcon(), tr("Relation node"), group);
    action->setCheckable(true);
    action->setData("3|relation");
    action->setShortcut(QKeySequence(tr("Alt+7")));
    group->addAction(action);
    editBar->addAction(action);
    mTypeChangeActionsList.append(action);

    action = new QAction(QIcon(), tr("Group node"), group);
    action->setCheckable(true);
    action->setData("3|group");
    action->setShortcut(QKeySequence(tr("Alt+8")));
    group->addAction(action);
    editBar->addAction(action);
    mTypeChangeActionsList.append(action);

    editBar->setWindowTitle(tr("Node struct types"));
    mEditToolBarsList.append(editBar);
    layout->addWidget(editBar);
    //==================================================================
    editBar = new QToolBar;
    QToolBar *constPairBar = new QToolBar;
    group = new QActionGroup(editBar);
    action = new QAction(QIcon(), tr("Const element"), group);
    action->setCheckable(true);
    action->setData("2|const");
    action->setShortcut(QKeySequence(tr("Alt+C")));
    group->addAction(action);
    editBar->addAction(action);
    constPairBar->addAction(action);
    mTypeChangeActionsList.append(action);

    action = new QAction(QIcon(), tr("Variable element"), group);
    action->setCheckable(true);
    action->setData("2|var");
    action->setShortcut(QKeySequence(tr("Alt+V")));
    group->addAction(action);
    editBar->addAction(action);
    constPairBar->addAction(action);
    mTypeChangeActionsList.append(action);

    editBar->setWindowTitle(tr("Element's constansy"));
    mEditToolBarsList.append(editBar);
    layout->addWidget(editBar);
    mNodeBars->setLayout(layout);

    layout = new QVBoxLayout;
    layout->addWidget(constPairBar);
    //================================================================
    editBar = new QToolBar;
    group = new QActionGroup(editBar);
    action = new QAction(QIcon(), tr("Positive pair"), group);
    action->setCheckable(true);
    action->setData("3|pos");
    action->setShortcut(QKeySequence(tr("Alt+P")));
    group->addAction(action);
    editBar->addAction(action);
    mTypeChangeActionsList.append(action);

    action = new QAction(QIcon(), tr("Negative pair"), group);
    action->setCheckable(true);
    action->setData("3|neg");
    action->setShortcut(QKeySequence(tr("Alt+N")));
    group->addAction(action);
    editBar->addAction(action);
    mTypeChangeActionsList.append(action);

    action = new QAction(QIcon(), tr("Fuzzy pair"), group);
    action->setCheckable(true);
    action->setData("3|fuz");
    action->setShortcut(QKeySequence(tr("Alt+F")));
    group->addAction(action);
    editBar->addAction(action);
    mTypeChangeActionsList.append(action);

    editBar->setWindowTitle(tr("Pair's positivity"));
    mEditToolBarsList.append(editBar);
    layout->addWidget(editBar);
    //=================================================================
    editBar = new QToolBar;
    group = new QActionGroup(editBar);
    action = new QAction(QIcon(), tr("Permanent pair"), group);
    action->setCheckable(true);
    action->setData("4|perm");
    action->setShortcut(QKeySequence(tr("Alt+E")));
    group->addAction(action);
    editBar->addAction(action);
    mTypeChangeActionsList.append(action);

    action = new QAction(QIcon(), tr("Temporary pair"), group);
    action->setCheckable(true);
    action->setData("4|temp");
    action->setShortcut(QKeySequence(tr("Alt+T")));
    group->addAction(action);
    editBar->addAction(action);
    mTypeChangeActionsList.append(action);

    editBar->setWindowTitle(tr("Pair's temporariness"));
    mEditToolBarsList.append(editBar);
    layout->addWidget(editBar);
    //================================================================
    editBar = new QToolBar;
    group = new QActionGroup(editBar);
    mCommonArcType = new QAction(QIcon(), tr("Common arc"), group);
    mCommonArcType->setCheckable(true);
    mCommonArcType->setData("5|noorien");
    mCommonArcType->setShortcut(QKeySequence(tr("Alt+U")));
    group->addAction(mCommonArcType);
    editBar->addAction(mCommonArcType);

    mCommonPairType = new QAction(QIcon(), tr("Common pair"), group);
    mCommonPairType->setCheckable(true);
    mCommonPairType->setData("5|orient");
    mCommonPairType->setShortcut(QKeySequence(tr("Alt+O")));
    group->addAction(mCommonPairType);
    editBar->addAction(mCommonPairType);

    mCommonAccessoryPairType = new QAction(QIcon(), tr("Common accessory pair"), group);
    mCommonAccessoryPairType->setCheckable(true);
    mCommonAccessoryPairType->setData("5|orient/accessory");
    mCommonAccessoryPairType->setShortcut(QKeySequence(tr("Alt+O")));
    group->addAction(mCommonAccessoryPairType);
    editBar->addAction(mCommonAccessoryPairType);

    editBar->setWindowTitle(tr("Common pair's type"));
    mEditToolBarsList.append(editBar);
    layout->addWidget(editBar);
    mPairBars->setLayout(layout);
    setZValue(10);
}

SCgTypePanel::~SCgTypePanel()
{
    delete mOpacityTimer;
    //    delete mNodeBars;
    //    delete mPairBars;
    delete mCommonArcType;
    delete mCommonPairType;
    delete mCommonAccessoryPairType;
}

void SCgTypePanel::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    mOpacityTimer->stop();
    setOpacity(1);
    QGraphicsProxyWidget::hoverEnterEvent(event);
}

void SCgTypePanel::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (parentItem() && !parentItem()->isSelected())
        parentItem()->setSelected(true);
    QGraphicsProxyWidget::hoverMoveEvent(event);
}

void SCgTypePanel::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mOpacityTimer->start();
    QGraphicsProxyWidget::hoverLeaveEvent(event);
}

void SCgTypePanel::updateOpacity()
{
    qreal op = opacity();
    op -= .05;
    // checked if edit bar was removed earlier
    if (op <= .1 && scene())
    {
        scene()->removeItem(this);
        setWidget(0);
        mOpacityTimer->stop();
    }
    else
        setOpacity(op);
    if (!scene() && mOpacityTimer->isActive())
        mOpacityTimer->stop();
}

void SCgTypePanel::editToolBarsStateChanged()
{
    foreach (QToolBar *bar, mEditToolBarsList)
        bar->setEnabled(false);

    if (scene() && scene()->selectedItems().size() == 1)
    {
        QGraphicsItem *item = scene()->selectedItems().at(0);
        Q_ASSERT(item != 0);
        if (SCgObject::isSCgObjectType(item->type()))
        {
            SCgObject *obj = static_cast<SCgObject*>(item);
            QStringList divAlias = obj->typeAlias().split("/");
            if (divAlias.size() > 1)
            {
                // take object type: node or pair
                if (divAlias.at(0) == "node")
                {
                    setWidget(mNodeBars);
                    actionForType(divAlias.at(1))->setChecked(true);
                    actionForType(divAlias.at(2))->setChecked(true);
                    mEditToolBarsList.at(0)->setEnabled(true);
                    mEditToolBarsList.at(1)->setEnabled(true);
                }
                else if (divAlias.at(0) == "pair")
                {
                    setWidget(mPairBars);
                    mCommonArcType->setChecked(false);
                    mCommonPairType->setChecked(false);
                    mCommonAccessoryPairType->setChecked(false);

                    foreach (QAction *act, mTypeChangeActionsList)
                    {
                        QStringList l = act->data().toString().split("|");
                        if (divAlias.contains(l.at(1))) act->setChecked(true);
                        else act->setChecked(false);
                    }
                    // activate actions for common types
                    // checked if divAlias[2] and divAlias[3] equals to '-'
                    if (divAlias[2] == divAlias[3])
                    {
                        if (divAlias[4] == "noorien")
                            mCommonArcType->setChecked(true);
                        if (divAlias[4] == "orient" && divAlias.size() == 6)
                            mCommonAccessoryPairType->setChecked(true);
                        if (divAlias[4] == "orient" && divAlias.size() == 5)
                            mCommonPairType->setChecked(true);
                    }
                    mEditToolBarsList.at(1)->setEnabled(true);
                    mEditToolBarsList.at(2)->setEnabled(true);
                    mEditToolBarsList.at(3)->setEnabled(true);
                    mEditToolBarsList.at(4)->setEnabled(true);
                }
            }
        }
    }
}

QAction* SCgTypePanel::actionForType(QString type)
{
    foreach (QAction *act, mTypeChangeActionsList)
    {
        QStringList l = act->data().toString().split("|");
        if (l.at(1) == type) return act;
    }
    return 0;
}


QList<QToolBar*> SCgTypePanel::toolBarsList()
{
    return mEditToolBarsList;
}

void SCgTypePanel::setToolBarForType(int type)
{
    switch(type)
    {
    case SCgNode::Type :
    {
        setWidget(mNodeBars);
        break;
    }
    case SCgPair::Type :
    {
        setWidget(mPairBars);
        break;
    }
    default: return;
    }
}
