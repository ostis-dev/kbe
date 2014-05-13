#ifndef SCSOBJECTINFOREADER_H
#define SCSOBJECTINFOREADER_H

#include <QString>
#include <QList>
#include <QVector>
#include <QPointF>
#include <QMap>
#include <QPair>

class SCgObjectInfo;

//! Reads and stores SCgObjectInfo structures from pANTLR_BASE_TREE.
//! NOTE: only *.gwf files are supported.
class ScsObjectInfoReader
{
public:
    ScsObjectInfoReader();
    virtual ~ScsObjectInfoReader();

    typedef QList<SCgObjectInfo*>       ObjectInfoList;
    typedef QMap<int, ObjectInfoList>   TypeToObjectsMap;

    /*! Reads info from pANTLR_BASE_TREE.
     * @param fileName file name.
     * @return If read successfully returns true.
     */
    bool read(QString fileName);

    /**
     * \defgroup accessFunctions Access Functions
     * @{
     */
    const TypeToObjectsMap& objectsInfo() const
    {
        return mObjectsInfo;
    }
private:
    //! hold all read object info
    TypeToObjectsMap mObjectsInfo;
    //! file name
    QString mFileName;
    //! parts of source scs code (after using ANTLR parser)
    QList<QStringList> stringFirstLevelInfo;
    //! first id of scg object
    int idElement = 1;
    //! id of scg element and his identificator
    struct id2Idtf
    {
        int id;
        QString idtf;
    };
    QList<id2Idtf> listIdIdtf;
    /*! Generates scg node info from scs source file (after ANTLR parser).
     * @param temp parts of scs source files.
     * @return If generated successfully returns true.
     */
    bool parseNodes(QStringList temp);
    /*! Generates scg pair info from scs source file (after ANTLR parser).
     * @param temp parts of scs source files.
     * @return If generated successfully returns true.
     */
    bool parsePairs(QStringList temp);
    /*! Get type and identificator of scs element.
     * @param type  type of scs element.
     * @param idtf of scs element.
     * @param str scs sentence.
     * @return If element has id and identificator successfully returns true.
     */
    bool getIdAndType(QString* type,QString* idtf,QString str);
    /*! Check, if scs element has identificator.
     * @param str scs sentence.
     * @return If scs element has identificator successfully returns true.
     */
    bool checkIdAndType(QString str);
    /*! Get first and last elements in scs sentence.
     * @param str scs sentence.
     * @return Returns first and last elements in scs sentence.
     */
    QStringList getPairBeginEnd(QStringList str);
    /*! Check if list of structure id2Idtf contains inputed scs element.
     * @param str identificator of scs element.
     * @return If such element contains inputed scs element returns true.
     */
    bool structContains(QString str);

};

#endif // SCSOBJECTINFOREADER_H
