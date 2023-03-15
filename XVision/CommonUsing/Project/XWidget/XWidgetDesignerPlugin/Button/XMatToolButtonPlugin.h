#ifndef XMATTOOLBUTTONPLUGIN_H
#define XMATTOOLBUTTONPLUGIN_H

#include <QDesignerCustomWidgetInterface>


class XMatToolButtonPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    explicit XMatToolButtonPlugin(QObject *parent = nullptr);

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return m_initialized; }
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override { return "XWidget-Buttons"; }
    QString includeFile() const override { return "XMatToolButton.h"; }
    QString name() const override { return "XMatToolButton"; }
    QString toolTip() const override { return "XMatToolButton"; }
    QString whatsThis() const override { return "XMatToolButton"; }
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

#endif // XMATTOOLBUTTONPLUGIN_H
