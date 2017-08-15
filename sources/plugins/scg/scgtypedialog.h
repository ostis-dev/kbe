/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QDialog>
class QBoxLayout;

/*! \brief Dialog for selecting type of SCg-object
 *
 *  This dialog shows user all available combinations of properties (constancy, permanency, etc.)
 *  and allows to choose one by clicking on one of buttons.
 */
class SCgTypeSelectionDialog : public QDialog
{
    Q_OBJECT
public:
    /*!
     * \param objectType SCg-object type
     * \warning Object type should be valid ("node" or "pair"),
     * otherwise displayed types may not be applied to the actual object.
    */
    SCgTypeSelectionDialog(const QString& objectType, QWidget* parent = 0);

    //! \return SCg-object type; @see SCgAlphabet::initialize().
    QString getChosenType() const;

public slots:
    void onChooseType();

private:
    void addTypeButton(const QIcon& icon, const QString& text, QBoxLayout* layout);

    //! If slot onChooseType() was called by one of the buttons
    //! mChosenType will contain chosen type.
    QString mChosenType;
};
