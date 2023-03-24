#include "XWidgetPlugins.h"
/*[Button]*/
#include "XMatFlatButtonPlugin.h"
#include "XMatRaisedButtonPlugin.h"
#include "XMatToolButtonPlugin.h"
#include "XMatCheckBoxPlugin.h"
#include "XMatRadioButtonPlugin.h"
#include "XMatTogglePlugin.h"
/*[Input]*/
#include "XMatLineEditPlugin.h"
#include "XMatPlainTextEditPlugin.h"
#include "XMatComboBoxPlugin.h"
#include "XMatSliderPlugin.h"
#include "XMatSpinBoxPlugin.h"
#include "XMatDoubleSpinBoxPlugin.h"
/*[Display]*/
#include "XMatLabelPlugin.h"
#include "XMatVLinePlugin.h"
#include "XMatHLinePlugin.h"
/*[Progress]*/
#include "XMatCircularProgressPlugin.h"
#include "XMatProgressPlugin.h"


struct XWidgetPlugins::Impl
{
    QList<QDesignerCustomWidgetInterface*> widgets;
};

XWidgetPlugins::XWidgetPlugins(QObject* parent /*= 0*/) : QObject(parent), m_impl(std::make_unique<Impl>())
{
    m_impl->widgets.push_back(new XMatFlatButtonPlugin(this));
    m_impl->widgets.push_back(new XMatRaisedButtonPlugin(this));
    m_impl->widgets.push_back(new XMatToolButtonPlugin(this));
    m_impl->widgets.push_back(new XMatTogglePlugin(this));  
    m_impl->widgets.push_back(new XMatCheckBoxPlugin(this));
    m_impl->widgets.push_back(new XMatRadioButtonPlugin(this));

    m_impl->widgets.push_back(new XMatLineEditPlugin(this));
    m_impl->widgets.push_back(new XMatPlainTextEditPlugin(this));
    m_impl->widgets.push_back(new XMatComboBoxPlugin(this));
    m_impl->widgets.push_back(new XMatSliderPlugin(this));
    m_impl->widgets.push_back(new XMatSpinBoxPlugin(this));
    m_impl->widgets.push_back(new XMatDoubleSpinBoxPlugin(this));


    m_impl->widgets.push_back(new XMatLabelPlugin(this));
    m_impl->widgets.push_back(new XMatVLinePlugin(this));
    m_impl->widgets.push_back(new XMatHLinePlugin(this));

    m_impl->widgets.push_back(new XMatProgressPlugin(this));
    m_impl->widgets.push_back(new XMatCircularProgressPlugin(this));

}

XWidgetPlugins::~XWidgetPlugins() {}

QList<QDesignerCustomWidgetInterface*> XWidgetPlugins::customWidgets() const { return m_impl->widgets; }
