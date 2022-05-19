#ifndef HVSCENE_H
#define HVSCENE_H
#include "hvstrategymanager.h"

class hvScene
{
public:
    hvScene();
    void setStrategyManager(hvStrategyManager* pclStgMngr);
    hvStrategyManager& getStrategyManager(void);
    virtual ~hvScene();
    virtual void init(SceneInfo& stSceneInfo);
    virtual void uninit(void);
    virtual void update(void);
    virtual void show(void);
    virtual void hide(void);

private:
     SceneInfo m_stSceneCfg;
     hvStrategyManager* m_pclStgMngr;

};

#endif // HVSCENE_H
