#ifndef SCGFIVEMODE_H
#define SCGFIVEMODE_H

#include "scgmode.h"

class SCgFiveMode: public SCgMode
{
    Q_OBJECT
public:
    explicit SCgFiveMode(SCgScene* parent);

    virtual ~SCgFiveMode();

    /*! @defgroup mouseEvendHandling Mouse Events
     *  @{
     */
    void mouseDoubleClick(QGraphicsSceneMouseEvent *event);
    /*! @}*/

    virtual SCgScene::EditMode mode()
    {
        return SCgScene::Mode_Five;
    }

protected:


};

#endif // SCGFIVEMODE_H
