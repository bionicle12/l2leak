#pragma once

#include "l2core/MemoryObject.h"
#include "l2core/geometry/FVector.h"

#include <string>
#include <vector>

class CTerritory : public MemoryObject
{
public:
    CTerritory();   // L2NPC 0x00470DA0
    ~CTerritory();  // L2NPC 0x00471ED0

    static void* operator new(size_t size);  // L2PNC 0x0048A310
    static void operator delete(void* ptr);  // L2PNC inlined inside 0x00471E90

    long AddRef(const char* file, int line, ORTs workType);               // L2PNC 0x00470C50
    void Release(const char* file, int line, ORTs nWorkType, bool flag);  // L2PNC 0x00470C70

    const std::wstring& GetName() const;  // L2NPC 0x00427900
    void SetName(const wchar_t* name);    // L2NPC 0x0048A260

    bool IsConvex() const;                                        // L2NPC 0x004713C0
    bool IsInside(const FVector& point, bool checkHeight) const;  // L2NPC 0x00470F90

    void AddTerritoryPoint(const FVector& point);  // L2NPC 0x00470EB0
    void ExpandHeight(int minZ, int maxZ);         // L2NPC inlined in CParserForNPCSpawn::yyaction

    FVector PickRandomPos_TBD() const;  // L2NPC 0x00471150

private:
    static long s_nAlloc;  // L2PNC 0x021808D4

    std::wstring m_territoryName;

    typedef std::vector<FVector> FVectorList;
    FVectorList m_points;

    int m_minZ;
    int m_maxZ;
    int m_maxX;
    int m_minX;
    int m_maxY;
    int m_minY;
};
