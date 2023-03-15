#ifndef XMATSLIDERPLUGIN_H
#define XMATSLIDERPLUGIN_H

#include <QDesignerCustomWidgetInterface>


class XMatSliderPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    explicit XMatSliderPlugin(QObject *parent = nullptr);

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return m_initialized; }
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override { return "XWidget-Input"; }
    QString includeFile() const override { return "XMatSlider.h"; }
    QString name() const override { return "XMatSlider"; }
    QString toolTip() const override { return "XMatSlider"; }
    QString whatsThis() const override { return "XMatSlider"; }
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

#endif // XMATSLIDERPLUGIN_H
