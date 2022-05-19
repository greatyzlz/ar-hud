#ifndef HVSCREEN_H
#define HVSCREEN_H

#include <vector>
#include <map>
#include "hvhmiconfig.h"
#include "hvprioritymanager.h"
#include "hvregionmanager.h"
#include "hvlayermanager.h"
#include "hvscene.h"
#include "hvstrategymanager.h"

using namespace std;

class hvScreen
{
public:
    hvScreen(const HvHmiCfg stCfg, hvStrategyManager& clStgMngr);
    ~hvScreen();
    void init();
    void uninit();
    void addScene(hvString strSceneName);
    void delScene(hvString strScenName);
    void show(void);
    void update(void);
    void hide(hvChar cZone);
    void hideAll(void);


private:
    HvHmiCfg m_stScrnCfg;
    hvScene * m_pclCurScene;
    map<hvString, hvScene*> m_mNotDeclareScenes;
    map<hvString, hvScene*> * m_mDeclareScenes;
    hvPriorityManager m_clPriMngr;
    hvLayerManager m_clLayerMngr;
    hvRegionManager m_clRegionMngr;
    hvStrategyManager& m_clStgMngr;

    hvuInt m_unFrameNo;

    hvBool trigeredScene(hvInt nSceneId);
    hvScene *getScenePtr(hvString strScnName);
    void initNotDeclareScenes(void);
    void PriorityManage(hvChar Region);
};

#endif // HVSCREEN_H
