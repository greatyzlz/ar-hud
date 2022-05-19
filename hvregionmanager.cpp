#include "hvregionmanager.h"
#include <algorithm>

using namespace std;

hvRegionManager::hvRegionManager()
{
    RegionInfo stRgnInfo;

    m_mstRgnInfo = {
        pair<hvChar, RegionInfo>('A', stRgnInfo),
        pair<hvChar, RegionInfo>('B', stRgnInfo),
        pair<hvChar, RegionInfo>('C', stRgnInfo)
    };

}

hvRegionManager::~hvRegionManager()
{

}

void hvRegionManager::init()
{
    for (auto& stRgnInfo : m_mstRgnInfo)
    {
        stRgnInfo.second.cName = stRgnInfo.first;
        stRgnInfo.second.eCorrelation = NO_CORRELATION;
        stRgnInfo.second.ePriority = LOW;
    }
}

void hvRegionManager::updateRegionCorrelation()
{
    //TODO: 根据StrategyManager计算出当前屏幕各区域的边界位置, 如果两个区域边界相互靠近某个范围, 则设置这两个区域相关
}

const RegionInfo& hvRegionManager::getRegionCorrelation(hvChar cRegion)
{
    return m_mstRgnInfo[cRegion];
}

const map<hvChar, RegionInfo> &hvRegionManager::getRegionCorrelation()
{
    return m_mstRgnInfo;
}

void hvRegionManager::updateRegionPriority()
{
    //TODO: will be relized by discussing, 根据下次反馈及讨论, 实现区域的优先级设置

}

