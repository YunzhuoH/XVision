#ifndef XMATSPINBOXPLUGIN_H
#define XMATSPINBOXPLUGIN_H

#include <QDesignerCustomWidgetInterface>


class XMatSpinBoxPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    explicit XMatSpinBoxPlugin(QObject *parent = nullptr);

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return m_initialized; }
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override { return "XWidget-Input"; }
    QString includeFile() const override { return "XMatSpinBox.h"; }
    QString name() const override { return "XMatSpinBox"; }
    QString toolTip() const override { return "XMatSpinBox"; }
    QString whatsThis() const override { return "XMatSpinBox"; }
    QWidget* createWidget(QWidget* parent) override;
    void initialize(QDesignerFormEditorInterface* core) override
    {
        if (m_initialized)
            return;
        m_initialized = true;
    }


private:
    bool m_initialized = false;
};

#endif // XMATSPINBOXPLUGIN_H
