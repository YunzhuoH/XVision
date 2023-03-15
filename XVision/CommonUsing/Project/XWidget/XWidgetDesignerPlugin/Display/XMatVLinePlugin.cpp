#include "XMatVLinePlugin.h"
#include "XMatVLine.h"

XMatVLinePlugin::XMatVLinePlugin(QObject *parent): QObject(parent = nullptr) {}

QIcon XMatVLinePlugin::icon() const
{
  return QIcon(":/images/XMatVLine.png");
}

QString XMatVLinePlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XMatVLine\" name=\"xMatVLine\">\n"
           " </widget>\n"
           "</ui>\n";
}

QWidget* XMatVLinePlugin::createWidget(QWidget* parent) { return new XMatVLine(parent); }
