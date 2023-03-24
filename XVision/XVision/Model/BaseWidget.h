#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
#include "LangDef.h"
#include "UiUtils.h"

class BaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = nullptr);
protected:
    virtual void initFrm()=0;
signals:

};

#endif // BASEWIDGET_H
