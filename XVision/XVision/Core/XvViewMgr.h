#ifndef XVIEWMGR_H
#define XVIEWMGR_H

#include <QObject>

///界面管理器(单例)
/// 连接界面和其他管理器
/// todo:
class XvViewMgr : public QObject
{
    Q_OBJECT
public:
    explicit XvViewMgr(QObject *parent = nullptr);

signals:

};

#endif // XVIEWMGR_H
