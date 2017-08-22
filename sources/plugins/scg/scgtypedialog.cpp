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
#include <QAction>
#include <QShortcut>

SCgTypeSelectionDialog::SCgTypeSelectionDialog(int objectType, QWidget* parent)
    : QDialog(parent)
    , mObjectType(objectType)
{
    setWindowTitle(tr("Select type"));
    setStyleSheet("QGroupBox QPushButton"
                  "{ padding: 3px 3px 3px 3px;"
                  "  text-align: left; }"
                  "QGroupBox QPushButton:focus"
                  "{ outline: none;"
                  "  background-color: #dbdbdb; }");

    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* topLayout = new QHBoxLayout();

    QVBoxLayout* constLayout = new QVBoxLayout();
    QVBoxLayout* varLayout = new QVBoxLayout();
    QHBoxLayout* unknownLayout = new QHBoxLayout();

    mConstGroup = new QGroupBox(tr("Constants") + " (C)");
    mConstGroup->setLayout(constLayout);

    QAction* focusConstAction = new QAction(this);
    focusConstAction->setShortcut(QKeySequence("C"));
    addAction(focusConstAction);
    connect(focusConstAction, SIGNAL(triggered(bool)), mConstGroup, SLOT(setFocus()));

    mVarGroup = new QGroupBox(tr("Variables") + " (V)");
    mVarGroup->setLayout(varLayout);

    QAction* focusVarAction = new QAction(this);
    focusVarAction->setShortcut(QKeySequence("V"));
    addAction(focusVarAction);
    connect(focusVarAction, SIGNAL(triggered(bool)), mVarGroup, SLOT(setFocus()));

    mUnknownGroup = new QGroupBox(tr("Constancy unknown") + " (X)");
    mUnknownGroup->setLayout(unknownLayout);

    QAction* focusUnknownAction = new QAction(this);
    focusUnknownAction->setShortcut(QKeySequence("X"));
    addAction(focusUnknownAction);
    connect(focusUnknownAction, SIGNAL(triggered(bool)), mUnknownGroup, SLOT(setFocus()));

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

    int hotkey = 1;
    for (it = constTypes.cbegin(); it != constTypes.cend(); ++it)
        addTypeButton(it.value(), it.key(), hotkey++, mConstGroup);
    hotkey = 1;
    for (it = varTypes.cbegin(); it != varTypes.cend(); ++it)
        addTypeButton(it.value(), it.key(), hotkey++, mVarGroup);
    hotkey = 1;
    for (it = unknownTypes.cbegin(); it != unknownTypes.cend(); ++it)
        addTypeButton(it.value(), it.key(), hotkey++, mUnknownGroup);
}

void SCgTypeSelectionDialog::addTypeButton(const QIcon& icon, const QString& text, int hotkey, QWidget* parent)
{
    QPushButton* button = new QPushButton(icon, text);
    button->setIconSize(QSize(24, 24));
    button->setToolTip(QString::number(hotkey));
    connect(button, SIGNAL(clicked(bool)), this, SLOT(onChooseType()));

    if (parent->layout())
        parent->layout()->addWidget(button);
    else
        return;

    QShortcut* shortcut = new QShortcut(parent);
    shortcut->setKey(QString::number(hotkey));
    shortcut->setContext(Qt::WidgetWithChildrenShortcut);
    connect(shortcut, SIGNAL(activated()), button, SLOT(click()));
}

QString SCgTypeSelectionDialog::getChosenType() const
{
    return mChosenType;
}
