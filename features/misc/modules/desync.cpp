#include "../misc.h"
#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <iostream>
#include <Psapi.h>
#include <thread>
#include <chrono>
#pragma comment(lib, "Psapi.lib")

using namespace roblox;

std::string findRobloxPath() {
    HANDLE hProcessSnap;
    PROCESSENTRY32W pe32;
    std::string exePath = "";

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
        return "";

    pe32.dwSize = sizeof(PROCESSENTRY32W);
    if (!Process32FirstW(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return "";
    }

    do {
        std::wstring wExe = pe32.szExeFile;
        std::string exeName;
        exeName.assign(wExe.begin(), wExe.end());

        if (_stricmp(exeName.c_str(), "RobloxPlayerBeta.exe") == 0) {
            HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
            if (hProc) {
                char buffer[MAX_PATH];
                if (GetModuleFileNameExA(hProc, NULL, buffer, MAX_PATH)) {
                    exePath = buffer;
                    CloseHandle(hProc);
                    break;
                }
                CloseHandle(hProc);
            }
        }
    } while (Process32NextW(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return exePath;
}

void blockRoblox() {
    if (!globals::misc::roblox_path.empty()) {
        std::string cmdOut = "netsh advfirewall firewall add rule name=\"" + globals::misc::firewall_rule_name + "_OUT\" dir=out program=\"" + globals::misc::roblox_path + "\" action=block enable=yes";
        system(cmdOut.c_str());
        std::cout << "[+] Started The Goon\n";
    }
}

void unblockRoblox() {
    std::string cmdDel = "netsh advfirewall firewall delete rule name=\"" + globals::misc::firewall_rule_name + "_OUT\"";
    system(cmdDel.c_str());
    std::cout << "[-] Stopped Gooning\n";
}

void hooks::desync() {
    // Removed cause its a shitty lag switcher
}
