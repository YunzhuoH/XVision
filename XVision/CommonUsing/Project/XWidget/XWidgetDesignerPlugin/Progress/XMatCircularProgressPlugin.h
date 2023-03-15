#ifndef XMATCIRCULARPROGRESSPLUGIN_H
#define XMATCIRCULARPROGRESSPLUGIN_H

#include <QDesignerCustomWidgetInterface>


class XMatCircularProgressPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    explicit XMatCircularProgressPlugin(QObject *parent = nullptr);

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return m_initialized; }
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override { return "XWidget-Progress"; }
    QString includeFile() const override { return "XMatCircularProgress.h"; }
    QString name() const override { return "XMatCircularProgress"; }
    QString toolTip() const override { return "XMatCircularProgress"; }
    QString whatsThis() const override { return "XMatCircularProgress"; }
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

#endif // XMATCIRCULARPROGRESSPLUGIN_H
