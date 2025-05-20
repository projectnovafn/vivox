#include "hooks.h"
#include "vivox.h"
#include <detours/detours.h>

static void (*_ClientVoiceChatSendJoinToken)(void*, bool, wchar_t**, void**);

static void ClientVoiceChatSendJoinToken_hook(void* pc, bool success, wchar_t** token, void** error)
{
    if (success)
    {
        std::wstring wideToken(*token);
        std::string narrowToken(wideToken.begin(), wideToken.end());
        curr_access_token = vx_strdup(narrowToken.c_str());
    }

    _ClientVoiceChatSendJoinToken(pc, success, token, error);
}

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
    _ClientVoiceChatSendJoinToken = Memcury::Scanner::FindPattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8D 99 ? ? ? ? 49 8B F9")
        .GetAs<decltype(_ClientVoiceChatSendJoinToken)>();
        
    auto create_join_token_patch = Memcury::Scanner::FindStringRef(L"Failed to get join token: OSS Unavailable")
        .ScanFor({ 0x74, 0x10 }, false)
        .GetAs<BYTE*>();

    *create_join_token_patch = 0xEB;

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    DetourAttach((void**)&_ClientVoiceChatSendJoinToken, ClientVoiceChatSendJoinToken_hook);
    DetourAttach((void**)&_GetProcAddress, GetProcAddress_hook);

    DetourTransactionCommit();
}