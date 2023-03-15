#include "XMatProgressPlugin.h"
#include "XMatProgress.h"

XMatProgressPlugin::XMatProgressPlugin(QObject *parent): QObject(parent = nullptr) {}

QIcon XMatProgressPlugin::icon() const
{
  return QIcon(":/images/XMatProgress.png");
}

QString XMatProgressPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XMatProgress\" name=\"xMatProgress\">\n"
           " </widget>\n"
           "</ui>\n";
}

QWidget* XMatProgressPlugin::createWidget(QWidget* parent) { return new XMatProgress(parent); }
