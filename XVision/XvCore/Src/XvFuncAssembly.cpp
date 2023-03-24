#include "XvFuncAssembly.h"
#include <QMutexLocker>

#include "LangDef.h"
#include "XvFuncBase.h"

using namespace XvCore;

XvFuncAssembly::XvFuncAssembly(QObject *parent)
    : QObject{parent}
{
    m_mapXvFuncInfo.clear();
}


XvFuncAssembly *XvFuncAssembly::s_Instance = NULL;
XvFuncAssembly *XvFuncAssembly::getInstance() {
  if (!s_Instance) {
     QMutex s_Mutex;
    QMutexLocker locker(&s_Mutex);
    if (!s_Instance) {
      s_Instance = new XvFuncAssembly();
    }
  }
  return s_Instance;
}

bool XvFuncAssembly::registerXvFunc(XvFuncBase* func)
{
    if(func==nullptr) return false;
    if(m_mapXvFuncInfo.contains(func->VFuncRole()))
    {
        return false;
    }
    auto role=func->VFuncRole();
    auto type=func->VFuncType();
    auto name=func->VFuncName();
    auto icon=func->VFuncIcon();
    auto meta=*func->metaObject(); 
    XvFuncBaseInfo info(role,type,name,icon,meta);
    m_mapXvFuncInfo.insert(role,info);
    emit sgRegisterNewXvFunc(info);
    return true;
}

XvFuncBase *XvFuncAssembly::createNewXvFunc(QString role)
{
    if(m_mapXvFuncInfo.contains(role))
    {
        auto info=m_mapXvFuncInfo[role];
        auto objVfunc= info.meta.newInstance();
        XvFuncBase* iVFunc=qobject_cast<XvFuncBase*>(objVfunc);
        return iVFunc;
    }
    else
    {
        return nullptr;
    }
}

XvFuncBaseInfo XvFuncAssembly::getXvFuncInfo(QString role)
{
    if(m_mapXvFuncInfo.contains(role))
    {
        return m_mapXvFuncInfo[role];
    }
    else
    {
        return XvFuncBaseInfo();
    }
}

QList<XvFuncBaseInfo> XvFuncAssembly::getXvFuncInfos()
{
    QList<XvFuncBaseInfo> lst;
    foreach (auto info, m_mapXvFuncInfo)
    {
        lst.append(info);
    }
    return lst;
}


QList<XvFuncBaseInfo> XvFuncAssembly::getXvFuncInfos(const EXvFuncType &type)
{
    QList<XvFuncBaseInfo> lst;
    foreach (auto info, m_mapXvFuncInfo)
    {
        if(info.type==type)
        {
            lst.append(info);
        }
    }
    return lst;
}



QList<XvFuncTypeInfo> XvFuncAssembly::getXvFuncTypeInfos()
{
    QList<XvFuncTypeInfo> lst;
    lst.append(XvFuncTypeInfo(EXvFuncType::Null,getLang(Core_XvFuncType_Null,"无"),QPixmap(":/image/XvFuncType_Null.svg")));
    lst.append(XvFuncTypeInfo(EXvFuncType::ImageAcquisition,getLang(Core_XvFuncType_ImageAcquisition,"图像采集"),QPixmap(":/image/XvFuncType_ImageAcquisition.svg")));
    lst.append(XvFuncTypeInfo(EXvFuncType::Calibration,getLang(Core_XvFuncType_Calibration,"校正标定"),QPixmap(":/image/XvFuncType_Calibration.svg")));
    lst.append(XvFuncTypeInfo(EXvFuncType::Contraposition,getLang(Core_XvFuncType_Contraposition,"对位"),QPixmap(":/image/XvFuncType_Contraposition.svg")));
    lst.append(XvFuncTypeInfo(EXvFuncType::Location,getLang(Core_XvFuncType_Location,"定位"),QPixmap(":/image/XvFuncType_Location.svg")));
    lst.append(XvFuncTypeInfo(EXvFuncType::ImageProcessing,getLang(Core_XvFuncType_ImageProcessing,"图像处理"),QPixmap(":/image/XvFuncType_ImageProcessing.svg")));
    lst.append(XvFuncTypeInfo(EXvFuncType::Measurement,getLang(Core_XvFuncType_Measurement,"测量"),QPixmap(":/image/XvFuncType_Measurement.svg")));
    lst.append(XvFuncTypeInfo(EXvFuncType::DefectDetection,getLang(Core_XvFuncType_DefectDetection,"检测"),QPixmap(":/image/XvFuncType_DefectDetection.svg")));
    lst.append(XvFuncTypeInfo(EXvFuncType::Recognition,getLang(Core_XvFuncType_Recognition,"识别"),QPixmap(":/image/XvFuncType_Recognition.svg")));
    lst.append(XvFuncTypeInfo(EXvFuncType::Communication,getLang(Core_XvFuncType_Communication,"通讯"),QPixmap(":/image/XvFuncType_Communication.svg")));
    lst.append(XvFuncTypeInfo(EXvFuncType::MachineLearning,getLang(Core_XvFuncType_MachineLearning,"机器学习"),QPixmap(":/image/XvFuncType_MachineLearning.svg")));
    lst.append(XvFuncTypeInfo(EXvFuncType::DataProcessing,getLang(Core_XvFuncType_DataProcessing,"数据处理"),QPixmap(":/image/XvFuncType_DataProcessing.svg")));
    lst.append(XvFuncTypeInfo(EXvFuncType::Logic,getLang(Core_XvFuncType_Logic,"逻辑"),QPixmap(":/image/XvFuncType_Logic.svg")));
    lst.append(XvFuncTypeInfo(EXvFuncType::Special,getLang(Core_XvFuncType_Special,"特殊"),QPixmap(":/image/XvFuncType_Special.svg")));
    lst.append(XvFuncTypeInfo(EXvFuncType::Other,getLang(Core_XvFuncType_Other,"其他"),QPixmap(":/image/XvFuncType_Other.svg")));
    lst.append(XvFuncTypeInfo(EXvFuncType::User,getLang(Core_XvFuncType_User,"用户"),QPixmap(":/image/XvFuncType_User.svg")));
    return lst;
}

XvFuncTypeInfo XvFuncAssembly::getXvFuncTypeInfo(const EXvFuncType &type)
{
    auto lst=getXvFuncTypeInfos();
    foreach (auto info, lst)
    {
        if(info.type==type)
        {
            return info;
        }
    }
    return XvFuncTypeInfo();
}

