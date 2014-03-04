
#define _WIN32_WINNT    0x0500      /* for PKBDLLHOOKSTRUCT */

#include <windows.h>
#include "hook.h"


HINSTANCE __g_HookInstance;
HHOOK __g_Hook;


LRESULT CALLBACK __HookLowLevelKeyboardProc(int code, WPARAM wparam, LPARAM lparam)
{
    switch(code)
    {
    case HC_ACTION:
        {
            PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lparam;
            switch(wparam)
            {
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
            case WM_KEYUP:
            case WM_SYSKEYUP:
                {
                	/* 屏蔽按键 */
                    if((VK_LWIN == key->vkCode) || (VK_RWIN == key->vkCode))
                    {
                        return TRUE;
                    }
                }  break;
            }
        }  break;
    }
    return CallNextHookEx(__g_Hook, code, wparam, lparam);
}


void KeyHookInit()
{
    __g_Hook = SetWindowsHookEx(WH_KEYBOARD_LL, __HookLowLevelKeyboardProc, __g_HookInstance, 0);
}


void KeyHookCleanup()
{
    UnhookWindowsHookEx(__g_Hook);
}



BOOL WINAPI DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    /* save application instance */
    __g_HookInstance = hInstDLL;

    switch(fdwReason)
    { 
        case DLL_PROCESS_ATTACH:
            {}break;
        case DLL_THREAD_ATTACH:
            {}break;
        case DLL_THREAD_DETACH:
            {}break;
        case DLL_PROCESS_DETACH:
            {}break;
    }
    return TRUE;
}
