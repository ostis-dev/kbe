/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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
        Mode_SCp,
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

    /*!
     * @brief Gets all items with a given type which added to the scene
     * @param type Type of objects that need to be selected from the scene
     * @return List of selected objects
     */
    QList<SCgObject*> itemsByType(int type) const;

    /*! Create sc.g-node.
     * @param pos    sc.g-node position.
     * @return Created sc.g-node
     */
    SCgNode* createSCgNode(const QPointF &pos);

    /*! Create sc.g-pair.
     * @param begObj   Begin object.
     * @param endObj   End object.
     * @param points   Line points
     * @return Created sc.g-pair
     */
    SCgPair* createSCgPair(SCgObject *begObj, SCgObject *endObj, const QVector<QPointF> &points);

    /*! Create sc.g-bus.
      * @param points   Bus line points
      * @param owner    sc.g-node that owned bus
      * @return Created sc.g-bus
      */
    SCgBus* createSCgBus(const QVector<QPointF>& points, SCgNode *owner);

    /*! Create sc.g-contour.
     *  @return Created sc.g-contour
     */
    SCgContour* createSCgContour(const QVector<QPointF> &points);

    void doCommand(SCgBaseCommand * command);


    /*! Create undo/redo command to delete selected objects.
     * @param parentCmd Pointer to parend undo/redo command
     * @param addToStack Flag to add created command into stack
     */
    SCgBaseCommand* deleteSelObjectsCommand(SCgBaseCommand* parentCmd = 0,
                                            bool addToStack = true);

    /*! Create undo/redo command to move objects
     * @param info Map that contains initial and finish posiitons of moved objects
     * @param parentCmd Pointer to parend undo/redo command
     * @param addToStack Flag to add created command into stack
     */
    SCgBaseCommand* moveSelectedCommand(const ObjectUndoInfo& info,
                                        SCgBaseCommand* parentCmd = 0,
                                        bool addToStack = true);

    /*! Create undo/redo command to add point into specified object.
     * @param obj Object whose points will be changed.
     * @param point This point will be added.
     * @param parentCmd Pointer to parend undo/redo command
     * @param addToStack Flag to add created command into stack
     */
    SCgBaseCommand* addPointCommand(SCgPointObject* obj,
                                    const QPointF& point,
                                    SCgBaseCommand* parentCmd = 0,
                                    bool addToStack = true);

    /*! @} */

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

    QGraphicsItem* itemAt(const QPointF & point) const;

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

