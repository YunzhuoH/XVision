#include "XvSingleApplication.h"
#include "XvCoreMgr.h"
#include <XLogger>
#include "LangDef.h"
#include "AppMainWindow.h"

#ifdef QBREAKPAD_ENABLE
#include "QBreakpadHandler.h"
#endif

const SingleApplication::Options opts = SingleApplication::ExcludeAppPath | SingleApplication::ExcludeAppVersion | SingleApplication::SecondaryNotification;


static QString getStyleByPath(const QString &path)
{
    QString qss;
    QFile file(path);
    if (file.open(QFile::ReadOnly))
    {
        qss.append(file.readAll());
    }
    file.close();
    return qss;
}

XvSingleApplication::XvSingleApplication(int &argc, char **argv)
: SingleApplication(argc, argv, false, opts)
{

}

bool XvSingleApplication::init()
{
    this->setStyleSheet(getStyleByPath(":/style/Light_Default.css"));

#ifdef QBREAKPAD_ENABLE
    QBreakpadInstance.setDumpPath("Crash");
#endif

    XLang->init();
    XLog->init();
    Log_Event(getLang(APP_RUNSTART,"软件开始运行"));
    XvCore->init();

    m_appMainWindow=new AppMainWindow();
    return true;
}

bool XvSingleApplication::uninit()
{
    XvCore->uninit();
    Log_Event(getLang(APP_RUNEND,"软件运行结束"));
    XLang->uninit();
    return true;
}

int XvSingleApplication::run()
{
    m_appMainWindow->showMaximized();
    return this->exec();
}
