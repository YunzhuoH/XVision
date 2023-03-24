#ifndef UIUTILS_H
#define UIUTILS_H

#include <QtCore>
#include <QAbstractButton>
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
#endif // UIUTILS_H
