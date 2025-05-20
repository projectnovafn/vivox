#include "framework.h"
#include "hooks.h"

#include <detours/detours.h>

BOOL APIENTRY DllMain(HMODULE hModule, int dwReason)
{
    if (dwReason == 1)
    {
        DisableThreadLibraryCalls(hModule);

        vivox_sdk::init();

        init_hooks();
    }

    return 1;
}