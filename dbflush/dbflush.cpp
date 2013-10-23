/* 
	Database Flush
	(C) ultrashot 2013
*/

#include "stdafx.h"
#include "regext.h"

HREGNOTIFY hNotify = NULL;
DWORD prevValue = 0;

void Callback(HREGNOTIFY hNotify, DWORD dwUserData, PBYTE pData, UINT cbData)
{
    DWORD value = 0;
    RegistryGetDWORD(HKEY_LOCAL_MACHINE, L"System\\State\\Phone", L"Active Call Count", &value);
    if (value != prevValue)
    {
        prevValue = value;
        if (value == 0)
        {
            CeFlushDBVol(NULL);
        }
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    Callback(NULL, 0, NULL, 0);
    RegistryNotifyCallback(HKEY_LOCAL_MACHINE, L"System\\State\\Phone", L"Active Call Count", Callback, 0, NULL, &hNotify);
    MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

