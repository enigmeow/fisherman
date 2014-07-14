//#ifndef UNICODE
//#define UNICODE
//#endif

#include <windows.h>
#include <stdio.h>
#include <psapi.h>
#include <strsafe.h>

#define NT_SUCCESS(x) ((x) >= 0)
#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004

#define SystemHandleInformation 16
#define ObjectBasicInformation 0
#define ObjectNameInformation 1
#define ObjectTypeInformation 2

typedef NTSTATUS (NTAPI *_NtQuerySystemInformation)(ULONG SystemInformationClass,
                                                    PVOID SystemInformation,
                                                    ULONG SystemInformationLength,
                                                    PULONG ReturnLength);

typedef NTSTATUS (NTAPI *_NtDuplicateObject)(HANDLE SourceProcessHandle,
                                             HANDLE SourceHandle,
                                             HANDLE TargetProcessHandle,
                                             PHANDLE TargetHandle,
                                             ACCESS_MASK DesiredAccess,
                                             ULONG Attributes,
                                             ULONG Options);
typedef NTSTATUS (NTAPI *_NtQueryObject)(HANDLE ObjectHandle,
                                         ULONG ObjectInformationClass,
                                         PVOID ObjectInformation,
                                         ULONG ObjectInformationLength,
                                         PULONG ReturnLength);

typedef struct _UNICODE_STRING {
  USHORT Length;
  USHORT MaximumLength;
  PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _SYSTEM_HANDLE {
  ULONG ProcessId;
  BYTE ObjectTypeNumber;
  BYTE Flags;
  USHORT Handle;
  PVOID Object;
  ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE, *PSYSTEM_HANDLE;

typedef struct _SYSTEM_HANDLE_INFORMATION {
  ULONG HandleCount;
  SYSTEM_HANDLE Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

typedef enum _POOL_TYPE {
  NonPagedPool,
  PagedPool,
  NonPagedPoolMustSucceed,
  DontUseThisType,
  NonPagedPoolCacheAligned,
  PagedPoolCacheAligned,
  NonPagedPoolCacheAlignedMustS
} POOL_TYPE, *PPOOL_TYPE;

typedef struct _OBJECT_TYPE_INFORMATION {
  UNICODE_STRING Name;
  ULONG TotalNumberOfObjects;
  ULONG TotalNumberOfHandles;
  ULONG TotalPagedPoolUsage;
  ULONG TotalNonPagedPoolUsage;
  ULONG TotalNamePoolUsage;
  ULONG TotalHandleTableUsage;
  ULONG HighWaterNumberOfObjects;
  ULONG HighWaterNumberOfHandles;
  ULONG HighWaterPagedPoolUsage;
  ULONG HighWaterNonPagedPoolUsage;
  ULONG HighWaterNamePoolUsage;
  ULONG HighWaterHandleTableUsage;
  ULONG InvalidAttributes;
  GENERIC_MAPPING GenericMapping;
  ULONG ValidAccess;
  BOOLEAN SecurityRequired;
  BOOLEAN MaintainHandleCount;
  USHORT MaintainTypeList;
  POOL_TYPE PoolType;
  ULONG PagedPoolUsage;
  ULONG NonPagedPoolUsage;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

extern "C" {
  BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
};

char*  UnicodeToUtf8( const WCHAR* wstr )
{
  const WCHAR* w;

  int len = 0;
  for ( w = wstr; *w; w++ ) {
    if ( *w < 0x0080 ) len++;
    else if ( *w < 0x0800 ) len += 2;
    else len += 3;
  }
       
  unsigned char* szOut = ( unsigned char* )malloc( len+1 );
  if ( szOut == NULL )
    return NULL;
       
  int i = 0;
  for ( w = wstr; *w; w++ ) {
    if ( *w < 0x0080 )
      szOut[i++] = ( unsigned char ) *w;
    else if ( *w < 0x0800 ) {
      szOut[i++] = 0xc0 | (( *w ) >> 6 );
      szOut[i++] = 0x80 | (( *w ) & 0x3f );
    } else {
      szOut[i++] = 0xe0 | (( *w ) >> 12 );
      szOut[i++] = 0x80 | (( ( *w ) >> 6 ) & 0x3f );
      szOut[i++] = 0x80 | (( *w ) & 0x3f );
    } 
  }
       
  szOut[ i ] = '\0';
  return ( char* )szOut;
}

PVOID GetLibraryProcAddress(PSTR LibraryName, PSTR ProcName) {
  return GetProcAddress(GetModuleHandleA(LibraryName), ProcName);
}
#define BUFSIZE 512

void NormalizeFileName(const char *src, char *dst) 
{
  char szDrive[3] = TEXT("c:");
  char drives[BUFSIZE];
  drives[0] = '\0';

  GetLogicalDriveStrings(BUFSIZE-1, drives);

  const char *p = drives;
  while (*p && p < &drives[BUFSIZE]) {
    TCHAR szName[MAX_PATH];

    szDrive[0] = *p;
    QueryDosDevice(szDrive, szName, MAX_PATH);
    int slen = strlen(szName);
    if (strncmp(src, szName, slen) == 0) {
      sprintf(dst,"%s%s", p, &src[slen + 1]);
      return;
    }
    p += 4;
  }
}

_NtQuerySystemInformation NtQuerySystemInformation = 0;
_NtDuplicateObject NtDuplicateObject = 0;
_NtQueryObject NtQueryObject = 0;

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
  DWORD dwProcessId;
  HINSTANCE hInstance;
  HANDLE processHandle;
  NTSTATUS status;
  PSYSTEM_HANDLE_INFORMATION handleInfo;
  ULONG handleInfoSize = 0x10000;
  ULONG i;
  char Str[255];

  if (!hWnd)
    return TRUE;		// Not a window

  if (!::IsWindowVisible(hWnd))
    return TRUE;		// Not visible

  GetClassName(hWnd, Str, sizeof(Str)); // Probably not toontown
  if (strcmp(Str, "WinGraphicsWindow0")) 
    return TRUE;

  hInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
  (void) GetWindowThreadProcessId(hWnd, &dwProcessId);

  if (!(processHandle = OpenProcess(PROCESS_DUP_HANDLE, FALSE, dwProcessId))) 
    return TRUE;

  handleInfo = (PSYSTEM_HANDLE_INFORMATION)malloc(handleInfoSize);

  /* NtQuerySystemInformation won't give us the correct buffer size, 
     so we guess by doubling the buffer size. */
  while ((status = NtQuerySystemInformation(SystemHandleInformation, handleInfo, handleInfoSize, NULL)) == STATUS_INFO_LENGTH_MISMATCH)
    handleInfo = (PSYSTEM_HANDLE_INFORMATION)realloc(handleInfo, handleInfoSize *= 2);

  /* NtQuerySystemInformation stopped giving us STATUS_INFO_LENGTH_MISMATCH. */
  if (!NT_SUCCESS(status)) {
    free(handleInfo);
    return TRUE;
  }

  for (i = 0; i < handleInfo->HandleCount; i++) {
    SYSTEM_HANDLE handle = handleInfo->Handles[i];
    HANDLE dupHandle = NULL;
    POBJECT_TYPE_INFORMATION objectTypeInfo;
    PVOID objectNameInfo;
    UNICODE_STRING objectName;
    ULONG returnLength;

    /* Check if this handle belongs to the PID the user specified. */
    if (handle.ProcessId != dwProcessId)
      continue;

    /* Duplicate the handle so we can query it. */
    if (!NT_SUCCESS(NtDuplicateObject(processHandle, (HANDLE) handle.Handle, GetCurrentProcess(), &dupHandle, 0, 0, 0))) 
      continue;

    /* Query the object type. */
    objectTypeInfo = (POBJECT_TYPE_INFORMATION)malloc(0x1000);

    if (!NT_SUCCESS(NtQueryObject(dupHandle, ObjectTypeInformation, objectTypeInfo, 0x1000, NULL))) {
      free(objectTypeInfo);
      CloseHandle(dupHandle);
      continue;
    }

    if ((handle.GrantedAccess == 0x0012019f) || (handle.GrantedAccess == 0x00120189)) {
      /* We have the type, so display that. */
      free(objectTypeInfo);
      CloseHandle(dupHandle);
      continue;
    }

    objectNameInfo = malloc(0x1000);
    if (!NT_SUCCESS(NtQueryObject(dupHandle, ObjectNameInformation, objectNameInfo, 0x1000, &returnLength))) {
      /* Reallocate the buffer and try again. */
      objectNameInfo = realloc(objectNameInfo, returnLength);
      if (!NT_SUCCESS(NtQueryObject(dupHandle, ObjectNameInformation, objectNameInfo, returnLength, NULL))) {
        free(objectTypeInfo);
        free(objectNameInfo);
        CloseHandle(dupHandle);
        continue;
      }
    }

    /* Cast our buffer into an UNICODE_STRING. */
    objectName = *(PUNICODE_STRING)objectNameInfo;

    /* Print the information! */
    if (objectName.Length) {
      /* The object has a name. */
      char *n = UnicodeToUtf8(objectTypeInfo->Name.Buffer);
      if (strcmp(n, "File") == 0) {
        char *v = UnicodeToUtf8(objectName.Buffer);
        int slen = strlen(v);
        if (v[slen-3] == 'l' && v[slen-2] == 'o' && v[slen-1] == 'g') {
          const char *p = &v[slen - 4];
          while (*p != '\\' && p > v)
            p--;
          p++;
          if (strncmp(p, "toontown", 8) == 0) {
            char rname[255];
            NormalizeFileName(v, rname);
          
            printf("[%#x] %s: %s\n", handle.Handle, n, v);
            i = handleInfo->HandleCount;
          }
        }
        free((void *)v);
      }
      free((void *)n);
    } // if (objectName.Length)

    free(objectTypeInfo);
    free(objectNameInfo);
    CloseHandle(dupHandle);
  } // for (i = 0; i < handleInfo->HandleCount; i++)

  free(handleInfo);
  CloseHandle(processHandle);

  return TRUE;
}

int wmain(int argc, WCHAR *argv[]) {
  NtQuerySystemInformation = (_NtQuerySystemInformation) GetLibraryProcAddress("ntdll.dll", "NtQuerySystemInformation");
  NtDuplicateObject = (_NtDuplicateObject) GetLibraryProcAddress("ntdll.dll", "NtDuplicateObject");
  NtQueryObject = (_NtQueryObject) GetLibraryProcAddress("ntdll.dll", "NtQueryObject");

  EnumWindows(&EnumWindowsProc, NULL);

  return 0;
}
