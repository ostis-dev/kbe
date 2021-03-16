#pragma once

#include <QTextStream>
#include <QVector>
#include <QHash>
#include <memory>

class SCgObject;
class SCgContour;
class SCgNode;

class StreamWriter;
class QTextStream;

class SCgStreamWriter
{
public:
    typedef QVector<QPair<QString, QString>> RelationValueVector;

    SCgStreamWriter();

    void setOutputFiles(QIODevice *device, QIODevice *layoutDevice);

    void preprocess(QVector<SCgObject *> const & vec);
    void writeOrdered(QVector<SCgObject *> const & vec);

private:
    class StreamWriter
    {
    public:
        QString indent;
        StreamWriter();
        StreamWriter(QIODevice *device);
        void write(QString s);
        void setDevice(QIODevice *device);
        ~StreamWriter(){}
    private:
        QTextStream stream;
    };

    static const QString END_LINE;
    static const QString END_PART_SENT;
    static const QString END_SENT;
    static const QString TAB;

    void writeObject(SCgObject *object);
    void writeObjectWithDeps(SCgObject *obj);
    void writeNode(SCgObject *obj);
    void writePair(SCgObject *obj);
    void writeBus(SCgObject *obj);
    void writeContour(SCgObject *obj);
    void writeSCgProperties(QString const & idtf, RelationValueVector const & properties);
    void writePoints(QString const & idtf, QVector<QPointF> const & points, bool cyclic);

    QString linkWrap(QString const & idtf);
    QString linkWrap(int number);
    QString linkWrap(double number);
    QString getIdtf(QString const & prefix);
    QString getIdtf(SCgObject *obj);
    QString getSCgIdtf(SCgObject *obj);
    QString getAlias(QString const & base);
    QString getTemp(QString const & base);
    static QString makeAlias(QString const & base);
    static QString makeTemp(QString const & base);
    static QString convertType(QString const & type);

    StreamWriter scg;
    StreamWriter scs;

    QHash<int, QVector<SCgObject *> > children;
    QHash<SCgObject *, QList<SCgObject *>> deps;
    QHash<SCgObject *, short> dfsStatus;

    QHash<QString, int> count;
    QHash<int, QString> names;
    QHash<int, QString> scgNames;
};
