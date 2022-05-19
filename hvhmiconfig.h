#ifndef HVHMICONFIG_H
#define HVHMICONFIG_H

#include <vector>
#include "hvTypes.h"
#include "graphengine.h"

using namespace std;

struct ScreenSize
{
    hvInt w;
    hvInt h;
};

struct ScreenInfo
{
    hvInt nScreenId;
    hvString strScreenName;
    ScreenSize stSize;
};

struct SceneInfo
{
    hvString strSceneName;
    hvInt nGraphicSN;
    hvChar cZone;
    hvString strResourcePath;
    vector <hvInt> nPosition;
    hvInt nPriority;
    hvInt nLayer;
    VIEW_HANDLE ViewHandle;
};

struct HvHmiCfg
{
    ScreenInfo stScrnInfo;
    vector <SceneInfo> vstScenes;
};

class hvHMIConfig
{
public:
    hvHMIConfig();
    ~hvHMIConfig();
    hvBool loadConfig(hvString strCfgPath);
    const vector <HvHmiCfg> & getConfig(void);
private:
    vector <HvHmiCfg> m_vstHMICfg;
};

#endif // HVHMICONFIG_H
