#include "hvstrategymanager.h"
#include <dlfcn.h>
#define LIBSTRATEGY_PATH        "/usr/lib/libstratety.so"

hvStrategyManager::hvStrategyManager(hvGlobalData& clGlobalData) :
    m_clGloBalData(clGlobalData)
{

}

hvStrategyManager::~hvStrategyManager()
{

}

void hvStrategyManager::init()
{
    //TODO: 根据strategy动态库来实现
//    hvChar *error;
//    m_pDlHandle = dlopen(LIBSTRATEGY_PATH, RTLD_LAZY);

//    if (!m_pDlHandle)
//    {
//        fprintf(stderr, "%s\n", dlerror());
//        exit(EXIT_FAILURE);
//    }

//    dlerror();    /* Clear any existing error */

//    cosine = (double (*)(double)) dlsym(handle, "cos");

//    /* According to the ISO C standard, casting between function
//    pointers and 'void *', as done above, produces undefined results.
//    POSIX.1-2003 and POSIX.1-2008 accepted this state of affairs and
//    proposed the following workaround:

//      *(void **) (&cosine) = dlsym(handle, "cos");

//    This (clumsy) cast conforms with the ISO C standard and will
//    avoid any compiler warnings.

//    The 2013 Technical Corrigendum to POSIX.1-2008 (a.k.a.
//    POSIX.1-2013) improved matters by requiring that conforming
//    implementations support casting 'void *' to a function pointer.
//    Nevertheless, some compilers (e.g., gcc with the '-pedantic'
//    option) may complain about the cast used in this program. */

//    error = dlerror();
//    if (error != NULL) {
//    fprintf(stderr, "%s\n", error);
//    exit(EXIT_FAILURE);
//    }

//    printf("%f\n", (*cosine)(2.0));
//    dlclose(handle);
//    exit(EXIT_SUCCESS);

}

void hvStrategyManager::uninit()
{
//    dlclose(m_pDlHandle);
}

const vector<HvHmiCfg> &hvStrategyManager::getConfigData()
{
    return m_clGloBalData.getConfigData();
}

hvBool hvStrategyManager::getTriggerStatus(hvString strSceneName)
{
    //TODO:调用libstrategy获取场景的触发状态
    return true;
}

hvInt hvStrategyManager::getCurrentScreenId()
{
    return 0;
    //TODO:根据libstrategy获取当前屏幕Id
}
