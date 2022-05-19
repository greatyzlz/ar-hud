#ifndef HVFCWSCENE_H
#define HVFCWSCENE_H
#include "hvscene.h"
#include "hvldwscene.h"

class hvFCWScene : public hvScene
{
public:
    hvFCWScene();
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

#endif // HVFCWSCENE_H
