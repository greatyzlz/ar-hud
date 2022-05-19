#ifndef HVREGIONMANAGER_H
#define HVREGIONMANAGER_H
#include "hvTypes.h"
#include <map>
#include <vector>

using namespace  std;

enum RegionCorrelation
{
    NO_CORRELATION = 0,
    A_CORRELATION,
    B_CORRELATION,
    C_CORRELATION,
    AB_CORRELATION,
    AC_CORRELATION,
    BC_CORRELATION,
};

enum RegionPriority
{
    LOW = 0,
    MIDDLE,
    HIGH
};

struct RegionInfo
{
    hvChar cName;
    RegionCorrelation eCorrelation;
    RegionPriority ePriority;
};

class hvRegionManager
{
public:
    hvRegionManager();
    ~hvRegionManager();
    void init(void);
    void uninit(void);
    void updateRegionCorrelation(void);
    const RegionInfo& getRegionCorrelation(hvChar cRegion);
    const map <hvChar, RegionInfo>& getRegionCorrelation(void);
    void updateRegionPriority(void);



private:
    map <hvChar, RegionInfo> m_mstRgnInfo;
};

#endif // HVREGIONMANAGER_H
