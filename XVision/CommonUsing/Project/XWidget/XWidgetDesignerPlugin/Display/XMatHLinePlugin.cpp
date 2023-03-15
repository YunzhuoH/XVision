#include "XMatHLinePlugin.h"
#include "XMatHLine.h"

XMatHLinePlugin::XMatHLinePlugin(QObject *parent): QObject(parent = nullptr) {}

QIcon XMatHLinePlugin::icon() const
{
  return QIcon(":/images/XMatHLine.png");
}

QString XMatHLinePlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XMatHLine\" name=\"xMatHLine\">\n"
           " </widget>\n"
           "</ui>\n";
}

QWidget* XMatHLinePlugin::createWidget(QWidget* parent) { return new XMatHLine(parent); }
