#ifndef XMATVLINEPLUGIN_H
#define XMATVLINEPLUGIN_H

#include <QDesignerCustomWidgetInterface>


class XMatVLinePlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    explicit XMatVLinePlugin(QObject *parent = nullptr);

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return m_initialized; }
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override { return "XWidget-Display"; }
    QString includeFile() const override { return "XMatVLine.h"; }
    QString name() const override { return "XMatVLine"; }
    QString toolTip() const override { return "XMatVLine"; }
    QString whatsThis() const override { return "XMatVLine"; }
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

#endif // XMATVLINEPLUGIN_H
