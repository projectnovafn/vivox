#pragma once
#include "framework.h"

#define VIVOX_API extern "C" __declspec(dllexport)
#define VIVOX_VERSION "Nova 1.0"

extern "C" IMAGE_DOS_HEADER __ImageBase;

inline std::string curr_access_token;
inline VX_HANDLE curr_account_handle;
inline VX_HANDLE curr_sessiongroup_handle;