#ifndef XMATDOUBLESPINBOXPLUGIN_H
#define XMATDOUBLESPINBOXPLUGIN_H

#include <QDesignerCustomWidgetInterface>


class XMatDoubleSpinBoxPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    explicit XMatDoubleSpinBoxPlugin(QObject *parent = nullptr);

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return m_initialized; }
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override { return "XWidget-Input"; }
    QString includeFile() const override { return "XMatDoubleSpinBox.h"; }
    QString name() const override { return "XMatDoubleSpinBox"; }
    QString toolTip() const override { return "XMatDoubleSpinBox"; }
    QString whatsThis() const override { return "XMatDoubleSpinBox"; }
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

#endif // XMATDOUBLESPINBOXPLUGIN_H
