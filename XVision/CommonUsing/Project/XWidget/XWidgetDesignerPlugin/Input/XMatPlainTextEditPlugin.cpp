#include "XMatPlainTextEditPlugin.h"
#include "XMatPlainTextEdit.h"

XMatPlainTextEditPlugin::XMatPlainTextEditPlugin(QObject *parent): QObject(parent = nullptr) {}

QIcon XMatPlainTextEditPlugin::icon() const
{
  return QIcon(":/images/XMatPlainTextEdit.png");
}

QString XMatPlainTextEditPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"XMatPlainTextEdit\" name=\"xMatPlainTextEdit\">\n"
           " </widget>\n"
           "</ui>\n";
}

QWidget* XMatPlainTextEditPlugin::createWidget(QWidget* parent) { return new XMatPlainTextEdit(parent); }
