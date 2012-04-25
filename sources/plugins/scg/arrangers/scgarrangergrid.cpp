#include "scgarrangergrid.h"

#include "scgview.h"
#include "scgnode.h"
#include "scgpointobject.h"

#include <QSpinBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QDialogButtonBox>

SCgGridArranger::SCgGridArranger(QObject *parent):
    SCgArranger(parent),
    mDialog(0),
    mXStep(15),
    mYStep(15),
    mIsSymmetrical(true),
    mXSpinBox(0),
    mYSpinBox(0),
    mGridColor(QColor(191, 100, 150, 150))
{

}

SCgGridArranger::~SCgGridArranger()
{

}

bool SCgGridArranger::configDialog()
{
    if(!mDialog)
            createDialog();
    mDialog->setParent(mView->viewport(), Qt::Dialog);

    // Create ghost only for visible objects
    QList<QGraphicsItem*> items = mView->items(QRect(0,0,mView->width(), mView->height()));
    createGhosts(items);

    recalculateGhostsPosition();

    bool res = mDialog->exec() == QDialog::Accepted;

    deleteGhosts();
    mPlaced.clear();
    drawGrid(false);

    mDialog->setParent(0, Qt::Dialog);

    return res;
}

void SCgGridArranger::xValueChanged(int newSpacing)
{
    mXStep = newSpacing;
    if(mIsSymmetrical && mYStep != mXStep)
        mYSpinBox->setValue(newSpacing);
    else
        recalculateGhostsPosition();
}

void SCgGridArranger::yValueChanged(int newSpacing)
{
    mYStep = newSpacing;
    if(mIsSymmetrical && mYStep != mXStep)
        mXSpinBox->setValue(newSpacing);
    else
        recalculateGhostsPosition();
}

void SCgGridArranger::symmetricalCheckBoxClicked(bool checked)
{
    if(checked)
        mYSpinBox->setValue(mXSpinBox->value());

    mIsSymmetrical = checked;
}

QDialog* SCgGridArranger::createDialog()
{
    mDialog = new QDialog();
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
    buttonBox->setParent(mDialog);

    QSpinBox* xSpin = new QSpinBox(mDialog);
    QSpinBox* ySpin = new QSpinBox(mDialog);

    QLabel* xLabel= new QLabel(tr("X axis step"),mDialog);
    QLabel* yLabel= new QLabel(tr("Y axis step"),mDialog);

    xSpin->setToolTip(tr("X axis step"));
    xSpin->setMinimum(15);
    xSpin->setMaximum(200);
    xSpin->setValue(mXStep);
    ySpin->setToolTip(tr("Y axis step"));
    ySpin->setMinimum(15);
    ySpin->setMaximum(200);
    ySpin->setValue(mYStep);
    mXSpinBox = xSpin;
    mYSpinBox = ySpin;

    QHBoxLayout *hl = new QHBoxLayout();

    QVBoxLayout *vl = new QVBoxLayout();
    vl->addWidget(xLabel);
    vl->addWidget(xSpin);
    hl->addLayout(vl);

    vl = new QVBoxLayout();
    vl->addWidget(yLabel);
    vl->addWidget(ySpin);
    hl->addLayout(vl);

    QCheckBox* symChkBox = new QCheckBox(tr("Symmetrical grid"));

    symChkBox->setChecked(mIsSymmetrical);

    vl = new QVBoxLayout();
    vl->addLayout(hl);
    vl->addWidget(symChkBox);
    vl->addWidget(buttonBox);

    connect(xSpin, SIGNAL(valueChanged(int)), this, SLOT(xValueChanged(int)));
    connect(ySpin, SIGNAL(valueChanged(int)), this, SLOT(yValueChanged(int)));
    connect(symChkBox, SIGNAL(clicked (bool)), this, SLOT(symmetricalCheckBoxClicked(bool)));
    connect(buttonBox, SIGNAL(accepted()), mDialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), mDialog, SLOT(reject()));

    mDialog->setLayout(vl);
    return mDialog;
}

inline QPointF SCgGridArranger::mapFromSceneToGrid(const QPointF& point)
{
    return QPointF(qRound(point.x() / mXStep) * mXStep, qRound(point.y() / mYStep) * mYStep);
}

void SCgGridArranger::recalculateGhostsPosition()
{
    drawGrid(true);
    mPlaced.clear();
    QMap<SCgObject*, SCgObject*>::const_iterator i = mGhosts.constBegin();
    while (i != mGhosts.constEnd())
    {
        placeToGrid(i.value(), i.key());
        ++i;
    }

}


void SCgGridArranger::startOperation()
{
    mPlaced.clear();
    foreach(QGraphicsItem* it, mView->items())
    {
        if(SCgObject::isSCgObjectType(it->type()))
        {
            SCgObject* obj = static_cast<SCgObject*>(it);
            if(!obj->isDead())
                calculatePosition(obj);
        }
    }
}

void SCgGridArranger::calculatePosition(SCgObject* obj)
{
    Q_ASSERT_X(obj != 0, "void SCgGridArranger::calculatePosition(SCgObject* obj)",
               "Object pointer is null");

    if(!mPlaced.contains(obj))
    {
        mPlaced.insert(obj);

        QGraphicsItem* parent = obj->parentItem();

        int objType = obj->type();

        if(parent && SCgObject::isSCgObjectType(parent->type()))
        {
            SCgObject *_obj = static_cast<SCgObject*>(parent);
            if (_obj != 0)
                calculatePosition(_obj);
        }

        // If it isn't a point object, then simple maps it coordinates to grid.
        if(objType == SCgNode::Type)
        {
            QPointF pos = mapFromSceneToGrid(obj->scenePos());
            if(!parent)
                registerCommand(obj, pos);
            else
                registerCommand(obj, parent->mapFromScene(pos));
        }
        // Else, map each point to grid and set new points to object.
        // By the way we should map incident objects.
        else if (SCgObject::isSCgPointObjectType(objType))
        {
            SCgPointObject* pointObj = static_cast<SCgPointObject*>(obj);

            QVector<QPointF> points = pointObj->scenePoints();

            for(int i = 0; i < points.size(); ++i)
                points[i] = mapFromSceneToGrid(points.at(i));

            SCgObject *b_obj = pointObj->objectWithRole(SCgPointObject::IncidentBegin);
            if (b_obj != 0)
                calculatePosition(b_obj);
            SCgObject *e_obj = pointObj->objectWithRole(SCgPointObject::IncidentEnd);
            if (e_obj != 0)
                calculatePosition(e_obj);

            registerCommand(pointObj, points);
        }
    }
}

void SCgGridArranger::placeToGrid(SCgObject* obj, SCgObject* realObj)
{
    if(!mPlaced.contains(obj))
    {
        if(!obj || !realObj)
            return;
        mPlaced.insert(obj);

        QGraphicsItem* parent = obj->parentItem();

        if(parent && SCgObject::isSCgObjectType(parent->type()))
            placeToGrid(static_cast<SCgObject*>(parent),static_cast<SCgObject*>(realObj->parentItem()));

        int objType = obj->type();

        // If it isn't a point object, then simple maps it coordinates to grid.
        if(objType == SCgNode::Type)
        {
            QPointF pos = mapFromSceneToGrid(realObj->scenePos());
            if(!parent)
                obj->setPos(pos);
            else
                obj->setPos(parent->mapFromScene(pos));
        }
        // Else, map each point to grid and set new points to object.
        // By the way we should map incident objects.
        else if (SCgObject::isSCgPointObjectType(objType))
        {
            SCgPointObject* realPointObj = static_cast<SCgPointObject*>(realObj);
            SCgPointObject* ghostPointObj = static_cast<SCgPointObject*>(obj);

            QVector<QPointF> points = realPointObj->scenePoints();

            for(int i = 0; i < points.size(); ++i)
                points[i] = mapFromSceneToGrid(points.at(i));

            placeToGrid(ghostPointObj->objectWithRole(SCgPointObject::IncidentBegin),
                        realPointObj->objectWithRole(SCgPointObject::IncidentBegin));
            placeToGrid(ghostPointObj->objectWithRole(SCgPointObject::IncidentEnd),
                        realPointObj->objectWithRole(SCgPointObject::IncidentEnd));

            ghostPointObj->setPoints(points);
        }
    }
}


void SCgGridArranger::drawGrid(bool draw)
{
    SCgScene* s = static_cast<SCgScene*>(mView->scene());
    s->setDrawGrid(draw, mGridColor, mXStep, mYStep);
}

QString SCgGridArranger::name() const
{
    return tr("Grid arrange");
}
