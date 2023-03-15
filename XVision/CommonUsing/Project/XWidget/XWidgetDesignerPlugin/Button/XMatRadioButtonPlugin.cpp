#include "XMatRadioButtonPlugin.h"
#include "XMatRadioButton.h"

XMatRadioButtonPlugin::XMatRadioButtonPlugin(QObject *parent): QObject(parent = nullptr) {}

QIcon XMatRadioButtonPlugin::icon() const
{
  return QIcon(":/images/XMatRadioButton.png");
}

QString XMatRadioButtonPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XMatRadioButton\" name=\"xMatRadioButton\">\n"
           " </widget>\n"
           "</ui>\n";
}

QWidget* XMatRadioButtonPlugin::createWidget(QWidget* parent) { return new XMatRadioButton(parent); }
