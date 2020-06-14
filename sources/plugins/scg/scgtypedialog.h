/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QDialog>
class QGroupBox;

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
     * \param objectType @see SCgObject::type()
     * \warning Object type should be valid (SCgNode::Type or SCgPair::Type),
     * otherwise no available types will be displayed.
    */
    SCgTypeSelectionDialog(int objectType, QWidget* parent = 0);

    //! \return SCg-object type; @see SCgAlphabet::initialize().
    QString getChosenType() const;

public slots:
    void onChooseType();

private:
    //! Place buttons, each representing one available type, on dialog
    void displayTypes();
    void addTypeButton(const QIcon& icon, const QString& text, int hotkey, QWidget* parent);

    const int mObjectType;

    //! If slot onChooseType() was called by one of the buttons
    //! mChosenType will contain chosen type.
    QString mChosenType;

    QGroupBox* mConstPermGroup;
    QGroupBox* mVarPermGroup;
    QGroupBox* mMetaPermGroup;
    QGroupBox* mConstTempGroup;
    QGroupBox* mVarTempGroup;
    QGroupBox* mMetaTempGroup;
    QGroupBox* mUnknownGroup;
};
