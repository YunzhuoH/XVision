#include "XMatLineEditPlugin.h"
#include "XMatLineEdit.h"

XMatLineEditPlugin::XMatLineEditPlugin(QObject *parent): QObject(parent = nullptr) {}

QIcon XMatLineEditPlugin::icon() const
{
  return QIcon(":/images/XMatLineEdit.png");
}

QString XMatLineEditPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XMatLineEdit\" name=\"xMatLineEdit\">\n"
           " </widget>\n"
           "</ui>\n";
}

QWidget* XMatLineEditPlugin::createWidget(QWidget* parent) { return new XMatLineEdit(parent); }
