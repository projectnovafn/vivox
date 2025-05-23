#include "hooks.h"
#include "vivox.h"
#include <detours/detours.h>

static FARPROC(*_GetProcAddress)(HMODULE, LPCSTR)
    = GetProcAddress;

FARPROC WINAPI GetProcAddress_hook(HMODULE hModule, LPCSTR lpProcName)
{
    if (hModule != (HMODULE)&__ImageBase)
        return _GetProcAddress(hModule, lpProcName);

    auto local_function = _GetProcAddress(hModule, lpProcName);

    if (local_function)
        return local_function;

    return _GetProcAddress(vivox_sdk::vivox_library, lpProcName);
}

void init_hooks()
{
    auto create_join_token_patch = Memcury::Scanner::FindStringRef(L"Failed to get join token: OSS Unavailable")
        .ScanFor({ 0x74, 0x10 }, false)
        .GetAs<BYTE*>();

    *create_join_token_patch = 0xEB;

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    DetourAttach((void**)&_GetProcAddress, GetProcAddress_hook);

    DetourTransactionCommit();
}