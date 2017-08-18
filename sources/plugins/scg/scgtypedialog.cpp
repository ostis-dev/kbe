/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgtypedialog.h"
#include "scgnode.h"
#include "scgpair.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QDialogButtonBox>

SCgTypeSelectionDialog::SCgTypeSelectionDialog(int objectType, QWidget* parent)
    : QDialog(parent)
    , mObjectType(objectType)
{
    setWindowTitle(tr("Select type"));

    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* topLayout = new QHBoxLayout();

    QVBoxLayout* constLayout = new QVBoxLayout();
    QVBoxLayout* varLayout = new QVBoxLayout();
    QHBoxLayout* unknownLayout = new QHBoxLayout();

    mConstGroup = new QGroupBox(tr("Constants"));
    mConstGroup->setLayout(constLayout);

    mVarGroup = new QGroupBox(tr("Variables"));
    mVarGroup->setLayout(varLayout);

    mUnknownGroup = new QGroupBox(tr("Constancy unknown"));
    mUnknownGroup->setLayout(unknownLayout);

    topLayout->addWidget(mConstGroup, 1);
    topLayout->addWidget(mVarGroup, 1);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(mUnknownGroup);

    QDialogButtonBox* box = new QDialogButtonBox(QDialogButtonBox::Cancel);
    box->button(QDialogButtonBox::Cancel)->setDefault(true);
    connect(box, SIGNAL(rejected()), this, SLOT(reject()));
    mainLayout->addWidget(box);

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);

    displayTypes();
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

void SCgTypeSelectionDialog::displayTypes()
{
    SCgAlphabet& alphabet = SCgAlphabet::getInstance();
    SCgAlphabet::SCgObjectTypesMap constTypes;
    SCgAlphabet::SCgObjectTypesMap varTypes;
    SCgAlphabet::SCgObjectTypesMap unknownTypes;

    switch (mObjectType)
    {
    case SCgNode::Type:
        alphabet.getNodeTypes(SCgAlphabet::Const, constTypes);
        alphabet.getNodeTypes(SCgAlphabet::Var, varTypes);
        alphabet.getNodeTypes(SCgAlphabet::ConstUnknown, unknownTypes);
        break;
    case SCgPair::Type:
        alphabet.getPairTypes(SCgAlphabet::Const, constTypes);
        alphabet.getPairTypes(SCgAlphabet::Var, varTypes);
        alphabet.getPairTypes(SCgAlphabet::ConstUnknown, unknownTypes);
        break;
    default:
        break;
    }

    SCgAlphabet::SCgObjectTypesMap::const_iterator it;

    for (it = constTypes.cbegin(); it != constTypes.cend(); ++it)
        addTypeButton(it.value(), it.key(), mConstGroup->layout());
    for (it = varTypes.cbegin(); it != varTypes.cend(); ++it)
        addTypeButton(it.value(), it.key(), mVarGroup->layout());
    for (it = unknownTypes.cbegin(); it != unknownTypes.cend(); ++it)
        addTypeButton(it.value(), it.key(), mUnknownGroup->layout());
}

void SCgTypeSelectionDialog::addTypeButton(const QIcon& icon, const QString& text, QLayout* layout)
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
