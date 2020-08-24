/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgtypedialog.h"
#include "scgnode.h"
#include "scgpair.h"
#include "scgcontour.h"

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

    QVBoxLayout* constPermLayout = new QVBoxLayout();
    QVBoxLayout* varPermLayout = new QVBoxLayout();
    QVBoxLayout* metaPermLayout = new QVBoxLayout();
    QVBoxLayout* constTempLayout = new QVBoxLayout();
    QVBoxLayout* varTempLayout = new QVBoxLayout();
    QVBoxLayout* metaTempLayout = new QVBoxLayout();
    QHBoxLayout* unknownLayout = new QHBoxLayout();

    mConstPermGroup = new QGroupBox(tr("Constants") + " (C)");
    mConstPermGroup->setLayout(constPermLayout);

    QAction* focusConstPermAction = new QAction(this);
    focusConstPermAction->setShortcut(QKeySequence("C"));
    addAction(focusConstPermAction);
    connect(focusConstPermAction, SIGNAL(triggered(bool)), mConstPermGroup, SLOT(setFocus()));

    mVarPermGroup = new QGroupBox(tr("Variables") + " (V)");
    mVarPermGroup->setLayout(varPermLayout);

    QAction* focusVarPermAction = new QAction(this);
    focusVarPermAction->setShortcut(QKeySequence("V"));
    addAction(focusVarPermAction);
    connect(focusVarPermAction, SIGNAL(triggered(bool)), mVarPermGroup, SLOT(setFocus()));

    mMetaPermGroup = new QGroupBox(tr("Meta") + " (M)");
    mMetaPermGroup->setLayout(metaPermLayout);

    QAction* focusMetaPermAction = new QAction(this);
    focusMetaPermAction->setShortcut(QKeySequence("M"));
    addAction(focusMetaPermAction);
    connect(focusMetaPermAction, SIGNAL(triggered(bool)), mMetaPermGroup, SLOT(setFocus()));

    mConstTempGroup = new QGroupBox(tr("Constants") + " (Q)");
    mConstTempGroup->setLayout(constTempLayout);

    QAction* focusConstTempAction = new QAction(this);
    focusConstTempAction->setShortcut(QKeySequence("Q"));
    addAction(focusConstTempAction);
    connect(focusConstTempAction, SIGNAL(triggered(bool)), mConstTempGroup, SLOT(setFocus()));

    mVarTempGroup = new QGroupBox(tr("Variables") + " (W)");
    mVarTempGroup->setLayout(varTempLayout);

    QAction* focusVarTempAction = new QAction(this);
    focusVarTempAction->setShortcut(QKeySequence("W"));
    addAction(focusVarTempAction);
    connect(focusVarTempAction, SIGNAL(triggered(bool)), mVarTempGroup, SLOT(setFocus()));

    mMetaTempGroup = new QGroupBox(tr("Meta") + " (N)");
    mMetaTempGroup->setLayout(metaTempLayout);

    QAction* focusMetaTempAction = new QAction(this);
    focusMetaTempAction->setShortcut(QKeySequence("N"));
    addAction(focusMetaTempAction);
    connect(focusMetaTempAction, SIGNAL(triggered(bool)), mMetaTempGroup, SLOT(setFocus()));

    mUnknownGroup = new QGroupBox(tr("Constancy unknown") + " (X)");
    mUnknownGroup->setLayout(unknownLayout);

    QAction* focusUnknownAction = new QAction(this);
    focusUnknownAction->setShortcut(QKeySequence("X"));
    addAction(focusUnknownAction);
    connect(focusUnknownAction, SIGNAL(triggered(bool)), mUnknownGroup, SLOT(setFocus()));

    switch (mObjectType)
    {
    case SCgNode::Type:
        topLayout->addWidget(mConstPermGroup, 1);
        topLayout->addWidget(mVarPermGroup, 1);
        topLayout->addWidget(mMetaPermGroup, 1);
        topLayout->addWidget(mConstTempGroup, 1);
        topLayout->addWidget(mVarTempGroup, 1);
        topLayout->addWidget(mMetaTempGroup, 1);
        break;
    case SCgPair::Type:
        topLayout->addWidget(mConstPermGroup, 1);
        topLayout->addWidget(mVarPermGroup, 1);
        topLayout->addWidget(mMetaPermGroup, 1);
        break;
    case SCgContour::Type:
        topLayout->addWidget(mConstPermGroup, 1);
        topLayout->addWidget(mVarPermGroup, 1);
    default:
        break;
    }

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(mUnknownGroup, 1);

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
    SCgAlphabet::SCgObjectTypesMap constPermTypes;
    SCgAlphabet::SCgObjectTypesMap varPermTypes;
    SCgAlphabet::SCgObjectTypesMap metaPermTypes;
    SCgAlphabet::SCgObjectTypesMap constTempTypes;
    SCgAlphabet::SCgObjectTypesMap varTempTypes;
    SCgAlphabet::SCgObjectTypesMap metaTempTypes;
    SCgAlphabet::SCgObjectTypesMap unknownTypes;

    switch (mObjectType)
    {
    case SCgNode::Type:
        alphabet.getNodeTypes(SCgAlphabet::Const, SCgAlphabet::Permanent, constPermTypes);
        alphabet.getNodeTypes(SCgAlphabet::Var, SCgAlphabet::Permanent, varPermTypes);
        alphabet.getNodeTypes(SCgAlphabet::Meta, SCgAlphabet::Permanent, metaPermTypes);
        alphabet.getNodeTypes(SCgAlphabet::Const, SCgAlphabet::Temporary, constTempTypes);
        alphabet.getNodeTypes(SCgAlphabet::Var, SCgAlphabet::Temporary, varTempTypes);
        alphabet.getNodeTypes(SCgAlphabet::Meta, SCgAlphabet::Temporary, metaTempTypes);
        alphabet.getNodeTypes(SCgAlphabet::ConstUnknown,  unknownTypes);
        break;
    case SCgPair::Type:
        alphabet.getPairTypes(SCgAlphabet::Const, constPermTypes);
        alphabet.getPairTypes(SCgAlphabet::Var, varPermTypes);
        alphabet.getPairTypes(SCgAlphabet::Meta, metaPermTypes);
        alphabet.getPairTypes(SCgAlphabet::ConstUnknown, unknownTypes);
        break;
    case SCgContour::Type:
        alphabet.getContourTypes(SCgAlphabet::Const, constPermTypes);
        alphabet.getContourTypes(SCgAlphabet::Var, varPermTypes);
        break;
    default:
        break;
    }

    SCgAlphabet::SCgObjectTypesMap::const_iterator it;

    int hotkey = 1;
    for (it = constPermTypes.cbegin(); it != constPermTypes.cend(); ++it)
        addTypeButton(it.value(), it.key(), hotkey++, mConstPermGroup);
    hotkey = 1;
    for (it = varPermTypes.cbegin(); it != varPermTypes.cend(); ++it)
        addTypeButton(it.value(), it.key(), hotkey++, mVarPermGroup);
    hotkey = 1;
    for (it = metaPermTypes.cbegin(); it != metaPermTypes.cend(); ++it)
        addTypeButton(it.value(), it.key(), hotkey++, mMetaPermGroup);
    hotkey = 1;
    for (it = constTempTypes.cbegin(); it != constTempTypes.cend(); ++it)
        addTypeButton(it.value(), it.key(), hotkey++, mConstTempGroup);
    hotkey = 1;
    for (it = varTempTypes.cbegin(); it != varTempTypes.cend(); ++it)
        addTypeButton(it.value(), it.key(), hotkey++, mVarTempGroup);
    hotkey = 1;
    for (it = metaTempTypes.cbegin(); it != metaTempTypes.cend(); ++it)
        addTypeButton(it.value(), it.key(), hotkey++, mMetaTempGroup);
    hotkey = 1;
    for (it = unknownTypes.cbegin(); it != unknownTypes.cend(); ++it)
        addTypeButton(it.value(), it.key(), hotkey++, mUnknownGroup);
}

void SCgTypeSelectionDialog::addTypeButton(const QIcon& icon, const QString& text, int hotkey, QWidget* parent)
{
    QPushButton* button = new QPushButton(icon, text);
    button->setIconSize(QSize(72, 24));
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
