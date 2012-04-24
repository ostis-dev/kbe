/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

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

#ifndef UPDATEEXTRACTOR_H
#define UPDATEEXTRACTOR_H

#include <QObject>

/*! Class that extracs update from zip archive
  */
class UpdateExtractor : public QObject
{
    Q_OBJECT
public:
    explicit UpdateExtractor(QObject *parent = 0);
    virtual ~UpdateExtractor();

    /*! Extract files from \p archive into \p directory
      * @param archive Path to archive to exctract data
      * @param directory Path to output directory
      *
      * @return Return true, if archive extracted wihtout any errors; otherwise return false
      */
    bool extract(const QString &archive, const QString &directory);

signals:
    
public slots:
    
};

#endif // UPDATEEXTRACTOR_H
