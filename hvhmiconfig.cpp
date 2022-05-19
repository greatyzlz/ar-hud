#include "hvhmiconfig.h"
#include <fstream>
#include <hvConfig.h>
#include <map>
#include <iostream>
#include <stack>

using namespace std;
using namespace boost::property_tree;

hvHMIConfig::hvHMIConfig()
{

}

hvHMIConfig::~hvHMIConfig()
{

}

hvBool hvHMIConfig::loadConfig(hvString strCfgPath)
{
    hvBool bRet = true;
    hvString strErrMsg;
    ptree root;
    map <hvString, hvChar> mString = {pair<hvString, hvChar>("A", 'A'),
                                     pair<hvString, hvChar>("a", 'a'),
                                     pair<hvString, hvChar>("B", 'B'),
                                     pair<hvString, hvChar>("b", 'b'),
                                     pair<hvString, hvChar>("C", 'C'),
                                     pair<hvString, hvChar>("c", 'c')};

    if (hvConfig::ReadJson(strCfgPath, root, strErrMsg))
    {
        HvHmiCfg stTmpCfg;
        hvInt nScreenId = 0;

        for (auto rtNode : root)
        {
            stTmpCfg.stScrnInfo.strScreenName = rtNode.first;
            stTmpCfg.stScrnInfo.nScreenId = nScreenId;
            nScreenId++;
            ptree ScrnSize = rtNode.second.get_child("SIZE");
            ptree::iterator itSize = ScrnSize.begin();
            stTmpCfg.stScrnInfo.stSize.w = itSize->second.get<hvInt>("");
            stTmpCfg.stScrnInfo.stSize.h = (itSize++ == ScrnSize.end() ? 0 : itSize->second.get<hvInt>(""));

            ptree scenes = rtNode.second.get_child("SCENES");;
            SceneInfo stScnTmp;

            for (ptree::iterator itScn = scenes.begin(); itScn != scenes.end(); ++itScn)
            {
                stScnTmp.strSceneName = itScn->first;
                stScnTmp.nGraphicSN = itScn->second.get<hvInt>("graphic_sn");
                stScnTmp.cZone = mString[itScn->second.get<hvString>("zone")];
                stScnTmp.strResourcePath = itScn->second.get<hvString>("res_path");
                ptree PosVector = itScn->second.get_child("position");
                for (auto val : PosVector)
                {
                    stScnTmp.nPosition.push_back(val.second.get<hvInt>(""));
                }
                stScnTmp.nPriority = itScn->second.get<hvInt>("priority");
                stScnTmp.nLayer = itScn->second.get<hvInt>("layer");
                stTmpCfg.vstScenes.push_back(stScnTmp);
                stScnTmp.nPosition.clear();
            }

            m_vstHMICfg.push_back(stTmpCfg);
            stTmpCfg.vstScenes.clear();
        }
    }
    else
    {
        bRet = false;
        std::cout << strErrMsg << endl;
    }

    return bRet;
}

const vector<HvHmiCfg>& hvHMIConfig::getConfig(void)
{
    return m_vstHMICfg;
}
