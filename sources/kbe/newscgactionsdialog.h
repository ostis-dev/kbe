#ifndef NEWSCGACTIONSDIALOG_H
#define NEWSCGACTIONSDIALOG_H

#include <QDialog>
#include <QListWidget>

class QListWidget;

/*!
 * New File dialog window.
 */
class newscgactionsdialog : public QDialog
{
    Q_OBJECT

    /* Available payloads for QListWidgetItem */
    enum Payload
    {
        EditorTypeRole = 0
    };
public:
    explicit newscgactionsdialog(QWidget *parent = 0);
    virtual ~newscgactionsdialog();

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

#endif // NEWSCGACTIONSDIALOG_H
