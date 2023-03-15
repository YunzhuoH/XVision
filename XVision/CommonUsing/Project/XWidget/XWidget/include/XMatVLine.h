#ifndef XMATVLINE_H
#define XMATVLINE_H

#include "XWidgetGlobal.h"
#include <QWidget>
#include <QScopedPointer>

class XMatVLinePrivate;
class XWIDGET_EXPORT XMatVLine : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(Qt::PenStyle lineStyle READ lineStyle WRITE setLineStyle)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(int lineCutLen READ lineCutLen WRITE setLineCurLen)
public:
    explicit XMatVLine(QWidget *parent = nullptr);
    ~XMatVLine();

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

   const QScopedPointer<XMatVLinePrivate> d_ptr;
private:
    Q_DISABLE_COPY(XMatVLine)
    Q_DECLARE_PRIVATE(XMatVLine)
};


#endif // XMATVLINE_H
