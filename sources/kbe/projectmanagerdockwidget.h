/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QDockWidget>

class ProjectManagerView;

class ProjectManagerDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit ProjectManagerDockWidget(QWidget *parent = 0);
    virtual ~ProjectManagerDockWidget();

    static ProjectManagerDockWidget* instance();

    ProjectManagerView* getTreeView();
private:
    static ProjectManagerDockWidget* mInstance;

    //! Content of this widget
    ProjectManagerView *mTreeView;
};



