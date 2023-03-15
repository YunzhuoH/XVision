#include "XvSingleApplication.h"
#include <XLogger>

int main(int argc, char *argv[])
{
    XvSingleApplication a(argc, argv);
    a.init();
    int nRet=0;
    nRet=a.run();
    a.uninit();
    return nRet;
}
