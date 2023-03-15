#ifndef XMATLINEEDITPLUGIN_H
#define XMATLINEEDITPLUGIN_H

#include <QDesignerCustomWidgetInterface>


class XMatLineEditPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    explicit XMatLineEditPlugin(QObject *parent = nullptr);

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return m_initialized; }
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override { return "XWidget-Input"; }
    QString includeFile() const override { return "XMatLineEdit.h"; }
    QString name() const override { return "XMatLineEdit"; }
    QString toolTip() const override { return "XMatLineEdit"; }
    QString whatsThis() const override { return "XMatLineEdit"; }
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

#endif // XMATLINEEDITPLUGIN_H
