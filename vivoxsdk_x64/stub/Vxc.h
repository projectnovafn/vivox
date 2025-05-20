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
#include "VxcTypes.h"

#define VIVOX_SDK_HAS_CRASH_REPORTING 1
#define VIVOX_SDK_HAS_VOICE_FONTS 1
#define VIVOX_SDK_HAS_GROUP_IM 1
#define VIVOX_SDK_HAS_MUTE_SCOPE 1
#define VIVOX_SDK_HAS_PARTICIPANT_TYPE 1
#define VIVOX_SDK_HAS_NETWORK_MESSAGE 1
#define VIVOX_SDK_HAS_AUX_DIAGNOSTIC_STATE 1
#define VIVOX_SDK_SESSION_RENDER_AUDIO_OBSOLETE 1
#define VIVOX_SDK_SESSION_GET_LOCAL_AUDIO_INFO_OBSOLETE 1
#define VIVOX_SDK_SESSION_MEDIA_RINGBACK_OBSOLETE 1
#define VIVOX_SDK_SESSION_CONNECT_OBSOLETE 1
#define VIVOX_SDK_EVT_SESSION_PARTICIPANT_LIST_OBSOLETE 1
#define VIVOX_SDK_HAS_INTEGRATED_PROXY 1
#define VIVOX_SDK_HAS_NO_CHANNEL_FOLDERS 1
#define VIVOX_SDK_HAS_NO_SCORE 1
#define VIVOX_SDK_HAS_GENERIC_APP_NOTIFICATIONS_ONLY 1
#define VIVOX_SDK_HAS_FRAME_TOTALS 1
#define VIVOX_SDK_NO_LEGACY_RECORDING 1
#define VIVOX_SDK_NO_IS_AD_PLAYING 1
#define VIVOX_SDK_HAS_ACCOUNT_SEND_MSG 1
#define VIVOX_SDK_HAS_PLC_STATS 1
#define VIVOX_SDK_HAS_DEVICE_ADDED_REMOVED 1
#define VIVOX_SDK_HAS_ADVANCED_AUDIO_LEVELS 1
#define VIVOX_SDK_HAS_AUDIO_UNIT_CALLBACKS 1
#define VIVOX_TYPES_ONLY 1

#define VX_GET_MESSAGE_NO_MESSAGE -1
#define VX_GET_MESSAGE_AVAILABLE 0
#define VX_GET_MESSAGE_FAILURE 1

#pragma pack(push)
#pragma pack(8)

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * A request cookie type.
     * Used when passing in requests to the SDK.
     */
    typedef char* VX_COOKIE;

    /**
     * A generic handle type for state objects (for example: accounts, connectors, sessions, or session groups).
     */
    typedef VX_COOKIE VX_HANDLE;

    typedef unsigned int VX_SDK_HANDLE;

    typedef __time64_t vx_time_t;

#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a cookie.
     * \ingroup memorymanagement
     */
    VIVOXSDK_DLLEXPORT int vx_cookie_create(const char* value, VX_COOKIE* cookie);

    /**
     * Free a cookie.
     * \ingroup memorymanagement
     */
    VIVOXSDK_DLLEXPORT int vx_cookie_free(VX_COOKIE* cookie);
#endif

    /**
     * A type of STUN probe.
     */
    typedef enum {
        /**
         * Use the default as configured on the account management server.
         */
        attempt_stun_unspecified = 0,

        /**
         * Use STUN.
         */
        attempt_stun_on = 1,

        /**
         * Do not use STUN.
         */
        attempt_stun_off = 2
    } vx_attempt_stun;

    /**
     * A type of API mode.
     * The required setting is connector_mode_normal.
     */
    typedef enum {
        /**
         * The default and only valid value.
         */
        connector_mode_normal = 0,

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        connector_mode_legacy = 1
    } vx_connector_mode;

    /**
     * A type of API mode.
     * The recommended setting is connector_mode_normal.
     */
    typedef enum {
        /**
         * Each handle is unique for the lifetime of the connector.
         */
        session_handle_type_unique = 0,

        /**
         * Handles are sequential integers.
         */
        session_handle_type_legacy = 1,

        /**
         * Handles are hierarchical numeric.
         */
        session_handle_type_heirarchical_numeric = 2,

        /**
         * Handles are hierarchical unique.
         */
        session_handle_type_heirarchical_unique = 3
    } vx_session_handle_type;

    /**
     * A type of logging for the application.
     * The Vivox SDK is capable of logging to a native log file and/or sending log information
     * to the client application through a callback method registered with the SDK.
     */
    typedef enum {
        /**
         * Unused.
         */
        log_to_none = 0,

        /**
         * \deprecated File logging is not supported. Use log_to_none instead.
         * Log to the native configured logfile.
         * @deprecated
         */
        log_to_file = 1,

        /**
         * Send log information to the client application through the registered callback method.
         */
        log_to_callback = 2,

        /**
         * \deprecated File logging is not supported. Use log_to_callback instead.
         * Log to the native configured log file and the client application through the registered callback method.
         * @deprecated
         */
        log_to_file_and_callback = 3
    } vx_log_type;

    /**
     * Used as a run time type indicator for all messages passed between the application and SDK.
     */
    typedef enum {
        /**
         * Unused.
         */
        msg_none = 0,

        /**
         * Indicates that the message is a request.
         * @see vx_req_base_t
         */
        msg_request = 1,

        /**
         * Indicates that the message is a response.
         * @see vx_resp_base_t
         */
        msg_response = 2,

        /**
         * Indicates that the message is an event.
         * @see vx_evt_base_t
         */
        msg_event = 3
    } vx_message_type;

    typedef enum {
        /**
         * Stop a recording.
         */
        VX_SESSIONGROUP_RECORDING_CONTROL_STOP = 0,

        /**
         * Start a recording.
         */
        VX_SESSIONGROUP_RECORDING_CONTROL_START = 1,

        /**
         * Flush a continuous recording.
         */
        VX_SESSIONGROUP_RECORDING_CONTROL_FLUSH_TO_FILE = 2
    } vx_sessiongroup_recording_control_type;

    typedef enum {
        /**
         * Stop audio injection.
         */
        VX_SESSIONGROUP_AUDIO_INJECTION_CONTROL_STOP = 0,
        vx_sessiongroup_audio_injection_control_stop = VX_SESSIONGROUP_AUDIO_INJECTION_CONTROL_STOP,

        /**
         * Start audio injection (only if currently stopped).
         */
        VX_SESSIONGROUP_AUDIO_INJECTION_CONTROL_START = 1,
        vx_sessiongroup_audio_injection_control_start = VX_SESSIONGROUP_AUDIO_INJECTION_CONTROL_START,

        /**
         * Restart audio injection (start if currently stopped, or stop if currently injecting and then restart).
         */
        VX_SESSIONGROUP_AUDIO_INJECTION_CONTROL_RESTART = 2,
        vx_sessiongroup_audio_injection_control_restart = VX_SESSIONGROUP_AUDIO_INJECTION_CONTROL_RESTART,

        VX_SESSIONGROUP_AUDIO_INJECTION_CONTROL_MIN = VX_SESSIONGROUP_AUDIO_INJECTION_CONTROL_STOP,
        vx_sessiongroup_audio_injection_control_min = vx_sessiongroup_audio_injection_control_stop,
        VX_SESSIONGROUP_AUDIO_INJECTION_CONTROL_MAX = VX_SESSIONGROUP_AUDIO_INJECTION_CONTROL_RESTART,
        vx_sessiongroup_audio_injection_control_max = vx_sessiongroup_audio_injection_control_restart
    } vx_sessiongroup_audio_injection_control_type;

    typedef enum {
        /**
         * Stop playback.
         * When playback is stopped, it closes the playback file and generates a media frame played event,
         * with 0 for the first frame, and 0 for the total frames.
         */
        VX_SESSIONGROUP_PLAYBACK_CONTROL_STOP = 0,

        /**
         * Start playback.
         */
        VX_SESSIONGROUP_PLAYBACK_CONTROL_START = 1,

        /**
         * Pause playback.
         */
        VX_SESSIONGROUP_PLAYBACK_CONTROL_PAUSE = 3,

        /**
         * Unpause playback.
         */
        VX_SESSIONGROUP_PLAYBACK_CONTROL_UNPAUSE = 4
    } vx_sessiongroup_playback_control_type;

    typedef enum {
        /**
         * Normal mode playback.
         */
        VX_SESSIONGROUP_PLAYBACK_MODE_NORMAL = 0,

        /**
         * Vox mode playback: Catch-up mode.
         * Skip all silence periods.
         * Playback at desired speed.
         */
        VX_SESSIONGROUP_PLAYBACK_MODE_VOX = 1
    } vx_sessiongroup_playback_mode;

    /**
     * The methods in which communication can be controlled.
     */
    typedef enum {
        /**
         * The issuing user does not hear the blocked user, and the blocked user does not hear the issuing user.
         */
        vx_control_communications_operation_block = 0,

        /**
         * The issuing user does hear the blocked user, and the blocked user does hear the issuing user,
         * unless the blocked user has also blocked the issuing user.
         */
        vx_control_communications_operation_unblock = 1,
        vx_control_communications_operation_list = 2,
        vx_control_communications_operation_block_list = 2, // Alias for vx_control_communications_operation_list
        vx_control_communications_operation_clear = 3,
        vx_control_communications_operation_clear_block_list = 3, // Alias for vx_control_communications_operation_clear
        vx_control_communications_operation_mute = 4,
        vx_control_communications_operation_unmute = 5,
        vx_control_communications_operation_mute_list = 6,
        vx_control_communications_operation_clear_mute_list = 7
    } vx_control_communications_operation;

    typedef enum {
        media_type_none = 0,
        media_type_text = 1,
        media_type_audio = 2,
        media_type_video = 3,
        media_type_audiovideo = 4
    } vx_media_type;

    typedef enum {
        termination_status_none = 0,
        termination_status_busy = 1,
        termination_status_decline = 2
    } vx_termination_status;

    typedef enum {
        diagnostic_dump_level_all = 0,
        diagnostic_dump_level_sessions = 1
    } vx_diagnostic_dump_level;

    typedef enum {
        media_ringback_none = 0,
        media_ringback_ringing = 1,       // 180
        // media_ringback_answer = 2,     // 200
        media_ringback_busy = 3,          // 486
        // media_ringback_terminated = 4  // 487
    } vx_media_ringback;

    typedef enum {
        channel_type_normal = 0,
        channel_type_positional = 2
    } vx_channel_type;

    typedef enum {
        channel_mode_none = 0,
        channel_mode_normal = 1,
        channel_mode_presentation = 2,
        channel_mode_lecture = 3,
        channel_mode_open = 4,
        channel_mode_auditorium = 5
    } vx_channel_mode;

    typedef enum {
        channel_search_type_all = 0,
        channel_search_type_non_positional = 1,
        channel_search_type_positional = 2
    } vx_channel_search_type;

    typedef enum {
        channel_moderation_type_all = 0,
        channel_moderation_type_current_user = 1
    } vx_channel_moderation_type;

    /**
     * The type of the session group specified at session group creation time.
     */
    typedef enum {
        /**
         * Normal type for general use.
         */
        sessiongroup_type_normal = 0,

        /**
         * Playback type.
         * Only use this for playing back a Vivox recording.
         * \note Live sessions cannot be added to this type of session group.
         */
        sessiongroup_type_playback = 1
    } vx_sessiongroup_type;

    /**
     * Indicates the reason why a participant was removed from a session.
     */
    typedef enum {
        participant_left = 0,
        participant_timeout = 1,
        participant_kicked = 2,
        participant_banned = 3
    } vx_participant_removed_reason;

    typedef struct vx_message_base {
        vx_message_type type;
        VX_SDK_HANDLE sdk_handle;
        unsigned long long create_time_ms;
        unsigned long long last_step_ms;
    } vx_message_base_t;

    /**
     * The set of requests that can be issued.
     */
    typedef enum {
        req_none = 0,
        req_connector_create = 1,
        req_connector_initiate_shutdown = 2,
        req_account_login = 3,
        req_account_logout = 4,
        req_account_set_login_properties = 5,
        req_sessiongroup_create = 6,
        req_sessiongroup_terminate = 7,
        req_sessiongroup_add_session = 8,
        req_sessiongroup_remove_session = 9,
        req_sessiongroup_set_focus = 10,
        req_sessiongroup_unset_focus = 11,
        req_sessiongroup_reset_focus = 12,
        req_sessiongroup_set_tx_session = 13,
        req_sessiongroup_set_tx_all_sessions = 14,
        req_sessiongroup_set_tx_no_session = 15,
        req_session_create = 16,  /**< Do not use. Instead, use req_sessiongroup_add_session */
        req_session_media_connect = 18,
        req_session_media_disconnect = 19,
        req_session_terminate = 21,
        req_session_mute_local_speaker = 22,
        req_session_set_local_speaker_volume = 23,
        req_session_set_local_render_volume = 24,
        req_session_channel_invite_user = 25,
        req_session_set_participant_volume_for_me = 26,
        req_session_set_participant_mute_for_me = 27,
        req_session_set_3d_position = 28,
        req_session_set_voice_font = 29,
        req_account_channel_add_acl = 53,
        req_account_channel_remove_acl = 54,
        req_account_channel_get_acl = 55,
        req_channel_mute_user = 56,
        req_channel_ban_user = 57,
        req_channel_get_banned_users = 58,
        req_channel_kick_user = 59,
        req_channel_mute_all_users = 60,
        req_connector_mute_local_mic = 61,
        req_connector_mute_local_speaker = 62,
        req_connector_set_local_mic_volume = 63,
        req_connector_set_local_speaker_volume = 64,
        req_connector_get_local_audio_info = 65,
        req_account_buddy_set = 67,
        req_account_buddy_delete = 68,
        req_account_list_buddies_and_groups = 71,
        req_session_send_message = 72,
        req_account_set_presence = 73,
        req_account_send_subscription_reply = 74,
        req_session_send_notification = 75,
        req_account_create_block_rule = 76,
        req_account_delete_block_rule = 77,
        req_account_list_block_rules = 78,
        req_account_create_auto_accept_rule = 79,
        req_account_delete_auto_accept_rule = 80,
        req_account_list_auto_accept_rules = 81,
        req_account_update_account = 82,  /**< Deprecated */
        req_account_get_account = 83,  /**< Deprecated */
        req_account_send_sms = 84,
        req_aux_connectivity_info = 86,
        req_aux_get_render_devices = 87,
        req_aux_get_capture_devices = 88,
        req_aux_set_render_device = 89,
        req_aux_set_capture_device = 90,
        req_aux_get_mic_level = 91,
        req_aux_get_speaker_level = 92,
        req_aux_set_mic_level = 93,
        req_aux_set_speaker_level = 94,
        req_aux_render_audio_start = 95,
        req_aux_render_audio_stop = 96,
        req_aux_capture_audio_start = 97,
        req_aux_capture_audio_stop = 98,
        req_aux_global_monitor_keyboard_mouse = 99,
        req_aux_set_idle_timeout = 100,
        req_aux_create_account = 101,
        req_aux_reactivate_account = 102,
        req_aux_deactivate_account = 103,
        req_account_post_crash_dump = 104,
        req_aux_reset_password = 105,
        req_sessiongroup_set_session_3d_position = 106,
        req_account_get_session_fonts = 107,
        req_account_get_template_fonts = 108,
        req_aux_start_buffer_capture = 109,
        req_aux_play_audio_buffer = 110,
        req_sessiongroup_control_recording = 111,
        req_sessiongroup_control_playback = 112,
        req_sessiongroup_set_playback_options = 113,
        req_session_text_connect = 114,
        req_session_text_disconnect = 115,
        req_channel_set_lock_mode = 116,
        req_aux_render_audio_modify = 117,
        req_session_send_dtmf = 118,
        req_aux_set_vad_properties = 120,
        req_aux_get_vad_properties = 121,
        req_sessiongroup_control_audio_injection = 124,
        req_account_channel_change_owner = 125,  /**< Not yet implemented (3030) */
        req_account_send_user_app_data = 128,  /**< Not yet implemented (3030) */
        req_aux_diagnostic_state_dump = 129,
        req_account_web_call = 130,
        req_account_anonymous_login = 131,
        req_account_authtoken_login = 132,
        req_sessiongroup_get_stats = 133,
        req_account_send_message = 134,
        req_aux_notify_application_state_change = 135,
        req_account_control_communications = 136,
        req_session_archive_query = 137,
        req_account_archive_query = 138,
        req_session_transcription_control = 139,
        req_aux_get_derumbler_properties = 140,
        req_aux_set_derumbler_properties = 141,
        req_session_chat_history_query = 142,
        req_account_chat_history_query = 143,
        req_max = req_account_chat_history_query + 1
    } vx_request_type;

    /**
     * Response types that are reported back to the calling app.
     */
    typedef enum {
        resp_none = 0,
        resp_connector_create = 1,
        resp_connector_initiate_shutdown = 2,
        resp_account_login = 3,
        resp_account_logout = 4,
        resp_account_set_login_properties = 5,
        resp_sessiongroup_create = 6,
        resp_sessiongroup_terminate = 7,
        resp_sessiongroup_add_session = 8,
        resp_sessiongroup_remove_session = 9,
        resp_sessiongroup_set_focus = 10,
        resp_sessiongroup_unset_focus = 11,
        resp_sessiongroup_reset_focus = 12,
        resp_sessiongroup_set_tx_session = 13,
        resp_sessiongroup_set_tx_all_sessions = 14,
        resp_sessiongroup_set_tx_no_session = 15,
        resp_session_create = 16,  /**< Do not use. */
        resp_session_media_connect = 18,
        resp_session_media_disconnect = 19,
        resp_session_terminate = 21,
        resp_session_mute_local_speaker = 22,
        resp_session_set_local_speaker_volume = 23,
        resp_session_set_local_render_volume = 24,
        resp_session_channel_invite_user = 25,
        resp_session_set_participant_volume_for_me = 26,
        resp_session_set_participant_mute_for_me = 27,
        resp_session_set_3d_position = 28,
        resp_session_set_voice_font = 29,
        resp_account_channel_get_list = 33,
        resp_account_channel_add_acl = 53,
        resp_account_channel_remove_acl = 54,
        resp_account_channel_get_acl = 55,
        resp_channel_mute_user = 56,
        resp_channel_ban_user = 57,
        resp_channel_get_banned_users = 58,
        resp_channel_kick_user = 59,
        resp_channel_mute_all_users = 60,
        resp_connector_mute_local_mic = 61,
        resp_connector_mute_local_speaker = 62,
        resp_connector_set_local_mic_volume = 63,
        resp_connector_set_local_speaker_volume = 64,
        resp_connector_get_local_audio_info = 65,
        resp_account_buddy_set = 67,
        resp_account_buddy_delete = 68,
        resp_account_list_buddies_and_groups = 71,
        resp_session_send_message = 72,
        resp_account_set_presence = 73,
        resp_account_send_subscription_reply = 74,
        resp_session_send_notification = 75,
        resp_account_create_block_rule = 76,
        resp_account_delete_block_rule = 77,
        resp_account_list_block_rules = 78,
        resp_account_create_auto_accept_rule = 79,
        resp_account_delete_auto_accept_rule = 80,
        resp_account_list_auto_accept_rules = 81,
        resp_account_update_account = 82,  /**< Deprecated */
        resp_account_get_account = 83,  /**< Deprecated */
        resp_account_send_sms = 84,
        resp_aux_connectivity_info = 86,
        resp_aux_get_render_devices = 87,
        resp_aux_get_capture_devices = 88,
        resp_aux_set_render_device = 89,
        resp_aux_set_capture_device = 90,
        resp_aux_get_mic_level = 91,
        resp_aux_get_speaker_level = 92,
        resp_aux_set_mic_level = 93,
        resp_aux_set_speaker_level = 94,
        resp_aux_render_audio_start = 95,
        resp_aux_render_audio_stop = 96,
        resp_aux_capture_audio_start = 97,
        resp_aux_capture_audio_stop = 98,
        resp_aux_global_monitor_keyboard_mouse = 99,
        resp_aux_set_idle_timeout = 100,
        resp_aux_create_account = 101,
        resp_aux_reactivate_account = 102,
        resp_aux_deactivate_account = 103,
        resp_account_post_crash_dump = 104,
        resp_aux_reset_password = 105,
        resp_sessiongroup_set_session_3d_position = 106,
        resp_account_get_session_fonts = 107,
        resp_account_get_template_fonts = 108,
        resp_aux_start_buffer_capture = 109,
        resp_aux_play_audio_buffer = 110,
        resp_sessiongroup_control_recording = 111,
        resp_sessiongroup_control_playback = 112,
        resp_sessiongroup_set_playback_options = 113,
        resp_session_text_connect = 114,
        resp_session_text_disconnect = 115,
        resp_channel_set_lock_mode = 116,
        resp_aux_render_audio_modify = 117,
        resp_session_send_dtmf = 118,
        resp_aux_set_vad_properties = 120,
        resp_aux_get_vad_properties = 121,
        resp_sessiongroup_control_audio_injection = 124,
        resp_account_channel_change_owner = 125,  /**< Not yet implemented (3030) */
        resp_account_send_user_app_data = 128,  /**< Not yet implemented (3030) */
        resp_aux_diagnostic_state_dump = 129,
        resp_account_web_call = 130,
        resp_account_anonymous_login = 131,
        resp_account_authtoken_login = 132,
        resp_sessiongroup_get_stats = 133,
        resp_account_send_message = 134,
        resp_aux_notify_application_state_change = 135,
        resp_account_control_communications = 136,
        resp_session_archive_query = 137,
        resp_account_archive_query = 138,
        resp_session_transcription_control = 139,
        resp_aux_get_derumbler_properties = 140,
        resp_aux_set_derumbler_properties = 141,
        resp_session_chat_history_query = 142,
        resp_account_chat_history_query = 143,
        resp_max = resp_account_chat_history_query + 1
    } vx_response_type;

    /**
     * Event types that are reported back to the calling app.
     */
    typedef enum {
        evt_none = 0,
        evt_account_login_state_change = 2,
        evt_buddy_presence = 7,
        evt_subscription = 8,
        evt_session_notification = 9,
        evt_message = 10,
        evt_aux_audio_properties = 11,
        evt_buddy_changed = 15,
        evt_buddy_group_changed = 16,
        evt_buddy_and_group_list_changed = 17,
        evt_keyboard_mouse = 18,
        evt_idle_state_changed = 19,
        evt_media_stream_updated = 20,
        evt_text_stream_updated = 21,
        evt_sessiongroup_added = 22,
        evt_sessiongroup_removed = 23,
        evt_session_added = 24,
        evt_session_removed = 25,
        evt_participant_added = 26,
        evt_participant_removed = 27,
        evt_participant_updated = 28,
        evt_sessiongroup_playback_frame_played = 30,
        evt_session_updated = 31,
        evt_sessiongroup_updated = 32,
        evt_media_completion = 33,
        evt_server_app_data = 35,
        evt_user_app_data = 36,
        evt_network_message = 38,
        evt_voice_service_connection_state_changed = 39,
        evt_publication_state_changed = 40,
        evt_audio_device_hot_swap = 41,
        evt_user_to_user_message = 42,
        evt_session_archive_message = 43,
        evt_session_archive_query_end = 44,
        evt_account_archive_message = 45,
        evt_account_archive_query_end = 46,
        evt_account_send_message_failed = 47,
        evt_transcribed_message = 48,
        evt_tts_injection_started = 49,
        evt_tts_injection_ended = 50,
        evt_tts_injection_failed = 51,
        evt_stt_failed = 52,
        evt_max = evt_stt_failed + 1
    } vx_event_type;

    typedef struct vx_req_base {
        vx_message_base_t message;
        vx_request_type type;
        VX_COOKIE cookie;
        void* vcookie;
    } vx_req_base_t;

    typedef struct vx_resp_base {
        vx_message_base_t message;
        vx_response_type type;
        int return_code;
        int status_code;
        char* status_string;
        vx_req_base_t* request;
        char* extended_status_info;
    } vx_resp_base_t;

    typedef struct vx_evt_base {
        vx_message_base_t message;
        vx_event_type type;
        char* extended_status_info;
    } vx_evt_base_t;

    typedef enum {
        ND_E_NO_ERROR = 0,
        ND_E_TEST_NOT_RUN = 1,
        ND_E_NO_INTERFACE = 2,
        ND_E_NO_INTERFACE_WITH_GATEWAY = 3,
        ND_E_NO_INTERFACE_WITH_ROUTE = 4,
        ND_E_TIMEOUT = 5,
        ND_E_CANT_ICMP = 6,
        ND_E_CANT_RESOLVE_VIVOX_UDP_SERVER = 7,
        ND_E_CANT_RESOLVE_ROOT_DNS_SERVER = 8,
        ND_E_CANT_CONVERT_LOCAL_IP_ADDRESS = 9,
        ND_E_CANT_CONTACT_STUN_SERVER_ON_UDP_PORT_3478 = 10,
        ND_E_CANT_CREATE_TCP_SOCKET = 11,
        ND_E_CANT_LOAD_ICMP_LIBRARY = 12,
        ND_E_CANT_FIND_SENDECHO2_PROCADDR = 13,
        ND_E_CANT_CONNECT_TO_ECHO_SERVER = 14,
        ND_E_ECHO_SERVER_LOGIN_SEND_FAILED = 15,
        ND_E_ECHO_SERVER_LOGIN_RECV_FAILED = 16,
        ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_STATUS = 17,
        ND_E_ECHO_SERVER_LOGIN_RESPONSE_FAILED_STATUS = 18,
        ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_SESSIONID = 19,
        ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_SIPPORT = 20,
        ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_AUDIORTP = 21,
        ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_AUDIORTCP = 22,
        ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_VIDEORTP = 23,
        ND_E_ECHO_SERVER_LOGIN_RESPONSE_MISSING_VIDEORTCP = 24,
        ND_E_ECHO_SERVER_CANT_ALLOCATE_SIP_SOCKET = 25,
        ND_E_ECHO_SERVER_CANT_ALLOCATE_MEDIA_SOCKET = 26,
        ND_E_ECHO_SERVER_SIP_UDP_SEND_FAILED = 27,
        ND_E_ECHO_SERVER_SIP_UDP_RECV_FAILED = 28,
        ND_E_ECHO_SERVER_SIP_TCP_SEND_FAILED = 29,
        ND_E_ECHO_SERVER_SIP_TCP_RECV_FAILED = 30,
        ND_E_ECHO_SERVER_SIP_NO_UDP_OR_TCP = 31,
        ND_E_ECHO_SERVER_SIP_NO_UDP = 32,
        ND_E_ECHO_SERVER_SIP_NO_TCP = 33,
        ND_E_ECHO_SERVER_SIP_MALFORMED_TCP_PACKET = 34,
        ND_E_ECHO_SERVER_SIP_UDP_DIFFERENT_LENGTH = 35,
        ND_E_ECHO_SERVER_SIP_UDP_DATA_DIFFERENT = 36,
        ND_E_ECHO_SERVER_SIP_TCP_PACKETS_DIFFERENT = 37,
        ND_E_ECHO_SERVER_SIP_TCP_PACKETS_DIFFERENT_SIZE = 38,
        ND_E_ECHO_SERVER_LOGIN_RECV_FAILED_TIMEOUT = 39,
        ND_E_ECHO_SERVER_TCP_SET_ASYNC_FAILED = 40,
        ND_E_ECHO_SERVER_UDP_SET_ASYNC_FAILED = 41,
        ND_E_ECHO_SERVER_CANT_RESOLVE_NAME = 42
    } ND_ERROR;

    typedef enum {
        ND_TEST_LOCATE_INTERFACE = 0,
        ND_TEST_PING_GATEWAY = 1,
        ND_TEST_DNS = 2,
        ND_TEST_STUN = 3,
        ND_TEST_ECHO = 4,
        ND_TEST_ECHO_SIP_FIRST_PORT = 5,
        ND_TEST_ECHO_SIP_FIRST_PORT_INVITE_REQUEST = 6,
        ND_TEST_ECHO_SIP_FIRST_PORT_INVITE_RESPONSE = 7,
        ND_TEST_ECHO_SIP_FIRST_PORT_REGISTER_REQUEST = 8,
        ND_TEST_ECHO_SIP_FIRST_PORT_REGISTER_RESPONSE = 9,
        ND_TEST_ECHO_SIP_SECOND_PORT = 10,
        ND_TEST_ECHO_SIP_SECOND_PORT_INVITE_REQUEST = 11,
        ND_TEST_ECHO_SIP_SECOND_PORT_INVITE_RESPONSE = 12,
        ND_TEST_ECHO_SIP_SECOND_PORT_REGISTER_REQUEST = 13,
        ND_TEST_ECHO_SIP_SECOND_PORT_REGISTER_RESPONSE = 14,
        ND_TEST_ECHO_MEDIA = 15,
        ND_TEST_ECHO_MEDIA_LARGE_PACKET = 16
    } ND_TEST_TYPE;

    /**
     * Determine how incoming calls are handled.
     * Set at login.
     */
    typedef enum {
        /**
         * Not valid for use.
         */
        mode_none = 0,

        /**
         * \deprecated This is deprecated and should not be used.
         * The incoming call is automatically connected if a call is not already established.
         * @deprecated
         */
        mode_auto_answer = 1,

        /**
         * Requires the client to explicitly answer the incoming call.
         */
        mode_verify_answer = 2,

        /**
         * The incoming call is automatically answered with a 486 busy.
         */
        mode_busy_answer = 3
    } vx_session_answer_mode;

    typedef enum {
        mode_auto_accept = 0,
        mode_auto_add = 1,
        mode_block = 2,
        mode_hide = 3,
        mode_application = 4
    } vx_buddy_management_mode;

    typedef enum {
        rule_none = 0,
        rule_allow = 1,
        rule_block = 2,
        rule_hide = 3
    } vx_rule_type;

    typedef enum {
        type_none = 0,
        type_root = 1,
        type_user = 2
    } vx_font_type;

    typedef enum {
        status_none = 0,
        status_free = 1,
        status_not_free = 2
    } vx_font_status;

    typedef enum {
        subscription_presence = 0
    } vx_subscription_type;

    typedef enum {
        notification_not_typing = 0,
        notification_typing = 1,
        notification_hand_lowered = 2,
        notification_hand_raised = 3,
        notification_min = notification_not_typing,
        notification_max = notification_hand_raised
    } vx_notification_type;

    /**
     */
    typedef enum {
        dtmf_0 = 0,
        dtmf_1 = 1,
        dtmf_2 = 2,
        dtmf_3 = 3,
        dtmf_4 = 4,
        dtmf_5 = 5,
        dtmf_6 = 6,
        dtmf_7 = 7,
        dtmf_8 = 8,
        dtmf_9 = 9,
        dtmf_pound = 10,
        dtmf_star = 11,
        dtmf_A = 12,
        dtmf_B = 13,
        dtmf_C = 14,
        dtmf_D = 15,
        dtmf_max = dtmf_D
    } vx_dtmf_type;

    typedef enum {
        text_mode_disabled = 0,
        text_mode_enabled = 1
    } vx_text_mode;

    typedef enum {
        channel_unlock = 0,
        channel_lock = 1
    } vx_channel_lock_mode;

    typedef enum {
        mute_scope_all = 0,
        mute_scope_audio = 1,
        mute_scope_text = 2
    } vx_mute_scope;

    /**
     * Hold a recorded audio frame.
     */
    typedef enum {
        VX_RECORDING_FRAME_TYPE_DELTA = 0,
        VX_RECORDING_FRAME_TYPE_CONTROL = 1
    } vx_recording_frame_type_t;

    typedef enum {
        op_none = 0,
        op_safeupdate = 1,
        op_delete = 2
    } vx_audiosource_operation;

    typedef enum {
        aux_audio_properties_none = 0
    } vx_aux_audio_properties_state;

    typedef enum {
        login_state_logged_out = 0,
        login_state_logged_in = 1,
        login_state_logging_in = 2,
        login_state_logging_out = 3,
        login_state_resetting = 4,
        login_state_error = 100
    } vx_login_state_change_state;

    typedef enum {
        publication_state_success = 0,
        publication_state_transient_error = 1,
        publication_state_permanent_error = 2
    } vx_publication_state_change_state;

    typedef enum {
        buddy_presence_unknown = 0,  /**< OBSOLETE */
        buddy_presence_pending = 1,  /**< OBSOLETE */
        buddy_presence_online = 2,
        buddy_presence_busy = 3,
        buddy_presence_brb = 4,
        buddy_presence_away = 5,
        buddy_presence_onthephone = 6,
        buddy_presence_outtolunch = 7,
        buddy_presence_custom = 8,  /**< OBSOLETE */
        buddy_presence_online_slc = 9,  /**< OBSOLETE */
        buddy_presence_closed = 0,  /**< OBSOLETE */
        buddy_presence_offline = 0,
        buddy_presence_chat = 10,
        buddy_presence_extended_away = 11,
        buddy_presence_min = buddy_presence_unknown,
        buddy_presence_max = buddy_presence_extended_away
    } vx_buddy_presence_state;

    typedef enum {
        session_notification_none = 0
    } vx_session_notification_state;

    typedef enum {
        message_none = 0
    } vx_message_state;

    typedef enum {
        // NB: Keep in sync with enum TextState in sessionproperties.h
        session_text_disconnected = 0,
        session_text_connected = 1,
        session_text_connecting = 2,
        session_text_disconnecting = 3
    } vx_session_text_state;

    typedef enum {
        // NB: Keep in sync with enum MediaState in sessionproperties.h
        // NB: MediaState has the additional state MediaStateIncoming, which is mapped to session_media_ringing or session_media_disconnected in different places.
        session_media_disconnected = 1,
        session_media_connected = 2,
        session_media_ringing = 3,
        session_media_connecting = 6,
        session_media_disconnecting = 7
    } vx_session_media_state;

    typedef enum {
        participant_user = 0,
        part_user = participant_user,  // For backward compatibility.

        participant_moderator = 1,
        part_moderator = participant_moderator,  // For backward compatibility.

        participant_owner = 2,
        part_focus = participant_owner  // For backward compatibility.
    } vx_participant_type;

    typedef enum {
        orientation_default = 0,
        orientation_legacy = 1,
        orientation_vivox = 2
    } orientation_type;

    typedef enum {
        media_completion_type_none = 0,
        aux_buffer_audio_capture = 1,
        aux_buffer_audio_render = 2,
        sessiongroup_audio_injection = 3
    } vx_media_completion_type;

    /**
     * Participant media flags.
     */
#define VX_MEDIA_FLAGS_AUDIO 0x1
#define VX_MEDIA_FLAGS_TEXT  0x2

     // Buddy for state dump.
    typedef struct vx_state_buddy_contact {
        vx_buddy_presence_state presence;
        char* display_name;
        char* application;
        char* custom_message;
        char* contact;
        char* priority;
        char* id;
    } vx_state_buddy_contact_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_state_buddy_contact_create(vx_state_buddy_contact_t** contact);
    VIVOXSDK_DLLEXPORT int vx_state_buddy_contact_free(vx_state_buddy_contact_t* contact);
#endif
    typedef vx_state_buddy_contact_t* vx_state_buddy_contact_ref_t;
    typedef vx_state_buddy_contact_ref_t* vx_state_buddy_contact_list_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_state_buddy_contact_list_create(int size, vx_state_buddy_contact_list_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_state_buddy_contact_list_free(vx_state_buddy_contact_t** list, int size);
#endif

    // Buddy for state dump.
    typedef struct vx_state_buddy {
        char* buddy_uri;
        char* display_name;
        int parent_group_id;
        char* buddy_data;
        // char* account_name;
        int state_buddy_contact_count;
        vx_state_buddy_contact_t** state_buddy_contacts;
    } vx_state_buddy_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_state_buddy_create(vx_state_buddy_t** buddy);
    VIVOXSDK_DLLEXPORT int vx_state_buddy_free(vx_state_buddy_t* buddy);
#endif
    typedef vx_state_buddy_t* vx_state_buddy_ref_t;
    typedef vx_state_buddy_ref_t* vx_state_buddy_list_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_state_buddy_list_create(int size, vx_state_buddy_list_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_state_buddy_list_free(vx_state_buddy_t** list, int size);
#endif

    typedef struct vx_state_buddy_group {
        int group_id;
        char* group_name;
        char* group_data;
    } vx_state_buddy_group_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_state_buddy_group_create(vx_state_buddy_group_t** group);
    VIVOXSDK_DLLEXPORT int vx_state_buddy_group_free(vx_state_buddy_group_t* group);
#endif
    typedef vx_state_buddy_group_t* vx_state_buddy_group_ref_t;
    typedef vx_state_buddy_group_ref_t* vx_state_buddy_group_list_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_state_buddy_group_list_create(int size, vx_state_buddy_group_list_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_state_buddy_group_list_free(vx_state_buddy_group_t** list, int size);
#endif

    /**
     * Channel participant.
     */
    typedef struct vx_participant {
        char* uri;
        char* first_name;
        char* last_name;
        char* display_name;
        char* username;
        int is_moderator;
        int is_moderator_muted;
        int is_moderator_text_muted;
        int is_muted_for_me;  // NOT CURRENTLY IMPLEMENTED
        int is_owner;
        int account_id;  /**< Deprecated */
    } vx_participant_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_participant_create(vx_participant_t** participant);
    VIVOXSDK_DLLEXPORT int vx_participant_free(vx_participant_t* participant);
#endif
    /** Creates a participant list with the given size. */
    typedef vx_participant_t* vx_participant_ref_t;
    typedef vx_participant_ref_t* vx_participant_list_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_participant_list_create(int size, vx_participant_list_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_participant_list_free(vx_participant_t** list, int size);
#endif

    /** State participant.
     * Only used for state dump.
     */
    typedef struct vx_state_participant {
        char* uri;
        char* display_name;
        int is_audio_enabled;
        int is_text_enabled;
        int is_audio_muted_for_me;
        int is_text_muted_for_me;           // Not currently supported.
        int is_audio_moderator_muted;
        int is_text_moderator_muted;
        int is_hand_raised;
        int is_typing;
        int is_speaking;
        int volume;
        double energy;
        vx_participant_type type;
        int is_anonymous_login;
    } vx_state_participant_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_state_participant_create(vx_state_participant_t** state_participant);
    VIVOXSDK_DLLEXPORT int vx_state_participant_free(vx_state_participant_t* state_participant);
#endif
    /** Creates a state_participant list with the given size. */
    typedef vx_state_participant_t* vx_state_participant_ref_t;
    typedef vx_state_participant_ref_t* vx_state_participant_list_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_state_participant_list_create(int size, vx_state_participant_list_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_state_participant_list_free(vx_state_participant_t** list, int size);
#endif

    /** State session.
     * Only used for state dump.
     */
    typedef struct vx_state_session {
        char* session_handle;
        char* uri;
        char* name;
        int is_audio_muted_for_me;
        int is_text_muted_for_me;  // Not currently supported.
        int is_transmitting;
        int is_focused;
        int volume;
        int session_font_id;
        int has_audio;
        int has_text;
        int is_incoming;
        int is_positional;
        int is_connected;
        int state_participant_count;
        vx_state_participant_t** state_participants;
        char* durable_media_id;
    } vx_state_session_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_state_session_create(vx_state_session_t** state_session);
    VIVOXSDK_DLLEXPORT int vx_state_session_free(vx_state_session_t* state_session);
#endif
    /** Creates a state_session list with the given size. */
    typedef vx_state_session_t* vx_state_session_ref_t;
    typedef vx_state_session_ref_t* vx_state_session_list_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_state_session_list_create(int size, vx_state_session_list_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_state_session_list_free(vx_state_session_t** list, int size);
#endif

    /** State session group.
     * Only used for state dump.
     */
    typedef struct vx_state_sessiongroup {
        char* sessiongroup_handle;
        int state_sessions_count;
        vx_state_session_t** state_sessions;
        int in_delayed_playback;
        double current_playback_speed;
        vx_sessiongroup_playback_mode current_playback_mode;
        int playback_paused;
        int loop_buffer_capacity;
        int first_loop_frame;
        int total_loop_frames_captured;
        int last_loop_frame_played;
        char* current_recording_filename;
        int total_recorded_frames;
    } vx_state_sessiongroup_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_state_sessiongroup_create(vx_state_sessiongroup_t** state_sessiongroup);
    VIVOXSDK_DLLEXPORT int vx_state_sessiongroup_free(vx_state_sessiongroup_t* state_sessiongroup);
#endif
    /** Creates a state_sessiongroup list with the given size. */
    typedef vx_state_sessiongroup_t* vx_state_sessiongroup_ref_t;
    typedef vx_state_sessiongroup_ref_t* vx_state_sessiongroup_list_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_state_sessiongroup_list_create(int size, vx_state_sessiongroup_list_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_state_sessiongroup_list_free(vx_state_sessiongroup_t** list, int size);
#endif

    /** State account.
     * Only used for state dump.
     */
    typedef struct vx_state_account {
        char* account_handle;
        char* account_uri;
        char* display_name;
        int is_anonymous_login;
        int state_sessiongroups_count;
        vx_login_state_change_state state;
        vx_state_sessiongroup_t** state_sessiongroups;
        int state_buddy_count;
        int state_buddy_group_count;
        vx_state_buddy_t** state_buddies;
        vx_state_buddy_group_t** state_buddy_groups;
    } vx_state_account_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_state_account_create(vx_state_account_t** state_account);
    VIVOXSDK_DLLEXPORT int vx_state_account_free(vx_state_account_t* state_account);
#endif
    /** Creates a state_account list with the given size. */
    typedef vx_state_account_t* vx_state_account_ref_t;
    typedef vx_state_account_ref_t* vx_state_account_list_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_state_account_list_create(int size, vx_state_account_list_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_state_account_list_free(vx_state_account_t** list, int size);
#endif

    /** State connector.
     * Only used for state dump.
     */
    typedef struct vx_state_connector {
        char* connector_handle;
        int state_accounts_count;
        vx_state_account_t** state_accounts;
        int mic_vol;
        int mic_mute;
        int speaker_vol;
        int speaker_mute;
    } vx_state_connector_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_state_connector_create(vx_state_connector_t** state_connector);
    VIVOXSDK_DLLEXPORT int vx_state_connector_free(vx_state_connector_t* state_connector);
#endif
    /** Creates a state_connector list with the given size. */
    typedef vx_state_connector_t* vx_state_connector_ref_t;
    typedef vx_state_connector_ref_t* vx_state_connector_list_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_state_connector_list_create(int size, vx_state_connector_list_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_state_connector_list_free(vx_state_connector_t** list, int size);
#endif

    /**
     * Channel struct.
     */
    typedef struct vx_channel {
        /**
         * The name of the channel.
         */
        char* channel_name;

        /**
         * The description of the channel.
         */
        char* channel_desc;

        /**
         * Not currently implemented.
         */
        char* host;

        /**
         * \deprecated This is deprecated and should not be used.
         * The numeric identifier of the channel.
         * @deprecated
         */
        int channel_id;

        /**
         * The maximum number of participants allowed in the channel.
         */
        int limit;

        /**
         * \deprecated This is deprecated and should not be used.
         * The forecasted number of participants in the channel.
         * @deprecated
         */
        int capacity;

        /**
         * The date and time that the channel was modified.
         */
        char* modified;

        /**
         * The URI of the channel owner.
         */
        char* owner;

        /**
         * The user name of the channel owner.
         */
        char* owner_user_name;

        /**
         * A flag that indicates whether the channel is persistent.
         * If the channel is not persistent, then it is deleted automatically after a certain period of inactivity.
         */
        int is_persistent;  /* 1 true, <= 0 false */

        /**
         * A flag that indicates whether the channel is password protected.
         */
        int is_protected;  /* 1 true, <= 0 false */

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        int size;

        /**
         * Identifies this as a channel (0) or as a positional (2).
         */
        int type;

        /**
         * The mode of the channel: none (0), normal (1), presentation (2), lecture (3), or open (4).
         */
        vx_channel_mode mode;

        /**
         * The URI of the channel.
         * Join the channel and perform moderator actions against the channel.
         */
        char* channel_uri;

        /**
         * The distance beyond which a participant is considered "out of range."
         * When a participant crosses this threshold distance from a particular listening position in a positional channel,
         * a participant update event is fired, which results in an entry being added (or removed) from the user's speakers list.
         * No audio is received for participants beyond this range.
         * The default value is 60.
         * This uses server defaults on create, and leaves existing values unchanged on update.
         */
        int max_range;

        /**
         * The distance from the listener below which the "gain rolloff" effects for a given audio rolloff model are not applied.
         * This is effectively the "audio plateau" distance: gain is constant up to this distance, and then falls off.
         * The default value is 3.
         * This uses server defaults on create, and leaves existing values unchanged on update.
         */
        int clamping_dist;

        /**
         * Indicates how sharp the audio attenuation will "rolloff" between the clamping and maximum distances.
         * Larger values result in steeper rolloffs.
         * The extent of rolloff depends on the selected distance model.
         * The default value is 1.1.
         * This uses server defaults on create, and leaves existing values unchanged on update.
         */
        double roll_off;

        /**
         * The (render side) loudness for all speakers in this channel.
         * The default value is 1.7.
         * This uses server defaults on create, and leaves existing values unchanged on update.
         *
         * \note This is a receive side value, and in practice, should not be raised above a value such as 2.5.
         */
        double max_gain;

        /**
         * The distance model for the channel.
         * This tells the server which algorithm to use when computing attenuation.
         * The audio from speakers abruptly drops to 0 at the maximum distance.
         * There are four possible values in this field:
         *    - 0 - None:
         *        - No distance-based attenuation is applied.
         *          All speakers are rendered as if they were in the same position as the listener.
         *    - 1 - Inverse Distance Clamped:
         *        - The attenuation increases in inverse proportion to the distance.
         *          The rolloff factor n is the inverse of the slope of the attenuation curve.
         *    - 2 - Linear Distance Clamped:
         *        - The attenuation increases in linear proportion to the distance.
         *          The rolloff factor is the negative slope of the attenuation curve.
         *    - 3 - Exponent Distance Clamped:
         *        - The attenuation increases in inverse proportion to the distance raised to the
         *          power of the rolloff factor.
         * The default audio model is 1 - Inverse Distance Clamped.
         * This uses server defaults on create, and leaves existing values unchanged on update.
         *
         * \note If channel_type == dir, this does not apply.
         */
        int dist_model;

        /**
         * Indicates whether audio is encrypted.
         */
        int encrypt_audio;

        /**
         * The display name of the channel owner.
         */
        char* owner_display_name;

        /**
         * The number of participants in the channel.
         */
        int active_participants;
    } vx_channel_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_channel_create(vx_channel_t** channel);
    VIVOXSDK_DLLEXPORT int vx_channel_free(vx_channel_t* channel);
#endif
    typedef vx_channel_t* vx_channel_ref_t;
    typedef vx_channel_ref_t* vx_channel_list_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_channel_list_create(int size, vx_channel_list_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_channel_list_free(vx_channel_t** list, int size);
#endif

    /**
     * Voice font struct.
     */
    typedef struct vx_voice_font {
        int id;
        int parent_id;
        vx_font_type type;
        char* name;
        char* description;
        char* expiration_date;
        int expired;  // 0 is false, 1 is true
        char* font_delta;
        char* font_rules;
        vx_font_status status;
    } vx_voice_font_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_voice_font_create(vx_voice_font_t** channel);
    VIVOXSDK_DLLEXPORT int vx_voice_font_free(vx_voice_font_t* channel);
#endif
    typedef vx_voice_font_t* vx_voice_font_ref_t;
    typedef vx_voice_font_ref_t* vx_voice_font_list_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_voice_font_list_create(int size, vx_voice_font_list_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_voice_font_list_free(vx_voice_font_t** list, int size);
    VIVOXSDK_DLLEXPORT int vx_string_list_create(int size, char*** list_out);
    VIVOXSDK_DLLEXPORT int vx_string_list_free(char** list);
#endif

    typedef struct vx_block_rule {
        char* block_mask;
        int presence_only;
    } vx_block_rule_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_block_rule_create(vx_block_rule_t** block_rule);
    VIVOXSDK_DLLEXPORT int vx_block_rule_free(vx_block_rule_t* block_rule);
#endif

    typedef vx_block_rule_t* vx_block_rule_ref_t;
    typedef vx_block_rule_ref_t* vx_block_rules_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_block_rules_create(int size, vx_block_rules_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_block_rules_free(vx_block_rule_t** list, int size);
#endif

    typedef struct vx_auto_accept_rule {
        char* auto_accept_mask;
        int auto_add_as_buddy;
        char* auto_accept_nickname;
    } vx_auto_accept_rule_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_auto_accept_rule_create(vx_auto_accept_rule_t** auto_accept_rule);
    VIVOXSDK_DLLEXPORT int vx_auto_accept_rule_free(vx_auto_accept_rule_t* auto_accept_rule);
#endif
    typedef vx_auto_accept_rule_t* vx_auto_accept_rule_ref_t;
    typedef vx_auto_accept_rule_ref_t* vx_auto_accept_rules_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_auto_accept_rules_create(int size, vx_auto_accept_rules_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_auto_accept_rules_free(vx_auto_accept_rule_t** list, int size);
#endif

    typedef struct vx_user_channel {
        char* uri;
        char* name;
    } vx_user_channel_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_user_channel_create(vx_user_channel_t** user_channel);
    VIVOXSDK_DLLEXPORT int vx_user_channel_free(vx_user_channel_t* user_channel);
#endif

    typedef vx_user_channel_t* vx_user_channel_ref_t;
    typedef vx_user_channel_ref_t* vx_user_channels_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_user_channels_create(int size, vx_user_channels_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_user_channels_free(vx_user_channel_t** list, int size);
#endif

    /**
     * test_type - Enumeration that defines the test performed (for values, see appendix ?15.8).
     * error_code - Enumeration that defines the error or success of the test (for values, see appendix ?15.9).
     * test_additional_info - Any additional information for this test. For example, this could be the IP addresses used, port numbers, or error information.
     */
    typedef struct vx_connectivity_test_result {
        ND_TEST_TYPE test_type;
        ND_ERROR test_error_code;
        char* test_additional_info;
    } vx_connectivity_test_result_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_connectivity_test_result_create(vx_connectivity_test_result_t** connectivity_test_result, ND_TEST_TYPE tt);
    VIVOXSDK_DLLEXPORT int vx_connectivity_test_result_free(vx_connectivity_test_result_t* connectivity_test_result);
#endif
    typedef vx_connectivity_test_result_t* vx_connectivity_test_result_ref_t;
    typedef vx_connectivity_test_result_ref_t* vx_connectivity_test_results_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_connectivity_test_results_create(int size, vx_connectivity_test_results_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_connectivity_test_results_free(vx_connectivity_test_result_t** list, int size);
#endif

    typedef struct vx_account {
        char* uri;
        char* firstname;
        char* lastname;
        char* username;
        char* displayname;
        char* email;
        char* phone;
        char* carrier;  // Not currently implemented.
        char* created_date;
    } vx_account_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_account_create(vx_account_t** account);
    VIVOXSDK_DLLEXPORT int vx_account_free(vx_account_t* account);
#endif

    /**
     * The type of device.
     */
    typedef enum vx_device_type {
        /**
         * This type is a specific device.
         */
        vx_device_type_specific_device = 0,

        /**
         * This type means to use whatever the system has configured as a default at the time of the call.
         * \note If the default system device changes, then you should not switch devices mid-call.
         */
        vx_device_type_default_system = 1,

        /**
         * This is the null device, which means that either the input or output from or to that device does not occur.
         */
        vx_device_type_null = 2,

        /**
         * This type means to use whatever the system has configured as a default communication device at the time of the call.
         * \note If the default communication device changes, then you should not switch devices mid-call.
         */
        vx_device_type_default_communication = 3
    } vx_device_type_t;

    typedef struct vx_device {
        /**
         * The identifier that is used to pass to vx_req_set_render_device or vx_req_set_capture_device.
         */
        char* device;

        /**
         * The display name to present to the user.
         */
        char* display_name;

        /**
         * The type of device.
         */
        vx_device_type_t device_type;
    } vx_device_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_device_create(vx_device_t** device);
    VIVOXSDK_DLLEXPORT int vx_device_free(vx_device_t* device);
#endif
    typedef vx_device_t* vx_device_ref_t;
    typedef vx_device_ref_t* vx_devices_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_devices_create(int size, vx_devices_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_devices_free(vx_device_t** list, int size);
#endif

    typedef struct vx_buddy {
        char* buddy_uri;
        char* display_name;
        int parent_group_id;
        char* buddy_data;
        int account_id;  /**< Deprecated */
        char* account_name;
    } vx_buddy_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_buddy_create(vx_buddy_t** buddy);
    VIVOXSDK_DLLEXPORT int vx_buddy_free(vx_buddy_t* buddy);
#endif
    typedef vx_buddy_t* vx_buddy_ref_t;
    typedef vx_buddy_ref_t* vx_buddy_list_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_buddy_list_create(int size, vx_buddy_list_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_buddy_list_free(vx_buddy_t** list, int size);
#endif

    typedef struct vx_group {
        int group_id;
        char* group_name;
        char* group_data;
    } vx_group_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_group_create(vx_group_t** group);
    VIVOXSDK_DLLEXPORT int vx_group_free(vx_group_t* group);
#endif
    typedef vx_group_t* vx_group_ref_t;
    typedef vx_group_ref_t* vx_group_list_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_group_list_create(int size, vx_group_list_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_group_list_free(vx_group_t** list, int size);
#endif

    typedef struct vx_name_value_pair {
        /**
         * The name of the parameter.
         */
        char* name;

        /**
         * The value of the parameter.
         */
        char* value;
    } vx_name_value_pair_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_name_value_pair_create(vx_name_value_pair_t** nvpair);
    VIVOXSDK_DLLEXPORT int vx_name_value_pair_free(vx_name_value_pair_t* nvpair);
#endif
    typedef vx_name_value_pair_t* vx_name_value_pair_ref_t;
    typedef vx_name_value_pair_ref_t* vx_name_value_pairs_t;
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_name_value_pairs_create(int size, vx_name_value_pairs_t* list_out);
    VIVOXSDK_DLLEXPORT int vx_name_value_pairs_free(vx_name_value_pair_t** list, int size);
#endif

    /* Vivox SDK functions */
#ifndef VIVOX_TYPES_ONLY
/**
 * Allocate string data to send to the SDK.
 * \note This function will not work until vx_initialize3() is called and after vx_uninitialize() is called.
 * \ingroup memorymanagement
 */
    VIVOXSDK_DLLEXPORT char* vx_strdup(const char*);

    /**
     * Free string data returned to the application.
     * This function is rarely used in practice.
     * \note This function will not work until vx_initialize3() is called and after vx_uninitialize() is called.
     * \ingroup memorymanagement
     */
    VIVOXSDK_DLLEXPORT int vx_free(char*);

    VIVOXSDK_DLLEXPORT int vx_unallocate(void* p);

    VIVOXSDK_DLLEXPORT void* vx_allocate(size_t nBytes);
    VIVOXSDK_DLLEXPORT void* vx_reallocate(void* p, size_t nBytes);
    VIVOXSDK_DLLEXPORT void* vx_calloc(size_t num, size_t bytesPerElement);

    VIVOXSDK_DLLEXPORT void* vx_allocate_aligned(size_t alignment, size_t size);
    VIVOXSDK_DLLEXPORT int vx_unallocate_aligned(void* p);

#define VX_GET_MESSAGE_NO_MESSAGE -1
#define VX_GET_MESSAGE_AVAILABLE 0
#define VX_GET_MESSAGE_FAILURE 1

    /**
     * The VxSDK polling function.
     * This should be called periodically to check for any incoming events.
     *
     * @param message           [out] The object containing the message data.
     * @return                  The status of the poll: VX_GET_MESSAGE_AVAILABLE = Success, VX_GET_MESSAGE_FAILURE = Failure, VX_GET_MESSAGE_NO_MESSAGE = No Message Available
     * \ingroup messaging
     */
    VIVOXSDK_DLLEXPORT int vx_get_message(vx_message_base_t** message);

    /**
     * \deprecated Use vx_issue_request2 instead.
     * Execute the given request.
     * On V4: This function initializes the SDK automatically if not already initialized (see vx_initialize3()).
     * On V5: This function has the same behavior as vx_issue_request2.
     *
     * @param request           The request object to execute. This is of one of the vx_req_* structs.
     * @return                  The success status of the request.
     * \ingroup messaging
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT int vx_issue_request(vx_req_base_t* request);

    /**
     * Execute the given request.
     * This function returns an error if the SDK is not initialized (see vx_initialize3()).
     *
     * @param request           The request object to execute. This is of one of the vx_req_* structs.
     * @return                  The success status of the request.
     * \ingroup messaging
     */
    VIVOXSDK_DLLEXPORT int vx_issue_request2(vx_req_base_t* request);

    /**
     * Execute the given request.
     * This function returns an error if the SDK is not initialized (see vx_initialize3()).
     *
     * @param request           The request object to execute. This is of one of the vx_req_* structs.
     * @param request_count     If non-null, vx_issue_request3 outputs the number of requests that are still outstanding.
     *                          Requests at a rate of 12 requests per second - an application can use this value to determine
     *                          if the application is issuing requests at an unacceptable rate.
     * @return                  The success status of the request.
     * \ingroup messaging
     */
    VIVOXSDK_DLLEXPORT int vx_issue_request3(vx_req_base_t* request, int* request_count);

    /**
     * Get the XML for the given request.
     *
     * @param request           The request object.
     * @param xml               [out] The XML string.
     * \ingroup xml
     */
    VIVOXSDK_DLLEXPORT int vx_request_to_xml(void* request, char** xml);

    /**
     * Get a request for the given XML string.
     *
     * @param xml               The XML string.
     * @param request           [out] The request struct.
     * @param error             [out] The XML parse error string (if any error occurs). NULL otherwise.
     * @return                  The request struct type. If no struct could be created from the XML, req_none is returned.
     * \ingroup xml
     */
    VIVOXSDK_DLLEXPORT vx_request_type vx_xml_to_request(const char* xml, void** request, char** error);

    /**
     * Get the XML for the given response.
     *
     * @param response          The response object.
     * @param xml               [out] The XML string.
     * \ingroup xml
     */
    VIVOXSDK_DLLEXPORT int vx_response_to_xml(void* response, char** xml);

    /**
     * Get a response for the given XML string.
     *
     * @param xml               The XML string.
     * @param response          [out] The response struct.
     * @param error             [out] The XML parse error string (if any error occurs). NULL otherwise.
     * @return                  The response struct type. If no struct could be created from the XML, resp_none is returned.
     * \ingroup xml
     */
    VIVOXSDK_DLLEXPORT vx_response_type vx_xml_to_response(const char* xml, void** response, char** error);

    /**
     * Get the XML for the given event.
     *
     * @param event             The event object.
     * @param xml               [out] The XML string.
     * \ingroup xml
     */
    VIVOXSDK_DLLEXPORT int vx_event_to_xml(void* event, char** xml);

    /**
     * Get a event for the given XML string.
     *
     * @param xml               The XML string.
     * @param event             [out] The event struct.
     * @param error             [out] The XML parse error string (if any error occurs). NULL otherwise.
     * @return                  The event struct type. If no struct could be created from the XML, req_none is returned.
     * \ingroup xml
     */
    VIVOXSDK_DLLEXPORT vx_event_type vx_xml_to_event(const char* xml, void** event, char** error);

    /**
     * Determine whether the XML refers to a request, response, or event.
     * \ingroup xml
     */
    VIVOXSDK_DLLEXPORT vx_message_type vx_get_message_type(const char* xml);

    /**
     * Get Millisecond Counter
     */
    VIVOXSDK_DLLEXPORT unsigned long long vx_get_time_ms(void);

    /**
     * Get Millisecond Counter
     */
    VIVOXSDK_DLLEXPORT unsigned long long vx_get_time_milli_seconds(void);

    /**
     * Get Microsecond Counter
     */
    VIVOXSDK_DLLEXPORT unsigned long long vx_get_time_micro_seconds(void);

    /**
     * Sleep for the specified number of milliseconds.
     *
     * @param milli_seconds     [in] Duration to sleep in milliseconds.
     * @return                  The difference between the actual and the specified sleep time in milliseconds.
     */
    VIVOXSDK_DLLEXPORT long long vx_sleep_milli_seconds(unsigned long long milli_seconds);

    /**
     * Register a callback that is called when a message is placed in the queue.
     * The application should use this to signal the main application thread that will then wakeup and call vx_get_message;
     * \ingroup messaging
     */
    VIVOXSDK_DLLEXPORT int vx_register_message_notification_handler(void (*pf_handler)(void*), void* cookie);

    /**
     * Unregister a notification handler.
     * \ingroup messaging
     */
    VIVOXSDK_DLLEXPORT int vx_unregister_message_notification_handler(void (*pf_handler)(void*), void* cookie);

    /**
     * Block the caller until a message is available.
     * Returns NULL if no message was available within the allotted time.
     * \ingroup messaging
     */
    VIVOXSDK_DLLEXPORT vx_message_base_t* vx_wait_for_message(int msTimeout);

    /**
     *
     * Register a callback that is called to initialize logging.
     * The application should use this to signal the main application thread that will then wakeup and call vx_get_message;
     * \ingroup diagnostics
     */
    VIVOXSDK_DLLEXPORT int vx_register_logging_initialization(
        vx_log_type log_type,
        const char* log_folder,
        const char* log_filename_prefix,
        const char* log_filename_suffix,
        int log_level,
        void (*pf_handler)(const char* source, const char* level, const char* message));

    /**
     * \deprecated File logging is not supported.
     * Get the SDK log file path.
     * \ingroup diagnostics
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT char* vx_get_log_file_path(void);

    /**
     * Unregister the logging callback notification handler.
     * Because the parameters are reserved for future use, pass NULL for each of the parameters
     * (for example: vx_unregister_logging_handler(0, 0);).
     * If a logging handler is registered, then it must be unregistered before shutting down the SDK.
     * \ingroup diagnostics
     *
     * @param pf_handler - OBSOLETE AND UNUSED
     * @param cookie - OBSOLETE AND UNUSED
     */
    VIVOXSDK_DLLEXPORT int vx_unregister_logging_handler(void (*pf_handler)(void*), void* cookie);

    VIVOXSDK_DLLEXPORT int vx_create_account(const char* acct_mgmt_server, const char* admin_name, const char* admin_pw, const char* uname, const char* pw);

    /**
     * The number of crash dumps stored on disk.
     * \ingroup diagnostics
     *
     * \note Not supported on the iPhone platform.
     */
    VIVOXSDK_DLLEXPORT int vx_get_crash_dump_count(void);

    /**
     * Enable crash dump generation.
     * \ingroup diagnostics
     *
     * \note Not supported on the iPhone platform.
     */
    VIVOXSDK_DLLEXPORT int vx_set_crash_dump_generation_enabled(int value);

    /**
     * Determine if crash dump generation is enabled.
     * \ingroup diagnostics
     *
     * \note Not supported on the iPhone platform.
     */
    VIVOXSDK_DLLEXPORT int vx_get_crash_dump_generation(void);

    /**
     * Get the Base64-encoded crash dump information.
     * \ingroup diagnostics
     *
     * \note Not supported on the iPhone platform.
     */
    VIVOXSDK_DLLEXPORT char* vx_read_crash_dump(int index);

    /**
     * Get the timestamp of a crash.
     * \ingroup diagnostics
     *
     * \note Not supported on the iPhone platform.
     */
    VIVOXSDK_DLLEXPORT time_t vx_get_crash_dump_timestamp(int index);

    /**
     * Delete the crash dump.
     * \ingroup diagnostics
     *
     * \note Not supported on the iPhone platform.
     */
    VIVOXSDK_DLLEXPORT int vx_delete_crash_dump(int index);

    /**
     * Stadia applications should call this routine before exiting.
     *
     * \note Applications must call vx_uninitialize() before calling this routine.
     * \attention PC, console, and mobile applications are not required to call this routine because it has no effect for applications on these platforms.
     * \ingroup memorymanagement
     */
    VIVOXSDK_DLLEXPORT int vx_on_application_exit(void);

    /**
     * Get the SDK version info.
     * \ingroup diagnostics
     */
    VIVOXSDK_DLLEXPORT const char* vx_get_sdk_version_info(void);

    /**
     * Get the SDK extended version info.
     * \ingroup diagnostics
     */
    VIVOXSDK_DLLEXPORT const char* vx_get_sdk_version_info_ex(void);

    /**
     * Apply a Vivox voice font to a .wav file.
     *
     * @param fontDefinition - A string that contains the font "definition" in XML format.
     * @param inputFile - A string that contains the path to the input .wav file, which contains the "unmodified" voice.
     * @param outputFile - A string that contains the path to the output .wav file with the font applied.
     * @return - 0 if successful, non-zero if failed.
     * \ingroup voicefonts
     */
    VIVOXSDK_DLLEXPORT int vx_apply_font_to_file(const char* fontDefinition, const char* inputFile, const char* outputFile);

    /**
     * Apply a Vivox voice font to a .wav file and return the energy ratio (Output Energy/Input Energy).
     *
     * @param fontDefinition - A string that contains the font "definition" in XML format.
     * @param inputFile - A string that contains the path to the input .wav file, which contains the "unmodified" voice.
     * @param outputFile - A string that contains the path to the output .wav file with the font applied.
     * @param energyRatio - The Raw Energy ratio between the input and output audio.
     * @return - 0 if successful, non-zero if failed.
     * \ingroup voicefonts
     */
    VIVOXSDK_DLLEXPORT int vx_apply_font_to_file_return_energy_ratio(const char* fontDefinition, const char* inputFile, const char* outputFile, double* energyRatio);

    /**
     * Apply a Vivox voice font to a .vxz file and return the energy ratio (Output Energy/Input Energy)
     *
     * @param fontDefinition - A string that contains the font "definition" in XML format.
     * @param inputFile - A string that contains the path to the input .vxz file, which contans the "unmodified" voice.
     * @param outputFile - A string that contains the path to the output .wav file with the font applied.
     * @param energyRatio - The Raw Energy ratio between the input and output audio.
     * @return - 0 if successful, non-zero if failed.
     * \ingroup voicefonts
     */
    VIVOXSDK_DLLEXPORT int vx_apply_font_to_vxz_file_return_energy_ratio(const char* fontDefinition, const char* inputFile, const char* outputFile, double* energyRatio);

    /**
     * Create a copy of the internal local audio buffer associated with the vx_req_aux_start_buffer_capture_t request/response.
     *
     * @param audioBufferPtr - A void pointer that should be passed in uninitialized.
     * @return               - No return value is provided. On success, the audioBufferPtr will point to a copy of the internal audio buffer. Otherwise, audioBufferPtr is set to NULL.
     * \see vx_req_aux_start_buffer_capture
     * \ingroup adi
     */
    VIVOXSDK_DLLEXPORT void* vx_copy_audioBuffer(void* audioBufferPtr);

    /**
     * Get the duration of the audio buffer in seconds.
     *
     * @param audioBufferPtr - A void pointer that should be passed in uninitialized.
     * @return               - The duration of the audio buffer in seconds.
     * \see vx_req_aux_start_buffer_capture
     * \ingroup adi
     */
    VIVOXSDK_DLLEXPORT double vx_get_audioBuffer_duration(void* audioBufferPtr);

    /**
     * Get the sample rate of the audio buffer.
     *
     * @param audioBufferPtr - A pointer to audio data in a Vivox proprietary format.
     * @return               - The sample rate of the buffer's data. 0 if the buffer does not exist.
     * \see vx_req_aux_start_buffer_capture
     * \ingroup adi
     */
    VIVOXSDK_DLLEXPORT int vx_get_audioBuffer_sample_rate(void* audioBufferPtr);

    /**
     * Free up all memory associated with an allocated Vivox audioBufferPtr.
     * Generated by the vx_copy_audioBuffer() call.
     *
     * @param audioBufferPtr - A pointer to audio data in a Vivox proprietary format.
     * \ingroup adi
     */
    VIVOXSDK_DLLEXPORT int vx_free_audioBuffer(void** audioBufferPtr);

    /**
     * Export audio data in an audioBufferPtr to a memory buffer as PCM.
     *
     * @param audioBufferPtr - A pointer to audio data in a Vivox proprietary format.
     * @param pcmBuffer      - A pointer to the pre-allocated memory buffer.
     * @param maxSamples     - The length of the buffer in samples.
     * @return               - The number of samples copied to the buffer. -1 if failed.
     * \ingroup adi
     */
    VIVOXSDK_DLLEXPORT int vx_export_audioBuffer_to_pcm(void* audioBufferPtr, short* pcmBuffer, int maxSamples);

    /**
     * Export audio data in an audioBufferPtr to a .wav file.
     *
     * @param audioBufferPtr - A pointer to audio data in a Vivox proprietary format.
     * @param outputFile     - A string that contains the path to the output .wav file.
     * @return               - 0 if successful, non-zero if failed.
     * \ingroup adi
     */
    VIVOXSDK_DLLEXPORT int vx_export_audioBuffer_to_wav_file(void* audioBufferPtr, const char* outputFile);

    /**
     * Export audio data in an audioBufferPtr to memory.
     *
     * @param audioBufferPtr - A pointer to audio data in a Vivox proprietary format.
     * @param audioBufferOut - An interleaved (if stereo) audio buffer of PCM-encoded audio. Note that this must be freed with vx_free().
     * @param nSamplesOut    - The number of samples.
     * @param sampleRateOut  - The sample rate of the audio buffer.
     * @param nChannelsOut   - The number of channels in the buffer.
     * @return               - 0 if successful, non-zero if failed.
     * \ingroup adi
     */
    VIVOXSDK_DLLEXPORT int vx_export_audioBuffer_to_memory(void* audioBufferPtr, short** audioBufferOut, int* nSamplesOut, int* sampleRateOut, int* nChannelsOut);

    /**
     * Set the default out of process server address.
     * When an address is set, requests issued by using vx_issue_request are sent to the server
     * at the supplied address instead of being handled in the current process context.
     *
     * @param address - The address of the out of process server. Use "127.0.0.1" for most applications.
     * @param port - port - Use 44125 for most applications.
     * @return - 0 if successful, non-zero if failed.
     * \ingroup messaging
     */
    VIVOXSDK_DLLEXPORT int vx_set_out_of_process_server_address(const char* address, unsigned short port);

    /**
     * \deprecated Use vx_initialize3() instead.
     * An application must call this API before calling any other Vivox API.
     * @return               - 0 if successful, non-zero if failed.
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT int vx_initialize(void);

    /**
     * An application must call this API before calling any other Vivox API, except vx_get_default_config3();
     * @return               - 0 if successful, non-zero if failed.
     * \ingroup initialization
     */
    VIVOXSDK_DLLEXPORT int vx_initialize3(vx_sdk_config_t* config, size_t config_size);

    /**
     * Check if the Vivox SDK was initialized with an vx_initialize3() call, and not yet uninitialized with an vx_uninitialize() call.
     * @return               - 0 if not initialized, non-zero if initialized.
     * \ingroup initialization
     */
    VIVOXSDK_DLLEXPORT int vx_is_initialized(void);

    /**
     * An application must call this API before calling any other Vivox API.
     * @return               - 0 if successful, non-zero if failed.
     * \ingroup initialization
     */
    VIVOXSDK_DLLEXPORT int vx_get_default_config3(vx_sdk_config_t* config, size_t config_size);

    /**
     * An application must call this before exit.
     * @return               - 0 if successful, non-zero if failed.
     * \ingroup initialization
     */
    VIVOXSDK_DLLEXPORT int vx_uninitialize(void);
#endif

#define VIVOX_V_V2_AUDIO_DATA_MONO_SIREN14_32000_EXPANDED 0x10001

    /**
     * \deprecated Use VIVOX_V_V2_AUDIO_DATA_MONO_SIREN14_32000_EXPANDED instead of VIVOX_V_V2_AUDIO_DATA_MONO_SIREN14_32000.
     * @deprecated
     */
#define VIVOX_V_V2_AUDIO_DATA_MONO_SIREN14_32000 VIVOX_V_V2_AUDIO_DATA_MONO_SIREN14_32000_EXPANDED

#define VIVOX_V_V2_AUDIO_DATA_MONO_SIREN7_16000_EXPANDED 0x10008

#define VIVOX_V_V2_AUDIO_DATA_MONO_OPUS_48000_EXPANDED 0x10009

#define VIVOX_V_V2_AUDIO_DATA_MONO_PCMU_8000_COLLAPSED 0x20005

     /**
      * \deprecated Use VIVOX_V_V2_AUDIO_DATA_MONO_PCMU_8000_COLLAPSED instead of VIVOX_V_V2_AUDIO_DATA_MONO_PCMU.
      * @deprecated
      */
#define VIVOX_V_V2_AUDIO_DATA_MONO_PCMU VIVOX_V_V2_AUDIO_DATA_MONO_PCMU_8000_COLLAPSED

#define VIVOX_V_V2_AUDIO_DATA_MONO_PCMU_8000_EXPANDED 0x10005

      /**
       * The configured_codecs field in vx_req_connector_create is a mask of these constants.
       */
#define VIVOX_VANI_PCMU         0x1   /* PCMU */
#define VIVOX_VANI_SIREN7       0x2   /* Siren7, 16kHz, 32kbps */
#define VIVOX_VANI_SIREN14      0x4   /* Siren14, 32kHz, 32kbps */
#define VIVOX_VANI_LEGACY_MASK  0x7
#define VIVOX_VANI_OPUS8        0x10  /* Opus, 48kHz, 8kbps */
#define VIVOX_VANI_OPUS40       0x20  /* Opus, 48kHz, 40kbps */
#define VIVOX_VANI_OPUS57       0x40  /* Opus, 48kHz, 57kbps */ /* proposed; pending research */
#define VIVOX_VANI_OPUS72       0x80  /* Opus, 48kHz, 72kbps */ /* proposed; pending research */
#define VIVOX_VANI_OPUS         VIVOX_VANI_OPUS40
#define VIVOX_VANI_OPUS_MASK    0xf0

       /**
        * The configured_codecs field in vx_req_connector_create is a mask of these constants.
        */
    typedef enum {
        vx_codec_pcmu = VIVOX_VANI_PCMU,               /* PCMU */
        vx_codec_siren7 = VIVOX_VANI_SIREN7,           /* Siren7, 16kHz, 32kbps */
        vx_codec_siren14 = VIVOX_VANI_SIREN14,         /* Siren14, 32kHz, 32kbps */
        vx_codec_opus8 = VIVOX_VANI_OPUS8,             /* Opus, 48kHz, 8kbps */
        vx_codec_opus40 = VIVOX_VANI_OPUS40,           /* Opus, 48kHz, 40kbps -- recommended Opus default */
        vx_codec_opus57 = VIVOX_VANI_OPUS57,           /* Opus, 48kHz, 57kbps -- proposed; pending research */
        vx_codec_opus72 = VIVOX_VANI_OPUS72            /* Opus, 48kHz, 72kbps -- proposed; pending research */
    } vx_codec;

    typedef struct vx_stat_sample {
        double sample_count;
        double sum;
        double sum_of_squares;
        double mean;
        double stddev;
        double min;
        double max;
        double last;
    } vx_stat_sample_t;

    typedef struct vx_stat_thread {
        int interval;
        int count_poll_lt_1ms;
        int count_poll_lt_5ms;
        int count_poll_lt_10ms;
        int count_poll_lt_16ms;
        int count_poll_lt_20ms;
        int count_poll_lt_25ms;
        int count_poll_gte_25ms;
    } vx_stat_thread_t;

    typedef struct vx_system_stats {
        int ss_size;
        int ar_source_count;
        int ar_source_queue_limit;
        int ar_source_queue_overflows;
        int ar_source_poll_count;
        unsigned msgovrld_count;
        vx_stat_sample_t ar_source_free_buffers;
        vx_stat_sample_t ar_source_queue_depth;
        vx_stat_thread_t vp_thread;
        vx_stat_thread_t ticker_thread;

        /**
         * VivoxClient::Client instance count.
         * \note V5 only. In V4, this is always equal to -1.
         */
        int clnt_count;

        /**
         * LoginContext instance count.
         * \note V5 only. In V4, this is always equal to -1.
         */
        int lc_count;

        /**
         * MorpheusSession instance count.
         * \note V5 only. In V4, this is always equal to -1.
         */
        int mps_count;

        /**
         * MorpheusSessionGroup instance count.
         * \note V5 only. In V4, this is always equal to -1.
         */
        int mpsg_count;

        /**
         * VivoxStro::StroMediaSession instance count.
         * \note V5 only. In V4, this is always equal to -1.
         */
        int strms_count;

        /**
         * VivoxStro::StroRtp instance count.
         * \note V5 only. In V4, this is always equal to -1.
         */
        int strr_count;

        /**
         * VivoxStro::StroSessionState instance count.
         * \note V5 only. In V4, this is always equal to -1.
         */
        int strss_count;

        /**
         * VoiceProcessor instance count.
         * \note V5 only. In V4, this is always equal to -1.
         */
        int vp_count;
    } vx_system_stats_t;

    /**
     * Indicates the state of the application.
     * \note Valid only on mobile platforms.
     */
    typedef enum vx_application_state_notification_type {
        vx_application_state_notification_type_before_background = 0,
        vx_application_state_notification_type_after_foreground = 1,
        vx_application_state_notification_type_periodic_background_idle = 2
    } vx_application_state_notification_type_t;

#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int vx_debug_call(void*);

    /**
     * Get statistics about various system internals.
     * @return - 0 if successful, non-zero if failed.
     */
    VIVOXSDK_DLLEXPORT int vx_get_system_stats(vx_system_stats_t* system_stats);

#define VX_VAR_DECODER_COUNT_LIMIT    "DecoderLimit"
#define VX_VAR_DECODER_HANGOVER_LIMIT "DecoderHangoverLimit"
#define VX_VAR_RTP_ENCRYPTION         "RTPEncryption"

    /**
     * Get named variables.
     * @param var_name - The name of the variable.
     * @param p_value - Where to store the value of the variable.
     * @return - 0 if successful, non-zero if failed.
     */
    VIVOXSDK_DLLEXPORT int vx_get_int_var(const char* var_name, int* p_value);

    /**
     * Set named variables.
     * @param var_name - The name of the variable.
     * @param - The integer value to set.
     * @return - 0 if successful, non-zero if failed.
     */
    VIVOXSDK_DLLEXPORT int vx_set_int_var(const char* var_name, int value);

    /**
     * Deallocate any message of any type.
     * \ingroup memorymanagement
     */
    VIVOXSDK_DLLEXPORT int vx_destroy_message(vx_message_base_t* message);
#endif

    /**
     * Error codes that are returned by the VXA subsystem.
     */
    typedef enum {
        /**
         * Method executed successfully.
         */
        VXA_SUCCESS = 0,

        /**
         * The caller provided an invalid parameter.
         */
        VXA_INVALID_PARAMETER = 1,

        /**
         * The caller attempted to open a device that does not exist.
         */
        VXA_DEVICE_DOES_NOT_EXIST = 2,

        /**
         * There was an unexpected operating system-specific failure.
         */
        VXA_INTERNAL_ERROR = 3,

        /**
         * The method could not allocate enough memory to complete the request.
         */
        VXA_OUT_OF_MEMORY = 4,

        /**
         * The method attempted to perform an invalid operation on the object in its current state.
         * Typically, this is an attempt to open an already open device, or to read or write a closed device.
         * Can also be called if VXA is not initialized.
         */
        VXA_INVALID_STATE = 5,

        /**
         * Returned by "read()" functions when there is no more data available.
         */
        VXA_NO_MORE_DATA = 6,

        /**
         * Returned by the method if the feature is not supported.
         */
        VXA_FEATURE_NOT_SUPPORTED = 7,

        /**
         * Returned by the method if there is an attempt to create more than MAX_VXA_DEVICE_COUNT devices.
         */
        VXA_MAX_DEVICES_EXCEEDED = 8,

        /**
         * Returned by the method if there are no more render buffers available.
         */
        VXA_NO_BUFFERS_AVAILABLE = 9,

        /**
         * Returned by the method if the app does not have microphone access permission.
         */
        VXA_ACCESS_DENIED = 10
    } VXA_ERROR_CODES;

    /**
     * Values passed when opening capture devices.
     */
    typedef enum {
        /**
         * Use acoustic echo cancellation.
         * \note This flag is not universally implemented.
         */
        VXA_CAPTURE_OPEN_FLAG_USE_AEC = 0x00000001,

        /**
         * Use automatic gain control.
         * \note This flag is not universally implemented.
         */
        VXA_CAPTURE_OPEN_FLAG_USE_AGC = 0x00000002
    } VXA_CAPTURE_FLAGS;

    /**
     * The common return code for vxa* methods.
     */
    typedef int vxa_status_t;

    /**
     * Get statistics that are useful for debugging audio capture issues.
     */
    typedef struct vxa_capture_device_stats_t {
        int buffer_underrun_count;
        int buffer_overrun_count;
        int other_error_count;
        int audio_queue_read_count;  // Correlate with buffer_underrun_count
        int audio_queue_write_count;  // Correlate with buffer_overrun_count
    } vxa_capture_device_stats_t;

    /**
     * Get statistics that are useful for debugging audio render issues.
     */
    typedef struct vxa_render_device_stats_t {
        int current_output_queue_depth_milliseconds;
        int buffer_underrun_count;
        int buffer_overrun_count;
        int other_error_count;
        int audio_queue_read_count;  // Correlate with buffer_underrun_count
        int audio_queue_write_count;  // Correlate with buffer_overrun_count
        int hardware_output_channels;
        int hardware_preferred_samplerate;
        int hardware_preferred_buffer_duration;
    } vxa_render_device_stats_t;

    /**
     * The maximum number of application-provided capture devices.
     * The maximum number of application-provided render devices.
     */
#define MAX_VXA_DEVICE_COUNT 32

     /**
      * Rolloff curve types to serve as the distance model for a positional channel.
      * This tells the server which algorithm to use when computing attenuation.
      */
    typedef enum {
        /**
         * No distance-based attenuation is applied.
         * All speakers are rendered as if they were in the same position as the listener.
         */
        channel_rolloff_curve_type_none = 0,

        /**
         * The attenuation increases in inverse proportion to the distance.
         * The rolloff factor is the inverse of the slope of the attenuation curve.
         */
        channel_rolloff_curve_type_inverse_distance_clamped = 1,

        /**
         * The attenuation increases in linear proportion to the distance.
         * The rolloff factor is the negative slope of the attenuation curve.
         */
        channel_rolloff_curve_type_linear_distance_clamped = 2,

        /**
         * The attenuation increases in inverse proportion to the distance
         * raised to the power of the rolloff factor.
         */
        channel_rolloff_curve_type_exponential_distance_clamped = 3
    } vx_channel_rolloff_curve_type;

#ifndef VIVOX_TYPES_ONLY
    /**
     * Generate a Vivox Access Token.
     *
     * !!! This function should only be called when prototyping or debugging token generation server implementations. !!!
     * It should not be in production code, because that would require the issuer/key pair to be resident client memory,
     * which would create a security exposure.
     *
     * @param issuer - A standard issuer claim.
     * @param expiration - A standard expiration time claim. If set to (vx_time_t)-1, uses the default time of now(0)+300.
     * @param vxa - A Vivox action, for example, "login", "join", "kick", or "mute".
     * @param serial number - Use this to guarantee uniqueness within an epoch second.
     * @param subject - Optional: The URI of the target of the actions "kick" and "mute". NULL otherwise.
     * @param from_uri - A SIP From URI.
     * @param to_uri - A SIP To URI.
     * @param key - A token-signing key
     * @param key_len - The length of the token-signing key.
     * @returns null-terminated - A buffer to be freed with vx_free(). If NULL is returned, an error occurred.
     */
    VIVOXSDK_DLLEXPORT char* vx_debug_generate_token(const char* issuer, vx_time_t expiration, const char* vxa, unsigned long long serial, const char* subject, const char* from_uri, const char* to_uri, const unsigned char* key, size_t key_len);

    /**
     * Synchronously download the contents of the specified URL with the GET method.
     *
     * @param url - [in] The URL of the resource to download.
     * @param response_code - [out] A pointer to the returned response code (0 on error, >= 200 after the request finished).
     * @param content - [out] A pointer to the downloaded content is stored here, and is guaranteed to be NULL-terminated. The memory is allocated automatically. Use vx_free_http() to free up the allocated buffers.
     * @param content_len - [out] A pointer to the returned content length.
     * @param content_type - [out] A pointer to the downloaded content type is stored here, and is guaranteed to be NULL-terminated. The memory is allocated automatically. Use vx_free_http() to free up the allocated buffers.
     * @param content_type_len - [out] A pointer to the returned content type length.
     * @return - 0 if successful, non-zero if failed.
     */
    VIVOXSDK_DLLEXPORT unsigned int vx_get_http(const char* url, unsigned int* response_code, char** content, size_t* content_len, char** content_type, size_t* content_type_len);

    /**
     * Free the memory allocated during the vx_get_http() call.
     * \note Call this function only if vx_get_http() returned zero.
     *
     * @param content - [in] The same value as what is passed to vx_get_http().
     * @param content_type - [in] The same value as what is passed to vx_get_http().
     */
    VIVOXSDK_DLLEXPORT int vx_free_http(char** content, char** content_type);

    /**
     * Get a random guest user ID with the given prefix.
     * The returned ID always starts and ends with the '.' character.
     * \note This must be deallocated with vx_free();
     *
     * @param - [in] prefix The prefix for the user.
     * \ingroup diagnostics
     */
    VIVOXSDK_DLLEXPORT char* vx_get_random_user_id(const char* prefix);

    /**
     * Get a random guest user ID for the given issuer with the given prefix.
     * The returned ID always starts and ends with the '.' character.
     * \note This must be deallocated with vx_free();
     *
     * @param prefix - [in] The prefix for the user.
     * @param issuer - [in, optional] The issuer. If NULL or an empty string is passed, the generated user ID is the same as what is generated by vx_get_random_user_id().
     * \ingroup diagnostics
     */
    VIVOXSDK_DLLEXPORT char* vx_get_random_user_id_ex(const char* prefix, const char* issuer);

    /**
     * Get a random ephemeral channel ID with the given prefix for the specific realm.
     *
     * The prefix should start with one of the following options:
     *     confctl-g- for general non-positional channels
     *     confctl-e- for echo channels
     *     confctl-d- for positional channels
     *
     * \note This must be deallocated with vx_free();
     *
     * @param prefix - [in] The prefix for the channel.
     * @param realm - [in] The realm for that channel (for example, mt1s.vivox.com).
     * \ingroup diagnostics
     */
    VIVOXSDK_DLLEXPORT char* vx_get_random_channel_uri(const char* prefix, const char* realm);

    /**
     * Get a random ephemeral channel ID for the given issuer with the given prefix for the specific realm.
     *
     * The prefix should start with one of the following options:
     *     confctl-g- for general non-positional channels
     *     confctl-e- for echo channels
     *     confctl-d- for positional channels
     *
     * \note This must be deallocated with vx_free();
     *
     * @param prefix - [in] The prefix for the channel.
     * @param realm - [in] The realm for that channel (for example, mt1s.vivox.com).
     * @param issuer - [in, optional] The issuer. If NULL or an empty string is passed, the generated channel ID is the same as what is generated by vx_get_random_channel_uri().
     * \ingroup diagnostics
     */
    VIVOXSDK_DLLEXPORT char* vx_get_random_channel_uri_ex(const char* prefix, const char* realm, const char* issuer);

    /**
     * Generate the fully specified URI of a user with the given name for the given realm and issuer.
     * \note This must be deallocated with vx_free();
     *
     * @param name - [in] The unique account name that you assigned to the user.
     * @param realm - [in] The realm for that user (for example, mt1s.vivox.com).
     * @param issuer - [in, optional] The issuer. If NULL or an empty string is passed, the generated user URI is the same as what is generated with no argument.
     */
    VIVOXSDK_DLLEXPORT char* vx_get_user_uri(const char* name, const char* realm, const char* issuer);

    /**
     * Generate the fully specified URI of an echo channel with the given name for the given realm and issuer.
     * \note This must be deallocated with vx_free();
     *
     * @param name - [in] The name you assigned to the channel.
     * @param realm - [in] The realm for that channel (for example, mt1s.vivox.com).
     * @param issuer - [in, optional] The issuer. If NULL or an empty string is passed, the generated user URI is the same as what is generated with no argument.
     */
    VIVOXSDK_DLLEXPORT char* vx_get_echo_channel_uri(const char* name, const char* realm, const char* issuer);

    /**
     * Generate the fully specified URI of a general non-positional channel with the given name for the given realm and issuer.
     * \note This must be deallocated with vx_free();
     *
     * @param name - [in] The name you assigned to the channel.
     * @param realm - [in] The realm for that channel (for example, mt1s.vivox.com).
     * @param issuer - [in, optional] The issuer. If NULL or an empty string is passed, the generated user URI is the same as what is generated with no argument.
     */
    VIVOXSDK_DLLEXPORT char* vx_get_general_channel_uri(const char* name, const char* realm, const char* issuer);

    /**
     * Generate the fully specified URI of a positional channel with the given name and 3D properties for the given realm and issuer.
     * \note This must be deallocated with vx_free(); URIs with different 3D properties are considered different channels.
     *
     * @param name - [in] The name you assigned to the channel.
     * @param realm - [in] The realm for that channel (for example, mt1s.vivox.com).
     * @param max_range - [in] The maximum distance from the listener at which a speaker can be heard. This must be an integer > 0.
     * @param clamping_distance - [in] The distance from the listener at which a speaker’s voice is heard at its original volume. This must be an integer in the range 0 <= clamping_distance <= max_range.
     * @param rolloff - [in] The strength of the volume attenuation as the speaker moves away from the listener. This must be a floating point value >= 0 that is rounded to three decimal places.
     * @param distance_model - [in] The curve that determines volume attenuation at distances between the clamping_distance and max_range, scaled by the rolloff.
     * @param issuer - [in, optional] The issuer. If NULL or an empty string is passed, the generated user URI is the same as what is generated with no argument.
     */
    VIVOXSDK_DLLEXPORT char* vx_get_positional_channel_uri(const char* name, const char* realm, int max_range, int clamping_distance, double rolloff, vx_channel_rolloff_curve_type distance_model, const char* issuer);

    /**
     * Return a textual representation of the compositional elements of a Vivox URI, suitable for logging.
     * For instance, whether it is a user or channel URI, the name, realm, and other properties are listed.
     * \note This must be deallocated with vx_free(); The string contains line breaks.
     *
     * @param is_multitenant - [in] 1 if the URI includes a token issuer, or 0 otherwise.
     * @param uri - [in] A fully specified URI representing a Vivox user or channel.
     */
    VIVOXSDK_DLLEXPORT char* vx_uri_to_string(int is_multitenant, const char* uri);
#endif

    /* Audio Quality Controls functions */
    /**
     * Values for OPUS VBR mode.
     */
    typedef enum {
        /**
         * A constant bitrate mode.
         */
        opus_mode_cbr = 0,

        /**
         * A limited variable bitrate mode.
         * \note The actual bitrate will never exceed the requested bitrate.
         */
        opus_mode_lvbr = 1,

        /**
         * A variable bitrate mode.
         */
        opus_mode_vbr = 2
    } vx_opus_vbr_mode;

    /**
     * Values for OPUS bandwidth.
     */
    typedef enum {
        /**
         * Automatic bandwidth (default).
         */
        opus_bandwidth_auto = 0,
        /**
         * Narrowband, 4kHz.
         */
        opus_bandwidth_nb = 1,
        /**
         * Medium-band, 6kHz.
         */
        opus_bandwidth_mb = 2,
        /**
         * Wideband, 8kHz.
         */
        opus_bandwidth_wb = 3,
        /**
         * Super-wideband, 12 kHz.
         */
        opus_bandwidth_swb = 4,
        /**
         * Fullband, 20 kHz.
         */
        opus_bandwidth_fb = 5
    } vx_opus_bandwidth;

    /**
     * Values for vx_crash_test( crash type ).
     */
    typedef enum vx_crash_test_type {
        /**
         * Crash on access to the zero pointer.
         */
        vx_crash_access_zero_pointer = 0,

        /**
         * Crash on access to a restricted page.
         */
        vx_crash_access_violation = 1,

        /**
         * Overflow the program stack.
         */
        vx_crash_stack_overflow = 2,

        /**
         * Corrupt the heap and try to allocate more memory.
         */
        vx_crash_heap_corruption = 3,

#ifdef __clang__
        /**
         * Corrupt the heap and try to allocate more memory.
         */
        vx_crash_builtin_trap = 4
#endif
    } vx_crash_test_type_t;

    /**
     * The Vivox eXtended Data (VXD) that is received.
     *
     * \ingroup session
     */
    typedef struct vx_vxd {
        /**
         * Struct version.
         * Must be sizeof(vx_vxd_t);
         */
        size_t version;

        /**
         * The URI of the participant whose properties are being updated.
         */
        char* participant_uri;

        /**
         * The data that is received.
         */
        char* data;

        /**
         * The amount of data received.
         */
        size_t data_size;
    } vx_vxd_t;

    /**
     * The type of path used by the SDK.
     */
    typedef enum {
        /**
         * The path to the folder where internal SDK data is stored.
         * Ends with a platform-specific separator.
         */
        path_cache_folder = 0
    } vx_path_id;

#ifdef __cplusplus
}
#endif

#pragma pack(pop)