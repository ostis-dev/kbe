#ifndef SCGUNDOCOMMANDS_H
#define SCGUNDOCOMMANDS_H

#include <QUndoCommand>
#include <QVector>
#include <QPointF>
#include <QMap>
#include <QPair>

#include "scgcontent.h"
#include "scgpointobject.h"
#include "scgscene.h"

class SCgObject;
class SCgNode;
class SCgPair;
class SCgContour;
class SCgBus;

class QGraphicsScene;
class QGraphicsItem;

/*! Base scg command for
  */
class SCgBaseCommand : public QUndoCommand
{
public:
    explicit SCgBaseCommand(SCgScene *scene,
                            SCgObject *object,
                            QUndoCommand *parent = 0);
    virtual ~SCgBaseCommand();

    /*! Get pointer to scene we worked with.
      @return pointer to scene.
      */
    QGraphicsScene *getScene() const;

protected:
    //! Pointer to scene that used for command working
    SCgScene *mScene;
    //! Pointer to object that command affects to
    SCgObject *mObject;
};

//! Moves specified object from it's initial position to finish position.
class SCgCommandObjectMove : public SCgBaseCommand
{
public:
    explicit SCgCommandObjectMove(SCgScene *scene,
                                  SCgObject* obj,
                                  const QPointF& oldPos,
                                  const QPointF& newPos,
                                  QUndoCommand *parent = 0 );
    virtual ~SCgCommandObjectMove();

protected:
    void redo();
    void undo();

private:
    QPointF mOldPosition;
    QPointF mNewPosition;
};

//! Moves specified object from it's initial position to finish position.
class SCgCommandSelectedObjectMove : public SCgBaseCommand
{
public:
    /*! This command will be major if we'll rewrite scene event handling.
     * @param undoInfo Map holding object and pair with its initial parent,position and final parent, position.
     */
    explicit SCgCommandSelectedObjectMove(SCgScene *scene,
                                      const SCgScene::ObjectUndoInfo& undoInfo,
                                      QUndoCommand *parent = 0 );
    virtual ~SCgCommandSelectedObjectMove();

    int id() const
    {
        return 1;
    }

    bool mergeWith (const QUndoCommand* command);

protected:
    void redo();
    void undo();

private:
    SCgScene::ObjectUndoInfo mUndoInfo;
};

//! Command for moving points on SCgPointObject
class SCgCommandPointMove : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene       Pointer to SCgScene that will be used for command working
      @param    obj         Pointer to object that will be changed
      @param    pointIndex  Index of changed point
      @param    oldPos      Old point position
      @param    newPos      New point position
      @param    parent      Pointer to parent command. @see QUndoCommand()
      */
    explicit SCgCommandPointMove(   SCgScene* scene,
                                    SCgPointObject* obj,
                                    int pointIndex,
                                    const QPointF& oldPos,
                                    const QPointF& newPos,
                                    QUndoCommand* parent = 0);

    virtual ~SCgCommandPointMove();

protected:
    void redo();
    void undo();

private:
    int mPointIndex;
    QPointF mOldPos;
    QPointF mNewPos;
};

//! Command for changing points on SCgPointObject
class SCgCommandPointsChange : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene       Pointer to SCgScene that will be used for command working
      @param    obj         Pointer to object that will be changed
      @param    newPoints   Points will be set;
      @param    parent      Pointer to parent command. @see QUndoCommand()
      */
    explicit SCgCommandPointsChange(   SCgScene* scene,
                                    SCgPointObject* obj,
                                    const QVector<QPointF>& newPoints,
                                    QUndoCommand* parent = 0);

    virtual ~SCgCommandPointsChange();

protected:
    void redo();
    void undo();

private:
    bool mIsPair;
    double mOldEndDot;
    double mOldBeginDot;
    QVector<QPointF> mOldPoints;
    QVector<QPointF> mNewPoints;
};

//! Command for changing begin and end objects of pair and owner of bus.
class SCgCommandChangeIncedentObject: public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene       Pointer to SCgScene that will be used for command working
      @param    obj         Pointer to object that will be changed
      @param    role        Role for changing incident point (begin or end).
      @param    newObj      New object for given role
      @param    newPoint    New point position (used for calculating new dotPos)
      @param    parent      Pointer to parent command. @see QUndoCommand()
      */
    explicit SCgCommandChangeIncedentObject(SCgScene* scene,
                                            SCgPointObject* obj,
                                            SCgPointObject::IncidentRole role,
                                            SCgObject* newObj,
                                            const QPointF& newPoint,
                                            QUndoCommand* parent = 0);

    virtual ~SCgCommandChangeIncedentObject();

protected:
    void redo();
    void undo();

private:
    SCgPointObject::IncidentRole mRole;
    SCgObject* mOldObject;
    SCgObject* mNewObject;
    QPointF mNewPoint;
    QPointF mOldPoint;
};

/*! Object deletion command
  */
class SCgCommandObjectDelete : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    object  Pointer to deleting object
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandObjectDelete(SCgScene *scene,
                                    SCgObject *object,
                                    QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandObjectDelete();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();
    //! List of deleted objects (object that was linked to deleting object)
    QList<SCgObject*> mDelList;
    //! Map of parent objects
    QMap<SCgObject*, QGraphicsItem*> mParents;
};

/*! Object insertion command
  */
class SCgCommandInsert : public QObject, public SCgBaseCommand
{
    Q_OBJECT
public:
    /*! Constructor
      @param scene          Pointer to SCgScene that will be used for command working
      @param objList        List of inserted objects
      @param parentContour  Pointer to parent contour (if 0 then parent is scene).
      @param parent         Pointer to parent command
      */
    explicit SCgCommandInsert(SCgScene *scene,
                              QList<SCgObject*> objList,
                              SCgContour* parentContour,
                              QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandInsert();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();
    //! List of inserted objects
    QList<SCgObject*> mList;
    //! Parent contour
    SCgContour* mParent;
private slots:

    void objectFromListDestroyed(QObject* obj);
};


/*! Object identification change command
  */
class SCgCommandObjectIdtfChange : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    object  Pointer to object for identifier changing
      @param    newIdtf New object identifier
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandObjectIdtfChange(SCgScene *scene,
                                        SCgObject *object,
                                        const QString &newIdtf,
                                        QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandObjectIdtfChange();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Old identifier
    QString mOldIdtf;
    //! New identifier
    QString mNewIdtf;
};

/*! Object type changing command
  */
class SCgCommandObjectTypeChange : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    object  Pointer to object for type changing
      @param    newType New object type
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandObjectTypeChange(SCgScene *scene,
                                        SCgObject *object,
                                        const QString &newType,
                                        QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandObjectTypeChange();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Old object type
    QString mOldType;
    //! New object type
    QString mNewType;
};

/*! SCg-node creation command
  */
class SCgCommandCreateNode : public QObject, public SCgBaseCommand
{
    Q_OBJECT
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    point   Position in scene
      @param    parentContour   Pointer to parent contour. If it's null, then node will be created in scene,
        else it will be created in that contour.
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandCreateNode(SCgScene *scene,
                                  const QPointF &point,
                                  SCgContour *parentContour,
                                  QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandCreateNode();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Node position in scene
    QPointF mPoint;
    //! Pointer to parent contour
    SCgContour *mParentContour;

private slots:
    void nodeDestroyed();
};

/*! SCg-pair creation command
  */
class SCgCommandCreatePair : public QObject, public SCgBaseCommand
{
    Q_OBJECT
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    points  Vector of line points (exluding incident points)
      @param    beginObject Pointer to begin object
      @param    endObject   Pointer to end object
      @param    parenContour    Pointer to parent contour. If it's null, then node will be created in scene,
        else it will be created in that contour.
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandCreatePair(SCgScene *scene,
                                  const QVector<QPointF> &points,
                                  SCgObject *beginObject,
                                  SCgObject *endObject,
                                  SCgContour *parentContour,
                                  QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandCreatePair();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Line point (excluding incedent points)
    QVector<QPointF> mPoints;
    //! Pointer to begin object
    SCgObject *mBeginObject;
    //! Pointer to end object
    SCgObject *mEndObject;
    //! Pointer to parent contour
    SCgContour *mParentContour;

private slots:
    void pairDestroyed();
};

/*! SCg-pair creation command
  */
class SCgCommandCreateBus : public QObject, public SCgBaseCommand
{
    Q_OBJECT
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    owner   SCgNode that is a bus owner
      @param    points  Vector of line points
      @param    owner   Pointer to owner object
      @param    parenContour    Pointer to parent contour. If it's null, then node will be created in scene,
        else it will be created in that contour.
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandCreateBus(SCgScene *scene,
                                 SCgNode *owner,
                                 const QVector<QPointF> &points,
                                 SCgContour *parentContour,
                                 QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandCreateBus();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Bus owner
    SCgNode *mOwner;
    //! Bus points
    QVector<QPointF> mPoints;
    //! Pointer to parent contour
    SCgContour *mParentContour;

private slots:
    void busDestroyed();
};

/*! Contour creation command
  */
class SCgCommandCreateContour : public QObject, public SCgBaseCommand
{
    Q_OBJECT
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    childs  List of child objects (all child object will be added to contour)
      @param    points  Vector of contour points
      @param    parentContour   Pointer to parent contour. If it's null, then node will be created in scene,
        else it will be created in that contour.
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandCreateContour(SCgScene *scene,
                                     const QList<QGraphicsItem*> &childs,
                                     const QVector<QPointF> &points,
                                     SCgContour *parentContour,
                                     QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandCreateContour();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Contour points
    QVector<QPointF> mPoints;
    //! List of child object
    QList<QGraphicsItem*> mChildObjects;
    //! Pointer to parent contour
    SCgContour *mParentContour;

private slots:
    void contourDestroyed();
};

/*! Contour deletion command
  */
class SCgCommandDeleteContour : public SCgBaseCommand
{
public:
    /*! Constructor
        @param  scene   Pointer to SCgScene that will be used for command working
        @param  contour Pointer to contour that need to be deleted
        @param  parent  Pointer to parent command
      */
    explicit SCgCommandDeleteContour(SCgScene *scene,
                                     SCgContour *contour,
                                     QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandDeleteContour();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Pointer to deleted contour
    SCgContour *mContour;
    //! List of child objects
    QList<QGraphicsItem*> mChilds;
};

/*! Content show/hide command
  */
class SCgCommandContentVisibility : public SCgBaseCommand
{
public:
    /*! Constructor
      @param    scene   Pointer to SCgScene that will be used for command working
      @param    node    Pointer to SCg-node for content show/hide
      @param    visibility    Visibility flag
      @param    parent  Pointer to parent command
      */
    explicit SCgCommandContentVisibility(SCgScene *scene,
                                         SCgNode *node,
                                         bool visibility,
                                         QUndoCommand *parent = 0);
    //! Destructor
    virtual ~SCgCommandContentVisibility();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Pointer to SCg-node for content show/hide
    SCgNode *mNode;
    //! Visibility flag
    bool mVisibility;
};

/*! Change content command
  */
class SCgCommandContentChange : public SCgBaseCommand
{
public:
    /*! Constructor
      */
    explicit SCgCommandContentChange(SCgScene *scene,
                                     SCgNode *node,
                                     const SCgContent::ContInfo &contInfo,
                                     QUndoCommand *parent = 0);
    virtual ~SCgCommandContentChange();

protected:
    //! @see    QUndoCommand::redo
    void redo();
    //! @see    QUndoCommand::undo
    void undo();

    //! Pointer to SCg-node for content changing
    SCgNode *mNode;
    //! Content information
    SCgContent::ContInfo mContentInfo;
    //! Old content information
    SCgContent::ContInfo mOldContentInfo;
    //! If content was visible before changing, holds true
    bool mContentVisibility;
};


#endif // SCGUNDOCOMMANDS_H
