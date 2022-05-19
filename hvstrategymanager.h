#ifndef HVSTRATEGYMANAGER_H
#define HVSTRATEGYMANAGER_H
#include "hvglobaldata.h"

class hvStrategyManager
{
public:
    hvStrategyManager(hvGlobalData& clGlobalData);
    ~hvStrategyManager();
    void init();
    void uninit(void);
    const vector <HvHmiCfg>& getConfigData(void);
    hvBool getTriggerStatus(hvString strSceneName);
    hvInt getCurrentScreenId(void);

private:
    hvGlobalData& m_clGloBalData;
    void * m_pDlHandle;
};

#endif // HVSTRATEGYMANAGER_H
