/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include <QObject>
#include <QMap>
#include <QVariant>
#include <QColor>

// Defines to make work with values more simple
#define scg_config  SCgConfig::getInstance()
#define scg_cfg_get_value(key)          scg_config->value(key)
#define scg_cfg_set_value(key, value)   scg_config->setValue(key, QVariant(value))

#define scg_cfg_set_value_color(key, value) scg_cfg_set_value(key, scg_config->color2string(value))

#define scg_cfg_get_value_string(key)       scg_cfg_get_value(key).toString()
#define scg_cfg_get_value_color(key)        scg_config->string2color(scg_cfg_get_value_string(key))

// --- default values ---
#define scg_cfg_get_default_value(key)          scg_config->defaultValue(key)
#define scg_cfg_set_default_value(key, value)   scg_config->setDefaultValue(key, QVariant(value))

#define scg_cfg_set_default_value_color(key, value) scg_cfg_set_default_value(key, scg_config->color2string(value))

#define scg_cfg_get_default_string(key)         scg_cfg_get_default_value(key).toString()
#define scg_cfg_get_default_color(key)          scg_config->string2color(scg_cfg_get_default_string(key))


// predefined keys
#define scg_key_element_color_normal QString("element/color/normal")
#define scg_key_element_color_selected QString("element/color/selected")
#define scg_key_element_color_highlight QString("element/color/highlight")
#define scg_text_element_color_normal QString("text/color/normal")
#define scg_text_element_color_selected QString("text/color/selected")
#define scg_text_element_color_highlight QString("text/color/highlight")

class SCgConfig : public QObject
{
    Q_OBJECT
public:
    explicit SCgConfig(QObject *parent = 0);
    virtual ~SCgConfig();

    static SCgConfig* getInstance();
    static void Destroy();

    /*! Set option value
      * @param option Option name. Use '/' to make hiararchy storage. Example 'color/element/normal'.
      * @param value Option value.
      */
    void setValue(const QString &option, const QVariant &value);

    /*! Get option value
      * @param option Option name.
      *
      * @return return specified option value.
      */
    QVariant value(const QString &option) const;

    /*! Check if option exists
      * @param option Option name.
      *
      * @return If option with specified name exists, then return true, else - return false.
      */
    bool haveValue(const QString &option) const;


    /*! Set default option value
      * @param option Option name.
      * @param value Option value.

      * @see SCgConfig::setValue
      */
    void setDefaultValue(const QString &option, const QVariant &value);

    /*! Get default option value
      * @param option Option name.
      *
      * @return return default value for specified option
      */
    QVariant defaultValue(const QString &option) const;

    /*! Check if default value for  option exists
      * @param option Option name.
      *
      * @return If default value for option exists, then return true, else - return false.
      */
    bool haveDefaultValue(const QString &option) const;

    /*! Represent QColor to QString
      * @param color Color to represent as string
      * @return return color represented as string
      */
    QString color2string(const QColor &color) const;
    /*! Build QColor from string representation
      * @param str String that contatins color.
      * @return Color made from string representation.
      */
    QColor string2color(const QString &str) const;

private:
    static SCgConfig *mInstance;

    //! Options value map
    QMap<QString, QVariant> mValues;
    //! Default values
    QMap<QString, QVariant> mDefaultValues;

protected:
    //! Initialize configuration
    void initialize();
    //! Initialize default values
    void initializeDefault();

    //! Read values from configuration storage
    void readConfiguration();
    //! Save configuration to storage
    void saveConfiguration();

signals:

public slots:

};


