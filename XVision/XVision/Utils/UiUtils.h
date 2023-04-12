#ifndef UIUTILS_H
#define UIUTILS_H

#include <QtCore>
#include <QAbstractButton>
#include "XMessageBox.h"
#include "LangDef.h"
///界面工具

/// 初始化按钮
/// btn:按钮
/// text:文本
/// tip:提示
/// icon:图标
/// iconsize:图标尺寸
/// minSize:最小尺寸
/// maxSize:最大尺寸
inline static void U_initSetButton(QAbstractButton* btn,
                                   const QString &text,
                                   const QString &tip,
                                   const QIcon &icon,
                                   const int &iconsize=0,
                                   const QSize minSize=QSize(),
                                   const QSize maxSize=QSize()
                                   )
{
    btn->setText(text);
    btn->setToolTip(tip);
    btn->setIcon(icon);
    if(iconsize>0)
    {
      btn->setIconSize(QSize(iconsize,iconsize));
    }
    if(minSize.isValid())
    {
        btn->setMinimumSize(minSize);
    }
    if(maxSize.isValid())
    {
        btn->setMaximumSize(maxSize);
    }

}
///获取XMessageBox消息盒按钮文本
/// lst：按钮类型列表
inline static QMap<XMessageBox::StandardButton,QString> U_getXMessageBoxButtonTexts(const QList<XMessageBox::StandardButton> &lst)
{
    QMap<XMessageBox::StandardButton,QString> map;

    foreach (auto btnType, lst)
    {
        switch (btnType)
        {
        case XMessageBox::StandardButton::Ok:
            map[XMessageBox::StandardButton::Ok]=getLang(App_UiCommon_Confirm,"确定");
            break;
        case XMessageBox::StandardButton::Save:
            map[XMessageBox::StandardButton::Save]=getLang(App_UiCommon_Save,"保存");
            break;
        case XMessageBox::StandardButton::SaveAll:
            map[XMessageBox::StandardButton::SaveAll]=getLang(App_UiCommon_SaveAll,"保存所有");
            break;
        case XMessageBox::StandardButton::Open :
            map[XMessageBox::StandardButton::Open]=getLang(App_UiCommon_Open,"打开");
            break;
        case XMessageBox::StandardButton::Yes:
            map[XMessageBox::StandardButton::Yes]=getLang(App_UiCommon_Yes,"是");
            break;
        case XMessageBox::StandardButton::YesToAll:
            map[XMessageBox::StandardButton::YesToAll]=getLang(App_UiCommon_YesToAll,"全是");
            break;
        case XMessageBox::StandardButton::No:
            map[XMessageBox::StandardButton::No]=getLang(App_UiCommon_No,"否");
            break;
        case XMessageBox::StandardButton::NoToAll:
            map[XMessageBox::StandardButton::NoToAll]=getLang(App_UiCommon_No,"全否");
            break;
        case XMessageBox::StandardButton::Abort:
            map[XMessageBox::StandardButton::Abort]=getLang(App_UiCommon_Abort,"中断");
            break;
        case XMessageBox::StandardButton::Retry:
            map[XMessageBox::StandardButton::Retry]=getLang(App_UiCommon_Retry,"重试");
            break;
        case XMessageBox::StandardButton::Ignore:
            map[XMessageBox::StandardButton::Ignore]=getLang(App_UiCommon_Ignore,"忽略");
            break;
        case XMessageBox::StandardButton::Close:
            map[XMessageBox::StandardButton::Close]=getLang(App_UiCommon_Close,"关闭");
            break;
        case XMessageBox::StandardButton::Cancel:
            map[XMessageBox::StandardButton::Ok]=getLang(App_UiCommon_Cancel,"取消");
            break;
        case XMessageBox::StandardButton::Discard:
            map[XMessageBox::StandardButton::Ok]=getLang(App_UiCommon_Discard,"废弃");
            break;
        case XMessageBox::StandardButton::Help:
            map[XMessageBox::StandardButton::Help]=getLang(App_UiCommon_Help,"帮助");
            break;
        case XMessageBox::StandardButton::Apply:
            map[XMessageBox::StandardButton::Apply]=getLang(App_UiCommon_Apply,"应用");
            break;
        case XMessageBox::StandardButton::Reset:
            map[XMessageBox::StandardButton::Reset]=getLang(App_UiCommon_Reset,"重置");
            break;
        case XMessageBox::StandardButton::RestoreDefaults:
            map[XMessageBox::StandardButton::RestoreDefaults]=getLang(App_UiCommon_RestoreDefaults,"恢复默认");
            break;
        }
    }
    return map;
}
#endif // UIUTILS_H
