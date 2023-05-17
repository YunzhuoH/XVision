#ifndef XFLOWGRAPHICSGLOBAL_H
#define XFLOWGRAPHICSGLOBAL_H

#include <QtGlobal>
#include <QtCore>
#include <QColor>
#include <QPainterPath>

#if defined(XFLOWGRAPHICS_LIBRARY)
#  define XFLOWGRAPHICS_PUBLIC Q_DECL_EXPORT
#else
#  define XFLOWGRAPHICS_PUBLIC Q_DECL_IMPORT
#endif

#pragma region 公共数据{

///连接区域数据
struct SConnectData
{
    SConnectData() {}
    SConnectData(const QString &_key,const QPointF &_pt,const QPainterPath &_area)
        :key(_key),pt(_pt),area(_area)
    {

    }
    ///连接点键
    QString key;
    ///连接点坐标(item坐标)
    QPointF pt;
    ///连接区域
    QPainterPath area;


};


#pragma endregion}

#endif // XFLOWGRAPHICSGLOBAL_H
