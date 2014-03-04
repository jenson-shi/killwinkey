
#include <windows.h>
#include <stdio.h>
#include "hook.h"
#include "resource.h"

HINSTANCE   __g_AppInstance;
HMENU       __g_AppMenu;
UINT        WM_TASKBARCREATED;          /* Task Icon */
char        __g_AppName[] = "KillWinKey v1.0";


LRESULT CALLBACK __AppWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch(msg)
    {
    case WM_CREATE:
        {
            NOTIFYICONDATA nid;

            KeyHookInit();

            /* TaskbarCreated is definition in system */
            WM_TASKBARCREATED = RegisterWindowMessage("TaskbarCreated");

            __g_AppMenu = LoadMenu(__g_AppInstance, MAKEINTRESOURCE(IDR_MENU1));
            __g_AppMenu = GetSubMenu(__g_AppMenu, 0);

            nid.cbSize              =   sizeof(NOTIFYICONDATA);
            nid.hWnd                =   hwnd;
            nid.hIcon               =   LoadIcon(__g_AppInstance, MAKEINTRESOURCE(IDI_ICON1));
            nid.uCallbackMessage    =   WM_USER;
            nid.uFlags              =   NIF_ICON | NIF_MESSAGE | NIF_TIP;
            nid.uID                 =   IDI_ICON1;
            strcpy(nid.szTip, __g_AppName);
            Shell_NotifyIcon(NIM_ADD, &nid);
        }  break;
    case WM_USER:
        {
            if((WM_RBUTTONDOWN == lparam) || (WM_LBUTTONDOWN == lparam))
            {
                POINT point;
                GetCursorPos(&point);
                /* fix the menu will not disappear when user press ESCAPE key or click the mouse outside the menu */
                SetForegroundWindow(hwnd);
                TrackPopupMenu(__g_AppMenu, TPM_RIGHTBUTTON, point.x, point.y, 0, hwnd, 0);
            }
        }  break;
    case WM_COMMAND:
        {
            switch(LOWORD(wparam))
            {
            case ID_MENU_ABOUT:
                {
                    char szMsg[128] = {0};
                    sprintf(szMsg, "Welcome to use %s\n\n\t\tBy Jenson\n\t\thttp://shixf.com/", __g_AppName);
                    MessageBox(hwnd, szMsg, __g_AppName, MB_TOPMOST);
                }
                break;
            case ID_MENU_EXIT:
                {
                    SendMessage(hwnd, WM_CLOSE, 0, 0);
                }
                break;
            }
        }  break;
    case WM_DESTROY:
        {
            /* cleanup tool bar icon */
            NOTIFYICONDATA nid;
            nid.uID             =   IDI_ICON1;
            nid.hWnd            =   hwnd;
            Shell_NotifyIcon(NIM_DELETE, &nid);

            KeyHookCleanup();
            PostQuitMessage(0);
        }  break;
    default:
        {
            if(WM_TASKBARCREATED == msg)
            {
                SendMessage(hwnd, WM_CREATE, wparam, lparam);
            }
        }  break;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
    WNDCLASS wndcls;
    HWND hWnd;
    MSG msg;

    __g_AppInstance = hInstance;
    if(FindWindow(0, __g_AppName))
    {
        MessageBox(0, "application already is in running.", __g_AppName, MB_ICONERROR);
        return 0;
    }

    wndcls.style            =   CS_HREDRAW | CS_VREDRAW;
    wndcls.lpfnWndProc      =   __AppWndProc;
    wndcls.cbClsExtra       =   0;
    wndcls.cbWndExtra       =   0;
    wndcls.hInstance        =   __g_AppInstance;
    wndcls.hIcon            =   LoadIcon(__g_AppInstance, MAKEINTRESOURCE(IDI_ICON1));
    wndcls.hCursor          =   LoadCursor(0, IDC_ARROW);
    wndcls.hbrBackground    =   (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndcls.lpszMenuName     =   0;
    wndcls.lpszClassName    =   __g_AppName;

    if(!RegisterClass(&wndcls))
    {
        MessageBox(0, "initialize failed.", __g_AppName, MB_ICONERROR);
        return 0;
    }

    /* use WS_EX_TOOLWINDOW to hide tool bar's window */
    hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, __g_AppName, __g_AppName, WS_POPUP, 
                            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
                            0, 0, __g_AppInstance, 0);
    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    while(GetMessage(&msg, 0, 0 , 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

