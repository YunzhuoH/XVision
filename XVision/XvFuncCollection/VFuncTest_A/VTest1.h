#ifndef VTEST1_H
#define VTEST1_H

#include <QObject>

class VTest1 : public QObject
{
    Q_OBJECT
public:
    explicit VTest1(QObject *parent = nullptr);

signals:

};

#endif // VTEST1_H
