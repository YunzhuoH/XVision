#include "XvSingleApplication.h"


int main(int argc, char *argv[])
{
    XvSingleApplication a(argc, argv);
    a.init();
    int nRet=a.run();
    a.uninit();
    return nRet;
 }
