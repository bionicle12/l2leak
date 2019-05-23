#include "l2core/geometry/CTerritory.h"

#include "l2core/geometry/Math.h"
#include "l2core/logger/CLog.h"
#include "l2core/memory/Allocator.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2PNC 0x021808D4
long CTerritory::s_nAlloc = ::InterlockedIncrement(&MemoryObject::s_classCounter);  // L2PNC 0x004C6C40

// L2NPC 0x00470DA0
CTerritory::CTerritory()
    : MemoryObject()
    , m_points()
    , m_minZ(0x8000)
    , m_maxZ(-0x8000 + 1)
    , m_maxX(-0x20000)
    , m_minX(0x30000 - 1)
    , m_maxY(-0x38000)
    , m_minY(0x40000 - 1)
{
    guard(L"CTerritory::CTerritory()");
    unguard();
}

// L2NPC 0x0048A310
void* CTerritory::operator new(size_t size)
{
    void* memory = g_allocator.allocate(size, 1, L"CTerritory");

    ::InterlockedIncrement(&Allocator::g_allocatedObjects[CTerritory::s_nAlloc]);

    Allocator::s_classRefNames[CTerritory::s_nAlloc] = "CTerritory";
    Allocator::g_allocatedMemory[CTerritory::s_nAlloc] = sizeof(CTerritory);

    return memory;
}

// L2PNC inlined inside 0x00471E90
void CTerritory::operator delete(void* ptr)
{
    g_winlog.Add(LOG_ERROR, L"Never Call Oprator Delete!!! CTerritory at file[%s], line[%d]", TEXT(__FILE__), __LINE__);
    CallStack::ReportCallStack();
}

// L2NPC 0x00471ED0
CTerritory::~CTerritory()
{
    guard(L"CTerritory::~CTerritory()");  // FIXED: added
    unguard();
}

// L2NPC 0x00470C50
long CTerritory::AddRef(const char* file, int line, ORTs workType)
{
    ::InterlockedIncrement(&m_nRefCount);
    return m_nRefCount;
}

// L2NPC 0x00470C70
void CTerritory::Release(const char* file, int line, ORTs nWorkType, bool flag)
{
    long refCountAfterRelease = ::InterlockedDecrement(&m_nRefCount);
    if (refCountAfterRelease > 0)
    {
        return;
    }

    if (refCountAfterRelease != 0)
    {
        if (refCountAfterRelease > -1)
        {
            return;
        }

        g_winlog.Add(LOG_ERROR, "Invalid Memory (%d) on CTerritory(%d)", refCountAfterRelease, m_identity);
        if (file)
        {
            g_winlog.Add(LOG_ERROR, "           Caller : file[%s], line[%d]", file, line);
        }

        ReportOrt(0, 0);
        CallStack::ReportCallStack();

        return;
    }

    if (inTimer())
    {
        if (file)
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CTerritory] at file[%s], line[%d]", file, line);
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CTerritory::s_nAlloc]);
        }
        else
        {
            g_winlog.Add(LOG_ERROR, "deleting in-timer-object![CTerritory]");
            ReportOrt(0, 0);
            ::InterlockedDecrement(&Allocator::g_allocatedObjects[CTerritory::s_nAlloc]);
        }
        return;
    }

    this->~CTerritory();

    g_allocator.deallocate(this);

    ::InterlockedDecrement(&Allocator::g_allocatedObjects[CTerritory::s_nAlloc]);
}

// L2NPC 0x00427900
const std::wstring& CTerritory::GetName() const
{
    return m_territoryName;
}

// L2NPC 0x0048A260
void CTerritory::SetName(const wchar_t* name)
{
    m_territoryName.assign(name);
}

// L2NPC 0x004713C0
bool CTerritory::IsConvex() const
{
    guard(L"bool CTerritory::IsConvex()");

    if (m_points.size() < 3)
    {
        unguard();
        return false;
    }

    if (m_points.size() == 3)
    {
        unguard();
        return true;
    }

    const FVector& a1 = m_points[0];
    int preLastIndex = m_points.size() - 2;
    const FVector& y = m_points[preLastIndex];
    int lastIndex = m_points.size() - 1;
    const FVector& z = m_points[lastIndex];

    bool isCCW = Math::IsClockWiseAngle(y, z, a1);

    for (size_t i = 0; i <= m_points.size() - 3; ++i)
    {
        const FVector& a = m_points[i + 0];
        const FVector& b = m_points[i + 1];
        const FVector& c = m_points[i + 2];

        if (Math::IsStraigtLine(a, b, c))
        {
            continue;
        }

        bool isNextAngleClockWise = Math::IsClockWiseAngle(a, b, c);

        // polygon is convex, if sin of all angles have same sign (either all clock or counterclock wise)
        if (isCCW != isNextAngleClockWise)
        {
            unguard();
            return false;
        }
    }

    unguard();
    return true;
}

// L2NPC 0x00470F90
bool CTerritory::IsInside(const FVector& point, bool checkHeight) const
{
    guard(L"bool CTerritory::IsInside(const FVector &v, bool check_height)");

    if (m_points.empty())
    {
        g_winlog.Add(LOG_ERROR, "GetTerritoryPointSize()<=0 at file[%s], line[%d]", __FILE__, __LINE__);
        unguard();
        return false;
    }

    if ((checkHeight && (point.z < m_minZ || point.z > m_maxZ)) || (point.x < m_minX || point.x > m_maxX) || (point.y < m_minY || point.y > m_maxY))
    {
        return false;
        unguard();
    }

    if (m_points.size() - 1 <= 0)
    {
        unguard();
        return true;
    }

    for (size_t i = 0; i < m_points.size() - 1; ++i)
    {
        bool isCCW = Math::IsClockWiseAngle(point, m_points[i], m_points[i + 1]);
        if (!isCCW)
        {
            unguard();
            return false;
        }
    }

    unguard();
    return true;
}

// L2NPC 0x00470EB0
void CTerritory::AddTerritoryPoint(const FVector& point)
{
    guard(L"void CTerritory::AddTerritoryPoint(FVector *a)");

    m_points.push_back(point);

    if (point.x < m_minX)
    {
        m_minX = static_cast<int>(point.x);
    }

    if (point.x > m_maxX)
    {
        m_maxX = static_cast<int>(point.x);
    }

    if (point.y < m_minY)
    {
        m_minY = static_cast<int>(point.y);
    }

    if (point.y > m_maxY)
    {
        m_maxY = static_cast<int>(point.y);
    }

    unguard();
}

// L2NPC inlined in CParserForNPCSpawn::yyaction
void CTerritory::ExpandHeight(int minZ, int maxZ)
{
    if (minZ < m_minZ)
    {
        m_minZ = minZ;
    }

    if (m_maxZ < maxZ)
    {
        m_maxZ = maxZ;
    }
}

// L2NPC 0x00471150
FVector CTerritory::PickRandomPos_TBD() const
{
    FVector result;
    /*
    int v2; // eax@1
    int v3; // ecx@1
    _; // edx@1
    std::vector_FDVector::iterator *v5; // eax@1
    int i; // ebx@1
    int size; // ebp@2
    FVector *result; // eax@3
    int v9; // ecx@3
    double v10; // st7@5
    double v11; // st7@5
    FVector *v12; // eax@5
    double v13; // st6@5
    double v14; // st5@5
    int v15; // esi@7
    int v16; // eax@9
    int v17; // edx@9
    uint32_t v18; // ecx@9
    double v19; // [sp+14h] [bp-60h]@4
    double v20; // [sp+1Ch] [bp-58h]@4
    double v21; // [sp+24h] [bp-50h]@5
    double v22; // [sp+2Ch] [bp-48h]@5
    IVector v23; // [sp+34h] [bp-40h]@4
    IVector v24; // [sp+40h] [bp-34h]@4
    double v25; // [sp+60h] [bp-14h]@5
    int v26; // [sp+70h] [bp-4h]@1
    a; // [sp+78h] [bp+4h]@9

    v2 = *(*__readfsdword(44) + 8);
    v3 = CallStack::s_threadStackSizes[v2];
    CallStack::s_threadStackSizes[v2] = v3 + 1;
    */
    guard(L"FVector CTerritory::PickRandomPos()");

    /*
    _this__ = _this_;
    v5 = m_points._First;
    i = 0;
    v26 = 0;
    if ( v5 && (size = m_points._Last - v5, size > 0) )
    {
        v23.X = 0;
        v23.Y = 0;
        v23.Z = 0;
        v24.X = 0;
        v24.Y = 0;
        v24.Z = 0;
        v19 = 0.0;
        qmemcpy(&v20, &v23, 24u);
        if ( size > 0 )
        {
            do
            {
                v10 = Utils::GetRandomNumber(0.0, 1.0);
                v11 = v10 * v10;
                v12 = m_points._First[i].value;
                v13 = v11 * v12->x;
                ++i;
                v14 = v11 * v12->y;
                v25 = v11 * v12->z;
                *&v23.X = v13 + v20;
                *&v23.Z = v21 + v14;
                *&v24.Y = v22 + v25;
                qmemcpy(&v20, &v23, 0x18u);
                v19 = v11 + v19;
            }
            while ( i < size );
            _this__ = _this_;
        }
        *&v23.X = v20 * (1.0 / v19);
        *&v23.Z = v21 * (1.0 / v19);
        *&v24.Y = v22 * (1.0 / v19);
        qmemcpy(&v20, &v23, 0x18u);
        v22 = _this__->m_d.m_maxZ;
        v15 = LODWORD(dword_217C288);
        if ( !LODWORD(dword_217C288) )
            g_winlog.Add(LOG_ERROR, "NULL m_geo at file[%s], line[%d]", "c:\\serverservice\\l2npc\\world.h", 122);
        v16 = GeoData::sub_41FD40(v15, v21, v20, v22);
        v17 = LODWORD(v20);
        _this_a = v16;
        result = out;
        HIDWORD(out->x) = HIDWORD(v20);
        v18 = HIDWORD(v21);
        LODWORD(out->x) = v17;
        out->z = _this_a;
        *&out->y = __PAIR__(v18, LODWORD(v21));
        v9 = *(*__readfsdword(44) + 8);
    }
    else
    {
        g_winlog.Add(LOG_ERROR, "GetTerritoryPointSize()<=0 at file[%s], line[%d]", __FILE__, __LINE__);
        result = out;
        *&out->x = 0i64;
        *&out->y = 0i64;
        *&out->z = 0i64;
        v9 = *(*__readfsdword(44) + 8);
    }
*/
    unguard();
    return result;
}
