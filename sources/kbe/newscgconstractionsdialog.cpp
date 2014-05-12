#include "newscgconstractionsdialog.h"

#include "ui_mainwindow.h"

#include "config.h"

#include "pluginmanager.h"
#include "interfaces/editorinterface.h"
#include "mainwindow.h"
#include "newscgactionsdialog.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <QKeyEvent>
#include <QPushButton>


newscgconstractionsdialog::newscgconstractionsdialog(QWidget *parent):
    QDialog(parent)
{
    QVBoxLayout *lay = new QVBoxLayout;
    QLabel *lab = new QLabel(tr("List of constractions"));

    mAvailableTypesList = new QListWidget(this);
    mAvailableTypesList->setSelectionMode(QAbstractItemView::SingleSelection);
    mAvailableTypesList->setIconSize(QSize(32, 32));

    QString projectPath(PROJECT_PATH);
    QDir dir(projectPath+"/construction");
    QStringList gwf  = dir.entryList(QStringList("*.gwf"));
    int i = 0;
    foreach (QString file, gwf)
    {
       QListWidgetItem *itemToAdd = new QListWidgetItem(file);
       itemToAdd->setData(EditorTypeRole,file);
       mAvailableTypesList->addItem(itemToAdd);
       i++;
    }

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

newscgconstractionsdialog::~newscgconstractionsdialog()
{
}

QString newscgconstractionsdialog::selectedEditor() const
{
    return mAvailableTypesList->selectedItems().at(0)->data(EditorTypeRole).toString();
}


void newscgconstractionsdialog::openNewProgram(QModelIndex index)
{
    QString projectPath(PROJECT_PATH);
    QString file = projectPath + "/construction/"+index.data().toString();
    MainWindow *m = MainWindow::getInstance();

    if(QFile::exists(file))
    {
        m->load(file);
        close();
    }

}

