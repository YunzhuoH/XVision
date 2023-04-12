#include "XvCoreHelper.h"
#include "LangDef.h"

using namespace XvCore;

XvCoreHelper::XvCoreHelper()
{

}

QMap<EXvFuncRunStatus,QString>  XvCoreHelper::getRunStatusLang()
{
    QMap<EXvFuncRunStatus,QString> map;
    map[EXvFuncRunStatus::Init]=getLang(Core_XvFunc_RunStatusInit,"初始状态");
    map[EXvFuncRunStatus::Running]=getLang(Core_XvFunc_RunStatusRunning,"正在运行");
    map[EXvFuncRunStatus::Ok]=getLang(Core_XvFunc_RunStatusOk,"运行成功");
    map[EXvFuncRunStatus::Fail]=getLang(Core_XvFunc_RunStatusFail,"运行失败");
    map[EXvFuncRunStatus::Error]=getLang(Core_XvFunc_RunStatusError,"运行错误");
    return map;
}
