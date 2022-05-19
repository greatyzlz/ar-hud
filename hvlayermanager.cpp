#include "hvlayermanager.h"
#include <algorithm>

using namespace std;

hvLayerManager::hvLayerManager()
{
    vector <LayerInfo> vLayerInfo;

    m_mLayerMngr = {
        pair <hvChar, vector<LayerInfo>>('A', vLayerInfo),
        pair <hvChar, vector<LayerInfo>>('B', vLayerInfo),
        pair <hvChar, vector<LayerInfo>>('C', vLayerInfo)
    };
}

hvLayerManager::~hvLayerManager()
{

}

void hvLayerManager::addLayer(hvChar cRgn, hvString strScnName, hvInt nLayerNo)
{
    map <hvChar, hvChar> mChMap = {
        pair<hvChar, hvChar>('a', 'A'),
        pair<hvChar, hvChar>('A', 'A'),
        pair<hvChar, hvChar>('b', 'B'),
        pair<hvChar, hvChar>('B', 'B'),
        pair<hvChar, hvChar>('c', 'C'),
        pair<hvChar, hvChar>('C', 'C')
    };

    LayerInfo stLayerInfo = {strScnName, nLayerNo};

    m_mLayerMngr[mChMap[cRgn]].push_back(stLayerInfo);

    if (m_mLayerMngr[mChMap[cRgn]].size() >= 2)
    {
        sort(m_mLayerMngr[mChMap[cRgn]].begin(), m_mLayerMngr[mChMap[cRgn]].end(), hvLayerManager::compareLayer);
    }

}

const vector<LayerInfo> &hvLayerManager::getRegionLayer(hvChar cRgn)
{
    map <hvChar, hvChar> mChMap = {
        pair<hvChar, hvChar>('a', 'A'),
        pair<hvChar, hvChar>('A', 'A'),
        pair<hvChar, hvChar>('b', 'B'),
        pair<hvChar, hvChar>('B', 'B'),
        pair<hvChar, hvChar>('c', 'C'),
        pair<hvChar, hvChar>('C', 'C')
    };

    return m_mLayerMngr[mChMap[cRgn]];
}

hvInt hvLayerManager::getRegionLayerNum(hvChar cRgn)
{
    return getRegionLayer(cRgn).size();
}

void hvLayerManager::delRegionLayer(hvChar cRgn)
{
    map <hvChar, hvChar> mChMap = {
        pair<hvChar, hvChar>('a', 'A'),
        pair<hvChar, hvChar>('A', 'A'),
        pair<hvChar, hvChar>('b', 'B'),
        pair<hvChar, hvChar>('B', 'B'),
        pair<hvChar, hvChar>('c', 'C'),
        pair<hvChar, hvChar>('C', 'C')
    };

    m_mLayerMngr[mChMap[cRgn]].clear();
}

void hvLayerManager::clearAll()
{
    for (auto& vLayer : m_mLayerMngr)
    {
        vLayer.second.clear();
    }
}

hvBool hvLayerManager::compareLayer(LayerInfo lLayer, LayerInfo rLayer)
{
    return lLayer.nLayerNo < rLayer.nLayerNo;
}
