#ifndef HVPRIORITYMANAGER_H
#define HVPRIORITYMANAGER_H
#include "hvTypes.h"
#include "hvhmiconfig.h"
#include <vector>
#include <map>

enum ShowStatus
{
    SHOW_INIT = 0,
    SHOW_READY,
    SHOW_PLAY,
    SHOW_STOP,
    SHOW_END
};

struct ProjFuncInfo
{
    hvInt nFuncId;
    hvString strName;
    hvInt nFuncSN;
    hvInt nPriority;
};

struct ZoneStatus
{
    hvInt nCurFunc;
    hvInt nHiPriFunc;
    ShowStatus eShowStatus;
    hvuInt isHighPri;
    vector <ProjFuncInfo> vstFuncTab;
    hvuInt unTabSize;
    hvInt nGraphicSNMax;
};

class hvPriorityManager
{
public:
    hvPriorityManager();
    ~hvPriorityManager();
    void init(const vector <SceneInfo>& vstCfg);
    void uninit(void);
    ZoneStatus& getZoneStatus(hvChar zone);
    hvInt checkFree(ZoneStatus& stZnSts, hvInt nWaitFunc);
    hvInt changeStatus(ZoneStatus& stZnSts, ShowStatus eNewStatus, hvInt nCurFunc);
    hvInt getCurrentFun(const ZoneStatus& stZnSts);
    hvInt getHighPriorityFun(ZoneStatus& stZnSts);
    ShowStatus getCurrentFunStatus(const ZoneStatus& stZnSts);
    ShowStatus getCurrentFunStatusByName(const hvString& strName);

    void resetFuncStatus(ZoneStatus& stZnSts);

    map <hvChar, ZoneStatus>& getZoneStatusMap(void);
    hvInt getIdxOfFuncTab(const vector <ProjFuncInfo>& vstFuncTab, hvInt nGraphSN);

    static hvBool comparePriority(ProjFuncInfo lFuncInfo, ProjFuncInfo rFuncInfo);

private:
    vector <SceneInfo> m_vstHmiCfg;
    map <hvChar, ZoneStatus> m_mZoneStatus;

    hvInt getGraphicSNMax(const ZoneStatus &stZnSts);
    hvInt setFuncStatus(ZoneStatus& stZnSts, ShowStatus eStatus, hvInt nCurFunc);
    void setZoneHighPriorityFlag(ZoneStatus& stZnSts, hvInt isHighPri);

};

#endif // HVPRIORITYMANAGER_H
