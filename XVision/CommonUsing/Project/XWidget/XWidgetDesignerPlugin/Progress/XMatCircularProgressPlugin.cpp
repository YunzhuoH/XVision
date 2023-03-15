#include "XMatCircularProgressPlugin.h"
#include "XMatCircularProgress.h"

XMatCircularProgressPlugin::XMatCircularProgressPlugin(QObject *parent): QObject(parent = nullptr) {}

QIcon XMatCircularProgressPlugin::icon() const
{
  return QIcon(":/images/XMatCircularProgress.png");
}

QString XMatCircularProgressPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XMatCircularProgress\" name=\"xMatCircularProgress\">\n"
           " </widget>\n"
           "</ui>\n";
}

QWidget* XMatCircularProgressPlugin::createWidget(QWidget* parent) { return new XMatCircularProgress(parent); }
