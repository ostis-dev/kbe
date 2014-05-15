/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#include "updateinstaller.h"

#include <QFileInfo>
#include <QDir>
#include <QDomDocument>

UpdateInstaller::UpdateInstaller(const QString &patchPath, QObject *parent) :
    QObject(parent),
    mPatchPath(patchPath)
{
}

UpdateInstaller::~UpdateInstaller()
{
}

bool UpdateInstaller::installUpdate()
{
    QList<Rule> rules;
    getRules(rules);
    if (rules.isEmpty())
        return false;
    for (int i = 0; i < rules.size(); i++) {
        Rule rule = rules.at(i);
        if (!performRule(rule))
            return false;
    }
    //if (!cleanUpdates())
    //    return false;
    return true;
}

void UpdateInstaller::getRules(QList<Rule> &rulesList)
{
    static QString rulesFile = "_info.xml";
    QFileInfo fi(QDir(mPatchPath),rulesFile);
    if (!fi.exists())
        return;
    QFile file(fi.filePath());
    QDomDocument doc(rulesFile);
    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!doc.setContent(&file)) {
        file.close();
        return;
    }
    file.close();
    QDomElement root = doc.documentElement();
    if (root.tagName() != "info")
        return;
    QDomElement rules = root.firstChildElement("rules");
    QDomElement rule = rules.firstChildElement("rule");
    while (!rule.isNull())
    {
        Rule r;
        if (rule.attribute("is_dir") == "1")
            r.dir = true;
        else
            r.dir = false;
        if (rule.attribute("type") == "+")
            r.action = true;
        else
            r.action = false;
        r.fileName = rule.text();
        rulesList.append(r);
        rule = rule.nextSiblingElement("rule");
    }
    return;
}

bool UpdateInstaller::performRule(Rule rule)
{
    bool result = true;
    if (!rule.action) { // rule - (delete)
        if (rule.dir) // rule for directory
            result = rmDir(rule.fileName);
        else { // rule for file
            QFileInfo fi(rule.fileName);
            if (fi.exists())
                result = QFile::remove(fi.filePath());
        }
    }
    else { // rule + (add)
        static QString updatesDir = "_update_files/files/";
        if (rule.dir)  // rule for directory
            result = cpDir(updatesDir+rule.fileName);
        else // rule for file
            result = cpFile(rule.fileName);
    }
    return result;
}

bool UpdateInstaller::cpFile(const QString &filePath)
{
    QDir d(mPatchPath+"/files");
    QFileInfo fi(d,filePath);
    if (!fi.exists())
        return false;
    return QFile::copy(fi.filePath(), cpCheck(fi));
}

bool UpdateInstaller::cpDir(const QString &dirPath)
{
    bool result = true;
    QDir dir(dirPath);
    Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot))
    {
        QString srcPath = info.filePath();
        if (info.isDir())
            result = cpDir(srcPath);
        if (info.isFile())
            result = QFile::copy(srcPath, cpCheck(info));
        if (!result)
            return result;
    }
    return result;
}

QString UpdateInstaller::cpCheck(const QFileInfo &fileInfo)
{
    QString dstFilePath = fileInfo.filePath();
    dstFilePath = dstFilePath.replace("_update_files/files/",QString()); // destination file path
    QString dstDirPath = dstFilePath;
    dstDirPath = dstDirPath.replace(fileInfo.fileName(),QString()); //destination dir path
    if (!dstDirPath.isEmpty()) {
        QDir d;
        if (!d.exists(dstDirPath)) //create destination dir if it doesn't exists
            d.mkpath(dstDirPath);
    }
    QFileInfo fi(dstFilePath);
    if (fi.exists())
        QFile::remove(fi.filePath()); //delete file if it exists (cause QFile::copy() doesn't support overwrite)
    return dstFilePath;
}


bool UpdateInstaller::rmDir(const QString &dirPath)
{
    bool result =  true;
    QDir dir(dirPath);
    if (dir.exists()) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System |
                                                    QDir::Hidden  | QDir::AllDirs |
                                                    QDir::Files, QDir::DirsFirst))
        {
            if (info.isDir())
                result = rmDir(info.filePath());
            if (info.isFile())
                result = QFile::remove(info.filePath());
            if (!result)
                return result;
        }
        QDir d;
        result = d.rmdir(dirPath);
    }
    return result;
}

/*
bool UpdateInstaller::cleanUpdates()
{
    static QString _updatesDir = "_update_files";
    static QString _updatesCheckSum = "_update.checksum";
    static QString _updatesFile = "_update.update";
    static QString _updatesXml = "_updates.xml";
    if (!rmDir(_updatesDir))
        return false;
    if (!QFile::remove(_updatesCheckSum))
        return false;
    if (!QFile::remove(_updatesFile))
        return false;
    if (!QFile::remove(_updatesXml))
        return false;
    return true;
}
*/
