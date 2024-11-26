// Copyright (c) Softanics

#include "stdafx.h"
#include <string>

#define DEF_BOXEDAPPSDK_INTERFACES_NOT_REQUIRED
#include "..\\..\\..\\BoxedApp\\src\\BoxedAppSDK\\BoxedAppSDK.h"

#if USE_STATIC_BX

#ifdef _WIN64
#pragma comment(lib, "..\\..\\..\\BoxedApp\\bxsdk\\obj\\x64\\debug\\BoxedAppSDK_StaticLib\\bxsdk64.lib")
#else
#pragma comment(lib, "..\\..\\..\\BoxedApp\\bxsdk\\obj\\Win32\\debug\\BoxedAppSDK_StaticLib\\bxsdk32.lib")
#endif // _WIN64

#else

#ifdef _WIN64
#pragma comment(lib, "..\\..\\..\\BoxedApp\\bxsdk\\bin\\debug\\bxsdk64.lib")
#else
#pragma comment(lib, "..\\..\\..\\BoxedApp\\bxsdk\\bin\\debug\\bxsdk32.lib")
#endif // _WIN64

#endif

int _tmain(int argc, _TCHAR* argv[])
{
    BoxedAppSDK_Init();
    BoxedAppSDK_EnableOption(DEF_BOXEDAPPSDK_OPTION__EMBED_BOXEDAPP_IN_CHILD_PROCESSES, TRUE);
    BoxedAppSDK_EnableOption(DEF_BOXEDAPPSDK_OPTION__INHERIT_OPTIONS, TRUE);

    argc--;
    argv++;

    if (argc < 2)
    {
        printf("Usage: VirtualExeRunner.exe <path of file with exe data> <path of virtual exe name>\r\n");
        return -1;
    }

    LPWSTR szDataFilePath = argv[0];
    LPWSTR szVirtualFilePath = argv[1];

    CloseHandle(BoxedAppSDK_CreateVirtualFileW(szVirtualFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_NEW, 0, NULL));

    CopyFileW(szDataFilePath, szVirtualFilePath, FALSE);

    STARTUPINFO startup_info = { 0 };
    startup_info.cb = sizeof(startup_info);

    PROCESS_INFORMATION pi;
    BOOL bRes = CreateProcessW(NULL, szVirtualFilePath, NULL, NULL, FALSE, 0, NULL, NULL, &startup_info, &pi);
    DWORD dwLastError = GetLastError();

    if (bRes)
        printf("CreateProcessW() returns TRUE\r\n");
    else
        printf("CreateProcessW() failed, GetLastError() = %d\r\n", dwLastError);

    return 0;
}
