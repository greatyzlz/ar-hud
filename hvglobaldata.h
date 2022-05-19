#ifndef HVGLOBALDATA_H
#define HVGLOBALDATA_H
#include "hvhmiconfig.h"

#define CONFIG_PATH         "/home/bot/samba/ar-hud/hmi_config.json"

class hvGlobalData
{
public:
    hvGlobalData();
    ~hvGlobalData();
    hvBool init(void);
    void putConfigData(void);
    vector <HvHmiCfg>& getConfigData(void);
    void putMessageData(void);
    void getMessageData(void);

private:
    vector <HvHmiCfg> m_vstHMIConfig;
    hvHMIConfig m_clHmiConfig;

};

#endif // HVGLOBALDATA_H
