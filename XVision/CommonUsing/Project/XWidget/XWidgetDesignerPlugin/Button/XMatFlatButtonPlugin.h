#ifndef XMATFLATBUTTONPLUGIN_H
#define XMATFLATBUTTONPLUGIN_H

#include <QDesignerCustomWidgetInterface>


class XMatFlatButtonPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    explicit XMatFlatButtonPlugin(QObject *parent = nullptr);

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return m_initialized; }
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override { return "XWidget-Buttons"; }
    QString includeFile() const override { return "XMatFlatButton.h"; }
    QString name() const override { return "XMatFlatButton"; }
    QString toolTip() const override { return "XMatFlatButton"; }
    QString whatsThis() const override { return "XMatFlatButton"; }
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
