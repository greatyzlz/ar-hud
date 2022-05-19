#include "hvscreen.h"
#include <iostream>
#include "hvscenedeclarations.h"
#include "graphengine.h"
#include <unistd.h>

using namespace std;

hvScreen::hvScreen(const HvHmiCfg stCfg, hvStrategyManager& clStgMngr) : m_clStgMngr(clStgMngr)
{
    m_unFrameNo = 0;
    m_stScrnCfg = stCfg;

    m_mDeclareScenes = NULL;

    if (m_stScrnCfg.stScrnInfo.nScreenId < static_cast<hvInt>(g_vmScreenScenes.size()))
    {
        m_mDeclareScenes = &g_vmScreenScenes[m_stScrnCfg.stScrnInfo.nScreenId];
        initNotDeclareScenes();
    }
    else
    {
        cout << __FILE__ << ":" << __LINE__ << "->Screen: " << m_stScrnCfg.stScrnInfo.nScreenId << " scenes not declare" << endl;
    }
}

hvScreen::~hvScreen()
{

}

void hvScreen::init()
{ 
    m_clRegionMngr.init();
    m_clPriMngr.init(m_stScrnCfg.vstScenes);

    for (auto& cfg : m_stScrnCfg.vstScenes)
    {
        m_clLayerMngr.addLayer(cfg.cZone, cfg.strSceneName, cfg.nLayer);
    }

    vector <hvChar> vRgn = {'A', 'B', 'C'};

    for (auto Rgn : vRgn)
    {
        vector <LayerInfo> vstLayerInfo = m_clLayerMngr.getRegionLayer(Rgn);
        hvInt nPrevLayerNo = -1;
        VIEW_HANDLE PrevViewHandle = NULL;

        for (auto stLyrInfo : vstLayerInfo)
        {
            for (auto& cfg : m_stScrnCfg.vstScenes)
            {
                if (cfg.strSceneName == stLyrInfo.strSceneName)
                {
                    cfg.ViewHandle = NULL;
                    if (stLyrInfo.nLayerNo == nPrevLayerNo)
                    {
                        cfg.ViewHandle = PrevViewHandle;
                    }
                    else
                    {
                        cfg.ViewHandle = HASCOEngine_View_Create(0, 0,
                                                                 m_stScrnCfg.stScrnInfo.stSize.w,
                                                                 m_stScrnCfg.stScrnInfo.stSize.h,
                                                                 stLyrInfo.nLayerNo,
                                                                 VIEW2D);
                    }
                    nPrevLayerNo = stLyrInfo.nLayerNo;
                    PrevViewHandle = cfg.ViewHandle;

                    if (NULL != cfg.ViewHandle)
                    {
                        hvScene * pclScene = getScenePtr(cfg.strSceneName);
                        pclScene->setStrategyManager(&m_clStgMngr);
                        pclScene->init(cfg);
//                        cout << "HASCOEngine_View_Create " << cfg.strSceneName << " view succeed" << endl;
                    }
                    else
                    {
                        cout << "HASCOEngine_View_Create failed " << endl;
                    }
                }
            }
        }
    }
//    for (auto& cfg : m_stScrnCfg.vstScenes)
//    {
//        cfg.ViewHandle = m_ViewHandle;
//        hvScene * pclScene = getScenePtr(cfg.strSceneName);
//        pclScene->init(cfg);
    //    }
}

void hvScreen::uninit()
{

}

void hvScreen::show(void)
{
    //TODO:region manage for (auto region: region map)
    map <hvChar, RegionInfo> mstRgnInfo = m_clRegionMngr.getRegionCorrelation();

    for (auto stRgnInfo : mstRgnInfo)
    {
        if (NO_CORRELATION == stRgnInfo.second.eCorrelation)
        {
            PriorityManage(stRgnInfo.first);
        }
        else
        {
            //TODO: 当区域间相关时，根据讨论，实现区域相关后的显示
        }
    }

    m_unFrameNo++;
}

void hvScreen::update()
{
    map<hvChar, ZoneStatus> & mZoneSts = m_clPriMngr.getZoneStatusMap();

    for (auto stZnSts : mZoneSts)
    {
        hvInt nCurFunc = m_clPriMngr.getCurrentFun(stZnSts.second);

        for (auto stScene : m_stScrnCfg.vstScenes)
        {
            if (nCurFunc == stScene.nGraphicSN)
            {
                hvScene* pclScene = getScenePtr(stScene.strSceneName);
                pclScene->update();
            }
        }
    }


}

void hvScreen::hide(hvChar cZone)
{

    ZoneStatus& stZnSts = m_clPriMngr.getZoneStatus(cZone);
    hvInt nCurFunc = m_clPriMngr.getCurrentFun(stZnSts);
    hvInt nCurFuncIdx = m_clPriMngr.getIdxOfFuncTab(stZnSts.vstFuncTab, nCurFunc);

    if ((nCurFuncIdx < static_cast<hvInt>(stZnSts.vstFuncTab.size())) &&
         (nCurFuncIdx != -1))
    {
        hvScene* pclScene = getScenePtr(stZnSts.vstFuncTab[nCurFuncIdx].strName);

        pclScene->hide();
        m_clPriMngr.changeStatus(stZnSts, SHOW_END, nCurFunc);
    }

}

void hvScreen::hideAll()
{
    map<hvChar, ZoneStatus> & mZoneSts = m_clPriMngr.getZoneStatusMap();

    for (auto stZnSts : mZoneSts)
    {
        hide(stZnSts.first);
    }
}
//#define LAYER
//#define SWITCH
#define FCW
hvBool hvScreen::trigeredScene(hvInt nSceneId)
{
    hvBool bRet = false;
#ifdef LAYER
    if ((0 == nSceneId) || (1 == nSceneId))
    {
        bRet = true;
    }
#elif defined (SWITCH)
    static hvInt nScn = 0;
    if (m_unFrameNo % 1000 < 500)
    {
        nScn = 0;
    }
    else if (m_unFrameNo % 1000 >= 500)
    {
        nScn = 1;
    }
    else
    {
        ;
    }

    if (nSceneId == nScn)
        bRet = true;
#elif defined (FCW)
    if (nSceneId == 2)
    {
        bRet = true;
    }
#endif
    return bRet;
    //TODO:call stratagy manager to return scene trigger status
//    return m_clStgMngr.getTriggerStatus(strSceneName);
}

hvScene *hvScreen::getScenePtr(hvString strScnName)
{
    hvScene * pclScene = NULL;
    map<hvString, hvScene *>::iterator itScene = m_mDeclareScenes->find(strScnName);

    if (itScene != m_mDeclareScenes->end())
    {
        pclScene = itScene->second;
    }
    else
    {
        pclScene = m_mNotDeclareScenes[strScnName];
    }

    return pclScene;
}

void hvScreen::initNotDeclareScenes()
{
    for (auto cfg : m_stScrnCfg.vstScenes)
    {
//        cout << __FUNCTION__ << ":" << __LINE__ << ":" << cfg.strSceneName << endl;
        map<hvString, hvScene *>::iterator itScene = m_mDeclareScenes->find(cfg.strSceneName);

        if (itScene == m_mDeclareScenes->end())
        {
            m_mNotDeclareScenes.insert(make_pair(cfg.strSceneName, new hvScene));
        }
    }
}

void hvScreen::PriorityManage(hvChar Region)
{
    hvInt nCurFuncSN = -1;
    hvInt nHighPriSN = -1;
    hvInt nCheckRet = 0;

    ZoneStatus& stZnShowStatus = m_clPriMngr.getZoneStatus(Region);

    for (ProjFuncInfo stFuncInfo : stZnShowStatus.vstFuncTab)
    {
        m_clPriMngr.resetFuncStatus(stZnShowStatus);
        nCurFuncSN = m_clPriMngr.getCurrentFun(stZnShowStatus);
        hvScene * pclScene = getScenePtr(stFuncInfo.strName);

        if (trigeredScene(stFuncInfo.nFuncSN))
        {
            nCheckRet = m_clPriMngr.checkFree(stZnShowStatus, stFuncInfo.nFuncSN);
            nHighPriSN = m_clPriMngr.getHighPriorityFun(stZnShowStatus);

            if (nCheckRet < 0)
            {
                if (nCurFuncSN == stFuncInfo.nFuncSN)
                {
                    cout << "[" << stFuncInfo.strName << "]: <Id-" << m_unFrameNo << "> this zone is busy! Waiting other function [" \
                         << nHighPriSN << "] to exit" << endl;
                }
            }
            else if (2 == nCheckRet)
            {
                pclScene->hide();

                m_clPriMngr.changeStatus(stZnShowStatus, SHOW_END, Region);
                cout << "[" << stFuncInfo.strName << "]: <Id-" << m_unFrameNo << "> HighPriFunc = " \
                     << nCurFuncSN << " this func start to destory !" << endl;
            }
            else //nCheckRet == 0,1
            {
                if (0 == nCheckRet)
                {
                    cout << "[" << stFuncInfo.strName << "]: <Id-" << m_unFrameNo << "> is first showing !" << endl;
                }
                else
                {
                    if (m_unFrameNo % 50 == 0)
                    {
                        cout << "[" << stFuncInfo.strName << "]: <Id-" << m_unFrameNo << "> is showing !" << endl;
                    }
                }

                pclScene->show();

            }
        }
        else
        {
            if (nCurFuncSN == stFuncInfo.nFuncSN)
            {
                pclScene->hide();
                m_clPriMngr.changeStatus(stZnShowStatus, SHOW_END, stFuncInfo.nFuncSN);
                cout << "[" << stFuncInfo.strName << "]: <Id-" << m_unFrameNo << "> HighPriFunc = " \
                     << nCurFuncSN << " this func start to destory !" << endl;
            }
        }
    }
}
