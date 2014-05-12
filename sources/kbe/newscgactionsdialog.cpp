#include "newscgactionsdialog.h"
#include "pluginmanager.h"
#include "interfaces/editorinterface.h"
#include "newfiledialog.h"
#include "newscgconstractionsdialog.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <QKeyEvent>
#include <QPushButton>


#include "mainwindow.h"

newscgactionsdialog::newscgactionsdialog(QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout *lay = new QVBoxLayout;
    QLabel *lab = new QLabel(tr("List of actions:"));

    mAvailableTypesList = new QListWidget(this);
    mAvailableTypesList->setSelectionMode(QAbstractItemView::SingleSelection);
    mAvailableTypesList->setIconSize(QSize(32, 32));

    QListWidgetItem *itemToAdd = new QListWidgetItem("new");
    itemToAdd->setData(EditorTypeRole, "new");
    mAvailableTypesList->addItem(itemToAdd);

    QListWidgetItem *itemToAdd1 = new QListWidgetItem("construction");
    itemToAdd1->setData(EditorTypeRole, "construction");
    mAvailableTypesList->addItem(itemToAdd1);

    QHBoxLayout *buttonLay = new QHBoxLayout;

    if (mAvailableTypesList->count() > 0)
        mAvailableTypesList->item(0)->setSelected(true);

    QPushButton *butCancel = new QPushButton(tr("Cancel"));

    buttonLay->addWidget(butCancel, 1, Qt::AlignRight);

    lay->addWidget(lab);
    lay->addWidget(mAvailableTypesList);
    lay->addLayout(buttonLay);
    setLayout(lay);

    connect(mAvailableTypesList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(openNewProgram(QModelIndex)));
    connect(butCancel, SIGNAL(clicked()), this, SLOT(reject()));

    parentWidget()->close();
}

newscgactionsdialog::~newscgactionsdialog()
{
}

QString newscgactionsdialog::selectedEditor() const
{
    return mAvailableTypesList->selectedItems().at(0)->data(EditorTypeRole).toString();
}

void newscgactionsdialog::openNewProgram(QModelIndex index)
{

    if((index.data().toString()) == "construction")
    {
        newscgconstractionsdialog* scgDialog = new newscgconstractionsdialog(this);
        scgDialog->exec();

    }
    if(index.data().toString() == "new")
    {
        MainWindow *m = MainWindow::getInstance();
        m->createSubWindowByType("scg");
        close();

    }

}
