#include "hvprioritymanager.h"
#include <iostream>
#include <algorithm>

using namespace std;

hvPriorityManager::hvPriorityManager()
{
}

hvPriorityManager::~hvPriorityManager()
{

}

void hvPriorityManager::init(const vector <SceneInfo>& vstCfg)
{
    m_vstHmiCfg = vstCfg;
    vector <ProjFuncInfo> vstFuncInfo;
    ZoneStatus stZnSts;
    map <hvChar, hvChar> cZnMap = {pair <hvChar, hvChar>('a', 'A'),
                                   pair <hvChar, hvChar>('A', 'A'),
                                   pair <hvChar, hvChar>('b', 'B'),
                                   pair <hvChar, hvChar>('B', 'B'),
                                   pair <hvChar, hvChar>('c', 'C'),
                                   pair <hvChar, hvChar>('C', 'C')};
    m_mZoneStatus = {pair<hvChar, ZoneStatus>('A', stZnSts),
                     pair<hvChar, ZoneStatus>('B', stZnSts),
                     pair<hvChar, ZoneStatus>('C', stZnSts)};

    for (auto cfg : m_vstHmiCfg)
    {
        ProjFuncInfo stFuncInfo;
//        stFuncInfo.nFuncId = nIdx;
        stFuncInfo.nFuncSN = cfg.nGraphicSN;
        stFuncInfo.strName = cfg.strSceneName;
        stFuncInfo.nPriority = cfg.nPriority;
        m_mZoneStatus[cZnMap[cfg.cZone]].vstFuncTab.push_back(stFuncInfo);
//        ++nIdx;
    }

    for (auto& ZnSts : m_mZoneStatus)
    {
        hvInt nIdx = 0;
        sort(ZnSts.second.vstFuncTab.begin(), ZnSts.second.vstFuncTab.end(), hvPriorityManager::comparePriority);
        for (auto& stFunc : ZnSts.second.vstFuncTab)
        {
            stFunc.nFuncId = nIdx;
            ++nIdx;
        }

        ZnSts.second.nGraphicSNMax = getGraphicSNMax(ZnSts.second);
        ZnSts.second.nCurFunc = ZnSts.second.nGraphicSNMax;
        ZnSts.second.isHighPri = 0;
        ZnSts.second.eShowStatus = SHOW_INIT;
        ZnSts.second.nHiPriFunc = ZnSts.second.nGraphicSNMax;
    }
//    for (map<hvChar, ZoneStatus>::iterator it = m_mZoneStatus.begin(); it != m_mZoneStatus.end(); ++it)
//    {
//        it->second.nGraphicSNMax = getGraphicSNMax(it->second);
//        it->second.nCurFunc = it->second.nGraphicSNMax;
//        it->second.isHighPri = 0;
//        it->second.eShowStatus = SHOW_INIT;
//        it->second.nHiPriFunc = it->second.nGraphicSNMax;
//    }
}

hvInt hvPriorityManager::checkFree(ZoneStatus &stZnSts, hvInt nWaitFunc)
{
    hvInt nCurFuncIdx = 0;
    hvInt nWaitFuncIdx = 0;

    if (SHOW_READY == stZnSts.eShowStatus)
    {
        setFuncStatus(stZnSts, SHOW_PLAY, nWaitFunc);
        return 0;
    }

    if (stZnSts.nCurFunc == nWaitFunc)
    {
        if (stZnSts.isHighPri)
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }

    nWaitFuncIdx = getIdxOfFuncTab(stZnSts.vstFuncTab, nWaitFunc);
    nCurFuncIdx = getIdxOfFuncTab(stZnSts.vstFuncTab, stZnSts.nCurFunc);

    if ((nWaitFuncIdx < 0) || (nCurFuncIdx < 0))
    {
        cout << "eShowStatus=" << stZnSts.eShowStatus << ", CurFunc=" << stZnSts.nHiPriFunc << ", isHighPri=" << stZnSts.isHighPri << endl;
        return -2;
    }

    if (stZnSts.vstFuncTab[nWaitFuncIdx].nPriority < stZnSts.vstFuncTab[nCurFuncIdx].nPriority)
    {
        stZnSts.isHighPri = 1;
        stZnSts.nHiPriFunc = nWaitFunc;
    }

    return -1;
}

hvInt hvPriorityManager::changeStatus(ZoneStatus &stZnSts, ShowStatus eNewStatus, hvInt nCurFunc)
{
    hvInt nRet = 0;

    if (nCurFunc != stZnSts.nCurFunc)
    {
        return -1;
    }

    setFuncStatus(stZnSts, eNewStatus, nCurFunc);

    return nRet;
}

ShowStatus hvPriorityManager::getCurrentFunStatus(const ZoneStatus &stZnSts)
{
    return stZnSts.eShowStatus;
}

void hvPriorityManager::resetFuncStatus(ZoneStatus &stZnSts)
{
    if ((SHOW_END == stZnSts.eShowStatus) || (SHOW_INIT == stZnSts.eShowStatus))
    {
        setFuncStatus(stZnSts, SHOW_READY, stZnSts.nGraphicSNMax);
    }
}

map<hvChar, ZoneStatus> &hvPriorityManager::getZoneStatusMap()
{
    return m_mZoneStatus;
}

hvInt hvPriorityManager::getCurrentFun(const ZoneStatus &stZnSts)
{
    return stZnSts.nCurFunc;
}

ZoneStatus &hvPriorityManager::getZoneStatus(hvChar zone)
{
    map <hvChar, hvChar> cZnMap = {pair <hvChar, hvChar>('a', 'A'),
                                   pair <hvChar, hvChar>('A', 'A'),
                                   pair <hvChar, hvChar>('b', 'B'),
                                   pair <hvChar, hvChar>('B', 'B'),
                                   pair <hvChar, hvChar>('c', 'C'),
                                   pair <hvChar, hvChar>('C', 'C')};

    return m_mZoneStatus[zone];
}

hvInt hvPriorityManager::getIdxOfFuncTab(const vector<ProjFuncInfo>& vstFuncTab, hvInt nGraphSN)
{
    hvInt nRet = -1;

    for (auto stFunc : vstFuncTab)
    {
        if (stFunc.nFuncSN == nGraphSN)
        {
            nRet = stFunc.nFuncId;
            break;
        }
    }

    return nRet;
}

hvBool hvPriorityManager::comparePriority(ProjFuncInfo lFuncInfo, ProjFuncInfo rFuncInfo)
{
    return lFuncInfo.nPriority < rFuncInfo.nPriority;
}

hvInt hvPriorityManager::getGraphicSNMax(const ZoneStatus &stZnSts)
{
    hvInt nRet = -1;

    for (auto Func : stZnSts.vstFuncTab)
    {
        if (Func.nFuncSN > nRet)
        {
            nRet = Func.nFuncSN;
        }
    }

    return nRet + 1;
}

hvInt hvPriorityManager::setFuncStatus(ZoneStatus &stZnSts, ShowStatus eStatus, hvInt nCurFunc)
{
    stZnSts.nCurFunc = nCurFunc;
    stZnSts.eShowStatus = eStatus;
    stZnSts.isHighPri = 0;
    stZnSts.nHiPriFunc = getGraphicSNMax(stZnSts);
    return 0;
}

void hvPriorityManager::setZoneHighPriorityFlag(ZoneStatus &stZnSts, hvInt nIsHighPri)
{
    stZnSts.isHighPri = nIsHighPri;
}

hvInt hvPriorityManager::getHighPriorityFun(ZoneStatus &stZnSts)
{
    return stZnSts.nHiPriFunc;
}
