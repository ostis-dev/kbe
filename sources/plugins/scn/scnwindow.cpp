/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

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

#include "scnwindow.h"
#include "scneditorscene.h"

#include <QVBoxLayout>
#include <QGraphicsView>

SCnWindow::SCnWindow(QWidget *parent) :
    QWidget(parent),
    mIsSaved(false),
    mEditorScene(0),
    mEditorView(0)
{
    mEditorView = new QGraphicsView(this);
    mEditorScene = new SCnEditorScene();

    mEditorView->setResizeAnchor(QGraphicsView::NoAnchor);
    mEditorView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    mEditorView->setScene(mEditorScene);


    mEditorView->setCacheMode(QGraphicsView::CacheNone);//CacheBackground);
    mEditorView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    mEditorView->setRenderHint(QPainter::Antialiasing);
    mEditorView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    mEditorView->setResizeAnchor(QGraphicsView::NoAnchor);
    mEditorView->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);

    mEditorView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //mEditorView->setDragMode(QGraphicsView::RubberBandDrag);

    if (!mEditorScene->items().empty())
        mEditorView->centerOn(mEditorScene->items().first());

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mEditorView);

    setLayout(layout);
}

SCnWindow::~SCnWindow()
{

}

QWidget* SCnWindow::widget()
{
    return this;
}

QToolBar* SCnWindow::toolBar()
{
    return 0;
}

QList<QWidget*> SCnWindow::widgetsForDocks()
{
    return QList<QWidget*>();
}

bool SCnWindow::isSaved() const
{
    return mIsSaved;
}

void SCnWindow::_update()
{

}

QIcon SCnWindow::icon() const
{
    return QIcon();
}

bool SCnWindow::loadFromFile(const QString &fileName)
{
    EditorInterface::loadFromFile(fileName);

    return false;
}

bool SCnWindow::saveToFile(const QString &fileName)
{
    EditorInterface::saveToFile(fileName);

    return false;
}

QStringList SCnWindow::supportedFormatsExt() const
{
    QStringList res;
    res << "scns";
    return res;
}

QIcon SCnWindow::findIcon(const QString &iconName)
{
    return QIcon(":/media/icons/" + iconName);
}

void SCnWindow::printFile()
{

}

void SCnWindow::printPreviewFile()
{

}

void SCnWindow::exportFileToPDF(const QString &fileName)
{

}
// ---------------------
SCnWindowFactory::SCnWindowFactory(QObject *parent) :
    QObject(parent)
{

}

SCnWindowFactory::~SCnWindowFactory()
{

}

const QString& SCnWindowFactory::name() const
{
    static QString name = "scn";
    return name;
}

EditorInterface* SCnWindowFactory::createInstance()
{
    return new SCnWindow();
}

QStringList SCnWindowFactory::supportedFormatsExt()
{
    QStringList res;
    res << "scns";
    return res;
}
