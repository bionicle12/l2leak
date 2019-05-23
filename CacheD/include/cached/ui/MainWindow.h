#pragma once

#include <windows.h>

#define MAX_LOADSTRING 100

class MainWindow
{
public:
    static ATOM RegisterCacheDClass(HINSTANCE hInstance);         // L2CacheD 0x0040A710
    static bool InitInstance(HINSTANCE hInstance, int nCmdShow);  // L2CacheD 0x0040AA10

public:
    static wchar_t s_windowClass[MAX_LOADSTRING];  // L2CacheD 0x004F28C0
    static wchar_t s_title[MAX_LOADSTRING];        // L2CacheD 0x004F27E8

private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msgType, WPARAM wParam, LPARAM lParam);       // L2CacheD 0x0040A260
    static INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT msgType, WPARAM wParam, LPARAM lParam);  // L2CacheD 0x00409E70
};
