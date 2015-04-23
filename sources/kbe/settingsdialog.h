/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QDialog>

class QTabWidget;
class QDialogButtonBox;

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget * parent);
    ~SettingsDialog();

    void initialize();

private:
    /// Create general tab widget
    void createGeneralTab();

private:
    /// Pointer to dialog box with buttons ok, cancel
    QDialogButtonBox * mButtonBox;
    /// Pointer to tab widget tha tcontains widgets for plugins
    QTabWidget * mTabWidget;
    /// Pointer to tab widget with general configuration
    QWidget * mGeneralTab;
};


