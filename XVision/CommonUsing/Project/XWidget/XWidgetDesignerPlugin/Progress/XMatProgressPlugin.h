#ifndef XMATPROGRESSPLUGIN_H
#define XMATPROGRESSPLUGIN_H

#include <QDesignerCustomWidgetInterface>


class XMatProgressPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    explicit XMatProgressPlugin(QObject *parent = nullptr);

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return m_initialized; }
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override { return "XWidget-Progress"; }
    QString includeFile() const override { return "XMatProgress.h"; }
    QString name() const override { return "XMatProgress"; }
    QString toolTip() const override { return "XMatProgress"; }
    QString whatsThis() const override { return "XMatProgress"; }
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

#endif // XMATPROGRESSPLUGIN_H
