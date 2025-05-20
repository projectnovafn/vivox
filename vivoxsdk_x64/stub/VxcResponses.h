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

#include "Vxc.h"
#include "VxcRequests.h"

#pragma pack(push)
#pragma pack(8)

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * The response for vx_req_connector_create
     * \see vx_req_connector_create
     * \ingroup connector
     */
    typedef struct vx_resp_connector_create {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * Valid on success, handle value for this initialized connector instance.
         */
        VX_HANDLE connector_handle;

        /**
         * The version number of the SDK.
         */
        char* version_id;

        /**
         * The type of backend used, as defined in the `vx_backend_type` enum in `VxcTypes.h`.
         * For Vixox SDK version 5, this is always XMPP (`1`).
         */
        int backend_type;

        /**
         * Valid on success, default realm received by this initialized connector instance.
         */
        char* default_realm;
    } vx_resp_connector_create_t;

    /**
     * The response for vx_req_connector_initiate_shutdown
     * \see vx_req_connector_initiate_shutdown
     * \ingroup connector
     */
    typedef struct vx_resp_connector_initiate_shutdown {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        char* client_name;
    } vx_resp_connector_initiate_shutdown_t;

    /**
     * \deprecated This is deprecated and should not be used.
     * The response for vx_req_account_login
     * \see vx_req_account_login
     * \ingroup login
     * @deprecated
     */
    typedef struct vx_resp_account_login {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * Valid on success, handle value for this initialized account login.
         */
        VX_HANDLE account_handle;

        /**
         * The ID of the account.
         */
        int account_id;

        /**
         * The display name of the account, if available.
         */
        char* display_name;

        /**
         * The URI of the user.
         */
        char* uri;

        /**
         * The number of aliases that are associated with this account.
         */
        int num_aliases;

        /**
         * The URI for list-based buddy presence.
         * \note Available in select systems only.
         */
        char* buddy_list_uri;

        /**
         * The encoded URI for the user with the tag.
         * This uniquely identifies users that might appear multiple times in a channel.
         */
        char* encoded_uri_with_tag;
    } vx_resp_account_login_t;

    /**
     * \deprecated Use vx_req_account_anonymous_login instead.
     * The response for vx_req_account_authtoken_login
     * \see vx_req_account_authtoken_login
     * \ingroup login
     * @deprecated
     */
    typedef struct vx_resp_account_authtoken_login {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * Valid on success, handle value for this initialized account login.
         */
        VX_HANDLE account_handle;

        /**
         * The ID of the account.
         */
        int account_id;

        /**
         * The user name of the account.
         */
        char* user_name;

        /**
         * The display name of the account, if available.
         */
        char* display_name;

        /**
         * The URI of the user.
         */
        char* uri;

        /**
         * The number of aliases that are associated with this account.
         */
        int num_aliases;

        /**
         * The URI for list-based buddy presence.
         * \note Available in select systems only.
         */
        char* buddy_list_uri;

        /**
         * The encoded URI for the user with the tag.
         * This uniquely identifies users that might appear multiple times in a channel.
         */
        char* encoded_uri_with_tag;
    } vx_resp_account_authtoken_login_t;

    /**
     * The response for vx_req_account_anonymous_login
     * \see vx_req_account_anonymous_login
     * \ingroup login
     */
    typedef struct vx_resp_account_anonymous_login {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * Valid on success, handle value for this initialized account login.
         */
        VX_HANDLE account_handle;

        /**
         * The ID of the account.
         */
        int account_id;

        /**
         * The display name of the account, if available.
         */
        char* displayname;

        /**
         * The URI of the user.
         */
        char* uri;

        /**
         * The encoded URI for the user with the tag.
         * This uniquely identifies users that might appear multiple times in a channel.
         */
        char* encoded_uri_with_tag;
    } vx_resp_account_anonymous_login_t;

    /**
     * The response for vx_req_account_logout
     * \see vx_req_account_logout
     * \ingroup login
     */
    typedef struct vx_resp_account_logout {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_account_logout_t;

    /**
     * \deprecated This is deprecated and should not be used.
     * The response for vx_req_account_set_login_properties
     * \see vx_req_account_set_login_properties
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_resp_account_set_login_properties {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_account_set_login_properties_t;

    /**
     * \deprecated This is deprecated and should not be used.
     * The response for vx_req_sessiongroup_create
     * \see vx_req_sessiongroup_create
     * \ingroup sessiongroup
     * @deprecated
     */
    typedef struct vx_resp_sessiongroup_create {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * Valid on success, handle value for this created session.
         */
        VX_HANDLE sessiongroup_handle;
    } vx_resp_sessiongroup_create_t;

    /**
     * \deprecated This is deprecated and should not be used.
     * The response for vx_req_sessiongroup_terminate
     * \see vx_req_sessiongroup_terminate
     * \ingroup sessiongroup
     * @deprecated
     */
    typedef struct vx_resp_sessiongroup_terminate {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_sessiongroup_terminate_t;

    /**
     * The response for vx_req_sessiongroup_add_session
     * \see vx_req_sessiongroup_add_session
     * \ingroup sessiongroup
     */
    typedef struct vx_resp_sessiongroup_add_session {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * Valid on success, handle value for this created session.
         */
        VX_HANDLE session_handle;
    } vx_resp_sessiongroup_add_session_t;

    /**
     * The response for vx_req_sessiongroup_remove_session
     * \see vx_req_sessiongroup_remove_session
     * \ingroup sessiongroup
     */
    typedef struct vx_resp_sessiongroup_remove_session {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_sessiongroup_remove_session_t;

    /**
     * The response for vx_req_sessiongroup_set_focus
     * \see vx_req_sessiongroup_set_focus
     * \ingroup sessiongroup
     */
    typedef struct vx_resp_sessiongroup_set_focus {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_sessiongroup_set_focus_t;

    /**
     * The response for vx_req_sessiongroup_unset_focus
     * \see vx_req_sessiongroup_unset_focus
     * \ingroup sessiongroup
     */
    typedef struct vx_resp_sessiongroup_unset_focus {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_sessiongroup_unset_focus_t;

    /**
     * The response for vx_req_sessiongroup_reset_focus
     * \see vx_req_sessiongroup_reset_focus
     * \ingroup sessiongroup
     */
    typedef struct vx_resp_sessiongroup_reset_focus {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_sessiongroup_reset_focus_t;

    /**
     * The response for vx_req_sessiongroup_set_tx_session
     * \see vx_req_sessiongroup_set_tx_session
     * \ingroup sessiongroup
     */
    typedef struct vx_resp_sessiongroup_set_tx_session {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_sessiongroup_set_tx_session_t;

    /**
     * The response for vx_req_sessiongroup_set_tx_all_sessions
     * \see vx_req_sessiongroup_set_tx_all_sessions
     * \ingroup sessiongroup
     */
    typedef struct vx_resp_sessiongroup_set_tx_all_sessions {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_sessiongroup_set_tx_all_sessions_t;

    /**
     * The response for vx_req_sessiongroup_set_tx_no_session
     * \see vx_req_sessiongroup_set_tx_no_session
     * \ingroup sessiongroup
     */
    typedef struct vx_resp_sessiongroup_set_tx_no_session {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_sessiongroup_set_tx_no_session_t;

    /**
     * The response for vx_req_sessiongroup_set_session_3d_position
     * \see vx_req_sessiongroup_set_session_3d_position
     * \ingroup sessiongroup
     */
    typedef struct vx_resp_sessiongroup_set_session_3d_position {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_sessiongroup_set_session_3d_position_t;

    /**
     * The response for vx_req_sessiongroup_control_audio_injection
     * \see vx_req_sessiongroup_control_audio_injection
     * \ingroup adi
     */
    typedef struct vx_resp_sessiongroup_control_audio_injection {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_sessiongroup_control_audio_injection_t;

    /**
     * \deprecated This is deprecated and should not be used.
     * The response for vx_req_session_create
     * \see vx_req_session_create
     * @deprecated
     */
    typedef struct vx_resp_session_create {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * Valid on success, handle value for this created session group.
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * Valid on success, handle value for this created session.
         */
        VX_HANDLE session_handle;
    } vx_resp_session_create_t;

    /**
     * The response for vx_req_session_media_connect
     * \see vx_req_session_media_connect
     * \ingroup session
     */
    typedef struct vx_resp_session_media_connect {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_session_media_connect_t;

    /**
     * The response for vx_req_session_media_disconnect
     * \see vx_req_session_media_disconnect
     * \ingroup session
     */
    typedef struct vx_resp_session_media_disconnect {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_session_media_disconnect_t;

    /**
     * The response for vx_req_session_text_connect
     * \see vx_req_session_text_connect
     * \ingroup session
     */
    typedef struct vx_resp_session_text_connect {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_session_text_connect_t;

    /**
     * The response for vx_req_session_text_disconnect
     * \see vx_req_session_text_disconnect
     * \ingroup session
     */
    typedef struct vx_resp_session_text_disconnect {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_session_text_disconnect_t;

    /**
     * The response for vx_req_session_terminate
     * \see vx_req_session_terminate
     * \ingroup session
     */
    typedef struct vx_resp_session_terminate {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_session_terminate_t;

    /**
     * The response for vx_req_session_mute_local_speaker
     * \see vx_req_session_mute_local_speaker
     * \ingroup session
     */
    typedef struct vx_resp_session_mute_local_speaker {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_session_mute_local_speaker_t;

    /**
     * \deprecated Use vx_req_aux_set_speaker_level_t instead.
     * The response for vx_req_session_set_local_speaker_volume_t
     * \see vx_req_session_set_local_speaker_volume
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_resp_session_set_local_speaker_volume {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_session_set_local_speaker_volume_t;

    /**
     * The response for vx_req_session_set_local_render_volume
     * \see vx_req_session_set_local_render_volume
     * \ingroup session
     */
    typedef struct vx_resp_session_set_local_render_volume {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_session_set_local_render_volume_t;

    /**
     * The response for vx_req_session_channel_invite_user
     * \see vx_req_session_channel_invite_user
     * \ingroup session
     */
    typedef struct vx_resp_session_channel_invite_user {
        vx_resp_base_t base;
    } vx_resp_session_channel_invite_user_t;

    /**
     * The response for vx_req_session_set_participant_volume_for_me
     * \see vx_req_session_set_participant_volume_for_me
     * \ingroup session
     */
    typedef struct vx_resp_session_set_participant_volume_for_me {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_session_set_participant_volume_for_me_t;

    /**
     * The response for vx_req_session_set_participant_mute_for_me
     * \see vx_req_session_set_participant_mute_for_me
     * \ingroup session
     */
    typedef struct vx_resp_session_set_participant_mute_for_me {
        vx_resp_base_t base;
    } vx_resp_session_set_participant_mute_for_me_t;

    /**
     * The response for vx_req_session_set_3d_position
     * \see vx_req_session_set_3d_position
     * \ingroup session
     */
    typedef struct vx_resp_session_set_3d_position {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_session_set_3d_position_t;

    /**
     * The response for vx_req_session_set_voice_font
     * \see vx_req_session_set_voice_font
     * \ingroup voicefonts
     */
    typedef struct vx_resp_session_set_voice_font {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_session_set_voice_font_t;

    /**
     * The response for vx_req_account_channel_change_owner
     * \see vx_req_account_channel_change_owner_t
     */
    typedef struct vx_resp_account_channel_change_owner {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_account_channel_change_owner_t;

    /**
     * The response for vx_req_account_send_user_app_data
     * \see vx_req_account_send_user_app_data_t
     */
    typedef struct vx_resp_account_send_user_app_data {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_account_send_user_app_data_t;

    /**
     * \deprecated This is deprecated and should not be used.
     * The response for vx_req_account_channel_add_acl
     * \see vx_req_account_channel_add_acl
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_resp_account_channel_add_acl {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_account_channel_add_acl_t;

    /**
     * \deprecated This is deprecated and should not be used.
     * The response for vx_req_account_channel_remove_acl
     * \see vx_req_account_channel_remove_acl
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_resp_account_channel_remove_acl {
        vx_resp_base_t base;
    } vx_resp_account_channel_remove_acl_t;

    /**
     * \deprecated This is deprecated and should not be used.
     * The response for vx_req_account_channel_get_acl
     * \see vx_req_account_channel_get_acl
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_resp_account_channel_get_acl {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The number of entries in the "participants" array.
         */
        int participants_size;

        /**
         * A list of users in the channel's Access Control List.
         * \note Only the URI field on the participant structures is guaranteed to be present.
         */
        vx_participant_t** participants;
    } vx_resp_account_channel_get_acl_t;

    /**
     * The response for vx_req_channel_mute_user
     * \see vx_req_channel_mute_user
     * \ingroup channel
     */
    typedef struct vx_resp_channel_mute_user {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_channel_mute_user_t;

    /**
     * \deprecated This is deprecated and should not be used.
     * The response for vx_req_channel_ban_user
     * \see vx_req_channel_ban_user
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_resp_channel_ban_user {
        vx_resp_base_t base;
    } vx_resp_channel_ban_user_t;

    /**
     * \deprecated This is deprecated and should not be used.
     * The response for vx_req_channel_get_banned_users
     * \see vx_req_channel_get_banned_users
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_resp_channel_get_banned_users {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The number of entries in the "banned_users" array.
         */
        int banned_users_count;

        /**
         * A list of users banned from the specified channel.
         */
        vx_participant_t** banned_users;
    } vx_resp_channel_get_banned_users_t;

    /**
     * \deprecated This is deprecated and should not be used.
     * The response for vx_req_channel_kick_user
     * \see vx_req_channel_kick_user
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_resp_channel_kick_user {
        vx_resp_base_t base;
    } vx_resp_channel_kick_user_t;

    /**
     * The response for vx_req_channel_mute_all_users
     * \see vx_req_channel_mute_all_users
     * \ingroup channel
     */
    typedef struct vx_resp_channel_mute_all_users {
        vx_resp_base_t base;
    } vx_resp_channel_mute_all_users_t;

    /**
     * \deprecated This is deprecated and should not be used.
     * The response for vx_req_channel_set_lock_mode
     * \see vx_req_channel_set_lock_mode
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_resp_channel_set_lock_mode {
        vx_resp_base_t base;
    } vx_resp_channel_set_lock_mode_t;

    /**
     * The response for vx_req_connector_mute_local_mic
     * \see vx_req_connector_mute_local_mic
     * \ingroup devices
     */
    typedef struct vx_resp_connector_mute_local_mic {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_connector_mute_local_mic_t;

    /**
     * The response for vx_req_connector_mute_local_speaker
     * \see vx_req_connector_mute_local_speaker
     * \ingroup devices
     */
    typedef struct vx_resp_connector_mute_local_speaker {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_connector_mute_local_speaker_t;

    /**
     * \deprecated Use vx_resp_aux_set_mic_level instead.
     * The response for vx_req_connector_set_local_mic_volume
     * \see vx_req_connector_set_local_mic_volume
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_resp_connector_set_local_mic_volume {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_connector_set_local_mic_volume_t;

    /**
     * \deprecated Use vx_resp_aux_set_speaker_level instead.
     * The response for vx_req_connector_set_local_speaker_volume
     * \see vx_req_connector_set_local_speaker_volume
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_resp_connector_set_local_speaker_volume {
        vx_resp_base_t base;
    } vx_resp_connector_set_local_speaker_volume_t;

    /**
     * The response for vx_req_connector_get_local_audio_info
     * \see vx_req_connector_get_local_audio_info
     * \ingroup devices
     */
    typedef struct vx_resp_connector_get_local_audio_info {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The level of the speaker audio.
         * This is a non-negative integer value between 0 and 100 (inclusive).
         * The default value is 50, in which no gain is applied to the audio.
         * When this value is 0, no speaker audio is rendered.
         */
        int speaker_volume;

        /**
         * A number, which is either true (mute) or false (unmute).
         */
        int is_speaker_muted;

        /**
         * The level of the microphone audio.
         * This is a non-negative integer value between 0 and 100 (inclusive).
         * The default value is 50, in which no gain is applied to the audio.
         * When this value is 0, no microphone audio is rendered.
         */
        int mic_volume;

        /**
         * A number, which is either 1 (mute) or 0 (unmute).
         */
        int is_mic_muted;
    } vx_resp_connector_get_local_audio_info_t;

    /**
     * The response for vx_req_account_buddy_set
     * \see vx_req_account_buddy_set
     * \ingroup buddy
     */
    typedef struct vx_resp_account_buddy_set {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The account ID of the buddy.
         */
        int account_id;
    } vx_resp_account_buddy_set_t;

    /**
     * The response for vx_req_account_buddy_delete
     * \see vx_req_account_buddy_delete
     * \ingroup buddy
     */
    typedef struct vx_resp_account_buddy_delete {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_account_buddy_delete_t;

    /**
     * \deprecated This is deprecated and should not be used.
     * The response for vx_req_account_list_buddies_and_groups
     * \see vx_req_account_list_buddies_and_groups
     * \ingroup buddy
     * @deprecated
     */
    typedef struct vx_resp_account_list_buddies_and_groups {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The number of buddies found in the list.
         */
        int buddy_count;

        /**
         * The number of groups found in the list.
         */
        int group_count;

        /**
         * A collection of buddy structures.
         */
        vx_buddy_t** buddies;

        /**
         * A collection of group structures.
         */
        vx_group_t** groups;
    } vx_resp_account_list_buddies_and_groups_t;

    /**
     * The response for vx_req_session_send_message
     * \see vx_req_session_send_message
     * \ingroup buddy
     */
    typedef struct vx_resp_session_send_message {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_session_send_message_t;

#ifndef DOXYGEN_MAM_SKIP
    /**
     * The response for vx_req_session_archive_query
     * \see vx_req_session_archive_query
     * \note V5 only.
     * \ingroup session
     */
    typedef struct vx_resp_session_archive_query {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The ID of the started query.
         * Use this ID to identify relevant vx_evt_session_archive_message and vx_evt_session_archive_query_end events.
         */
        char* query_id;
    } vx_resp_session_archive_query_t;
#endif

    /**
     * The response for vx_req_session_chat_history_query
     * \see vx_req_session_chat_history_query
     * \note V5 only.
     * \ingroup session
     */
    typedef struct vx_resp_session_chat_history_query {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The ID of the started query.
         * Use this ID to identify relevant vx_evt_session_chat_history_message and vx_evt_session_chat_history_query_end events.
         */
        char* query_id;
    } vx_resp_session_chat_history_query_t;

    /**
     * The response for vx_req_account_set_presence
     * \see vx_req_account_set_presence
     * \ingroup buddy
     */
    typedef struct vx_resp_account_set_presence {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_account_set_presence_t;

    /**
     * The response for vx_req_account_send_subscription_reply
     * \see vx_req_account_send_subscription_reply
     * \ingroup buddy
     */
    typedef struct vx_resp_account_send_subscription_reply {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_account_send_subscription_reply_t;

    /**
     * The response for vx_req_session_send_notification
     * \see vx_req_session_send_notification
     * \ingroup session
     */
    typedef struct vx_resp_session_send_notification {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_session_send_notification_t;

    /**
     * \deprecated This is deprecated and should not be used.
     * The response for vx_req_session_send_dtmf
     * \see vx_req_session_send_dtmf
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_resp_session_send_dtmf {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_session_send_dtmf_t;

    /**
     * The response for vx_req_account_create_block_rule
     * \see vx_req_account_create_block_rule
     * \ingroup buddy
     */
    typedef struct vx_resp_account_create_block_rule {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_account_create_block_rule_t;

    /**
     * The response for vx_req_account_delete_block_rule
     * \see vx_req_account_delete_block_rule
     * \ingroup buddy
     */
    typedef struct vx_resp_account_delete_block_rule {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_account_delete_block_rule_t;

    /**
     * The response for vx_req_account_list_block_rules
     * \see vx_req_account_list_block_rules
     * \ingroup buddy
     */
    typedef struct vx_resp_account_list_block_rules {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The number of block rules returned in the list.
         */
        int rule_count;

        /**
         * A list of block rules for the given account.
         */
        vx_block_rule_t** block_rules;
    } vx_resp_account_list_block_rules_t;

    /**
     * The response for vx_req_account_create_auto_accept_rule
     * \see vx_req_account_create_auto_accept_rule
     * \ingroup buddy
     */
    typedef struct vx_resp_account_create_auto_accept_rule {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_account_create_auto_accept_rule_t;

    /**
     * The response for vx_req_account_delete_auto_accept_rule
     * \see vx_req_account_delete_auto_accept_rule
     * \ingroup buddy
     */
    typedef struct vx_resp_account_delete_auto_accept_rule {
        vx_resp_base_t base;
    } vx_resp_account_delete_auto_accept_rule_t;

    /**
     * The response for vx_req_account_list_auto_accept_rules
     * \see vx_req_account_list_auto_accept_rules
     * \ingroup buddy
     */
    typedef struct vx_resp_account_list_auto_accept_rules {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The number of block rules returned in the list.
         */
        int rule_count;

        /**
         * A list of block rules for the given account.
         */
        vx_auto_accept_rule_t** auto_accept_rules;
    } vx_resp_account_list_auto_accept_rules_t;

    /**
     * \deprecated This is deprecated and should not be used.
     * The response for vx_req_account_update_account
     * \see vx_req_account_update_account
     * @deprecated
     */
    typedef struct vx_resp_account_update_account {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_account_update_account_t;

    /**
     * \deprecated This is deprecated and should not be used.
     * The response for vx_req_account_get_account
     * \see vx_req_account_get_account
     * @deprecated
     */
    typedef struct vx_resp_account_get_account {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * A pointer to a 'vx_account_t' struct which contains information about the account.
         */
        vx_account_t* account;
    } vx_resp_account_get_account_t;

    /**
     * The response for vx_req_account_send_sms
     * \see vx_req_account_send_sms
     */
    typedef struct vx_resp_account_send_sms {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_account_send_sms_t;

    /**
     * The response for vx_req_aux_connectivity_info
     * \see vx_req_aux_connectivity_info
     * \ingroup diagnostics
     */
    typedef struct vx_resp_aux_connectivity_info {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        int count;

        /**
         * A list of the test results for each test.
         */
        vx_connectivity_test_result_t** test_results;

        /**
         * The well known IP address used.
         */
        char* well_known_ip;

        /**
         * The stun server used.
         */
        char* stun_server;

        /**
         * The echo server used.
         */
        char* echo_server;

        /**
         * The echo port used.
         */
        int echo_port;

        /**
         * The timeout used.
         */
        int timeout;

        /**
         * The first (primary) simulated port for SIP testing.
         */
        int first_sip_port;

        /**
         * The second (fallback) simulated port for SIP testing.
         */
        int second_sip_port;

        /**
         * The simulated RTP port.
         */
        int rtp_port;

        /**
         * The simulated RTCP port.
         */
        int rtcp_port;
    } vx_resp_aux_connectivity_info_t;

    /**
     * The response for vx_req_aux_get_render_devices
     * \see vx_req_aux_get_render_devices
     * \ingroup devices
     */
    typedef struct vx_resp_aux_get_render_devices {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The number of render devices found.
         */
        int count;

        /**
         * An array of pointers to 'vx_device_t' structs.
         */
        vx_device_t** render_devices;

        /**
         * The render device currently in use by the Vivox SDK for the requested user.
         */
        vx_device_t* current_render_device;

        /**
         * The effective render device of the requested user.
         */
        vx_device_t* effective_render_device;

        /**
         * The default system render device of the requested user.
         */
        vx_device_t* default_render_device;

        /**
         * The default communication render device of the requested user.
         */
        vx_device_t* default_communication_render_device;
    } vx_resp_aux_get_render_devices_t;

    /**
     * The response for vx_req_aux_get_capture_devices
     * \see vx_req_aux_get_capture_devices
     * \ingroup devices
     */
    typedef struct vx_resp_aux_get_capture_devices {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The number of capture devices found.
         */
        int count;

        /**
         * A list of capture devices.
         */
        vx_device_t** capture_devices;

        /**
         * The current capture device of the requested user.
         */
        vx_device_t* current_capture_device;

        /**
         * The effective capture device of the requested user.
         */
        vx_device_t* effective_capture_device;

        /**
         * The default system capture device of the requested user.
         */
        vx_device_t* default_capture_device;

        /**
         * The default communication capture device of the requested user.
         */
        vx_device_t* default_communication_capture_device;
    } vx_resp_aux_get_capture_devices_t;

    /**
     * The response for vx_req_aux_set_render_device
     * \see vx_req_aux_set_render_device
     * \ingroup devices
     */
    typedef struct vx_resp_aux_set_render_device {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The globally unique ID assigned to the open instance of the current render device (after the set).
         * Empty if no device is open for this user.
         * This is useful for differentiating between discrete instances of "No Device".
         */
        char* open_render_device_guid;
    } vx_resp_aux_set_render_device_t;

    /**
     * The response for vx_req_aux_set_capture_device
     * \see vx_req_aux_set_capture_device
     * \ingroup devices
     */
    typedef struct vx_resp_aux_set_capture_device {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The globally unique ID assigned to the open instance of the current capture device (after the set).
         * Empty if no device is open for this user.
         * This is useful for differentiating between discrete instances of "No Device".
         */
        char* open_capture_device_guid;
    } vx_resp_aux_set_capture_device_t;

    /**
     * The response for vx_req_aux_get_mic_level
     * \see vx_req_aux_get_mic_level
     * \ingroup devices
     */
    typedef struct vx_resp_aux_get_mic_level {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The master "microphone" level.
         * This is a non-negative integer value between 0 and 100 (inclusive). The default value is 50.
         * A +6 increase represents a doubling of energy, and a +20 increase represents a tenfold increase in energy.
         */
        int level;
    } vx_resp_aux_get_mic_level_t;

    /**
     * The response for vx_req_aux_get_speaker_level
     * \see vx_req_aux_get_speaker_level
     * \ingroup devices
     */
    typedef struct vx_resp_aux_get_speaker_level {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The master "speaker" level.
         * This is a non-negative integer value between 0 and 100 (inclusive). The default value is 50.
         * A +6 increase represents a doubling of energy, and a +20 increase represents a tenfold increase in energy.
         */
        int level;
    } vx_resp_aux_get_speaker_level_t;

    /**
     * The response for vx_req_aux_set_mic_level
     * \see vx_req_aux_set_mic_level
     * \ingroup devices
     */
    typedef struct vx_resp_aux_set_mic_level {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_aux_set_mic_level_t;

    /**
     * The response for vx_req_aux_set_speaker_level
     * \see vx_req_aux_set_speaker_level_t
     * \ingroup devices
     */
    typedef struct vx_resp_aux_set_speaker_level {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_aux_set_speaker_level_t;

    /**
     * The response for vx_req_aux_render_audio_start
     * \see vx_req_aux_render_audio_start
     * \ingroup devices
     */
    typedef struct vx_resp_aux_render_audio_start {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_aux_render_audio_start_t;

    /**
     * The response for vx_req_aux_render_audio_modify
     */
    typedef struct vx_resp_aux_render_audio_modify {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_aux_render_audio_modify_t;

    /**
     * The response for vx_req_aux_get_vad_properties
     * \see vx_req_aux_set_vad_properties
     * \ingroup devices
     */
    typedef struct vx_resp_aux_get_vad_properties {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The "Hangover time" - the time (in milliseconds) that it takes for the VAD to switch back to silence
         * from speech mode after the last speech frame has been detected.
         */
        int vad_hangover;

        /**
         * A non-negative integer value between 0 and 100 (inclusive) which indicates the sensitivity of the VAD.
         * The default value is 50. Increasing this value corresponds to decreasing the sensitivity of the VAD,
         * where 0 is the most sensitive, and 100 is the least sensitive.
         */
        int vad_sensitivity;

        /**
         * A dimensionless value between 0 and 20000 (default 576) which controls how the VAD separates speech from background noise.
         */
        int vad_noise_floor;

        /**
         * VAD Automatic Parameter Selection - If this mode is 1 (enabled), then vad_hangover, vad_sensitivity, and vad_noise_floor
         * are ignored and the VAD automatically optimizes parameters.
         */
        int vad_auto;
    } vx_resp_aux_get_vad_properties_t;

    /**
     * The response for vx_req_aux_set_vad_properties
     * \see vx_req_aux_set_vad_properties
     * \ingroup devices
     */
    typedef struct vx_resp_aux_set_vad_properties {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_aux_set_vad_properties_t;

    /**
     * The response for vx_req_aux_get_derumbler_properties
     * \see vx_req_aux_set_derumbler_properties
     * \ingroup devices
     */
    typedef struct vx_resp_aux_get_derumbler_properties {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * Indicates whether the derumbler should be enabled (default=1) or disabled (0).
         */
        int enabled;

        /**
         * The frequency where the derumbler high-pass filter enters into full attenuation.
         * All frequencies at and below this corner frequency are greatly reduced in amplitude.
         * Frequencies above this corner frequency remain at their original amplitude,
         * aside from the frequencies that are just above the corner frequency.
         * Valid values are: 15, 60 (default), 100.
         */
        int stopband_corner_frequency;
    } vx_resp_aux_get_derumbler_properties_t;

    /**
     * The response for vx_req_aux_set_derumbler_properties
     * \see vx_req_aux_set_derumbler_properties
     * \ingroup devices
     */
    typedef struct vx_resp_aux_set_derumbler_properties {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_aux_set_derumbler_properties_t;

    /**
     * The response for vx_req_aux_render_audio_stop
     * \see vx_req_aux_render_audio_stop
     * \ingroup devices
     */
    typedef struct vx_resp_aux_render_audio_stop {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_aux_render_audio_stop_t;

    /**
     * The response for vx_req_aux_capture_audio_start
     * \see vx_req_aux_capture_audio_start
     * \ingroup devices
     */
    typedef struct vx_resp_aux_capture_audio_start {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_aux_capture_audio_start_t;

    /**
     * The response for vx_req_aux_capture_audio_stop
     * \see vx_req_aux_capture_audio_stop
     * \ingroup devices
     */
    typedef struct vx_resp_aux_capture_audio_stop {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * An opaque pointer to the captured audio buffer.
         * \note This pointer is not marshalled when working with the VivoxVoiceService.
         */
        void* audioBufferPtr;
    } vx_resp_aux_capture_audio_stop_t;

    /**
     * The response for vx_req_aux_global_monitor_keyboard_mouse
     * \see vx_req_aux_global_monitor_keyboard_mouse
     * \ingroup devices
     */
    typedef struct vx_resp_aux_global_monitor_keyboard_mouse {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_aux_global_monitor_keyboard_mouse_t;

    /**
     * The response for vx_req_aux_set_idle_timeout
     * \see vx_req_aux_set_idle_timeout
     * \ingroup devices
     */
    typedef struct vx_resp_aux_set_idle_timeout {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_aux_set_idle_timeout_t;

    /**
     * The response for vx_req_aux_create_account
     * \see vx_req_aux_create_account
     */
    typedef struct vx_resp_aux_create_account {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_aux_create_account_t;

    /**
     * The response for vx_req_aux_reactivate_account
     * \see vx_req_aux_reactivate_account
     */
    typedef struct vx_resp_aux_reactivate_account {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_aux_reactivate_account_t;

    /**
     * The response for vx_req_aux_deactivate_account
     * \see vx_req_aux_deactivate_account
     */
    typedef struct vx_resp_aux_deactivate_account {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_aux_deactivate_account_t;

    /**
     * The response for vx_req_account_post_crash_dump
     * \note This response is not applicable to the XML interface.
     * \see vx_req_account_post_crash_dump
     * \ingroup diagnostics
     */
    typedef struct vx_resp_account_post_crash_dump {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_account_post_crash_dump_t;

    /**
     * The response for vx_req_aux_reset_password
     * \see vx_req_aux_reset_password
     */
    typedef struct vx_resp_aux_reset_password {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_aux_reset_password_t;

    /**
     * The response for vx_req_account_get_session_fonts
     * \see vx_req_account_get_session_fonts
     * \ingroup voicefonts
     */
    typedef struct vx_resp_account_get_session_fonts {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * A list of session fonts.
         */
        vx_voice_font_t** session_fonts;

        /**
         * The number of session fonts.
         */
        int session_font_count;
    } vx_resp_account_get_session_fonts_t;

    /**
     * The response for vx_req_account_get_template_fonts
     * \see vx_req_account_get_template_fonts
     * \ingroup voicefonts
     */
    typedef struct vx_resp_account_get_template_fonts {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
        /**
         * A list of session fonts.
         */
        vx_voice_font_t** template_fonts;
        /**
         * The number of session fonts.
         */
        int template_font_count;
    } vx_resp_account_get_template_fonts_t;

    /**
     * The response for vx_req_aux_start_buffer_capture
     * \see vx_req_aux_start_buffer_capture
     * \ingroup adi
     */
    typedef struct vx_resp_aux_start_buffer_capture {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_aux_start_buffer_capture_t;

    /**
     * The response for vx_req_aux_play_audio_buffer
     * \see vx_req_aux_play_audio_buffer
     * \ingroup adi
     */
    typedef struct vx_resp_aux_play_audio_buffer {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_aux_play_audio_buffer_t;

    /**
     * The response for vx_req_aux_diagnostic_state_dump
     * \see vx_req_aux_diagnostic_state_dump
     */
    typedef struct vx_resp_aux_diagnostic_state_dump {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The number of connector objects in the state dump.
         */
        int state_connector_count;

        /**
         * A collection of connector objects in the state dump.
         */
        vx_state_connector_t** state_connectors;

        /**
         * The render device currently in use by the Vivox SDK.
         */
        vx_device_t* current_render_device;

        /**
         * The effective render device.
         */
        vx_device_t* effective_render_device;

        /**
         * The current capture device.
         */
        vx_device_t* current_capture_device;

        /**
         * The effective capture device.
         */
        vx_device_t* effective_capture_device;
    } vx_resp_aux_diagnostic_state_dump_t;

    /**
     * The response for vx_req_account_web_call
     * \see vx_req_account_web_call
     */
    typedef struct vx_resp_account_web_call {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The HTTP content type
         */
        char* content_type;

        /**
         * The content length
         */
        int content_length;

        /**
         * The content
         */
        char* content;
    } vx_resp_account_web_call_t;

    /**
     * Get the network statistics associated with a particular session group.
     * \see vx_req_sessiongroup_get_stats
     */
    typedef struct vx_resp_sessiongroup_get_stats {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * RESERVED FOR FUTURE USE
         */
        int insufficient_bandwidth;

        /**
         * RESERVED FOR FUTURE USE
         */
        int min_bars;

        /**
         * RESERVED FOR FUTURE USE
         */
        int max_bars;

        /**
         * \deprecated This is deprecated and should not be used.
         * An indication of the network quality in the range of 1-5, with 5 indicating the best quality.
         * @deprecated
         */
        int current_bars;

        /**
         * RESERVED FOR FUTURE USE
         */
        int pk_loss;

        /**
         * The number of packets received.
         */
        int incoming_received;

        /**
         * The number of incoming packets expected.
         */
        int incoming_expected;

        /**
         * The number of packets lost in the network.
         */
        int incoming_packetloss;

        /**
         * The number of packets received too late to be useful and discarded.
         */
        int incoming_out_of_time;

        /**
         * The number of packets received but discarded because the local queue overflowed.
         */
        int incoming_discarded;

        /**
         * The number of packets sent.
         */
        int outgoing_sent;

        /**
         * The number of render device underruns.
         * \note Applicable to mobile platforms only.
         */
        int render_device_underruns;

        /**
         * The number of render device overruns.
         * \note Applicable to mobile platforms only.
         */
        int render_device_overruns;

        /**
         * The number of render device errors.
         * \note Applicable to mobile platforms only.
         */
        int render_device_errors;

        /**
         * The SIP call ID.
         */
        char* call_id;

        /**
         * A flag which indicates whether Packet Loss Concealment (error correction) has occurred.
         */
        int plc_on;

        /**
         * The number of 10ms synthetic frames generated by Packet Loss Concealment.
         */
        int plc_synthetic_frames;

        /**
         * A codec negotiated in the current call.
         */
        char* codec_name;

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        int codec_mode;

        /**
         * The minimum network latency, which is detected in seconds.
         * This is zero if no latency measurements are made.
         */
        double min_latency;

        /**
         * The maximum network latency, which is detected in seconds.
         * This is zero if no latency measurements are made.
         */
        double max_latency;

        /**
         * The number of times that latency was measured.
         */
        int latency_measurement_count;

        /**
         * The total number of seconds of measured network latency.
         */
        double latency_sum;

        /**
         * The last latency that was measured.
         */
        double last_latency_measured;

        /**
         * The number of latency measurement packets lost.
         * This counter is reset to 0 every time vx_req_sessiongroup_get_stats is called.
         */
        int latency_packets_lost;

        /**
         * A computation of quality.
         */
        double r_factor;

        /**
         * The number of latency measurement request packets sent.
         */
        int latency_packets_sent;

        /**
         * The number of latency measurement response packets dropped.
         */
        int latency_packets_dropped;

        /**
         * The number of latency measurement packets that were too short or otherwise malformed.
         */
        int latency_packets_malformed;

        /**
         * The number of latency measurement packets that arrived before they were sent.
         * \note This can occur if there are clock adjustments.
         */
        int latency_packets_negative_latency;

        /**
         * The beginning of the sample period in fractional seconds since midnight on January 1, 1970 GMT.
         */
        double sample_interval_begin;

        /**
         * The end of the sample period in fractional seconds since midnight on January 1, 1970 GMT.
         */
        double sample_interval_end;

        /**
         * The number of intervals where 0, 1, 2, 3, or 4 or greater audio frames were read from the capture device.
         */
        int capture_device_consecutively_read_count[5];

        /**
         * The OPUS bit rate that was used for encoding the last transmitted OPUS packet.
         * If no OPUS packets were transmitted, this value is -1.
         */
        int current_opus_bit_rate;

        /**
         * The OPUS complexity that was used for encoding the last transmitted OPUS packet.
         * If no OPUS packets were transmitted, this value is -1.
         */
        int current_opus_complexity;

        /**
         * The OPUS VBR mode (vx_opus_vbr_mode) that was used for encoding the last transmitted OPUS packet.
         * If no OPUS packets were transmitted, this value is -1 .
         */
        int current_opus_vbr_mode;

        /**
         * The OPUS bandwith (vx_opus_bandwidth) that was used for encoding the last transmitted OPUS packet.
         * If no OPUS packets were transmitted, this value is -1.
         */
        int current_opus_bandwidth;

        /**
         * The OPUS max packet size limit that was used for encoding the last transmitted OPUS packet.
         * If no OPUS packets were transmitted, this value is -1.
         */
        int current_opus_max_packet_size;

        /**
         * Signals whether transport is secure (1) or not secure (0).
         * \note V5 only. In V4, this value is always equal to 0.
         */
        int signal_secure;
    } vx_resp_sessiongroup_get_stats_t;

    /**
     * The response for vx_req_account_send_message
     * \see vx_req_account_send_message
     * \ingroup buddy
     */
    typedef struct vx_resp_account_send_message {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;

        /**
         * The request ID assigned to the message sent.
         * This is non-NULL if the message is sent to a server.
         * If the message send failure will be reported by the server,
         * the SDK raises the evt_resp_account_send_message_failed event with this request ID.
         * \see vx_evt_resp_account_send_message_failed
         * \note V5 only. In V4, this is always equal to NULL.
         */
        char* request_id;
    } vx_resp_account_send_message_t;
#ifndef DOXYGEN_MAM_SKIP
    /**
     * The response for vx_req_account_archive_query
     * \see vx_req_account_archive_query
     * \note V5 only.
     * \ingroup account
     */
    typedef struct vx_resp_account_archive_query {
        /**
         * The common properties for all responses.
         */

        vx_resp_base_t base;
        /**
         * The ID of the started query.
         * Use this ID to identify relevant vx_evt_account_archive_message and vx_evt_account_archive_query_end events.
         */
        char* query_id;
    } vx_resp_account_archive_query_t;
#endif
    /**
     * The response for vx_req_account_chat_history_query
     * \see vx_req_account_chat_history_query
     * \note V5 only.
     * \ingroup account
     */
    typedef struct vx_resp_account_chat_history_query {
        /**
         * The common properties for all responses.
         */

        vx_resp_base_t base;
        /**
         * The ID of the started query.
         * Use this ID to identify relevant vx_evt_account_chat_history_message and vx_evt_account_chat_history_query_end events.
         */
        char* query_id;
    } vx_resp_account_chat_history_query_t;
    /**
     * The response for vx_req_aux_notify_application_state_change
     * \see vx_req_aux_notify_application_state_change
     */
    typedef struct vx_resp_aux_notify_application_state_change {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_aux_notify_application_state_change_t;

    /**
     * The response for vx_req_account_control_communications
     * \see vx_req_account_control_communications
     */
    typedef struct vx_resp_account_control_communications {
        /**
         * The common properties for all responses.
         */

        vx_resp_base_t base;
        /**
         * A line feed separated list of blocked or muted URIs.
         * This can be null for clear list operations or if no one was muted or blocked.
         */
        char* blocked_uris;
    } vx_resp_account_control_communications_t;

    /**
     * The response for vx_req_session_transcription_control
     * \see vx_req_session_transcription_control
     * \ingroup session
     */
    typedef struct vx_resp_session_transcription_control {
        /**
         * The common properties for all responses.
         */
        vx_resp_base_t base;
    } vx_resp_session_transcription_control_t;

#ifndef VIVOX_TYPES_ONLY
    /**
     * Deallocate a response object of any type.
     * \ingroup memorymanagement
     */
    VIVOXSDK_DLLEXPORT int destroy_resp(vx_resp_base_t* pCmd);
#endif

#ifdef __cplusplus
}
#endif

#pragma pack(pop)