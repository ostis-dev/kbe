#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>

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
        ExtensionPayloadRole = 0
    };
public:
    /*!
     * Creates an instance of NewFileDialog with specified list of available formats \p availableFormats.
     * \param availableFormats List with extensions of available formats.
     */
    explicit NewFileDialog(const QStringList &availableTypes, QWidget *parent = 0);
    virtual ~NewFileDialog();

    /*!
     * \return Format currently selected by the user
     */
    QString selectedFormat() const;
signals:
    
public slots:

private:
    //! Holds items avaliable for user to select.
    QListWidget *mAvailableTypesList;
};

#endif // NEWFILEDIALOG_H
