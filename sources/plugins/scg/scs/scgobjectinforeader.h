#pragma once

#include <QString>
#include <QList>
#include <QVector>
#include <QPointF>
#include <QMap>
#include <QSet>
#include <QHash>
#include <QPair>
#include <QTextStream>

#include <sc-memory/scs/scs_parser.hpp>

class SCgObjectInfo;

class SCgObjectInfoReader
{
public:
    typedef QList<SCgObjectInfo*>       ObjectInfoList;
    typedef QMap<int, ObjectInfoList>   TypeToObjectsMap;

    SCgObjectInfoReader(bool isOwner = true);

    explicit SCgObjectInfoReader(QIODevice *dev, QIODevice *layoutdev, bool isOwner = true);

    virtual ~SCgObjectInfoReader();

    //! This method must be called before any access to elements.
    bool read(QIODevice *dev, QIODevice *layoutDev);

    const TypeToObjectsMap& objectsInfo() const
    {
        return mObjectsInfo;
    }
private:
    const int CONTENT_TYPE_IMAGE = 4;

    TypeToObjectsMap mObjectsInfo;
    scs::Parser parser;
    QMap<scs::ElementHandle, scs::ElementHandle> parents;
    QHash<QString, int> ids;
    int cnt = 0;

    QMap<scs::ElementHandle, QPair<scs::ElementHandle, scs::ElementHandle>> edges;
    QMap<scs::ElementHandle, QVector<QPair<scs::ElementHandle, scs::ElementHandle>>> outEdges;
    QMap<scs::ElementHandle, QVector<QPair<scs::ElementHandle, scs::ElementHandle>>> inEdges;
    QTextStream scsStream;
    QTextStream scgStream;

    void parseNode(const scs::ElementHandle &node, const scs::ElementHandle &scgNode);
    void parseNode2(const scs::ElementHandle &node, const scs::ElementHandle &scgNode, QString const & typev);
    void parsePair(const scs::ElementHandle &pair, const scs::ElementHandle &scsPair);
    void parseBus(const scs::ElementHandle &bus);
    void parseContour(const scs::ElementHandle &contour);

    void addEdge(const scs::ElementHandle &edge, const scs::ElementHandle &start, const scs::ElementHandle &end);
    QPair<scs::ElementHandle, scs::ElementHandle> getEdge(const scs::ElementHandle &el);
    QVector<QPointF> getPoints(const scs::ElementHandle &set);
    QHash<QString, QString> getRelValues(const scs::ElementHandle &el);
    const QVector<QPair<scs::ElementHandle, scs::ElementHandle>> & getIn(const scs::ElementHandle &el);
    const QVector<QPair<scs::ElementHandle, scs::ElementHandle>> & getOut(const scs::ElementHandle &el);
    scs::ElementHandle findRelValueByIdtf(const scs::ElementHandle &el, const QString &idtf, bool out = true);

    QString getId(QString idtf);
    QString getParentId(const scs::ElementHandle &el);
    QString getSystemIdtf(const scs::ElementHandle &el);

    static QString convertType(ScType type);
    bool isTypeExtended(QString type);
    static QString convertExtendedType(QString const & type);

    //! Deletes all read info.
    void del();

    //! Holds true if this object takes ownership of created info structures.
    bool mIsOwner;

    QPair<qint32, qint32> mVersion;
};
