#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>

#include <QLabel>
#include <QListWidget>

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
    void openNewProgram(QModelIndex index);

private:
    //! Holds items avaliable for user to select.
    QListWidget *mAvailableTypesList;
};

#endif // NEWFILEDIALOG_H
