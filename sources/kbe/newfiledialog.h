/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QDialog>

class QListWidget;

/*!
 * New File dialog window.
 */
class NewFileDialog : public QDialog
{
    Q_OBJECT

    /* Available payloads for QListWidgetItem */
    enum Payload
    {
        EditorTypeRole = 0
    };
public:
    explicit NewFileDialog(QWidget *parent = 0);
    virtual ~NewFileDialog();

    /*!
     * \return Format currently selected by the user
     */
    QString selectedEditor() const;
signals:
    
public slots:

private:
    //! Holds items avaliable for user to select.
    QListWidget *mAvailableTypesList;
};


