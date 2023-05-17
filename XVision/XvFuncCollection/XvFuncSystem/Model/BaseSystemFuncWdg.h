#ifndef BASESYSTEMFUNCWDG_H
#define BASESYSTEMFUNCWDG_H

#include "XFramelessWidget.h"
#include "XvFunc.h"
#include "XLanguage.h"
using namespace XvCore;

class QLabel;
class QLineEdit;
class QPlainTextEdit;
class BaseSystemFuncWdg: public XFramelessWidget
{

public:
    explicit BaseSystemFuncWdg(XvFunc *func,QWidget *parent = nullptr);
    ~BaseSystemFuncWdg();
protected:
    ///获取算子
    template<typename T>
    T *getFunc()
    {
        return dynamic_cast<T*>(m_func);
    }
protected:
    struct SBindResultTag
    {
        SBindResultTag()
        {

        }
        SBindResultTag(XvFunc* f,const QString &name):func(f),resultName(name)
        {

        }
        ///是否有效
        bool isValid()
        {
            return func&&(!resultName.isEmpty());
        }

        XvFunc* func=nullptr;
        QString resultName="";

    };

protected:
    ///添加cmb结果绑定
    /// type:数据类型
    /// canCustom:是否可自定义
    static void initCmbBindResultTag(XvFunc *func,QComboBox* cmb,const QStringList &types,const bool &canCustom=false);
    ///获取cmb结果绑定
    static bool getCmbBindResultTag(QComboBox* cmb,SBindResultTag &tag);
    ///获取cmb绑定
    static bool setCmbBindResultTag(QComboBox* cmb,const SBindResultTag &tag);
    ///通过XObject更新标签显示文本
    static void updateLbTextWithXObject(QLabel* lb,XObject* obj,const QString &suffix="");
    ///初始化布尔量QComboBox
    static void initCmbByBool(QComboBox* cmb);

    ///设置cmb绑定
    void setCmbBind(XObject* param,QComboBox* cmb);
    ///设置QComboBox控件并修改QLineEdit使能
    void setCmbWithCmbEnable(QComboBox* cmbBind,QComboBox* cmbVal, const QString &paramName);
    ///设置QComboBox控件并修改QLineEdit使能
    void setCmbWithLetEnable(QComboBox* cmbBind,QLineEdit* letVal, const QString &paramName);

    void setCmbWithPetEnable(QComboBox* cmbBind,QPlainTextEdit* letVal, const QString &paramName);

    ///初始化界面
    virtual void initFrm();
    ///初始化固定尺寸
    virtual void initFixedSize();
    ///显示事件
    void showEvent(QShowEvent *event) override;
    ///隐藏事件
    void hideEvent(QHideEvent *event) override;

protected slots:
    ///算子运行更新事件
    virtual void onFuncRunUpdate() {};
    ///显示事件响应
    virtual void onShow(){};
    ///隐藏事件响应
    virtual void onHide(){};
protected:
    XvFunc* m_func=nullptr;
    bool m_bShowing=false;//是否正在显示


};

#endif // BASESYSTEMFUNCWDG_H
