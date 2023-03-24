#ifndef XMLSERIALIZABLE_H
#define XMLSERIALIZABLE_H

#include <QObject>
#include <QtXml>
#include <QVariant>
#include "XvDataGlobal.h"

#define XML_CRT_ELE XmlSerializable::createXmlElement

#define XML_ADD_ATB XmlSerializable::addAttribute
#define XML_ADD_NODE XmlSerializable::addTextNode

#define XML_GET_ATB XmlSerializable::getAttribute
#define XML_GET_NODE XmlSerializable::getTextNode

/// XML可序列化基类
/// 需要重写toXmlElement/fromXmlElement接口 实现对XML的转换
class XVDATA_EXPORT XmlSerializable
{

public:
    ///转换成XmlElement
    /// @param
    /// doc:Xml文档
    /// @return
    /// QDomElement:转换后的Xml节点
    virtual QDomElement toXmlElement(QDomDocument& doc);

    ///从XmlElement转换成当前类
    /// @param
    /// xmlEle:当前进行转换的Xml节点
    /// @return
    /// bool:是否转换成功
    virtual bool fromXmlElement(QDomElement& xmlEle);

public:
    /*================保存操作================*/
    ///创建一个Xml元素节点
    /// @param
    /// doc:Xml文档
    /// parEle:父节点
    /// tagName:节点Tag名称
    static QDomElement createXmlElement(QDomDocument &doc,QDomElement& parEle,const QString &tagName)
    {
        QDomElement xmlEle= doc.createElement(tagName);
        parEle.appendChild(xmlEle);
        return xmlEle;
    }

    ///在XML元素节点中添加一个属性
    /// @param
    /// xmlEle:需要添加的元素节点
    /// name:属性名
    /// var:属性值
    static void addAttribute(QDomElement& xmlEle,const QString &name,const QVariant &var)
    {
         xmlEle.setAttribute(name,var.toString());
    }

    ///在XML元素节点中添加一个文本子节点
    /// @param
    /// doc:Xml文档
    /// parEle:父节点
    /// name:TextNode名称
    /// var:节点值
    /// @return
    /// 添加的文本子节点
    static QDomElement addTextNode(QDomDocument &doc,QDomElement &parEle,const QString &name,const QVariant &var)
    {
        QDomElement textEle = doc.createElement(name);
        QDomText textNode = doc.createTextNode(var.toString());
        textEle.appendChild(textNode);
        parEle.appendChild(textEle);
        return textEle;
    }

    /*================读取操作================*/

    ///获取属性
    /// @param
    /// ele:需要获取属性的节点
    /// name:属性名
    /// @return
    /// template T:进行转换的泛型
    template<typename T>
    static T getAttribute(QDomElement &ele,QString name)
    {
        QVariant var=ele.attribute(name);
        return var.value<T>();
    }

    ///获取子元素节点文本
    /// @param
    /// ele:需要获取文本子节点的节点
    /// subTagName:子节点Tag名称
    /// @return
    /// template T:进行转换的泛型
    template<typename T>
    static T getTextNode(QDomElement &ele,QString subTagName)
    {
        QDomElement subEle=ele.firstChildElement(subTagName);
        QVariant var(subEle.text());
        return var.value<T>();
    }
};

#endif // XMLSERIALIZABLE_H
