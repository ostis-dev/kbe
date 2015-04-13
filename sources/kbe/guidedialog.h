/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QDialog>

class GuideDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GuideDialog(QWidget *parent = 0);
    virtual ~GuideDialog();
    
signals:
    
public slots:
    void showStateChanged(int state);
};
