#ifndef HVSCREENMANGER_H
#define HVSCREENMANGER_H
#include "hvTypes.h"
#include <vector>
#include "hvscreen.h"
#include "hvstrategymanager.h"

using namespace std;

enum ChangeMode
{
    DIRECT = 1,
    GRAD
};

class hvScreenManager
{
public:
    hvScreenManager(hvStrategyManager& clStgMngr);
    ~hvScreenManager();

    void init(void);
    void uninit(void);
    void addScreen(hvInt nScnNo);
    void delScreen(hvInt nScnNo);
    void changeScreenFromId(hvInt nDstScreen);
    void setChangeMode(ChangeMode eMode);
    hvInt getCurrentId(void);
    void show(void);
    void show(hvInt nScrnNo);
    void hide(void);
    void hide(hvInt nScrnNo);
    void update(void);
    void update(hvInt nScrnNo);

private:
    vector <hvScreen*> m_pclScreen;
    hvInt m_nCurScrnId;
    ChangeMode m_eChangeMode;
    hvStrategyManager& m_clStgMngr;
};

#endif // HVSCREENMANGER_H
