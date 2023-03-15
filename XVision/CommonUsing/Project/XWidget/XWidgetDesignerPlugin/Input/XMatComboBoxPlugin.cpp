#include "XMatComboBoxPlugin.h"
#include "XMatComboBox.h"

XMatComboBoxPlugin::XMatComboBoxPlugin(QObject *parent): QObject(parent = nullptr) {}

QIcon XMatComboBoxPlugin::icon() const
{
   return QIcon(":/images/XMatComboBox.png");
}

QString XMatComboBoxPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XMatComboBox\" name=\"xMatComboBox\">\n"
           " </widget>\n"
           "</ui>\n";
}

QWidget* XMatComboBoxPlugin::createWidget(QWidget* parent) { return new XMatComboBox(parent); }
