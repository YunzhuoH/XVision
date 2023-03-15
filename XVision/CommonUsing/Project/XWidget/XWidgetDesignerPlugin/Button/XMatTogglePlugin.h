#ifndef XMATTOGGLEPLUGIN_H
#define XMATTOGGLEPLUGIN_H

#include <QDesignerCustomWidgetInterface>


class XMatTogglePlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    explicit XMatTogglePlugin(QObject *parent = nullptr);

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return m_initialized; }
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override { return "XWidget-Buttons"; }
    QString includeFile() const override { return "XMatToggle.h"; }
    QString name() const override { return "XMatToggle"; }
    QString toolTip() const override { return "XMatToggle"; }
    QString whatsThis() const override { return "XMatToggle"; }
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

#endif // XMATTOGGLEPLUGIN_H
