#pragma once
#include "framework.h"
#include "hooks.h"

#include <Windows.h>
#include <cstdio>
#include <cstdarg>
#include <queue>

inline vx_sdk_config_t vivox_sdk_config;

VIVOX_API char* vx_strdup(const char* str);