#ifndef XLANGUAGE_H
#define XLANGUAGE_H

#include "XLanguageGlobal.h"
#include <QMap>
#include <QString>
#include <QScopedPointer>

#define XLang XLanguage::getInstance()

class XLanguagePrivate;
class XLANGUAGE_EXPORT XLanguage
{
public:
    ///获取单例
    static XLanguage *getInstance();
private:
    XLanguage();
    static XLanguage* s_Instance;
public:
    ///语言初始化
    void init();
    ///语言反初始化
    void uninit();
public:
    ///获取所有语言类型:1-QString:类型 2-QString:名称
    QMap<QString,QString> getLangTypes();
    ///获取当前语言类型
    QString getCurLangType() const;
    ///获取语言
    QString getLang(const QString &key,QString defLang="");
    ///设置语言
    QString setLang(const QString &key,QString lang);
    ///切换语言
    bool switchLang(const QString &type);
protected:
    const QScopedPointer<XLanguagePrivate> d_ptr;
    ///是否已经初始化
    bool m_bIsInit=false;
    ///是否需要保存XML
    bool m_bNeedSave=false;
    ///当前语言类型
    QString m_strCurType="";
private:
    Q_DECLARE_PRIVATE(XLanguage)
};
static QString getLang(const QString &key,QString defLang="")
{
    return XLang->getLang(key,defLang);
}
static QString setLang(const QString &key,QString lang)
{
    return XLang->setLang(key,lang);
}

#endif // XLANGUAGE_H
