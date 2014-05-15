/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2014 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#ifndef SCGCONTENTSTRING_H
#define SCGCONTENTSTRING_H

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

#endif // SCGCONTENTSTRING_H
