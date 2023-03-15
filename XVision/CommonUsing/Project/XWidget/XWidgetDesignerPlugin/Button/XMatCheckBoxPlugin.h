#ifndef XMATCHECKBOXPLUGIN_H
#define XMATCHECKBOXPLUGIN_H

#include <QDesignerCustomWidgetInterface>


class XMatCheckBoxPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    explicit XMatCheckBoxPlugin(QObject *parent = nullptr);

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return m_initialized; }
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override { return "XWidget-Buttons"; }
    QString includeFile() const override { return "XMatCheckBox.h"; }
    QString name() const override { return "XMatCheckBox"; }
    QString toolTip() const override { return "XMatCheckBox"; }
    QString whatsThis() const override { return "XMatCheckBox"; }
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

#endif // XMATCHECKBOXPLUGIN_H
