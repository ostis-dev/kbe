/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QListView>
class QUndoStack;

/* We don't use QUndoView directly, because this approach is more flexible.
 */
class SCgUndoView: public QListView//public QUndoView
{
    Q_OBJECT
public:

    SCgUndoView(QWidget* parent = 0);

    virtual ~SCgUndoView();

    //! Sets stack as a model of this view.
    void setStack(QUndoStack* st);

private:



};

