#pragma once
#include "QtGlobal"
#include "QVector"
#include <QTextStream>

class SCgConverter{

public:
    SCgConverter(QByteArray);
    void SCgConverter::startConverter();
    void SCgConverter::writeToFile();
    bool SCgConverter::findString(int,QString);
    void SCgConverter::createBunchRelation(QString);
    void SCgConverter::createApplianceRelation(QString);
    void SCgConverter::createBinaryRelation(QString);

private:
    QVector<QString> nodeInVector;
    QVector<QString> nodeIdtfVector;
    QVector<int> nodeType;
    QString fileText;
    QString SCgConverter::returnString(int,QString);
    void SCgConverter::createSCS();
    struct node{
        int type;
        QString idtf;
        QString id;
         QString parentId;
    };

    QVector<node> elementNode;

    struct arc{
        int type;
         QString bId;
         QString eId;
         QString id;
          QString parentId;
    };
    QVector<arc> elementArc;
    struct pair{
        int type;
        QString bId;
         QString eId;
         QString id;
          QString parentId;
    };

    QVector<pair> elementPair;

    struct contour{
        QString name;
        QString id;
        QString parentId;
    };

    QVector<contour> elementContour;

    struct bus{
        QString owner;
        QString id;

    };

    QVector<bus> elementBus;

};
