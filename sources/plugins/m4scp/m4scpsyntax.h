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

#ifndef M4SCPSYNTAX_H
#define M4SCPSYNTAX_H

#include <QStringList>

/*! This class contains lists of all keywords
  */
class M4SCpSyntax
{
public:
    //! Initialize keyword lists
    static void initialize();

    //! Return list of operators
    static const QStringList& operators();

    //! Return list of attributes
    static const QStringList& attributes();

    //! Return list of ordinals
    static const QStringList& ordinals();

    //! Get last symbols for words
    static const QString& eow();

protected:
    //! List of all m4scp operators
    static QStringList mOperatorsList;
    //! List of all m4scp attributes
    static QStringList mAttributesList;
    //! List of all m4scp ordinals
    static QStringList mOrdinalsList;

    //! Symbols that used as end of word
    static QString mEndOfWord;

};

#endif // M4SCPSYNTAX_H
