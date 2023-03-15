#include "XMatTogglePlugin.h"
#include "XMatToggle.h"

XMatTogglePlugin::XMatTogglePlugin(QObject *parent): QObject(parent = nullptr) {}

QIcon XMatTogglePlugin::icon() const
{
  return QIcon(":/images/XMatToggle.png");
}

QString XMatTogglePlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XMatToggle\" name=\"xMatToggle\">\n"
           " </widget>\n"
           "</ui>\n";
}

QWidget* XMatTogglePlugin::createWidget(QWidget* parent) { return new XMatToggle(parent); }
