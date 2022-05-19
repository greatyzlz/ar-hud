#ifndef HVLDWSCENE_H
#define HVLDWSCENE_H
#include "hvscene.h"
#include "graphengine.h"

struct FlashPara
{
    hvuInt nOnFrm;
    hvuInt nOffFrm;
};

class hvLDWScene : public hvScene
{
public:
    hvLDWScene();
    void init(SceneInfo& stSceneInfo) override;
    void uninit() override;
    void show() override;
    void update() override;
    void hide() override;

private:
    SceneInfo m_stSceneCfg;
    NODE_HANDLE m_NodeHandle;
    FlashPara m_stFlashPara;
    float m_fBaseX;
    float m_fBaseY;
    float m_fWidth;
    float m_fHeight;
};

#endif // HVLDWSCENE_H
