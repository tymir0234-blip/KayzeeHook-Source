#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <iostream>
#include <string>
#include <thread>
#include <filesystem>
#include <fstream>
#include <functional>
#include <map>
#include <random>
#include <chrono>
#include <intrin.h>

#include "util/classes/classes.h"
#include "util/globals.h"
#include "features/wallcheck/wallcheck.h"


int main(/* Fixed & Updated by phoenix */) {
    HWND hwnd = GetConsoleWindow();
    SetWindowText(hwnd, (("KayzeeHook")));
    
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 12;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
    
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, 0, 200, LWA_ALPHA);

    engine::startup();
}