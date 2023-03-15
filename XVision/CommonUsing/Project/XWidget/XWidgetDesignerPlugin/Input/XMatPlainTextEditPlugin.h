#ifndef XMATPLAINTEXTEDITPLUGIN_H
#define XMATPLAINTEXTEDITPLUGIN_H

#include <QDesignerCustomWidgetInterface>


class XMatPlainTextEditPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    explicit XMatPlainTextEditPlugin(QObject *parent = nullptr);

    bool isContainer() const override { return false; }
    bool isInitialized() const override { return m_initialized; }
    QIcon icon() const override;
    QString domXml() const override;
    QString group() const override { return "XWidget-Input"; }
    QString includeFile() const override { return "XMatPlainTextEdit.h"; }
    QString name() const override { return "XMatPlainTextEdit"; }
    QString toolTip() const override { return "XMatPlainTextEdit"; }
    QString whatsThis() const override { return "XMatPlainTextEdit"; }
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

#endif // XMATPLAINTEXTEDITPLUGIN_H
