#ifndef HVLAYERMANAGER_H
#define HVLAYERMANAGER_H
#include "hvTypes.h"
#include <map>
#include <vector>
using namespace std;

struct LayerInfo
{
    hvString strSceneName;
    hvInt nLayerNo;
};

class hvLayerManager
{
public:
    hvLayerManager();
    ~hvLayerManager();
    void addLayer(hvChar cRgn, hvString strScnName, hvInt nLayerNo);
    const vector<LayerInfo> &getRegionLayer(hvChar cRgn);
    hvInt getRegionLayerNum(hvChar cRgn);
    void delRegionLayer(hvChar cRgn);
    void clearAll(void);
    static hvBool compareLayer(LayerInfo lLayer, LayerInfo rLayer);
private:
    map <hvChar, vector<LayerInfo>> m_mLayerMngr;
};

#endif // HVLAYERMANAGER_H
