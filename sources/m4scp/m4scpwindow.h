#ifndef M4SCPWINDOW_H
#define M4SCPWINDOW_H

#include "basewindow.h"

class QTextEdit;
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

    QTextEdit *editor;
    M4SCpSyntaxHighlighter *highlighter;

};

#endif // M4SCPWINDOW_H
