#ifndef XMATRAISEDBUTTONPLUGIN_H
#define XMATRAISEDBUTTONPLUGIN_H

#include <QDesignerCustomWidgetInterface>


class XMatRaisedButtonPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    explicit XMatRaisedButtonPlugin(QObject *parent = nullptr);

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return m_initialized; }
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override { return "XWidget-Buttons"; }
    QString includeFile() const override { return "XMatRaisedButton.h"; }
    QString name() const override { return "XMatRaisedButton"; }
    QString toolTip() const override { return "XMatRaisedButton"; }
    QString whatsThis() const override { return "XMatRaisedButton"; }
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

#endif // XMATFLATBUTTONPLUGIN_H
