#include "hvhmi.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

hvHMI::hvHMI()
{
    m_bRunFlag = true;
}

hvHMI::~hvHMI()
{

}

void hvHMI::create(void)
{
    m_pclGlobalData = new hvGlobalData;
    m_pclStgManager = new hvStrategyManager(*m_pclGlobalData);
    m_pclScreenMngr = new hvScreenManager(*m_pclStgManager);

}

void hvHMI::destory(void)
{
    delete m_pclScreenMngr;
    delete m_pclStgManager;
    delete m_pclGlobalData;

}

void hvHMI::init()
{
    m_pclGlobalData->init();
    m_pclStgManager->init();
    m_pclScreenMngr->init();
}

void hvHMI::uninit()
{

}

void hvHMI::run()
{
//    vector <HvHmiCfg> vstHvCfg = m_pclGlobalData->getConfigData();

//    for (auto cfg:vstHvCfg)
//    {
//        cout << cfg.stScrnInfo.nScreenId << ": " << cfg.stScrnInfo.strScreenName << endl;
//        for (auto scn:cfg.vstScenes)
//        {
//            cout << scn.strSceneName << endl;
//        }
//    }

    while (m_bRunFlag)
    {
        m_pclScreenMngr->show();
        usleep(20000);//TODO: use timer

    }
}

void hvHMI::quit()
{
    m_bRunFlag = false;
}
