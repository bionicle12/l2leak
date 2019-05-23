/*
   This file has been generated by IDA.
   It contains local type definitions from
   the type library 'L2AuthD'
*/

#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long

struct _RTL_CRITICAL_SECTION_DEBUG;
struct tagWNDCLASSEXA;
struct HWND__;
struct HINSTANCE__;
struct HICON__;
struct HBRUSH__;
struct HDC__;
union _ULARGE_INTEGER;
struct _iobuf;

/* 1 */
struct _SCOPETABLE_ENTRY
{
    int EnclosingLevel;
    void* FilterFunc;
    void* HandlerFunc;
};

/* 2 */
typedef struct _SCOPETABLE_ENTRY* PSCOPETABLE_ENTRY;

/* 8 */
typedef void* PVOID;

/* 9 */
typedef unsigned __int32 DWORD;

/* 3 */
struct _EH3_EXCEPTION_REGISTRATION
{
    struct _EH3_EXCEPTION_REGISTRATION* Next;
    PVOID ExceptionHandler;
    PSCOPETABLE_ENTRY ScopeTable;
    DWORD TryLevel;
};

/* 4 */
typedef struct _EH3_EXCEPTION_REGISTRATION EH3_EXCEPTION_REGISTRATION;

/* 5 */
typedef struct _EH3_EXCEPTION_REGISTRATION* PEH3_EXCEPTION_REGISTRATION;

/* 6 */
struct CPPEH_RECORD
{
    DWORD old_esp;
    EXCEPTION_POINTERS* exc_ptr;
    struct _EH3_EXCEPTION_REGISTRATION registration;
};

/* 11 */
typedef unsigned __int32 UINT_PTR;

/* 10 */
typedef UINT_PTR SIZE_T;

/* 7 */
struct _MEMORY_BASIC_INFORMATION
{
    PVOID BaseAddress;
    PVOID AllocationBase;
    DWORD AllocationProtect;
    SIZE_T RegionSize;
    DWORD State;
    DWORD Protect;
    DWORD Type;
};

/* 15 */
typedef unsigned __int16 WORD;

/* 17 */
enum $8C57D1DDA788D6050A7C554DBD1EB1AC
{
    AddrMode1616 = 0x0,
    AddrMode1632 = 0x1,
    AddrModeReal = 0x2,
    AddrModeFlat = 0x3,
};

/* 16 */
typedef $8C57D1DDA788D6050A7C554DBD1EB1AC ADDRESS_MODE;

/* 14 */
struct _tagADDRESS
{
    DWORD Offset;
    WORD Segment;
    ADDRESS_MODE Mode;
};

/* 13 */
typedef _tagADDRESS ADDRESS;

/* 18 */
typedef void* LPVOID;

/* 19 */
typedef int BOOL;

/* 21 */
struct _KDHELP
{
    DWORD Thread;
    DWORD ThCallbackStack;
    DWORD NextCallback;
    DWORD FramePointer;
    DWORD KiCallUserMode;
    DWORD KeUserCallbackDispatcher;
    DWORD SystemRangeStart;
};

/* 20 */
typedef _KDHELP KDHELP;

/* 12 */
struct _tagSTACKFRAME
{
    ADDRESS AddrPC;
    ADDRESS AddrReturn;
    ADDRESS AddrFrame;
    ADDRESS AddrStack;
    LPVOID FuncTableEntry;
    DWORD Params[4];
    BOOL Far;
    BOOL Virtual;
    DWORD Reserved[3];
    KDHELP KdHelp;
};

/* 22 */
#pragma pack(push, 4)
struct WSAData
{
    WORD wVersion;
    WORD wHighVersion;
    char szDescription[257];
    char szSystemStatus[129];
    unsigned __int16 iMaxSockets;
    unsigned __int16 iMaxUdpDg;
    char* lpVendorInfo;
};
#pragma pack(pop)

/* 24 */
typedef unsigned __int16 u_short;

/* 23 */
#pragma pack(push, 4)
struct sockaddr
{
    u_short sa_family;
    char sa_data[14];
};
#pragma pack(pop)

/* 25 */
struct _SYSTEMTIME
{
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
};

/* 28 */
struct _SYSTEM_INFO::$A707B71C060B6D10F73A71917EA8473F::$AA04DEB0C6383F89F13D312A174572A9
{
    WORD wProcessorArchitecture;
    WORD wReserved;
};

/* 27 */
union _SYSTEM_INFO::$A707B71C060B6D10F73A71917EA8473F
{
    DWORD dwOemId;
    struct
    {
        WORD wProcessorArchitecture;
        WORD wReserved;
    };
};

/* 26 */
struct _SYSTEM_INFO
{
    union
    {
        DWORD dwOemId;
        struct
        {
            WORD wProcessorArchitecture;
            WORD wReserved;
        };
    };
    DWORD dwPageSize;
    LPVOID lpMinimumApplicationAddress;
    LPVOID lpMaximumApplicationAddress;
    DWORD dwActiveProcessorMask;
    DWORD dwNumberOfProcessors;
    DWORD dwProcessorType;
    DWORD dwAllocationGranularity;
    WORD wProcessorLevel;
    WORD wProcessorRevision;
};

/* 29 */
struct _FILETIME
{
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
};

/* 30 */
typedef _FILETIME FILETIME;

/* 31 */
struct _MEMORYSTATUS
{
    DWORD dwLength;
    DWORD dwMemoryLoad;
    DWORD dwTotalPhys;
    DWORD dwAvailPhys;
    DWORD dwTotalPageFile;
    DWORD dwAvailPageFile;
    DWORD dwTotalVirtual;
    DWORD dwAvailVirtual;
};

/* 33 */
typedef _RTL_CRITICAL_SECTION_DEBUG* PRTL_CRITICAL_SECTION_DEBUG;

/* 37 */
typedef __int32 LONG;

/* 38 */
typedef void* HANDLE;

/* 32 */
struct _RTL_CRITICAL_SECTION
{
    PRTL_CRITICAL_SECTION_DEBUG DebugInfo;
    LONG LockCount;
    LONG RecursionCount;
    HANDLE OwningThread;
    HANDLE LockSemaphore;
    DWORD SpinCount;
};

/* 36 */
struct _LIST_ENTRY
{
    _LIST_ENTRY* Flink;
    _LIST_ENTRY* Blink;
};

/* 35 */
typedef _LIST_ENTRY LIST_ENTRY;

/* 34 */
struct _RTL_CRITICAL_SECTION_DEBUG
{
    WORD Type;
    WORD CreatorBackTraceIndex;
    struct _RTL_CRITICAL_SECTION_DEBUG::_RTL_CRITICAL_SECTION* CriticalSection;
    LIST_ENTRY ProcessLocksList;
    DWORD EntryCount;
    DWORD ContentionCount;
    DWORD Spare[2];
};

/* 40 */
typedef unsigned __int32 u_long;

/* 39 */
#pragma pack(push, 4)
struct _WSABUF
{
    u_long len;
    char* buf;
};
#pragma pack(pop)

/* 41 */
typedef tagWNDCLASSEXA WNDCLASSEXA;

/* 43 */
typedef unsigned int UINT;

/* 49 */
typedef LONG LRESULT;

/* 45 */
typedef HWND__* HWND;

/* 47 */
typedef UINT WPARAM;

/* 48 */
typedef LONG LPARAM;

/* 44 */
typedef LRESULT(__stdcall* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

/* 50 */
typedef HINSTANCE__* HINSTANCE;

/* 52 */
typedef HICON__* HICON;

/* 54 */
typedef HICON HCURSOR;

/* 55 */
typedef HBRUSH__* HBRUSH;

/* 58 */
typedef char CHAR;

/* 57 */
typedef const CHAR* LPCSTR;

/* 42 */
struct tagWNDCLASSEXA
{
    UINT cbSize;
    UINT style;
    WNDPROC lpfnWndProc;
    int cbClsExtra;
    int cbWndExtra;
    HINSTANCE hInstance;
    HICON hIcon;
    HCURSOR hCursor;
    HBRUSH hbrBackground;
    LPCSTR lpszMenuName;
    LPCSTR lpszClassName;
    HICON hIconSm;
};

/* 46 */
struct HWND__
{
    int unused;
};

/* 51 */
struct HINSTANCE__
{
    int unused;
};

/* 53 */
struct HICON__
{
    int unused;
};

/* 56 */
struct HBRUSH__
{
    int unused;
};

/* 61 */
struct tagPOINT
{
    LONG x;
    LONG y;
};

/* 60 */
typedef tagPOINT POINT;

/* 59 */
struct tagMSG
{
    HWND hwnd;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD time;
    POINT pt;
};

/* 63 */
typedef HDC__* HDC;

/* 66 */
struct tagRECT
{
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
};

/* 65 */
typedef tagRECT RECT;

/* 67 */
typedef unsigned __int8 BYTE;

/* 62 */
struct tagPAINTSTRUCT
{
    HDC hdc;
    BOOL fErase;
    RECT rcPaint;
    BOOL fRestore;
    BOOL fIncUpdate;
    BYTE rgbReserved[32];
};

/* 64 */
struct HDC__
{
    int unused;
};

/* 68 */
typedef _ULARGE_INTEGER ULARGE_INTEGER;

/* 70 */
struct _ULARGE_INTEGER::$0354AA9C204208F00D0965D07BBE7FAC
{
    DWORD LowPart;
    DWORD HighPart;
};

/* 71 */
typedef unsigned __int64 ULONGLONG;

/* 69 */
union _ULARGE_INTEGER
{
    struct
    {
        DWORD LowPart;
        DWORD HighPart;
    };
    _ULARGE_INTEGER::$0354AA9C204208F00D0965D07BBE7FAC u;
    ULONGLONG QuadPart;
};

/* 74 */
typedef unsigned __int16 wchar_t;

/* 73 */
typedef wchar_t WCHAR;

/* 75 */
typedef _SYSTEMTIME SYSTEMTIME;

/* 72 */
struct _TIME_ZONE_INFORMATION
{
    LONG Bias;
    WCHAR StandardName[32];
    SYSTEMTIME StandardDate;
    LONG StandardBias;
    WCHAR DaylightName[32];
    SYSTEMTIME DaylightDate;
    LONG DaylightBias;
};

/* 76 */
struct _WIN32_FIND_DATAA
{
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD dwReserved0;
    DWORD dwReserved1;
    CHAR cFileName[260];
    CHAR cAlternateFileName[14];
};

/* 77 */
struct _SECURITY_ATTRIBUTES
{
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
};

/* 79 */
typedef CHAR* LPSTR;

/* 80 */
typedef BYTE* LPBYTE;

/* 78 */
struct _STARTUPINFOA
{
    DWORD cb;
    LPSTR lpReserved;
    LPSTR lpDesktop;
    LPSTR lpTitle;
    DWORD dwX;
    DWORD dwY;
    DWORD dwXSize;
    DWORD dwYSize;
    DWORD dwXCountChars;
    DWORD dwYCountChars;
    DWORD dwFillAttribute;
    DWORD dwFlags;
    WORD wShowWindow;
    WORD cbReserved2;
    LPBYTE lpReserved2;
    HANDLE hStdInput;
    HANDLE hStdOutput;
    HANDLE hStdError;
};

/* 81 */
struct _cpinfo
{
    UINT MaxCharSize;
    BYTE DefaultChar[2];
    BYTE LeadByte[12];
};

/* 82 */
struct _OSVERSIONINFOA
{
    DWORD dwOSVersionInfoSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformId;
    CHAR szCSDVersion[128];
};

/* 83 */
struct _Ctypevec
{
    unsigned __int32 _Hand;
    unsigned int _Page;
    const __int16* _Table;
    int _Delfl;
};

/* 85 */
typedef unsigned int _dev_t;

/* 86 */
typedef unsigned __int16 _ino_t;

/* 87 */
typedef __int32 _off_t;

/* 88 */
typedef __int32 time_t;

/* 84 */
#pragma pack(push, 8)
struct _stat
{
    _dev_t st_dev;
    _ino_t st_ino;
    unsigned __int16 st_mode;
    __int16 st_nlink;
    __int16 st_uid;
    __int16 st_gid;
    _dev_t st_rdev;
    _off_t st_size;
    time_t st_atime;
    time_t st_mtime;
    time_t st_ctime;
};
#pragma pack(pop)

/* 89 */
typedef _iobuf FILE;

/* 90 */
#pragma pack(push, 8)
struct _iobuf
{
    char* _ptr;
    int _cnt;
    char* _base;
    int _flag;
    int _file;
    int _charbuf;
    int _bufsiz;
    char* _tmpfname;
};
#pragma pack(pop)

/* 91 */
struct Concurrency::details::VirtualProcessor;

/* 92 */
struct Concurrency::details::SchedulingRing;

/* 93 */
struct streambuf;

/* 94 */
struct DNameNode;

/* 95 */
struct std::ios_base;

/* 96 */
struct std::locale::facet;

/* 97 */
struct std::_Locinfo;

/* 98 */
struct Concurrency::details::_Micro_queue::_Push_finalizer;

/* 99 */
struct Replicator;

/* 100 */
struct std::_Lockit;

/* 101 */
struct std::strstreambuf;

/* 102 */
struct std::locale;

/* 103 */
struct exception;

/* 104 */
struct type_info;

/* 105 */
struct Concurrency::details::_NonReentrantPPLLock;

/* 106 */
struct std::istrstream;

/* 107 */
struct std::ostrstream;

/* 108 */
struct std::strstream;

/* 109 */
struct std::locale::_Locimp;

/* 110 */
struct _msExcInfo
{
    int Id;
    void* Proc;
};

/* 111 */
struct _msExcept
{
    int Magic;
    int Count;
    void* InfoPtr;
    int CountDtr;
    void* DtrPtr;
    int _unk[3];
    _msExcInfo Info[];
};

/* 112 */
struct _msExcExt
{
    int _unk[3];
    int Count;
    void* RttiBlkPtr;
};

/* 113 */
struct _msRttiDscr
{
    int _unk;
    void* RttiPtr;
    int spoff;
    void* Dtr;
};

/* 114 */
union __declspec(align(8)) __m64
{
    unsigned __int64 m64_u64;
    float m64_f32[2];
    __int8 m64_i8[8];
    __int16 m64_i16[4];
    __int32 m64_i32[2];
    __int64 m64_i64;
    unsigned __int8 m64_u8[8];
    unsigned __int16 m64_u16[4];
    unsigned __int32 m64_u32[2];
};

/* 115 */
union __declspec(align(16)) __m128
{
    float m128_f32[4];
    unsigned __int64 m128_u64[2];
    __int8 m128_i8[16];
    __int16 m128_i16[8];
    __int32 m128_i32[4];
    __int64 m128_i64[2];
    unsigned __int8 m128_u8[16];
    unsigned __int16 m128_u16[8];
    unsigned __int32 m128_u32[4];
};

/* 116 */
struct __m128d
{
    double m128d_f64[2];
};

/* 117 */
union __declspec(align(16)) __m128i
{
    __int8 m128i_i8[16];
    __int16 m128i_i16[8];
    __int32 m128i_i32[4];
    __int64 m128i_i64[2];
    unsigned __int8 m128i_u8[16];
    unsigned __int16 m128i_u16[8];
    unsigned __int32 m128i_u32[4];
    unsigned __int64 m128i_u64[2];
};
