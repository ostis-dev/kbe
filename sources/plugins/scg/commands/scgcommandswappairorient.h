/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgbasecommand.h"

class SCgPair;

class SCgCommandSwapPairOrient : public SCgBaseCommand
{
public:
    explicit SCgCommandSwapPairOrient(SCgScene *scene, SCgPair *pair, QUndoCommand *parent);
    virtual ~SCgCommandSwapPairOrient();

protected:
    void redo();
    void undo();
};


