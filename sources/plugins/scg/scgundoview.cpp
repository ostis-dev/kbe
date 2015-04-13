/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgundoview.h"
#include "scgundoviewmodel.h"

SCgUndoView::SCgUndoView(QWidget* parent)
                    :QListView(parent)
{
    QItemSelectionModel* m = selectionModel();
    QAbstractItemModel* im = model();

    SCgUndoViewModel* newModel = new SCgUndoViewModel(this);
    setModel(newModel);
    setSelectionModel(newModel->selectionModel());

    delete m;
    delete im;
}

SCgUndoView::~SCgUndoView()
{

}

void SCgUndoView::setStack(QUndoStack* st)
{
    SCgUndoViewModel* vm = dynamic_cast<SCgUndoViewModel*>(model());
    Q_ASSERT_X( vm,
               "void ExtendedUndoView::setStack()",
               "Only ExtendedUndoViewModel is supported as model of ExtendedUndoView");

    vm->setStack(st);
}

