#include "vivox.h"

VIVOX_API const char* vx_get_sdk_version_info()
{
	return VIVOX_VERSION;
}

VIVOX_API int vx_get_default_config3(vx_sdk_config_t* config, size_t config_size)
{
	ZeroMemory(config, config_size);

	return 0;
}

VIVOX_API char* vx_strdup(const char* str)
{
	return vivox_sdk::vx_strdup(IsBadReadPtr(str, 8) ? "" : str);
}

VIVOX_API int vx_initialize3(vx_sdk_config_t* config, size_t config_size)
{
	vx_sdk_config_t	sdk_config{};
	vivox_sdk::vx_get_default_config3(&sdk_config, sizeof(sdk_config));

	sdk_config.callback_handle = config->callback_handle;
	sdk_config.pf_sdk_message_callback = config->pf_sdk_message_callback;
	sdk_config.pf_malloc_func = config->pf_malloc_func;
	sdk_config.pf_realloc_func = config->pf_realloc_func;
	sdk_config.pf_calloc_func = config->pf_calloc_func;
	sdk_config.pf_malloc_aligned_func = config->pf_malloc_aligned_func;
	sdk_config.pf_free_func = config->pf_free_func;
	sdk_config.pf_free_aligned_func = config->pf_free_aligned_func;

	sdk_config.allow_shared_capture_devices = config->allow_shared_capture_devices;
	sdk_config.force_capture_silence = config->force_capture_silence;
	sdk_config.initial_log_level = log_none;

	if (auto result = vivox_sdk::vx_initialize3(&sdk_config, sizeof(sdk_config)))
		return result;

	memcpy(&vivox_sdk_config, config, config_size);

	return 0;
}