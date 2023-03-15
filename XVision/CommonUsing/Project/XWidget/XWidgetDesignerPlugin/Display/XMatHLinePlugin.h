#ifndef XMATHLINEPLUGIN_H
#define XMATHLINEPLUGIN_H

#include <QDesignerCustomWidgetInterface>


class XMatHLinePlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    explicit XMatHLinePlugin(QObject *parent = nullptr);

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return m_initialized; }
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override { return "XWidget-Display"; }
    QString includeFile() const override { return "XMatHLine.h"; }
    QString name() const override { return "XMatHLine"; }
    QString toolTip() const override { return "XMatHLine"; }
    QString whatsThis() const override { return "XMatHLine"; }
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

#endif // XMATHLINEPLUGIN_H
