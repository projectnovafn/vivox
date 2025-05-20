#pragma once
#include "framework.h"
#include "vivox_sdk_binary.h"

namespace vivox_sdk
{
	inline HMODULE vivox_library;

	inline int(__fastcall* vx_initialize3)(vx_sdk_config_t*, size_t);
	inline int(__fastcall* vx_get_default_config3)(vx_sdk_config_t*, size_t);
	inline char* (__fastcall* vx_strdup)(const char*);
	inline char* (__fastcall* vx_get_sdk_version_info)();
	inline int(__fastcall* vx_issue_request)(vx_req_base_t*);
	inline int(__fastcall* vx_get_message)(vx_message_base_t**);
	inline int(__fastcall* vx_destroy_message)(vx_message_base_t*);
	inline void(__fastcall* vx_free)(void*);
	inline int(__fastcall* vx_debug_generate_token)();
	inline const char* (__fastcall* vx_get_error_string)(int);
	inline int(__fastcall* vx_issue_request3)(vx_req_base_t*);
	inline int(__fastcall* vx_uninitialize)();

	static void init()
	{
		WCHAR temp_path[MAX_PATH];
		WCHAR temp_file[MAX_PATH];

		if (GetTempPathW(MAX_PATH, temp_path) == 0)
			return;

		swprintf(temp_file, MAX_PATH, L"%s\\vivoxsdk.dll", temp_path);

		std::ofstream outFile(temp_file, std::ios::binary);
		outFile.write(reinterpret_cast<const char*>(vivox_sdk_binary), sizeof(vivox_sdk_binary));
		outFile.close();

		vivox_library = LoadLibraryW(temp_file);
		if (vivox_library == NULL) 
			return;

		vx_initialize3 = decltype(vx_initialize3)(GetProcAddress(vivox_library, "vx_initialize3"));
		vx_get_default_config3 = decltype(vx_get_default_config3)(GetProcAddress(vivox_library, "vx_get_default_config3"));
		vx_strdup = decltype(vx_strdup)(GetProcAddress(vivox_library, "vx_strdup"));
		vx_get_sdk_version_info = decltype(vx_get_sdk_version_info)(GetProcAddress(vivox_library, "vx_get_sdk_version_info"));
		vx_issue_request = decltype(vx_issue_request)(GetProcAddress(vivox_library, "vx_issue_request"));
		vx_get_message = decltype(vx_get_message)(GetProcAddress(vivox_library, "vx_get_message"));
		vx_destroy_message = decltype(vx_destroy_message)(GetProcAddress(vivox_library, "vx_destroy_message"));
		vx_free = decltype(vx_free)(GetProcAddress(vivox_library, "vx_free"));
		vx_debug_generate_token = decltype(vx_debug_generate_token)(GetProcAddress(vivox_library, "vx_debug_generate_token"));
		vx_get_error_string = decltype(vx_get_error_string)(GetProcAddress(vivox_library, "vx_get_error_string"));
		vx_issue_request3 = decltype(vx_issue_request3)(GetProcAddress(vivox_library, "vx_issue_request3"));
		vx_uninitialize = decltype(vx_uninitialize)(GetProcAddress(vivox_library, "vx_uninitialize"));
	}
}