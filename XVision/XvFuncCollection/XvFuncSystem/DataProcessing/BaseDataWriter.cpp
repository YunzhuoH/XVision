#include "BaseDataWriter.h"
#include <QThread>
#include "BaseDataWriterWdg.h"
#include "XLogger.h"
using namespace XvCore;

BaseDataWriter::BaseDataWriter(QObject *parent)
    :XvFunc(parent)
{
    _funcRole="BaseDataWriter";
    _funcName=getLang("XvFuncSystem_BaseDataWriter_Name","基础数据写入");
    _funcType=EXvFuncType::DataProcessing;

    result=new BaseDataWriterResult();

}

BaseDataWriter::~BaseDataWriter()
{
    if(m_frm)
    {
        delete m_frm;
        m_frm=nullptr;
    }
}

void BaseDataWriter::onShowFunc()
{
    if(!m_frm)
    {
        m_frm=new BaseDataWriterWdg(this);
    }
    m_frm->show();
    m_frm->raise();
}

EXvFuncRunStatus BaseDataWriter::run()
{
    return EXvFuncRunStatus::Ok;
}

