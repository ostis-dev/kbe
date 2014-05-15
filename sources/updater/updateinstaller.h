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

#ifndef UPDATEINSTALLER_H
#define UPDATEINSTALLER_H

#include <QObject>
#include <QList>

class QFileInfo;

struct Rule {
    bool dir;
    bool action;
    QString fileName;
};

/*! Class that installs specified update package
  */
class UpdateInstaller : public QObject
{
    Q_OBJECT
public:
    explicit UpdateInstaller(const QString &patchPath, QObject *parent = 0);
    virtual ~UpdateInstaller();

    /*! Installs updates
      * @return Return true, if updates installed wihtout any errors; otherwise return false
      */
    bool installUpdate();

signals:
    
public slots:

private:
    QString mPatchPath;

protected:

    /*! Extract files from \p archive into \p directory
      * @param Link to the list where you want to write rules
      */
    void getRules(QList<Rule> &rulesList);

    /*! Performs the rule
      * @param Rule to perform
      * @return Return true, if rule performed wihtout any errors; otherwise return false
      */
    bool performRule(Rule rule);

    /*! Copies the file
      * @param Path of the file you want to copy
      * @return Return true, if file copied wihtout any errors; otherwise return false
      */
    bool cpFile(const QString &filePath);

    /*! Copies the directory
      * @param Path of the directory you want to copy
      * @return Return true, if directory copied wihtout any errors; otherwise return false
      */
    bool cpDir(const QString &dirPath);

    /*! Deletes the directory
      * @param Path of the directory you want to delete
      * @return Return true, if directory deleted wihtout any errors; otherwise return false
      */
    bool rmDir(const QString &dirPath);

    /*! Checks the file in the program folder. If it exists, deletes it.
      * Creates the folders for a file, if they are not exist.
      * @param Information about the file you want to copy
      * @return Return destination file path
      */
    QString cpCheck(const QFileInfo &fileInfo);

    //bool cleanUpdates();
};

#endif // UPDATEINSTALLER_H
