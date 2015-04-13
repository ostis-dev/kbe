/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcontentchangedialog.h"

#include "scgcontentfactory.h"
#include "scgcontentdialog.h"
#include "scgnode.h"

#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>

SCgContentChangeDialog* SCgContentChangeDialog::mInstance = 0;

SCgContentChangeDialog* SCgContentChangeDialog::getInstance()
{
    Q_ASSERT(mInstance != 0);
    return mInstance;
}

SCgContentChangeDialog::SCgContentChangeDialog(SCgNode *node, QWidget *parent) :
    QDialog(parent),
    mNode(node),
    mDialog(0),
    mCenterLayout(0)
{
    Q_ASSERT(mInstance == 0);
    mInstance = this;

    QHBoxLayout *topLayout = new QHBoxLayout;
    QComboBox *comboFormats = new QComboBox(this);
    connect(comboFormats, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeFromat(QString)));
    topLayout->addWidget(comboFormats, 0, Qt::AlignLeft);

    QHBoxLayout *bottomLayout = new QHBoxLayout;

    mButtonApply = new QPushButton(tr("Apply"), this);
    connect(mButtonApply, SIGNAL(clicked()), this, SLOT(apply()));
    bottomLayout->addWidget(mButtonApply, 1, Qt::AlignRight);

    mCenterLayout = new QHBoxLayout;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(mCenterLayout);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);

    QList<QString> list = SCgContentFactory::supportedFormats();
    comboFormats->addItems(list);

    int curIndex = list.indexOf(mNode->contentFormat());
    if (curIndex > 0)
    	comboFormats->setCurrentIndex(curIndex);
}

SCgContentChangeDialog::~SCgContentChangeDialog()
{
    if (mDialog != 0)
    {
        delete mDialog;
        mDialog = 0;
    }

    mInstance = 0;
}

void SCgContentChangeDialog::changeFromat(QString format)
{
    if (mDialog)
    {
        delete mDialog;
        mDialog = 0;
    }

    mDialog = SCgContentFactory::createDialog(format, mNode);
    mDialog->setParent(this);
    mButtonApply->setEnabled(true);
    mCenterLayout->addWidget(mDialog);
    setFixedSize(mDialog->sizeHint() + QSize(40, 70));//resize(mDialog->sizeHint());
}

void SCgContentChangeDialog::apply()
{
    Q_ASSERT(mDialog);
    mDialog->apply();
    done(QDialog::Accepted);
}

void SCgContentChangeDialog::contentInfo(SCgContent::ContInfo &info)
{
    return mDialog->contentInfo(info);
}

void SCgContentChangeDialog::slotEnableApplyButton(QValidator::State state)
{
    if (state == QValidator::Acceptable)
    {
        mButtonApply->setEnabled(true);
    }
    else
    {
        mButtonApply->setEnabled(false);
    }
}
