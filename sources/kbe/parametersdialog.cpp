#include "parametersdialog.h"
#include "config.h"
#include "guidedialog.h"

#include <QDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QSettings>
#include <QCheckBox>
#include <QPushButton>

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

    QVBoxLayout *vertical = new QVBoxLayout();

    QTabWidget *tabWidget = new QTabWidget;
    tabWidget->addTab(new GeneralParametersTab(), tr("General"));
    tabWidget->addTab(new M4SCpParametersTab(), tr("M4SCp"));
    tabWidget->addTab(new SCgParametersTab(), tr("SCg"));
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

M4SCpParametersTab::M4SCpParametersTab(QWidget *parent):
    QWidget(parent)
{
    QVBoxLayout *verticalM = new QVBoxLayout();
    QLabel *label1M = new QLabel("METKAM");
    QLabel *label2M = new QLabel("METKA2M");
    verticalM->addWidget(label1M);
    verticalM->addWidget(label2M);
    setLayout(verticalM);
}

SCgParametersTab::SCgParametersTab(QWidget *parent):
    QWidget(parent)
{
    QVBoxLayout *verticalS = new QVBoxLayout();
    QLabel *label1S = new QLabel("METKAS");
    QLabel *label2S = new QLabel("METKA2S");
    verticalS->addWidget(label1S);
    verticalS->addWidget(label2S);
    setLayout(verticalS);
}

