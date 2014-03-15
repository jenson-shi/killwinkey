/*
  Copyright (c) 2014 Jenson Shi <jenson.shixf@gmail.com>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

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
