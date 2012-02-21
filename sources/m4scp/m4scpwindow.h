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

#ifndef M4SCPWINDOW_H
#define M4SCPWINDOW_H

#include "../basewindow.h"

class M4SCpCodeEditor;
class M4SCpSyntaxHighlighter;
class QIcon;

class M4SCpWindow : public BaseWindow
{
public:
    explicit M4SCpWindow(const QString& _windowTitle, QWidget *parent = 0);
    ~M4SCpWindow();
    /*! Get document save state.
      @return if document haven't any changes after last save, then return true, else - false.
      */
    bool isSaved() const;


    /*! Create tool bar
      */
    void createToolBar();

    /*! Load content from file.
      @param fileName   Name of file.
      @param loader     Loader to load file.

      @note File loader will be removed automaticaly. You doesn't need to do that.

      @return If file loaded, then return true, else - false.
      */
    bool loadFromFile(const QString &fileName, AbstractFileLoader *loader);

    /*! Save content to file.
      @param fileName   Name of file.
      @param writer     Writer to save file.

      @note File writer will be removed automaticaly. You doesn't need to do that.

      @return If file saved, then return true, else - false.
      */

    bool saveToFile(const QString &fileName, AbstractFileWriter *writer);

    /*! Update window imideately
      */
    void _update();

    /*! Get icon specified for window type
      */
    QIcon icon() const;

    QIcon findIcon(const QString &iconName) const;

private:

    M4SCpCodeEditor *mEditor;
    M4SCpSyntaxHighlighter *mHighlighter;

};

#endif // M4SCPWINDOW_H
