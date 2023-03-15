#include "XMatSpinBoxPlugin.h"
#include "XMatSpinBox.h"

XMatSpinBoxPlugin::XMatSpinBoxPlugin(QObject *parent): QObject(parent = nullptr) {}

QIcon XMatSpinBoxPlugin::icon() const
{
  return QIcon(":/images/XMatSpinBox.png");
}

QString XMatSpinBoxPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XMatSpinBox\" name=\"xMatSpinBox\">\n"
           " </widget>\n"
           "</ui>\n";
}

QWidget* XMatSpinBoxPlugin::createWidget(QWidget* parent) { return new XMatSpinBox(parent); }
