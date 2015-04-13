/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "scgconfig.h"

SCgConfig* SCgConfig::mInstance = 0;

SCgConfig* SCgConfig::getInstance()
{
    if (mInstance == 0)
    {
        mInstance = new SCgConfig();
        mInstance->initialize();
    }

    return mInstance;
}

void SCgConfig::Destroy()
{
    if(mInstance)
    {
        mInstance->saveConfiguration();
        delete mInstance;
    }
    mInstance = 0;
}

SCgConfig::SCgConfig(QObject *parent) :
    QObject(parent)
{
}

SCgConfig::~SCgConfig()
{

}

void SCgConfig::initialize()
{
    initializeDefault();

    // read values from configuration storage
    readConfiguration();
}

void SCgConfig::initializeDefault()
{
    // --- elements ---
    scg_cfg_set_default_value_color(scg_key_element_color_normal, QColor(0, 0, 0));
    scg_cfg_set_default_value_color(scg_key_element_color_selected, QColor(0, 193, 43));
    scg_cfg_set_default_value_color(scg_key_element_color_highlight, QColor(255, 124, 0));

    scg_cfg_set_default_value_color(scg_text_element_color_normal, QColor(0, 64, 164));
    scg_cfg_set_default_value_color(scg_text_element_color_selected, QColor(234, 102, 244));
    scg_cfg_set_default_value_color(scg_text_element_color_highlight, QColor(155, 157, 69));

    // copy default values to current
    mValues = mDefaultValues;
}

void SCgConfig::readConfiguration()
{

}

void SCgConfig::saveConfiguration()
{

}

void SCgConfig::setValue(const QString &option, const QVariant &value)
{
    mValues[option] = value;
}

QVariant SCgConfig::value(const QString &option) const
{
    Q_ASSERT_X(mValues.find(option) != mValues.end(),
               "const QVariant& SCgConfig::optionValue(const QString &option) const",
               "Option value for option doesn't exist");
    return mValues[option];
}

bool SCgConfig::haveValue(const QString &option) const
{
    return mValues.find(option) != mValues.end();
}

void SCgConfig::setDefaultValue(const QString &option, const QVariant &value)
{
    mDefaultValues[option] = value;
}

QVariant SCgConfig::defaultValue(const QString &option) const
{
    Q_ASSERT_X(mDefaultValues.find(option) != mDefaultValues.end(),
               "QVariant SCgConfig::defaultValue(const QString &option) const",
               "Default value for option doesn't exist");
    return mDefaultValues[option];
}

bool SCgConfig::haveDefaultValue(const QString &option) const
{
    return mDefaultValues.find(option) != mDefaultValues.end();
}


QString SCgConfig::color2string(const QColor &color) const
{
    return QString("%1 %2 %3 %4").arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());
}

QColor SCgConfig::string2color(const QString &str) const
{
    QStringList strs = str.split(" ");
    Q_ASSERT_X(strs.size() == 4,
               "QColor SCgConfig::string2color(const QString &str) const",
               "Invalid string that represents color");
    return QColor(strs[0].toInt(), strs[1].toInt(), strs[2].toInt(), strs[3].toInt());
}
