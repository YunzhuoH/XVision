#pragma once

#include <QDesignerCustomWidgetCollectionInterface>

#include <memory>

class XWidgetPlugins
    : public QObject
    , public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.XWidget.XWidgetPluginsCollectionInterface")
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
public:
    XWidgetPlugins(QObject* parent = 0);
    ~XWidgetPlugins();
    QList<QDesignerCustomWidgetInterface*> customWidgets() const override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
