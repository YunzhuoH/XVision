#include "XLanguage.h"
#include <QMutexLocker>
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QApplication>
#include <QDomDocument>

///简体中文
#define CN_S    "cn_s"
///繁体中文
#define CN_T    "cn_t"
///英语
#define ENG     "eng"

///语言xml目录
#define LANG_DIR "Language"
///iniGroup
#define LANGUAGE "Language"
///类型TagName
#define TYPE "Type"
/// 名称TagName
#define NAME "Name"

class XLanguagePrivate
{
public:
    XLanguagePrivate(XLanguage *q):q_ptr(q){}
    ~XLanguagePrivate(){};
    ///加载语言XML
    bool loadLangXml(const QString &path,const QString &type,const QString &name)
    {
        QFile file(path);
        file.open(QFile::ReadWrite | QFile::Text);
        m_dom.clear();
        m_dom.setContent(&file, false);
        file.close();
        m_root = m_dom.documentElement();
        if(m_root.isNull())
        {
           m_root= m_dom.createElement(LANGUAGE);
           m_root.setAttribute(TYPE,type);
           m_root.setAttribute(NAME,name);
           m_dom.appendChild(m_root);
        }
        m_strLoadPath=path;
        m_mapLang.clear();
        getLangMap(m_root,"",m_mapLang);
        return true;
    }
    ///保存XML语言文件
    bool saveLangXml()
    {       
        qSetGlobalQHashSeed(0);
        QFile file(m_strLoadPath);
        file.open(QFile::WriteOnly|QFile::Truncate | QFile::Text);
        QTextStream stream( &file );
        stream.setEncoding(QStringConverter::Utf8);
        m_dom.save(stream,4,QDomNode::EncodingFromTextStream);
        file.close();
        qSetGlobalQHashSeed(-1);
        return true;
    }
    ///获取语言键值对
    void getLangMap(QDomElement &ele,const QString tagName,QMap<QString,QString> &map)
    {
        auto eleList=ele.childNodes();
        if(eleList.count()==0)
        {
            QString strTempTag="";
            if (tagName != "")
            {
                strTempTag = tagName;
            }
            else
            {
                strTempTag = ele.tagName();
            }
            QString val=ele.text();
            map.insert(strTempTag,"");
        }
        else
        {
            for (int i = 0; i < eleList.count(); ++i)
            {
                auto e=eleList.at(i).toElement();
                auto lst0 = e.childNodes();
                if (lst0.count() == 0)
                {
                    QString strTempTag = "";
                    if (tagName != "")
                    {
                        strTempTag = tagName;
                    }
                    else
                    {
                        strTempTag = e.tagName();
                    }
                    QString val=ele.text();
                    map.insert(strTempTag,val);
                    continue;
                }
                else
                {
                    QString strTempTag = "";
                    if (tagName != "")
                    {
                       strTempTag = tagName + "_" + e.tagName();
                    }
                    else
                    {
                       strTempTag = e.tagName();
                    }
                    getLangMap(e, strTempTag, map);
                }
            }
        }
    }
    ///获取语言
    QString getLang(const QString &key)
    {
        if(m_mapLang.contains(key))
        {
            return m_mapLang[key];
        }
        else
        {
            return "";
        }
    }
    ///设置语言
    void setLang(const QString &key,const QString &lang)
    {
        m_mapLang[key]=lang;
        auto keys= key.split("_");
        QDomElement curEle=m_root;
        foreach (auto k, keys)
        {
            auto tempEle=curEle.firstChildElement(k);
            if(tempEle.isNull())
            {
                auto xel = m_dom.createElement(k);
                curEle.appendChild(xel);

                curEle = xel;
            }
            else
            {
                curEle=tempEle;
            }
        }
        if(curEle.hasChildNodes())
        {
            auto lst=curEle.childNodes();
            for (int i = 0; i < lst.count(); ++i)
            {
                auto child=lst.at(i);
                curEle.removeChild(child);
            }
        }
        curEle.appendChild(m_dom.createTextNode(lang));
    }

    ///获取语言XML文件类型和名称
    bool getLangTypeName(const QString &path, QString &type, QString &name)
    {
        QFile file(path);
        file.open(QFile::ReadWrite | QFile::Text);
        QDomDocument dom;
        dom.setContent(&file, false);
        file.close();
        QDomElement root = dom.documentElement();
        if(root.isNull())
        {
           return false;
        }
        else
        {
            type=root.attribute(TYPE);
            name=root.attribute(NAME);
            return true;
        }
    }
protected:
    XLanguage                      *const q_ptr;
    QDomDocument    m_dom;
    QDomElement     m_root;
    QString m_strLoadPath="";
    QMap<QString,QString> m_mapLang;

};

XLanguage::XLanguage()
    :d_ptr(new XLanguagePrivate(this))
{

}

XLanguage *XLanguage::s_Instance = NULL;
XLanguage *XLanguage::getInstance() {
  if (!s_Instance) {
    static QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new XLanguage();
    }
  }
  return s_Instance;
}

void XLanguage::init()
{
   Q_D(XLanguage);
   if(m_bIsInit) return;
   ///读取ini语言配置
   QString curAppPath= qApp->applicationDirPath();
   QString configPath=curAppPath+"/Language.ini";
   QSettings ini(configPath, QSettings::IniFormat);
   QString curLangType;//当前语言类型
   QString curLangName;//当前语言名称
   ini.beginGroup(LANGUAGE);
   curLangType= ini.value(TYPE).toString();
   curLangName=ini.value(NAME).toString();
   if(curLangType.isEmpty())
   {
      ini.setValue(TYPE,CN_S);
      ini.setValue(NAME,"简体中文");
      curLangType=CN_S;
      curLangName="简体中文";
   }
   ini.endGroup();
   ///读取XML文件语言映射
   /// 1.不存在创建目录
   /// 2.不存在创建文件
   /// 3.读取多语言到字典
   QString langPath=curAppPath+"/"+LANG_DIR;
   QDir langDir(langPath);
   if(!langDir.exists())
   {
      langDir.mkdir(langPath);
   }
   QString curLangFile=langPath+"/"+curLangType+".xml";
   d->loadLangXml(curLangFile,curLangType,curLangName);
   m_strCurType=curLangType;
   m_bIsInit=true;
}

void XLanguage::uninit()
{
    if(!m_bIsInit) return;
    Q_D(XLanguage);
    if(m_bNeedSave)
    {
       d->saveLangXml();
    }
    m_bIsInit=false;
}

QMap<QString, QString> XLanguage::getLangTypes()
{
    Q_D(XLanguage);
    QMap<QString,QString> map;
    QString curAppPath= qApp->applicationDirPath();
    QString langDir=curAppPath+"/"+LANG_DIR;
    QDir dir(langDir);
    auto fileList=dir.entryInfoList(QDir::Files);
    foreach (auto file, fileList)
    {
        QString type,name;
        if(d->getLangTypeName(file.filePath(),type,name))
        {
            map.insert(type,name);
        }

    }
    return map;
}

QString XLanguage::getCurLangType() const
{
    return m_strCurType;
}

QString XLanguage::getLang(const QString &key, QString defLang)
{  
    Q_D(XLanguage);
    if(!m_bIsInit)
    {
       init();
    }

    QString lang=d->getLang(key);
    if(!lang.isEmpty())
    {
        return lang;
    }
    else
    {
        d->setLang(key,defLang);
        if(!m_bNeedSave)
        {
            m_bNeedSave=true;
        }
        return defLang;
    }

}

QString XLanguage::setLang(const QString &key, QString lang)
{
    Q_D(XLanguage);
    d->setLang(key,lang);
    if(!m_bNeedSave)
    {
        m_bNeedSave=true;
    }
    return lang;
}

bool XLanguage::switchLang(const QString &type)
{
    auto map=getLangTypes();
    if(!map.contains(type))
    {
        return false;
    }
    QString curAppPath= qApp->applicationDirPath();
    QString configPath=curAppPath+"/Language.ini";
    QSettings ini(configPath, QSettings::IniFormat);
    QString curLangType=type;//当前语言类型
    QString curLangName=map[type];//当前语言名称
    ini.beginGroup(LANGUAGE);
    ini.setValue(TYPE,curLangType);
    ini.setValue(NAME,curLangName);
    ini.endGroup();
    this->uninit();
    this->init();
    return true;
}

