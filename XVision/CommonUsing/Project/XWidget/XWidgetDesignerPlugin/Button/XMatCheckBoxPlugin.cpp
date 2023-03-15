#include "XMatCheckBoxPlugin.h"
#include "XMatCheckBox.h"

XMatCheckBoxPlugin::XMatCheckBoxPlugin(QObject *parent): QObject(parent = nullptr) {}

QIcon XMatCheckBoxPlugin::icon() const
{
  return QIcon(":/images/XMatCheckBox.png");
}

QString XMatCheckBoxPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XMatCheckBox\" name=\"xMatCheckBox\">\n"
           " </widget>\n"
           "</ui>\n";
}

QWidget* XMatCheckBoxPlugin::createWidget(QWidget* parent) { return new XMatCheckBox(parent); }
