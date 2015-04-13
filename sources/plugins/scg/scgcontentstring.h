/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "scgcontentdialog.h"
#include "scgcontentfactory.h"
#include "scgcontentviewer.h"

class SCgNode;
class QLabel;
class QTextEdit;
class QCheckBox;

class SCgContentStringViewer : public SCgContentViewer
{
Q_OBJECT

public:
    explicit SCgContentStringViewer(QGraphicsItem *parent = 0);
    virtual ~SCgContentStringViewer();

protected:

    void setData(const QVariant &data);

    //! Widget to show text
    QLabel *mTextLabel;

};

// ---------------------------------------------------
class SCgContentStringDialog : public SCgContentDialog
{
Q_OBJECT

public:
    explicit SCgContentStringDialog(SCgNode *node, QWidget *parent = 0);
    virtual ~SCgContentStringDialog(){}

protected:
    void apply();

    //! @see    SCgContentDialog::contentInfo()
    void contentInfo(SCgContent::ContInfo &info);

private:
    //! Text edit area
    QCheckBox *mWrapCheckBox;
    QTextEdit *mTextEdit;

public slots:
	void setWordWrap(bool isWordWrap);

};

// ---------------------------------------------------
class SCgContentStringFactory : public SCgContentFactory
{
public:
    virtual ~SCgContentStringFactory(){}
    SCgContentViewer* createViewerInstance();
    SCgContentDialog* createDialogInstance(SCgNode *node);

    QMap<QString, MimeAndSCgTypes> supportedExtentions();
};


