/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

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
#define MINOR   4
#define PATCH   1
#define REVISION    0
#define RC      ""
#define CODENAME    "integrator"

#define VERSION Version(MAJOR, MINOR, PATCH, RC, REVISION, CODENAME)
#define VERSION_STR VERSION.toString()

