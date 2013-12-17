#include "parametersdialog.h"
#include "config.h"
#include "guidedialog.h"
#include "interfaces/editorinterface.h"
#include "pluginmanager.h"

#include <QDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QSettings>
#include <QCheckBox>
#include <QPushButton>
#include <QListWidget>

ParametersDialog::ParametersDialog(QWidget *parent):
    QDialog(parent)
{
    setWindowTitle(tr("Preferences"));
    setFixedSize(500,300);

    QPushButton *buttonOk = new QPushButton("OK");
    QPushButton *buttonCancel = new QPushButton("Cancel");

    QHBoxLayout *horizontal = new QHBoxLayout();
    horizontal->addWidget(buttonOk);
    horizontal->addWidget(buttonCancel);

    QTabWidget *tabWidget = new QTabWidget;
    tabWidget->addTab(new GeneralParametersTab(), tr("General"));

    QList<EditorFactoryInterface*> factories = PluginManager::instance()->editorFactoriesByType().values();
    QList<EditorFactoryInterface*>::iterator it, itEnd = factories.end();

    for (it = factories.begin(); it != itEnd; ++it)
    {
        /// @todo add custom icon and tooltip support.

        tabWidget->addTab((*it)->createNewParametersTab() , (*it)->name());
    }

    QVBoxLayout *vertical = new QVBoxLayout();
    vertical->addWidget(tabWidget);
    vertical->addLayout(horizontal);
    setLayout(vertical);

    connect(buttonCancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(accept()));
}

ParametersDialog::~ParametersDialog()
{

}

GeneralParametersTab::GeneralParametersTab(QWidget *parent):
    QWidget(parent)
{

    showStartupDialog = new QCheckBox("Show startup dialog");
    showStartupDialog->setChecked(settings.value(Config::settingsShowStartupDialog).toBool());

    connect(showStartupDialog, SIGNAL(stateChanged(int)), this, SLOT(showStateChanged(int)));

    QVBoxLayout *verticalG = new QVBoxLayout();
    QLabel *label1G = new QLabel("METKAG");
    QLabel *label2G = new QLabel("METKA2G");
    verticalG->addWidget(showStartupDialog);
    verticalG->addWidget(label1G);
    verticalG->addWidget(label2G);

    setLayout(verticalG);
}

void GeneralParametersTab::showStateChanged(int state)
{
    settings.setValue(Config::settingsShowStartupDialog, QVariant(showStartupDialog->isChecked()));
}
