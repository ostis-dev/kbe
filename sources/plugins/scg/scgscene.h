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

#ifndef SCGSCENE_H
#define SCGSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPathItem>
#include <QStringList>

#include "scgobject.h"
#include "scgcontent.h"
#include "commands/scgbasecommand.h"

class SCgMode;
class SCgNode;
class SCgPair;
class SCgBus;
class SCgContour;
class QGraphicsItemGroup;
class SCgBaseCommand;
class SCgPointObject;

class QUndoStack;

class SCgScene : public QGraphicsScene
{
Q_OBJECT

public:
    //! Pair with item's parent and item's position
    typedef QPair<QGraphicsItem*, QPointF> ParentAndPosition;
    typedef QPair<ParentAndPosition, ParentAndPosition> BeginAndEndPoints;
    typedef QMap<QGraphicsItem* ,  BeginAndEndPoints> ItemUndoInfo;
    typedef QMap<QGraphicsItem* ,  BeginAndEndPoints> ObjectUndoInfo;
    typedef enum
    {
        Mode_None   =   0,
        Mode_Select,
        Mode_Pair,
        Mode_Bus,
        Mode_Contour,
        Mode_InsertTemplate,
        Mode_Clone,

        // Don't use it. (Used to know count of all edit modes)
        Mode_Count
    } EditMode;

    enum FindFlag
    {
        CaseSensitive = 0x01,
        FindForward = 0x02,
        // Set this flag if needs checking item under cursor.
        CheckCurrent = 0x04
    };

    typedef int FindFlags;

    explicit SCgScene(QUndoStack *undoStack, QObject *parent = 0);
    virtual ~SCgScene();

    /*! Set new edit mode
        \param mode New edit mode

        @see editMode
      */
    void setEditMode(EditMode mode);

    /*! Get current edit mode
      \return Current edit mode
      @see SCgScene::setEditMode
      */
    EditMode editMode() const;

    /*! Get top most scg-object under point.
        \param point    point to get objects.
        \return Returns pointer to sc.g-object under point. If there are no any
                sc.g-object under point, then return null.
      */
    SCgObject* objectAt(const QPointF &point) const;

    /*! Render scene to image
      */
    void renderToImage(QPainter *painter, const QRectF &target, const QRectF &source, Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio);

    /*! Specifies parameters of drawing the scene background.
     *
     * Specifies parameters for grid will be drown.
     * @param color specifies color of the grid.
     * @param draw true, if needed to draw grid.
     * @param xStep X axis step.
     * @param yStep Y axis step
     */
    void setDrawGrid(bool draw, QColor color = QColor(), int xStep = 20, int yStep = 20);

    /*! Finds SCgObject by identifier on scene.
     * Items are sorted in lexicographical order. Find process starts from cursor (@see setCursor(QPointF))
     * @param ttf Identifier to find
     * @param flg set of flags. @see FindFlag enum.
     * @return first found object.
     */
    SCgObject* find(const QString &ttf, FindFlags flg);

    /*! Sets starting point for find process.
     *
     * @param cursor new cursor in scene coordinates.
     */
    void setCursorPos(const QPointF& cursor);

    //! @return List of used identifiers on this scene.
    QStringList idtfList();

    /**
    * @brief Gets all items with a given type which added to the scene
    * @param type Type of objects that need to be selected from the scene
    * @return List of selected objects
    */
    QList<SCgObject*> itemsByType(int type) const;

    /*! Create sc.g-node.
        @param pos    sc.g-node position.
        @return Created sc.g-node
      */
    SCgNode* createSCgNode(const QPointF &pos);

    /*! Create sc.g-pair.
        @param begObj   Begin object.
        @param endObj   End object.
        @param points   Line points
        @return Created sc.g-pair
      */
    SCgPair* createSCgPair(SCgObject *begObj, SCgObject *endObj, const QVector<QPointF> &points);

    /*! Create sc.g-bus.
        @param points   Bus line points
        @param owner    sc.g-node that owned bus
        @return Created sc.g-bus
      */
    SCgBus* createSCgBus(const QVector<QPointF>& points, SCgNode *owner);

    /*! Create sc.g-contour.
        @return Created sc.g-contour
      */
    SCgContour* createSCgContour(const QVector<QPointF> &points);

    /**
     * \defgroup undoCommands Unified access to undo/redo mechanism
     * @param parentCmd Parent command for new command.
     * @param addToScene if true then command will be added to undoStack
     * @return Created command.
     *
     * @{
     */

    /*! Change object identifier
      @param    object  Object to change identifier
      @param    idtf    New identifier
      */
    SCgBaseCommand* changeIdtfCommand(SCgObject *object,
    								const QString &idtf,
    								SCgBaseCommand* parentCmd = 0,
    								bool addToStack = true);

    /*! Change type of object
      */
    SCgBaseCommand* changeObjectTypeCommand(SCgObject *object,
    										const QString &type,
    										SCgBaseCommand* parentCmd = 0,
    										bool addToStack = true);

    /*! Delete contour without childs
      @param    contour    Pointer to contour we need to delete
      */
    SCgBaseCommand* deleteContourCommand(SCgContour *contour,
    									SCgBaseCommand* parentCmd = 0,
    									bool addToStack = true);

    /*! Show/hide content
      @param    node    Pointer to sc.g-node for content show/hide
      @param    visibility  Visibility flag. True - to show content, False - to hide.
      */
    SCgBaseCommand* changeContentVisibilityCommand(SCgNode *node,
    												bool visibility,
    												SCgBaseCommand* parentCmd = 0,
    												bool addToStack = true);

    /*! Change content data
      @param    node    Pointer to sc.g-node for content changing
      @param    contInfo    Content information
      */
    SCgBaseCommand* changeContentDataCommand(SCgNode *node,
    										const SCgContent::ContInfo &contInfo,
    										SCgBaseCommand* parentCmd = 0,
    										bool addToStack = true);

    /*! Delete selected objects.
      */
    SCgBaseCommand* deleteSelObjectsCommand(SCgBaseCommand* parentCmd = 0,
    										bool addToStack = true);

    /*! Command for moving objects
     * @param info Map with moved objects and their's initial and finish positions.
     */
    SCgBaseCommand* moveSelectedCommand(const ObjectUndoInfo& info,
    									SCgBaseCommand* parentCmd = 0,
    									bool addToStack = true);

    /*!
     * Adds point to specified object.
     * @param obj Object whose points will be changed.
     * @param point This point will be added.
     */
    SCgBaseCommand* addPointCommand(SCgPointObject* obj,
    								const QPointF& point,
    								SCgBaseCommand* parentCmd = 0,
    								bool addToStack = true);

    /*!
     * Command for creating node.
     */
    SCgBaseCommand* createNodeCommand(const QPointF& pos,
    								SCgContour* parent,
    								SCgBaseCommand* parentCmd = 0,
    								bool addToStack = true);

    /*!
     * OCommand for creating bus.
     */
    SCgBaseCommand* createBusCommand(SCgNode* owner,
    								const QVector<QPointF> &points,
    								SCgContour* parent,
    								SCgBaseCommand* parentCmd = 0,
    								bool addToStack = true);

    /*!
     * Command for creating pair.
     */
    SCgBaseCommand* createPairCommand( const QVector<QPointF> &points,
    									SCgObject* beginObj,
    									SCgObject* endObj,
    									SCgContour* parent,
    									SCgBaseCommand* parentCmd = 0,
    									bool addToStack = true);

    /*!
     * Command for creating contour.
     */
    SCgBaseCommand* createContourCommand(const QList<QGraphicsItem*>& childs,
    									const QVector<QPointF> &points,
    									SCgContour* parent,
    									SCgBaseCommand* parentCmd = 0,
    									bool addToStack = true);

    SCgBaseCommand* changeObjectPositionCommand(SCgObject* obj,
    											const QPointF& newPos,
    											SCgBaseCommand* parentCmd = 0,
    											bool addToStack = true);

    SCgBaseCommand* changeObjectPointsCommand(SCgPointObject* obj,
    										const QVector<QPointF>& newPoints,
    										SCgBaseCommand* parentCmd = 0,
    										bool addToStack = true);

    /**@}*/

    //! Adds given command @p cmd to scene's undoStack.
    void addCommandToStack(SCgBaseCommand* cmd);


    //! Returned previous edit mode
    EditMode previousMode() const;

    /*! Paste objects command.
     * @param itemList List of inserted objects
     * @param parent Parent contour.
     */
    void pasteCommand(QList<QGraphicsItem*> itemList, SCgContour* parent);

    /*! Clone objects command.
     * @param itemList List of inserted objects
     * @param parent Parent contour.
     */
    void cloneCommand(QList<QGraphicsItem*> itemList, SCgContour* parent);

private:
    QVector<SCgMode*> mSceneModes;
    //! Current edit mode
    SCgMode* mMode;
    //! Undo stack
    QUndoStack *mUndoStack;

    //! True, if needed to draw grid
    bool mIsGridDrawn;
    //! Grid parameters.
    int mXStep, mYStep;
    QColor mGridColor;

    //! Holds true if some identifiers were changed during the editing KB(and after creating new SCgScene).
    bool mIsIdtfModelDirty;
    //! Holds list of identifiers. @see mIdtfModelIsDirty, @see idtfList().
    QStringList mIdtfList;

    //! Updates @see mIdtfList and sets @see mIdtfModelIsDirty flag to false.
    void updateIdtfList();

    //! @see SCgScene::find(const QString &ttf, FindFlags flg). Find process begins from this position.
    QPointF mCursor;

private:
    //! previous edit mode
    EditMode mPreviousEditMode;

protected:
    /* mouse events */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    /* keyboard events */
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    //! @see QGraphicsScene::drawBackground()
    //! Draws grid background
    void drawBackground(QPainter *painter, const QRectF &rect);

    void dropEvent(QGraphicsSceneDragDropEvent *event);
signals:
    /*! Signal that emits on edit mode change
      * @param mode New edit mode
      */
    void editModeChanged(int mode);

public slots:
    void setIdtfDirtyFlag();
private slots:
    void ensureSelectedItemVisible();
};

#endif // SCGSCENE_H
