/* Copyright (c) 2013-2018 by Mercer Road Corp
 *
 * Permission to use, copy, modify or distribute this software in binary or source form
 * for any purpose is allowed only under explicit prior consent in writing from Mercer Road Corp
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND MERCER ROAD CORP DISCLAIMS
 * ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL MERCER ROAD CORP
 * BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 */
#pragma once

#include <time.h>

#pragma pack(push)
#pragma pack(8)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * SDK logging levels.
 */
typedef enum {
    log_none = -1,
    /**
     * Errors only.
     */
    log_error = 0,
    /**
     * Warnings only.
     */
    log_warning = 1,
    /**
     * Generic information.
     */
    log_info = 2,
    /**
     * Detailed debugging information. Likely to have performance implications.
     */
    log_debug = 3,
    /**
     * The most verbose logging level. Likely to have performance implications.
     */
    log_trace = 4,
    /**
     * Log almost everything. Very likely to have performance implications.
     */
    log_all = 5
} vx_log_level;

/**
 * Values for the backend type.
 */
typedef enum {
    backend_type_unknown = -1,
    backend_type_sip = 0,
    backend_type_xmpp = 1
} vx_backend_type;

/**
 * Values for the UDP packet type.
 */
typedef enum {
    vx_frame_type_rtp  = 0,
    vx_frame_type_rtcp = 1,
    vx_frame_type_sip_message   = 2,
    vx_frame_type_sip_keepalive = 3
} vx_udp_frame_type;


/**
 * A struct that holds per-participant data for a callback.
 */
typedef struct {
    const char *participant_uri;
    short *pcm_frames;
    int pcm_frame_count;
    int audio_frame_rate;
    int channels_per_frame;
} vx_before_recv_audio_mixed_participant_data_t;


/**
 * A callback functions declaration in C99 style for oRTP and eXosip libraries.
 */

/**
 * Called before any UDP frame is transmitted.
 * This callback must be a non-blocking callback.
 * It is recommended that this callback complete in less than 1 millisecond.
 */
typedef void (*pf_on_before_udp_frame_transmitted_t)(
        void *callback_handle,         // The handle passed in the vx_sdk_config_t structure
        vx_udp_frame_type frame_type,  // The UDP packet type
        void *payload_data,            // The data to be transmitted to the network
        int payload_data_len,          // The len of the data to be transmitted to the network
        void **header_out,             // Callback set - a pointer to header data (NULL if no header)
        int *header_len_out,           // Callback set - the length of the header data (0 if no header)
        void **trailer_out,            // Callback set - a pointer to trailer data (NULL if no trailer)
        int *trailer_len_out           // Callback set - the length of the trailer data (0 if no trailer)
        );

/**
 * Called after any UDP frame is transmitted.
 * The application can use this callback to deallocate the header and trailer, if necessary.
 */
typedef void (*pf_on_after_udp_frame_transmitted_t)(
        void *callback_handle,         // The handle passed in the vx_sdk_config_t structure
        vx_udp_frame_type frame_type,  // The UDP packet type
        void *payload_data,            // The data to be transmitted to the network
        int payload_data_len,          // The len of the data to be transmitted to the network
        void *header,                  // The header data passed in pf_on_before_udp_frame_transmitted
        int header_len,                // The length of the header data
        void *trailer,                 // The trailer data passed in pf_on_before_udp_frame_transmitted
        int trailer_len,               // The length of the trailer data
        int sent_bytes                 // The total number of bytes transmitted - < 0 indicates an error
        );

/**
 * Called after a thread is created.
 * The application can use this callback to monitor and profile thread creation.
 */
typedef void (*pf_on_thread_created_t)(void *callback_handle, const char *thread_name);

/**
 * Called before a thread is destructed.
 * The application can use this callback to monitor and profile thread destruction.
 */
typedef void (*pf_on_thread_exit_t)(void *callback_handle);

/**
 * Called when an audio processing unit is started in the audio processing thread.
 * No blocking operations should occur on this callback.
 */
typedef void (*pf_on_audio_unit_started_t)(void *callback_handle, const char *session_group_handle, const char *initial_target_uri);

/**
 * Called when an audio processing unit is stopped in the audio processing thread.
 * No blocking operations should occur on this callback.
 */
typedef void (*pf_on_audio_unit_stopped_t)(void *callback_handle, const char *session_group_handle, const char *initial_target_uri);

/**
 * Called after audio is read from the capture device.
 * No blocking operations should occur on this callback.
 */
typedef void (*pf_on_audio_unit_after_capture_audio_read_t)(
        void *callback_handle,
        const char *session_group_handle,
        const char *initial_target_uri,
        short *pcm_frames,
        int pcm_frame_count,
        int audio_frame_rate,
        int channels_per_frame
        );

/**
 * Called when an audio processing unit is about to send captured audio to the network from the audio processing thread.
 * No blocking operations should occur on this callback.
 */
typedef void (*pf_on_audio_unit_before_capture_audio_sent_t)(
        void *callback_handle,
        const char *session_group_handle,
        const char *initial_target_uri,
        short *pcm_frames,
        int pcm_frame_count,
        int audio_frame_rate,
        int channels_per_frame,
        int is_speaking
        );

/**
 * Called before an audio processing unit mixes the per-participant audio data to a single stream in the audio processing thread.
 * No blocking operations should occur on this callback.
 */
typedef void (*pf_on_audio_unit_before_recv_audio_mixed_t)(
        void *callback_handle,
        const char *session_group_handle,
        const char *initial_target_uri,
        vx_before_recv_audio_mixed_participant_data_t *participants_data,
        size_t num_participants);

/**
 * Called when an audio processing unit is about to write received audio to the render device in the audio processing thread.
 * No blocking operations should occur on this callback.
 */
typedef void (*pf_on_audio_unit_before_recv_audio_rendered_t)(
        void *callback_handle,
        const char *session_group_handle,
        const char *initial_target_uri,
        short *pcm_frames,
        int pcm_frame_count,
        int audio_frame_rate,
        int channels_per_frame,
        int is_silence
        );

/**
 * Called when the capture device status changes.
 * No blocking operations should occur on this callback.
 */
typedef void (*pf_on_audio_unit_capture_device_status_changed_t)(int);

/**
 * Called when an unexpected situation is encountered in the SDK.
 */
typedef void (*pf_on_assert_t)(int fatal);

/**
 * Configuration options that are passed to vx_initialize3().
 * \ingroup initialization
 */
typedef struct vx_sdk_config {
    /**
     * \deprecated Do not use this parameter, because it has no effect.
     * The number of threads used for encoding and decoding audio.
     * \note For client SDKs, this number must be 1.
     */
    int num_codec_threads;

    /**
     * \deprecated Do not use this parameter, because it has no effect.
     * The number of threads used for voice processing.
     * \note For client SDKs, this number must be 1.
     */
    int num_voice_threads;

    /**
     * \deprecated Do not use this parameter, because it has no effect.
     * The number of threads used for web requests.
     * \note For client SDKs, this number must be 1.
     */
    int num_web_threads;
    /**
     * The render source maximum queue depth.
     */
    int render_source_queue_depth_max;

    /**
     * The render source initial buffer count.
     */
    int render_source_initial_buffer_count;

    /**
     * The upstream jitter frame count.
     */
    int upstream_jitter_frame_count;

    /**
     * Indicate whether to allow shared capture devices (shared in the Vivox context only).
     */
    int allow_shared_capture_devices;

    /**
     * The maximum number of logins per user.
     */
    int max_logins_per_user;

    /**
     * A three-letter app ID.
     * \attention Do not set this value. For more information, contact your Vivox representative.
     */
    char app_id[3];

    /**
     * The certificate data directory where the certificate bundle is located.
     */
    char cert_data_dir[256];

    /**
     * A pointer to a function that is used to allocate memory.
     */
    void * (*pf_malloc_func)(size_t bytes);

    /**
     * A pointer to a function that is used to free memory.
     */
    void (*pf_free_func)(void *memory);

    /**
     * A pointer to a function that is used to reallocate memory.
     */
    void * (*pf_realloc_func)(void *memory, size_t bytes);

    /**
     * A pointer to a function that is used to allocate zeroed-out memory.
     */
    void * (*pf_calloc_func)(size_t num, size_t bytes);

    /**
     * A pointer to a function that is used to allocate aligned memory.
     */
    void *(*pf_malloc_aligned_func)(size_t alignment, size_t size);

    /**
     * A pointer to a function that is used to free aligned memory.
     */
    void (*pf_free_aligned_func)(void *memory);

    /**
     * Reserved for future use.
     */
    int reserved;

    /**
     * A handle for use in SPURS job queue functions.
     */
    void *job_queue_handle;

    /**
     * A function to synchronously queue a job to SPURS.
     * The job argument is a pointer CellSpursJobHeader structure.
     */
    int (*pf_queue_job_sync)(void *job_queue_handle, void *job, size_t size);

    /**
     * A function to asynchronously queue a job to SPURS.
     * The job argument is a pointer CellSpursJobHeader structure.
     */
    int (*pf_queue_job_async)(void *job_queue_handle, void *job, size_t size);

    /**
     * A processor affinity mask for SDK threads.
     * \note For more information, consult your documentation or contact your Vivox representative.
     */
    long long processor_affinity_mask;

    /**
     * A callback handle for message and logging notifications.
     */
    void *callback_handle;

    /**
     * Ensure that you are prepared to receive a logging callback immediately after calling vx_initialize3().
     */
    void (*pf_logging_callback)(void *callback_handle, vx_log_level level, const char *source, const char *message);

    /**
     * When the SDK message callback is called, call vx_get_message() until there are no more messages.
     */
    void (*pf_sdk_message_callback)(void *callback_handle);

    /**
     * The initial log level.
     */
    vx_log_level initial_log_level;

    /**
     * Disable audio device polling by using a timer.
     */
    int disable_device_polling;

    /**
     * For diagnostic purposes only.
     */
    int force_capture_silence;

    /**
     * Enable advanced automatic setting of audio levels.
     */
    int enable_advanced_auto_levels;

    /**
     * Called when an audio processing unit is started in the audio processing thread.
     * No blocking operations should occur on this callback.
     */
    pf_on_audio_unit_started_t pf_on_audio_unit_started;

    /**
     * Called when an audio processing unit is stopped in the audio processing thread.
     * No blocking operations should occur on this callback.
     */
    pf_on_audio_unit_stopped_t pf_on_audio_unit_stopped;

    /**
     * Called after audio is read from the capture device.
     * No blocking operations should occur on this callback.
     */
    pf_on_audio_unit_after_capture_audio_read_t pf_on_audio_unit_after_capture_audio_read;

    /**
     * Called when an audio processing unit is about to send captured audio to the network from the audio processing thread.
     * No blocking operations should occur on this callback.
     */
    pf_on_audio_unit_before_capture_audio_sent_t pf_on_audio_unit_before_capture_audio_sent;

    /**
     * Called before an audio processing unit mixes the per-participant audio data to a single stream in the audio processing thread.
     * No blocking operations should occur on this callback.
    */
    pf_on_audio_unit_before_recv_audio_mixed_t pf_on_audio_unit_before_recv_audio_mixed;

    /**
     * Called when an audio processing unit is about to write received audio to the render device in the audio processing thread.
     * No blocking operations should occur on this callback.
     */
    pf_on_audio_unit_before_recv_audio_rendered_t pf_on_audio_unit_before_recv_audio_rendered;

    /**
     * The number of 20 millisecond buffers for the capture device.
     */
    int capture_device_buffer_size_intervals;

    /**
     * The number of 20 millisecond buffers for the render device.
     */
    int render_device_buffer_size_intervals;

    /**
     * \note Only applicable to the Xbox One and iOS platforms.
     */
    int disable_audio_ducking;
    /**
     * Vivox Access Tokens (VAT) are a more scalable, usable, and extensible replacement
     * to the use of Access Control Lists for controlling access to Vivox resources.
     * This security token is generated by the game server and then validated by the Vivox system
     * to authorize certain Vivox operations at the time which those operations are to be performed.
     */
    int use_access_tokens;

    /**
     * If use_access_tokens is 1 and multiparty text is being used, set this to 1.
     * This can also be controlled by setting the VIVOX_ENABLE_MULTIPARTY_TEXT environment variable.
     */
    int enable_multiparty_text;

    /**
     * \attention Changes to this value must be coordinated with Vivox.
     * For most platforms, this uses a default of 1.
     */
    int enable_dtx;

    /**
     * The default codec mask that is used to initialize a connector's configured_codecs.
     */
    unsigned int default_codecs_mask;

    /**
     * Called before any UDP frame is transmitted.
     * This callback must be a non-blocking callback.
     * It is recommended that this callback complete in less than 1 millisecond.
     */
    pf_on_before_udp_frame_transmitted_t pf_on_before_udp_frame_transmitted;

    /**
     * Called after any UDP frame is transmitted.
     * The application can use this callback to deallocate the header and trailer, if necessary.
     */
    pf_on_after_udp_frame_transmitted_t pf_on_after_udp_frame_transmitted;

    /**
     * Enable fast network change detection.
     * The default value is 0.
     */
    int enable_fast_network_change_detection;

    /**
     * Use the operating system-configured proxy settings.
     * - The default value is 0.
     * - The value is 1 if the environment variable "VIVOX_USE_OS_PROXY_SETTINGS" is set.
     * \note Only applicable to the Windows platform.
     */
    int use_os_proxy_settings;

    /**
     * \attention Before changing this value, contact your developer support representative.
     * Enable persistent connections.
     * - The default value is 0.
     * - If the environment variable "VIVOX_ENABLE_PERSISTENT_HTTP" is set, the value is 1.
     * The use of proxies can interfere with any behavior that is controlled by this setting.
     * \note Only applicable to the Windows platform.
     */
    int enable_persistent_http;

    /**
     * \deprecated Do not use this parameter, because it has no effect.
     * The preferred server SIP port.
     * Set this parameter by using the environment variable "VIVOX_PREFERRED_SIP_PORT".
     * For development purposes, setting this parameter to a value of 0 will use the network configuration.
     * \note Setting this parameter to an incorrect value could result in delays in logging in or joining channels.
     * @deprecated
     */
    int preferred_sip_port;

    /**
     * \deprecated Do not use this parameter, because it has no effect.
     * By default, audio output goes to the mobile device's speakers, unless the value is set to 1.
     * On the iOS platform, when the audio session is set to the category "PlayAndRecord", the receiver,
     * which is the mobile device speaker that is put to your ear for voice calls, is used.
     * @deprecated
     */
    int default_render_to_receiver;

    /**
     * \deprecated Do not use this parameter, because it has no effect.
     * For platforms with soft mics, apply linear gain in dB before processing.
     * @deprecated
     */
    float mic_makeup_gain;

    /**
     * Called after a thread is created.
     * The application can use this callback to monitor and profile thread creation.
     */
    pf_on_thread_created_t pf_on_thread_created;

    /**
     * Called before a thread is destructed.
     * The application can use this callback to monitor and profile thread destruction.
     */
    pf_on_thread_exit_t pf_on_thread_exit;

    /**
     * \deprecated This function pointer is unused and is never called.
     * @deprecated
     */
    int (*pf_request_permission_for_network)(void);

    /**
     * Enable dynamic voice processing switching.
     * If enabled, the SDK automatically switches between hardware and software AECs.
     * - The default value is 1.
     * - To disable this capability, set the value to 0.
     */
    int dynamic_voice_processing_switching;

    /**
     * \attention This function is only called on specific platforms. For more information, contact Vivox.
     * If set, this function is called when the active capture device status is updated.
     */
    pf_on_audio_unit_capture_device_status_changed_t pf_on_audio_unit_capture_device_status_changed;

    /**
     * The number of millseconds to wait before disconnecting audio due to RTP timeout at the initial call time.
     * A zero or negative value turns off the guard, which is not recommended.
     */
    int never_rtp_timeout_ms;

    /**
     * The number of millseconds to wait before disconnecting audio due to RTP timeout after the call has been established.
     * A zero or negative value turns off the guard, which is not recommended.
     */
    int lost_rtp_timeout_ms;

    /**
     * Called when an unexpected situation is encountered in the SDK.
     */
    pf_on_assert_t pf_on_assert;
} vx_sdk_config_t;

#ifdef __cplusplus
}
#endif

#pragma pack(pop)