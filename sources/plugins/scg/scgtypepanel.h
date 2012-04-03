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

#ifndef SCGTYPEPANEL_H
#define SCGTYPEPANEL_H

#include <QGraphicsProxyWidget>

class QTimer;
class QToolBar;

/**
* @brief Class for ballon tool bar
*
*/
class SCgTypePanel : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    /**
    * @brief Constructor
    * @param parent Pointer to parent graphics item
    * @param wFlags Flags which represented various property of proxy widget
    */
    explicit SCgTypePanel(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);

    //! Destructor
    virtual ~SCgTypePanel();

    //! @return List of all accessible type changing tool bars
    QList<QToolBar*> toolBarsList();

    //! Set widget with edit actions corresponding to @p type
    void setToolBarForType(int type);
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
private:
    //! @return Action which connected with @p type attribute
    QAction* actionForType(QString type);

    //! Timer for tracking opacity value changes
    QTimer *mOpacityTimer;

    //! Widget with tool bars for node type changing
    QWidget *mNodeBars;

    //! Widget with tool bars for pair type changing
    QWidget *mPairBars;

    //! Action for change pair type to common arc
    QAction* mCommonArcType;

    //! Action for change pair type to common pair
    QAction* mCommonPairType;

    //! Action for change pair type to common accessory pair
    QAction* mCommonAccessoryPairType;

    //! List of all edit tool bars
    QList<QToolBar*> mEditToolBarsList;

    //! List of all type changing actions except three common pair type (vide supra)
    QList<QAction*> mTypeChangeActionsList;
signals:

public slots:
    /**
    * @brief Slot for tracking edit bars state changing
    * Tool bars state depends on scene's selected items and their types
    */
    void editToolBarsStateChanged();
private slots:
    /**
    * @brief Slot for update widget's opacity value
    * Remove ballon tool bars from the scene if opacity value less than 0.1
    */
    void updateOpacity();
};

#endif // SCGTYPEPANEL_H
