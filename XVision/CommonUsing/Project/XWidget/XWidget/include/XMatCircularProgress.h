#ifndef XMATCIRCULARPROGRESS_H
#define XMATCIRCULARPROGRESS_H

#include "XWidgetGlobal.h"

#include <QtWidgets/QProgressBar>
#include "XMatProgressDef.h"

class XMatCircularProgressPrivate;

class XWIDGET_EXPORT XMatCircularProgress : public QProgressBar
{
    Q_OBJECT

    Q_PROPERTY(qreal lineWidth WRITE setLineWidth READ lineWidth)
    Q_PROPERTY(qreal size WRITE setSize READ size)
    Q_PROPERTY(QColor color WRITE setColor READ color)
    Q_PROPERTY(QColor borderColor WRITE setBorderColor READ borderColor)

public:
    explicit XMatCircularProgress(QWidget *parent = 0);
    ~XMatCircularProgress();


    void setProgressType(ProgressType type);
    ProgressType progressType() const;



    void setLineWidth(qreal width);
    qreal lineWidth() const;

    void setSize(int size);
    int size() const;

    void setColor(const QColor &color);
    QColor color() const;

    void setBorderColor(const QColor &color);
    QColor borderColor() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<XMatCircularProgressPrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatCircularProgress)
    Q_DECLARE_PRIVATE(XMatCircularProgress)
};

#endif // XMATCIRCULARPROGRESS_H
