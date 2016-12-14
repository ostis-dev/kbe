#pragma once

#include <QObject>
#include <QList>


class SCgObject;

class SCgLayer : public QObject
{
    Q_OBJECT
public:
    SCgLayer(QString name);
    ~SCgLayer();

    void addObject(SCgObject* object);
    void deleteObject(SCgObject* object);
    bool isVisible();
    QString getName();
    QList<SCgObject*> getObjects();

public slots:
    void setVisible(bool visible);

private:
    QList<SCgObject*> objects;
    QString name;
    bool visible;
};
