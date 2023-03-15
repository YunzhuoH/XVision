#include "XMatFlatButtonPlugin.h"
#include "XMatFlatButton.h"

XMatFlatButtonPlugin::XMatFlatButtonPlugin(QObject *parent): QObject(parent = nullptr) {}

QIcon XMatFlatButtonPlugin::icon() const
{
  return QIcon(":/images/XMatFlatButton.png");
}

QString XMatFlatButtonPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XMatFlatButton\" name=\"xMatFlatButton\">\n"
           " </widget>\n"
           "</ui>\n";
}

QWidget* XMatFlatButtonPlugin::createWidget(QWidget* parent) { return new XMatFlatButton(parent); }
