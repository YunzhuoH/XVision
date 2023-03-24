#include "XvUtils.h"
#include <QFile>


QString XvUtils::getStyleByPath(const QString &path)
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
