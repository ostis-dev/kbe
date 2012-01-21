#ifndef SCGARRANGERGRID_H
#define SCGARRANGERGRID_H

#include "scgarranger.h"

class SCgGridArranger : public SCgArranger
{
Q_OBJECT

public:
    enum
    {
        Type = 3
    };
    explicit SCgGridArranger(QObject *parent = 0);
    virtual ~SCgGridArranger();

    //! @see SCgArranger::type().
    int type() const {return Type;}

protected:
    //!  @see SCgArranger::userMenu()
    bool userMenu();

    //!  @see SCgArranger::startOperation()
    void startOperation();

    //! Holds dialog window, shown to user.
    //! @see SCgGridArranger::createDialog()
    QDialog* mDialog;

    //! Creates dialog for asking grid parameters.
    QDialog* createDialog();

    //! Translates specified point, given in scene coordinates, to nearest grid node.
    inline QPointF mapFromSceneToGrid(const QPointF& point);

    /*! @defgroup grdParam Grid Parameters
     *  @{
     */
    int mXStep;
    int mYStep;
    bool mIsSymmetrical;

    QSpinBox* mXSpinBox;
    QSpinBox* mYSpinBox;
    /*! @}*/

    //! Holds grid color. The grid will be drown on scene.
    QColor mGridColor;

protected slots:
    /*! @defgroup Slots Slots For Reacting User Actions
     *  @{
     */
    void xValueChanged(int newSpacing);
    void yValueChanged(int newSpacing);
    void symmetricalCheckBoxClicked(bool checked);
    /*! @}*/

private:
    //! Draws grid on current scene (@see mView)
    /*!
     *
     * @param draw true if needed to draw grid.
     */
    void drawGrid(bool draw = true);

    //! Replaces ghosts on the scene with new grid parameters (@see grdParam)
    void recalculateGhostsPosition();

    //! Maps specified object from it's position to new position corresponding the grid
    void placeToGrid(SCgObject* obj, SCgObject* realObj);

    //! write new position of one of object in PositionMap.
    void calculatePosition(SCgObject* obj);

    //! Holds items already placed to the grid on current operation.
    QSet<SCgObject*> mPlaced;


};

#endif // SCGARRANGERGRID_H
