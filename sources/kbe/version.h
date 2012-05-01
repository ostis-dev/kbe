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

#ifndef VERSION_H
#define VERSION_H

#include <QString>

class Version
{
public:
    Version() : mVersion(0) {   }
    Version(unsigned int major, unsigned int minor, unsigned int patch, QString rc, unsigned int revision, QString codeName) :
            mRevision(revision),
            mReleaseCandidate(rc),
            mCodeName(codeName)
    {
        mVersion = (major << 16) + (minor << 8) + patch;
    }


    friend bool operator < (Version const &v1, Version const &v2)   { return (v1.getMajor() < v2.getMajor()) ? true : (v1.getMinor() < v2.getMinor()) ;}
    friend bool operator >=(Version const &v1, Version const &v2)   { return !(v1 < v2); }
    friend bool operator > (Version const &v1, Version const &v2)   { return (v2 < v1); }
    friend bool operator <=(Version const &v1, Version const &v2)   { return !(v1 > v2); }

    friend bool operator ==(Version const &v1, Version const &v2)   { return !(v1 < v2) && !(v1 > v2); }
    friend bool operator !=(Version const &v1, Version const &v2)   { return !(v1 == v2); }

    unsigned int getMajor() const { return (mVersion & 0xffff0000) >> 16; }
    unsigned int getMinor() const { return (mVersion & 0x0000ff00) >> 8; }
    unsigned int getPatch() const { return (mVersion & 0x000000ff); }

    /*! Converts version to string representation
      */
    QString toString()
    {
        return QString("%1.%2.%3 %4 (%5)").arg(getMajor()).arg(getMinor()).arg(getPatch()).arg(mReleaseCandidate).arg(mCodeName);
    }

protected:
    //! Version
    unsigned int mVersion;
    //! Subversion revision
    unsigned int mRevision;
    //! Release candidate
    QString mReleaseCandidate;
    //! Code name
    QString mCodeName;
};

#define MAJOR   0
#define MINOR   3
#define PATCH   0
#define REVISION    0
#define RC      ""
#define CODENAME    "integrator"

#define VERSION Version(MAJOR, MINOR, PATCH, RC, REVISION, CODENAME)
#define VERSION_STR VERSION.toString()

#endif // VERSION_H
