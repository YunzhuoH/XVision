#ifndef XMATHLINE_H
#define XMATHLINE_H

#include "XWidgetGlobal.h"
#include <QWidget>
#include <QScopedPointer>

class XMatHLinePrivate;
class XWIDGET_EXPORT XMatHLine : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(Qt::PenStyle lineStyle READ lineStyle WRITE setLineStyle)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(int lineCutLen READ lineCutLen WRITE setLineCurLen)
public:
    explicit XMatHLine(QWidget *parent = nullptr);
    ~XMatHLine();


    Qt::PenStyle lineStyle() const;
    void setLineStyle(Qt::PenStyle style);

    QColor lineColor() const;
    void setLineColor(QColor color);

    int lineWidth() const;
    void setLineWidth(int width);

    int lineCutLen() const;
    void setLineCurLen(int len);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

   const QScopedPointer<XMatHLinePrivate> d_ptr;
private:
    Q_DISABLE_COPY(XMatHLine)
    Q_DECLARE_PRIVATE(XMatHLine)
};
#endif // XMATHLINE_H
