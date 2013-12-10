#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

<<<<<<< HEAD
#include <QtWidgets/QDialog>
=======
#include <QDialog>
>>>>>>> bf0c1d6d3442b4bad1171f3e79d21965c3b6c417

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
<<<<<<< HEAD
        ExtensionPayloadRole = 0
    };
public:
    /*!
     * Creates an instance of NewFileDialog with specified list of available formats \p availableFormats.
     * \param availableFormats List with extensions of available formats.
     */
    explicit NewFileDialog(const QStringList &availableTypes, QWidget *parent = 0);
=======
        EditorTypeRole = 0
    };
public:
    explicit NewFileDialog(QWidget *parent = 0);
>>>>>>> bf0c1d6d3442b4bad1171f3e79d21965c3b6c417
    virtual ~NewFileDialog();

    /*!
     * \return Format currently selected by the user
     */
<<<<<<< HEAD
    QString selectedFormat() const;
=======
    QString selectedEditor() const;
>>>>>>> bf0c1d6d3442b4bad1171f3e79d21965c3b6c417
signals:
    
public slots:

private:
    //! Holds items avaliable for user to select.
    QListWidget *mAvailableTypesList;
};

#endif // NEWFILEDIALOG_H
