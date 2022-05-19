#include "hvglobaldata.h"
#include <iostream>

using namespace std;

hvGlobalData::hvGlobalData()
{

}

hvGlobalData::~hvGlobalData()
{

}

hvBool hvGlobalData::init()
{
    hvBool bRet = true;
    if (!m_clHmiConfig.loadConfig(CONFIG_PATH))
    {
        cout << "global data init error" << endl;
        bRet = false;
    }
    m_vstHMIConfig = m_clHmiConfig.getConfig();
    return bRet;
}

vector<HvHmiCfg> &hvGlobalData::getConfigData()
{
    return m_vstHMIConfig;
}
