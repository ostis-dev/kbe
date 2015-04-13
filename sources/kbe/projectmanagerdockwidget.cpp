/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "projectmanagerdockwidget.h"
#include "projectmanagerview.h"

#include <QFile>

ProjectManagerDockWidget* ProjectManagerDockWidget::mInstance = 0;

ProjectManagerDockWidget::ProjectManagerDockWidget(QWidget *parent)
    : QDockWidget(parent)
{
    mTreeView = new ProjectManagerView(this);

    this->setFeatures(QDockWidget::DockWidgetVerticalTitleBar);

    QFile file(":/media/stylesheets/projectmanager.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    mTreeView->setStyleSheet(styleSheet);

    setWidget(mTreeView);
}

ProjectManagerDockWidget::~ProjectManagerDockWidget()
{
    Q_ASSERT(mInstance != 0);
    mInstance = 0;
}

ProjectManagerDockWidget* ProjectManagerDockWidget::instance()
{
    if (!mInstance)
        mInstance = new ProjectManagerDockWidget();

    return mInstance;
}

ProjectManagerView* ProjectManagerDockWidget::getTreeView()
{
    return mTreeView;
}
