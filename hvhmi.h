#ifndef HVHMI_H
#define HVHMI_H
#include "hvglobaldata.h"
#include "hvhmiconfig.h"
#include "hvstrategymanager.h"
#include "hvscreenmanager.h"
#include "hvscene.h"
#include "hvprioritymanager.h"
#include "hvTypes.h"
#include <vector>

using namespace std;

class hvHMI
{
public:
    hvHMI();
    ~hvHMI();
    void create();
    void destory();
    void init();
    void uninit();
    void run();
    void quit();

private:
    hvGlobalData * m_pclGlobalData;
    hvStrategyManager * m_pclStgManager;
    hvScreenManager * m_pclScreenMngr;
    hvPriorityManager * m_pclPriority;
    hvBool m_bRunFlag;
    vector <hvScene> m_v;
};

#endif // HVHMI_H
