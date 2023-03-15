#include "XMatToolButtonPlugin.h"
#include "XMatToolButton.h"

XMatToolButtonPlugin::XMatToolButtonPlugin(QObject *parent): QObject(parent = nullptr) {}

QIcon XMatToolButtonPlugin::icon() const
{
  return QIcon(":/images/XMatToolButton.png");
}

QString XMatToolButtonPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XMatToolButton\" name=\"xMatToolButton\">\n"
           " </widget>\n"
           "</ui>\n";
}

QWidget* XMatToolButtonPlugin::createWidget(QWidget* parent) { return new XMatToolButton(parent); }
