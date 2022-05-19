#include "hvbsdscene.h"
#include <iostream>

using namespace std;

hvBSDScene::hvBSDScene()
{
    m_stFlashPara.nOnFrm = 20;
    m_stFlashPara.nOffFrm = 20;
    m_NodeHandle = NULL;

    m_fBaseX = 200.0;
    m_fBaseY = 0.0;
    m_fWidth = 70.0;
    m_fHeight = 576.0;
}

void hvBSDScene::init(SceneInfo &stSceneInfo)
{
    m_stSceneCfg = stSceneInfo;
    m_NodeHandle = NULL;
    sPoint3f vertex[4];
//    memset(vertex, 0, 4*sizeof(sPoint3));
    vertex[0].x = stSceneInfo.nPosition[0];
    vertex[0].y = stSceneInfo.nPosition[1];
    vertex[0].z = 0;
    vertex[1].x = stSceneInfo.nPosition[0] + stSceneInfo.nPosition[2];
    vertex[1].y = stSceneInfo.nPosition[1];
    vertex[1].z = 0;
    vertex[2].x = stSceneInfo.nPosition[0];
    vertex[2].y = stSceneInfo.nPosition[1] + stSceneInfo.nPosition[3];
    vertex[2].z = 0;
    vertex[3].x = stSceneInfo.nPosition[0] + stSceneInfo.nPosition[2];
    vertex[3].y = stSceneInfo.nPosition[1] + stSceneInfo.nPosition[3];
    vertex[3].z = 0;

    m_NodeHandle = HASCOEngine_Imagenode_Create(stSceneInfo.ViewHandle,
                                                const_cast<char *>(stSceneInfo.strResourcePath.c_str()),
                                                vertex, 2, 0);
    if (m_NodeHandle == NULL)
    {
        cout << "HASCOEngine_Imagenode_Create failed" << endl;
    }
    else
    {
        hide();
    }

}

void hvBSDScene::uninit()
{

}

void hvBSDScene::show()
{
    static hvuInt nCount = 0;

    if (nCount % (m_stFlashPara.nOnFrm + m_stFlashPara.nOffFrm) == 0)
    {
        HASCOEngine_Node_SetVisible(m_NodeHandle, SHOW);
    }
    else if (nCount % m_stFlashPara.nOnFrm == 0)
    {
        HASCOEngine_Node_SetVisible(m_NodeHandle, HIDE);
    }
    else
    {
        ;
    }
//HASCOEngine_Node_SetVisible(m_NodeHandle, SHOW);
    HASCOEngine_Invalidate();
    ++nCount;
}

void hvBSDScene::update()
{

}

void hvBSDScene::hide()
{
    HASCOEngine_Node_SetVisible(m_NodeHandle, HIDE);
    HASCOEngine_Invalidate();
}
