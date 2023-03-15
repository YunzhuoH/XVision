#include "XMatDoubleSpinBoxPlugin.h"
#include "XMatDoubleSpinBox.h"

XMatDoubleSpinBoxPlugin::XMatDoubleSpinBoxPlugin(QObject *parent): QObject(parent = nullptr) {}

QIcon XMatDoubleSpinBoxPlugin::icon() const
{
  return QIcon(":/images/XMatDoubleSpinBox.png");
}

QString XMatDoubleSpinBoxPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XMatDoubleSpinBox\" name=\"xMatDoubleSpinBox\">\n"
           " </widget>\n"
           "</ui>\n";
}

QWidget* XMatDoubleSpinBoxPlugin::createWidget(QWidget* parent) { return new XMatDoubleSpinBox(parent); }
