#ifndef XMATLABELPLUGIN_H
#define XMATLABELPLUGIN_H

#include <QDesignerCustomWidgetInterface>


class XMatLabelPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    explicit XMatLabelPlugin(QObject *parent = nullptr);

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return m_initialized; }
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override { return "XWidget-Display"; }
    QString includeFile() const override { return "XMatLabel.h"; }
    QString name() const override { return "XMatLabel"; }
    QString toolTip() const override { return "XMatLabel"; }
    QString whatsThis() const override { return "XMatLabel"; }
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

#endif // XMATLABELPLUGIN_H
