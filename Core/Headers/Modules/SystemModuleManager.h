#pragma once

/*the very backbone of this kernel*/

#include <__KCONF.h>
#include <Modules/KExports.h>
#include <Modules/Loader.h>

typedef enum MODULE_MASTER_TYPE
{
    MMT_General,
    MMT_Kernel,
    MMT_Driver,
} MODULE_MASTER_TYPE;

typedef enum MODULE_SLAVE_TYPE
{
    MST_General,
    MST_Service,
    MST_Tool,

    /*Kernel*/
    MST_Loader,
    MST_Linker,
    MST_VirtualMemoryManager,
    MST_PhysicalMemoryManager,
    MST_KernelHeapManager,
    MST_Threads,
    MST_Scheduler,
    MST_Processes,
    MST_IDT,
    MST_GDT,
    MST_TSS,
    MST_SMP,

    /*Drivers/Devices*/
    MST_Timer,
    MST_Keyboard,
    MST_Mouse,
    MST_DiskController,
    MST_Graphics,
    MST_FileSystem,
    MST_Buses,
    MST_Network,
    MST_Misc,
} MODULE_SLAVE_TYPE;

typedef enum MODULE_STATE
{
    MS_Unknown,
    MS_Loaded,
    MS_Initialized,
    MS_Running,
    MS_Stopped,
    MS_Unloaded,
    MS_Failure,
} MODULE_STATE;

typedef struct MODULE_VENDOR
{
    uint64_t VendorID;
    const char* VendorName;
} MODULE_VENDOR;

typedef struct MODULE_OPERATIONS /*Standard operations ALL modules MUST have*/
{
    int (*Init)(SYSTEM_ERROR*);
    int (*Exit)(SYSTEM_ERROR*);
} MODULE_OPERATIONS;

/*Record is filled in by the linker*/
typedef struct MODULE_RECORD
{
    uint64_t ModuleID;
    const char* ModuleName;
    MODULE_OPERATIONS StandardOperations;
} MODULE_RECORD;

typedef struct MODULE_VERSION
{
    uint32_t Major;
    uint32_t Minor;
    uint32_t Patch;
    uint32_t Build;
} MODULE_VERSION;

typedef struct MODULE_DEPENDENCY
{
    uint64_t ModuleID;
    MODULE_VERSION MinimumVersion;
    MODULE_VERSION MaximumVersion;
    bool Required;
} MODULE_DEPENDENCY;

typedef struct MODULE
{
    MODULE_RECORD* ModuleRecord;
    MODULE_MASTER_TYPE MasterType;
    MODULE_SLAVE_TYPE SlaveType;
    MODULE_VENDOR* Vendor;
    MODULE_STATE State;
    MODULE_VERSION Version;
    
    MODULE_DEPENDENCY Dependencies[MaxDependencies];
    uint32_t DependencyCount;
    uint64_t Dependents[MaxDependencies];
    uint32_t DependentCount;
    
    void* BaseAddress;
    uint64_t Size;
    uint32_t ReferenceCount;
    
    struct MODULE* Next;
    struct MODULE* Previous;
} MODULE;

typedef struct MODULE_TREE
{
    MODULE* Module;
    struct MODULE_TREE* Parent;
    struct MODULE_TREE* Children[MaxDependencies];
    uint32_t ChildCount;
} MODULE_TREE;

typedef struct MODULE_MANAGER
{
    MODULE* Head;
    MODULE* Tail;
    uint64_t ModuleCount;

    MODULE_TREE* RootNodes[MaxDependencies];
    uint32_t RootCount;
    MODULE* ModuleTable[MaxModules];

    uint64_t TotalLoaded;
    uint64_t TotalUnloaded;
    uint64_t TotalSwapped;
    uint64_t FailedLoads;
} MODULE_MANAGER;

extern MODULE_MANAGER SystemModuleManager; 

/*Don't worry if the API is too huge... this is the backbone so yet this 
    will be the most complex part of this kernel*/

int InitModuleManager(MODULE_MANAGER*, SYSTEM_ERROR*);
int ShutdownModuleManager(MODULE_MANAGER*, SYSTEM_ERROR*);
int RegisterModule(MODULE_MANAGER*, MODULE*, SYSTEM_ERROR*);
int UnregisterModule(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
MODULE* FindModule(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
MODULE* FindModuleByName(MODULE_MANAGER*, const char*, SYSTEM_ERROR*);
MODULE** FindModulesByType(MODULE_MANAGER*, MODULE_SLAVE_TYPE, uint32_t*, SYSTEM_ERROR*);
MODULE** GetAllModules(MODULE_MANAGER*, uint32_t*, SYSTEM_ERROR*);
int AddDependency(MODULE_MANAGER*, uint64_t, MODULE_DEPENDENCY*, SYSTEM_ERROR*);
int RemoveDependency(MODULE_MANAGER*, uint64_t, uint64_t, SYSTEM_ERROR*);
int ValidateDependencies(MODULE_MANAGER*, MODULE*, SYSTEM_ERROR*);
int CheckCircularDependency(MODULE_MANAGER*, MODULE*, SYSTEM_ERROR*);
MODULE** GetDependencies(MODULE_MANAGER*, uint64_t, uint32_t*, SYSTEM_ERROR*);
MODULE** GetDependents(MODULE_MANAGER*, uint64_t, uint32_t*, SYSTEM_ERROR*);
int BuildDependencyTree(MODULE_MANAGER*, SYSTEM_ERROR*);
int RebuildDependencyTree(MODULE_MANAGER*, SYSTEM_ERROR*);
MODULE_TREE* GetTreeNode(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int PrintDependencyTree(MODULE_MANAGER*, SYSTEM_ERROR*);
int GetTreeDepth(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int LoadModule(MODULE_MANAGER*, MODULE*, SYSTEM_ERROR*);
int UnloadModule(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int InitializeModule(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int StartModule(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int StopModule(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int RestartModule(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int SuspendModule(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int ResumeModule(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int SwapModule(MODULE_MANAGER*, uint64_t, MODULE*, SYSTEM_ERROR*);
int PrepareSwap(MODULE_MANAGER*, uint64_t, MODULE*, SYSTEM_ERROR*);
int CommitSwap(MODULE_MANAGER*, uint64_t, MODULE*, SYSTEM_ERROR*);
int RollbackSwap(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int CanSwap(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
MODULE* AcquireModule(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int ReleaseModule(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int GetReferenceCount(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int WaitForRelease(MODULE_MANAGER*, uint64_t, uint64_t, SYSTEM_ERROR*);
MODULE** GetLoadOrder(MODULE_MANAGER*, uint32_t*, SYSTEM_ERROR*);
MODULE** GetUnloadOrder(MODULE_MANAGER*, uint32_t*, SYSTEM_ERROR*);
int LoadAllModules(MODULE_MANAGER*, SYSTEM_ERROR*);
int UnloadAllModules(MODULE_MANAGER*, SYSTEM_ERROR*);
int CompareVersion(MODULE_VERSION*, MODULE_VERSION*);
bool IsVersionCompatible(MODULE_VERSION*, MODULE_VERSION*);
MODULE* FindModuleByVersion(MODULE_MANAGER*, const char*, MODULE_VERSION*, SYSTEM_ERROR*);
int CheckVersionConflicts(MODULE_MANAGER*, MODULE*, SYSTEM_ERROR*);
int SetModuleState(MODULE_MANAGER*, uint64_t, MODULE_STATE, SYSTEM_ERROR*);
MODULE_STATE GetModuleState(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
MODULE** GetModulesByState(MODULE_MANAGER*, MODULE_STATE, uint32_t*, SYSTEM_ERROR*);
int GetModuleStats(MODULE_MANAGER*, uint64_t, void*, SYSTEM_ERROR*);
int GetManagerStats(MODULE_MANAGER*, void*, SYSTEM_ERROR*);
uint64_t GetTotalMemoryUsage(MODULE_MANAGER*, SYSTEM_ERROR*);
int DumpModuleInfo(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int DumpAllModules(MODULE_MANAGER*, SYSTEM_ERROR*);
typedef void (*MODULE_EVENT_CALLBACK)(MODULE*, void*);
int RegisterEventCallback(MODULE_MANAGER*, uint64_t, MODULE_EVENT_CALLBACK, void*, SYSTEM_ERROR*);
int UnregisterEventCallback(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int TriggerEvent(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int LoadModules(MODULE_MANAGER*, MODULE**, uint32_t, SYSTEM_ERROR*);
int UnloadModules(MODULE_MANAGER*, uint64_t*, uint32_t, SYSTEM_ERROR*);
int SwapModules(MODULE_MANAGER*, uint64_t*, MODULE**, uint32_t, SYSTEM_ERROR*);
int DetectConflicts(MODULE_MANAGER*, MODULE*, SYSTEM_ERROR*);
int ResolveConflicts(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
MODULE** GetConflictingModules(MODULE_MANAGER*, uint64_t, uint32_t*, SYSTEM_ERROR*);
int SetModuleMetadata(MODULE_MANAGER*, uint64_t, const char*, void*, SYSTEM_ERROR*);
void* GetModuleMetadata(MODULE_MANAGER*, uint64_t, const char*, SYSTEM_ERROR*);
int LockModule(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int UnlockModule(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int TryLockModule(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);
int ValidateModule(MODULE_MANAGER*, MODULE*, SYSTEM_ERROR*);
int ValidateAllModules(MODULE_MANAGER*, SYSTEM_ERROR*);
int CheckModuleIntegrity(MODULE_MANAGER*, uint64_t, SYSTEM_ERROR*);

KEXPORT(SystemModuleManager)

KEXPORT(InitModuleManager)
KEXPORT(RegisterModule)
KEXPORT(UnregisterModule)
KEXPORT(FindModule)
KEXPORT(FindModuleByName)
KEXPORT(LoadModule)
KEXPORT(UnloadModule)
KEXPORT(SwapModule)
KEXPORT(AcquireModule)
KEXPORT(ReleaseModule)
KEXPORT(GetLoadOrder)
KEXPORT(BuildDependencyTree)
KEXPORT(ValidateDependencies)


