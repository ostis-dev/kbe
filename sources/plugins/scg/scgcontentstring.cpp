/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgcontentstring.h"

#include "scgnode.h"

#include <QLabel>
#include <QTextEdit>
#include <QCheckBox>
#include <QVBoxLayout>


SCgContentStringViewer::SCgContentStringViewer(QGraphicsItem *parent) :
        SCgContentViewer(parent),
        mTextLabel(0)
{
    setMinimumSize(10, 10);
}

SCgContentStringViewer::~SCgContentStringViewer()
{

}

void SCgContentStringViewer::setData(const QVariant &data)
{
    SCgContentViewer::setData(data);

    if (!mTextLabel)
    {
        mTextLabel = new QLabel();
    }

    mTextLabel->setText(data.toString());
    mTextLabel->setWordWrap(true);
    mTextLabel->setIndent(5);
    QFont font("Times New Roman", 10, 10, false);
    mTextLabel->setFont(font);
    mTextLabel->setFixedSize(mTextLabel->sizeHint()+QSize(10, 10));
    setWidget(mTextLabel);
    updateGeometry();
}

// ------------------------------
SCgContentStringDialog::SCgContentStringDialog(SCgNode *node, QWidget *parent) :
        SCgContentDialog(node, parent),
        mWrapCheckBox(0),
        mTextEdit(0)
{
    mTextEdit = new QTextEdit(this);
    mWrapCheckBox = new QCheckBox(tr("Word wrap"),this);

    QObject::connect(mWrapCheckBox,SIGNAL(toggled(bool)),this,SLOT(setWordWrap(bool)));

    mTextEdit->setEnabled(true);
    mTextEdit->setMinimumSize(350, 200);
    mTextEdit->setWordWrapMode(QTextOption::NoWrap);
    mTextEdit->setFocus();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mWrapCheckBox);
    mainLayout->setAlignment(mWrapCheckBox,Qt::AlignRight);
    mainLayout->addWidget(mTextEdit);
    setLayout(mainLayout);

    //mTextEdit->setHtml(mNode->contentData().toString());
    if (mNode->isContentData() && mNode->contentFormat() == "string")
        mTextEdit->setPlainText(mNode->contentData().toString());
    else
        mTextEdit->setPlainText("");
}

void SCgContentStringDialog::apply()
{
    //Q_ASSERT(mNode);
    // get text and set it to node
    //mNode->setContentData(QVariant(mTextEdit->toHtml()), "STRING");
    //mNode->setContent("string", QVariant(mTextEdit->toPlainText()) , "", SCgContent::String);
}

void SCgContentStringDialog::setWordWrap(bool isWordWrap)
{
    if (isWordWrap)
        mTextEdit->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    else
        mTextEdit->setWordWrapMode(QTextOption::NoWrap);
}

void SCgContentStringDialog::contentInfo(SCgContent::ContInfo &info)
{
    if (!mTextEdit->toPlainText().isEmpty()) {
        info.data       =   QVariant(mTextEdit->toPlainText());
        info.mimeType   =   QString("content/term");
        info.fileName   =   QString("");
        info.type       =   SCgContent::String;
    }
    else info.setEmpty();
}

// ------------------------------
SCgContentViewer* SCgContentStringFactory::createViewerInstance()
{
    return new SCgContentStringViewer();
}

SCgContentDialog* SCgContentStringFactory::createDialogInstance(SCgNode *node)
{
    return new SCgContentStringDialog(node);
}

QMap<QString, SCgContentFactory::MimeAndSCgTypes> SCgContentStringFactory::supportedExtentions() {
    QMap<QString, MimeAndSCgTypes> ext;
    ext["txt"] = qMakePair(QString("text/plain"), SCgContent::String);

    return ext;
}
