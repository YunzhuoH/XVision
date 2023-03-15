#include "XWidgetStyle.h"
#include <QApplication>
#include <QFile>

static QString getStyleByPath(const QString &path)
{
    QString qss;
    QFile file(path);
    if (file.open(QFile::ReadOnly))
    {
        qss.append(file.readAll());
    }
    file.close();
    return qss;
}


void XWidgetStyle::initStyle()
{
   qApp->setStyleSheet(getStyle());
}

QString XWidgetStyle::getStyle()
{
    return getStyleByPath(":/style/Default.css");
}
