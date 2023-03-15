#ifndef XMATCOMBOBOXPLUGIN_H
#define XMATCOMBOBOXPLUGIN_H

#include <QDesignerCustomWidgetInterface>


class XMatComboBoxPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    explicit XMatComboBoxPlugin(QObject *parent = nullptr);

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return m_initialized; }
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override { return "XWidget-Input"; }
    QString includeFile() const override { return "XMatComboBox.h"; }
    QString name() const override { return "XMatComboBox"; }
    QString toolTip() const override { return "XMatComboBox"; }
    QString whatsThis() const override { return "XMatComboBox"; }
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

#endif // XMATCOMBOBOXPLUGIN_H
