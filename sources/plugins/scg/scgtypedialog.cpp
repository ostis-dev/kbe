/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgtypedialog.h"
#include "scgnode.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QDialogButtonBox>

SCgTypeSelectionDialog::SCgTypeSelectionDialog(const QString& objectType, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Select type"));

    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* topLayout = new QHBoxLayout();

    QVBoxLayout* constLayout = new QVBoxLayout();
    QVBoxLayout* varLayout = new QVBoxLayout();
    QHBoxLayout* unknownLayout = new QHBoxLayout();

    QGroupBox* constGroup = new QGroupBox(tr("Constants"));
    constGroup->setLayout(constLayout);
    QGroupBox* varGroup = new QGroupBox(tr("Variables"));
    varGroup->setLayout(varLayout);
    QGroupBox* unknownGroup = new QGroupBox(tr("Constancy unknown"));
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

    // display available types
    SCgAlphabet& alphabet = SCgAlphabet::getInstance();
    SCgAlphabet::SCgObjectTypesMap types;
    SCgAlphabet::SCgObjectTypesMap::iterator it;

    alphabet.getObjectTypes(objectType, SCgAlphabet::Const, types);
    for (it = types.begin(); it != types.end(); ++it)
        addTypeButton(it.value(), it.key(), constLayout);

    types.clear();
    alphabet.getObjectTypes(objectType, SCgAlphabet::Var, types);
    for (it = types.begin(); it != types.end(); ++it)
        addTypeButton(it.value(), it.key(), varLayout);

    types.clear();
    alphabet.getObjectTypes(objectType, SCgAlphabet::ConstUnknown, types);
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
