#ifndef HVBSDSCENE_H
#define HVBSDSCENE_H
#include "hvscene.h"
#include "hvldwscene.h"

class hvBSDScene : public hvScene
{
public:
    hvBSDScene();
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

#endif // HVBSDSCENE_H
