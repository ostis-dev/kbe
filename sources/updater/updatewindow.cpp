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

#include "updatewindow.h"

#include <QTextBrowser>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

UpdateWindow::UpdateWindow(QWidget *parent) :
    QWidget(parent),
    mDescriptionBrowser(0),
    mProgressBar(0),
    mStartButton(0),
    mCancelButton(0)
{

    QVBoxLayout *layout = new QVBoxLayout(this);

    mDescriptionBrowser = new QTextBrowser(this);
    mProgressBar = new QProgressBar(this);
    mProgressBar->setTextVisible(true);

    layout->addWidget(mDescriptionBrowser);

    QHBoxLayout *hlayout = new QHBoxLayout(this);

    mStartButton = new QPushButton(tr("Start"), this);
    mCancelButton = new QPushButton(tr("Cancel"), this);
    mCancelButton->setEnabled(false);

    hlayout->addWidget(mProgressBar);
    hlayout->addWidget(mStartButton);
    hlayout->addWidget(mCancelButton);

    layout->addWidget(mProgressBar);
    layout->addLayout(hlayout);

    setLayout(layout);
}

UpdateWindow::~UpdateWindow()
{
}
