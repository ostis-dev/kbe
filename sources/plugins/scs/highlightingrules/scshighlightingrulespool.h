/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scsabstracthighlightingrule.h"

#include <QList>

class SCsHighlightingRulesPool
{
public:
    static SCsHighlightingRulesPool* getInstance();
    QList<SCsAbstractHighlightingRule*> rules();
    ~SCsHighlightingRulesPool();

private:
    SCsHighlightingRulesPool();

    void initScArcRules();

    QList<SCsAbstractHighlightingRule*> mRules;
    static SCsHighlightingRulesPool* msInstance;
};


