#ifndef NEWSCGCONSTRACTIONSDIALOG_H
#define NEWSCGCONSTRACTIONSDIALOG_H


#include <QDialog>
#include <QListWidget>


class QListWidget;

/*!
 * New File dialog window.
 */

class newscgconstractionsdialog: public QDialog
{
    Q_OBJECT

    /* Available payloads for QListWidgetItem */
    enum Payload
    {
        EditorTypeRole = 0
    };
public:
    explicit newscgconstractionsdialog(QWidget *parent = 0);
    virtual ~newscgconstractionsdialog();

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

#endif // NEWSCGCONSTRACTIONSDIALOG_H
