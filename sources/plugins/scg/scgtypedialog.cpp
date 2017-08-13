#include "scgtypedialog.h"
#include "scgnode.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QDialogButtonBox>

SCgTypeSelectionDialog::SCgTypeSelectionDialog(const QString& type, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Choose type"));

    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* topLayout = new QHBoxLayout();

    QVBoxLayout* constLayout = new QVBoxLayout();
    QVBoxLayout* varLayout = new QVBoxLayout();
    QHBoxLayout* unknownLayout = new QHBoxLayout();

    SCgAlphabet& alphabet = SCgAlphabet::getInstance();

    QGroupBox* constGroup = new QGroupBox(alphabet.aliasFromConstCode(SCgAlphabet::Const));
    constGroup->setLayout(constLayout);
    QGroupBox* varGroup = new QGroupBox(alphabet.aliasFromConstCode(SCgAlphabet::Var));
    varGroup->setLayout(varLayout);
    QGroupBox* unknownGroup = new QGroupBox(alphabet.aliasFromConstCode(SCgAlphabet::ConstUnknown));
    unknownGroup->setLayout(unknownLayout);

    topLayout->addWidget(constGroup, 1);
    topLayout->addWidget(varGroup, 1);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(unknownGroup);

    QDialogButtonBox* box = new QDialogButtonBox(QDialogButtonBox::Cancel);
    box->button(QDialogButtonBox::Cancel)->setDefault(true);
    connect(box, SIGNAL(rejected()), this, SLOT(reject()));
    mainLayout->addWidget(box);

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);

    SCgAlphabet::SCgObjectTypesMap types;
    SCgAlphabet::SCgObjectTypesMap::iterator it;

    alphabet.getObjectTypes(type, SCgAlphabet::Const, types);
    for (it = types.begin(); it != types.end(); ++it)
        addTypeButton(it.value(), it.key(), constLayout);

    types.clear();
    alphabet.getObjectTypes(type, SCgAlphabet::Var, types);
    for (it = types.begin(); it != types.end(); ++it)
        addTypeButton(it.value(), it.key(), varLayout);

    types.clear();
    alphabet.getObjectTypes(type, SCgAlphabet::ConstUnknown, types);
    for (it = types.begin(); it != types.end(); ++it)
        addTypeButton(it.value(), it.key(), unknownLayout);
}

void SCgTypeSelectionDialog::onChooseType()
{
    QPushButton* typeButton = qobject_cast<QPushButton*>(sender());

    if (typeButton)
    {
        mChosenType = typeButton->text();
        accept();
    }
}

void SCgTypeSelectionDialog::addTypeButton(const QIcon& icon, const QString& text, QBoxLayout* layout)
{
    QPushButton* button = new QPushButton(icon, text);
    button->setIconSize(QSize(24, 24));
    button->setStyleSheet("padding: 3px 3px 3px 3px; text-align: left;");
    layout->addWidget(button);

    connect(button, SIGNAL(clicked(bool)), this, SLOT(onChooseType()));
}

QString SCgTypeSelectionDialog::getChosenType() const
{
    return mChosenType;
}

