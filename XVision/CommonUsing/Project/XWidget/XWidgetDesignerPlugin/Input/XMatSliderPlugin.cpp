#include "XMatSliderPlugin.h"
#include "XMatSlider.h"

XMatSliderPlugin::XMatSliderPlugin(QObject *parent): QObject(parent = nullptr) {}

QIcon XMatSliderPlugin::icon() const
{
  return QIcon(":/images/XMatSlider.png");
}

QString XMatSliderPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XMatSlider\" name=\"xMatSlider\">\n"
           " </widget>\n"
           "</ui>\n";
}

QWidget* XMatSliderPlugin::createWidget(QWidget* parent) { return new XMatSlider(parent); }
