#pragma once

#include <windows.h>

#define MAX_LOADSTRING 100

class MainWindow
{
public:
    static bool InitInstance(HINSTANCE hInstance, int nCmdShow);  // L2LogD 0x004044F0
    static ATOM RegisterLogDClass(HINSTANCE hInstance);           // L2LogD 0x00404460

public:
    static wchar_t s_windowClass[MAX_LOADSTRING];  // L2LogD 0x00455C98
    static wchar_t s_title[MAX_LOADSTRING];        // L2LogD 0x00455D60

private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT mstType, WPARAM wParam, LPARAM lParam);        // L2LogD 0x00403EA0
    static INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT msgType, WPARAM wParam, LPARAM lParam);   // L2LogD 0x00403BE0
    static INT_PTR CALLBACK ConfigDlgProc(HWND hDlg, UINT msgType, WPARAM wParam, LPARAM lParam);  // L2LogD 0x004084B0
};
