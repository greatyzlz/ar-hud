#include "hvscreenmanager.h"
#include "hvglobaldata.h"
#include <iostream>

hvScreenManager::hvScreenManager(hvStrategyManager& clStgMngr):m_clStgMngr(clStgMngr)
{
    m_nCurScrnId = 0;
    m_eChangeMode = DIRECT;

}

hvScreenManager::~hvScreenManager()
{

}

void hvScreenManager::init()
{
    hvInt nScrnIdx = 0;
    vector <HvHmiCfg> vstCfg = m_clStgMngr.getConfigData();
    HASCOEngine_SystemCreate(vstCfg[m_nCurScrnId].stScrnInfo.stSize.w, vstCfg[m_nCurScrnId].stScrnInfo.stSize.h, BRUSH_TOOL);
    while (!HASCOEngine_GetTick());

    for (auto cfg : vstCfg)
    {
        m_pclScreen.push_back(new hvScreen(cfg, m_clStgMngr));
        m_pclScreen[nScrnIdx++]->init();
//        std::cout << cfg.vstScenes[0].strSceneName << endl;
    }
}

void hvScreenManager::uninit()
{
    for (hvScreen* pclScreen : m_pclScreen)
    {
        pclScreen->uninit();
        delete pclScreen;
    }
    m_pclScreen.clear();
}

void hvScreenManager::delScreen(hvInt nScnNo)
{
    hvInt nIdx = 0;

    for (vector <hvScreen*>::iterator it = m_pclScreen.begin(); it != m_pclScreen.end(); ++it)
    {
        if (nIdx == nScnNo)
        {
            m_pclScreen.erase(it);
        }

        ++nIdx;
    }
}

void hvScreenManager::changeScreenFromId(hvInt nDstScreen)
{
    if (m_nCurScrnId != nDstScreen)
    {
        m_nCurScrnId = nDstScreen;
    }
}

void hvScreenManager::setChangeMode(ChangeMode eMode)
{
    m_eChangeMode = eMode;
}

hvInt hvScreenManager::getCurrentId()
{
    return m_nCurScrnId;
}

void hvScreenManager::show() //TODO:according to screen ID
{
    //TODO:changeScreenFromId(nDstScreen)
    changeScreenFromId(m_clStgMngr.getCurrentScreenId());
    if (m_pclScreen.size() > 0)
    {
        m_pclScreen[m_nCurScrnId]->update();
        m_pclScreen[m_nCurScrnId]->show();
    }
    else
    {
        cout << "no screen!" << endl;
    }
}

void hvScreenManager::hide()
{
    m_pclScreen[m_nCurScrnId]->hideAll();
}

void hvScreenManager::update()
{
    m_pclScreen[m_nCurScrnId]->update();
}
