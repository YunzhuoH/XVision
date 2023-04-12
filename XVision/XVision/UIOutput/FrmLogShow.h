#ifndef FRMLOGSHOW_H
#define FRMLOGSHOW_H

#include "BaseWidget.h"

#define LOG_MAX_COUNT 200
#define UiLogShow FrmLogShow::getInstance()

namespace Ui {
class FrmLogShow;
}

class FrmLogShow : public BaseWidget
{
    Q_OBJECT
public:
    static FrmLogShow* getInstance();

private:
    explicit FrmLogShow(QWidget *parent = nullptr);
    ~FrmLogShow();
     Q_DISABLE_COPY(FrmLogShow)
protected:
    void initFrm() override;
protected slots:
    void onSignalLog(const QString &log,const XLogger::ELogType &logType);

    ///自定义菜单
    void onLogcustomContextMenuRequested(const QPoint &pos);
    ///清除日志
    void onClearLog();
    ///打开日志目录
    void onOpenLogDir();

private:
    Ui::FrmLogShow *ui;
    static FrmLogShow* s_Instance;
    QMap<XLogger::ELogType,QString> m_mapType;

};

#endif // FRMLOGSHOW_H
