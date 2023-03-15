#ifndef XMATRADIOBUTTONPLUGIN_H
#define XMATRADIOBUTTONPLUGIN_H

#include <QDesignerCustomWidgetInterface>


class XMatRadioButtonPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    explicit XMatRadioButtonPlugin(QObject *parent = nullptr);

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return m_initialized; }
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override { return "XWidget-Buttons"; }
    QString includeFile() const override { return "XMatRadioButton.h"; }
    QString name() const override { return "XMatRadioButton"; }
    QString toolTip() const override { return "XMatRadioButton"; }
    QString whatsThis() const override { return "XMatRadioButton"; }
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

#endif // XMATRADIOBUTTONPLUGIN_H
