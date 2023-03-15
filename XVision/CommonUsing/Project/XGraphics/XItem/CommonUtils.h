#ifndef COMMONUTILS_H
#define COMMONUTILS_H


#include <QtCore>
#include <QPainterPath>

///生成椭圆环
inline static QPainterPath genEllipseRing(const QPointF &ptCenter,const double &rx,const double &ry,const double &thickness)
{
    double size=thickness/2;
    QPainterPath ellipseOut;//外圆
    ellipseOut.addEllipse(ptCenter,rx+size,ry+size);
    QPainterPath ellipseIn;//内圆
    ellipseIn.addEllipse(ptCenter,rx-size,ry-size);
    return ellipseOut-ellipseIn;
}
///获取射线和椭圆交点
inline static QPointF getLineEllipseCross(const QPointF &startPt,const double &angle,const QPointF &ptEllipseCenter,const double &rx,const double &ry)
{
    double a=qDegreesToRadians((double)angle);
    int R=rx*ry/sqrt(pow(rx*sin(a),2)+pow(ry*cos(a),2));
    int x=startPt.x()+R*cos(a);
    int y=startPt.y()+R*sin(a);
    return QPointF(x,y);
}

#endif // COMMONUTILS_H
