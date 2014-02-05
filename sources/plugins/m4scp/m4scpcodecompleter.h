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

#ifndef M4SCPCODECOMPLETER_H
#define M4SCPCODECOMPLETER_H

#include <QtWidgets/QCompleter>
//#include <QMap>

class M4SCpCodeCompleter : public QCompleter
{
    Q_OBJECT
public:
    explicit M4SCpCodeCompleter(QObject *parent = 0);
    virtual ~M4SCpCodeCompleter();

    /*! Initialize complete dictionary.
      * This function must be call manualy, after completer creation
      */
    void initDictionary();

private:


signals:

public slots:

};

#endif // M4SCPCODECOMPLETER_H
