#include "hvscene.h"
#include <iostream>

using namespace std;

hvScene::hvScene()
{

}

void hvScene::setStrategyManager(hvStrategyManager * pclStgMngr)
{
    m_pclStgMngr = pclStgMngr;
}

hvStrategyManager &hvScene::getStrategyManager()
{
    return *m_pclStgMngr;
}

hvScene::~hvScene()
{

}

void hvScene::init(SceneInfo& stSceneInfo)
{
    m_stSceneCfg = stSceneInfo;
    cout << "default init " << stSceneInfo.strSceneName << endl;
}

void hvScene::uninit()
{

}

void hvScene::update()
{

}

void hvScene::show()
{
    cout << "show "  << m_stSceneCfg.strSceneName <<" default scene !" << endl;
}

void hvScene::hide()
{

}
