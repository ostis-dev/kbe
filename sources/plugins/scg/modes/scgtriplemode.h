#ifndef TRIPLEMODE_H
#define TRIPLEMODE_H

#include "scgmode.h"

class SCgTripleMode: public SCgMode
{
    Q_OBJECT
public:
    explicit SCgTripleMode(SCgScene* parent);

    virtual ~SCgTripleMode();

    /*! @defgroup mouseEvendHandling Mouse Events
     *  @{
     */
    void mouseDoubleClick(QGraphicsSceneMouseEvent *event);
    /*! @}*/

    virtual SCgScene::EditMode mode()
    {
        return SCgScene::Mode_Triple;
    }

protected:


};





#endif // TRIPLEMODE_H
