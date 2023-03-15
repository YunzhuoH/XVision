#include "XMatLabelPlugin.h"
#include "XMatLabel.h"

XMatLabelPlugin::XMatLabelPlugin(QObject *parent): QObject(parent = nullptr) {}

QIcon XMatLabelPlugin::icon() const
{
  return QIcon(":/images/XMatLabel.png");
}

QString XMatLabelPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XMatLabel\" name=\"xMatLabel\">\n"
           " </widget>\n"
           "</ui>\n";
}

QWidget* XMatLabelPlugin::createWidget(QWidget* parent) { return new XMatLabel(parent); }
