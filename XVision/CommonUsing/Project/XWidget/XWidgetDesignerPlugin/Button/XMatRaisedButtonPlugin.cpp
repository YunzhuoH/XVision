#include "XMatRaisedButtonPlugin.h"
#include "XMatRaisedButton.h"

XMatRaisedButtonPlugin::XMatRaisedButtonPlugin(QObject *parent): QObject(parent = nullptr) {}

QIcon XMatRaisedButtonPlugin::icon() const
{
    return QIcon(":/images/XMatRaisedButton.png");
}

QString XMatRaisedButtonPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XMatRaisedButton\" name=\"xMatRaisedButton\">\n"
           " </widget>\n"
           "</ui>\n";
}

QWidget* XMatRaisedButtonPlugin::createWidget(QWidget* parent) { return new XMatRaisedButton(parent); }
