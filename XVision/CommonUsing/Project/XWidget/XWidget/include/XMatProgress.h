#ifndef XMATPROGRESS_H
#define XMATPROGRESS_H

#include "XWidgetGlobal.h"
#include <QtWidgets/QProgressBar>
#include "XMatProgressDef.h"

class XMatProgressPrivate;

class XWIDGET_EXPORT XMatProgress : public QProgressBar
{
    Q_OBJECT

    Q_PROPERTY(QColor progressColor WRITE setProgressColor READ progressColor)
    Q_PROPERTY(QColor backgroundColor WRITE setProgressColor READ backgroundColor)
    Q_PROPERTY(QColor disabledColor WRITE setDisabledColor READ disabledColor)

public:
    explicit XMatProgress(QWidget *parent = 0);
    ~XMatProgress();

    void setProgressType(ProgressType type);
    ProgressType progressType() const;


    void setProgressColor(const QColor &color);
    QColor progressColor() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    const QScopedPointer<XMatProgressPrivate> d_ptr;

private:
    Q_DISABLE_COPY(XMatProgress)
    Q_DECLARE_PRIVATE(XMatProgress)
};

#endif // XMATPROGRESS_H
