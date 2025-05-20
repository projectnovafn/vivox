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

#pragma pack(push)
#pragma pack(8)

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * Sent whenever the login state of the particular account has transitioned from one value to another.
     * \ingroup login
     */
    typedef struct vx_evt_account_login_state_change {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The new state of the entity.
         * For specific state codes, refer to the codes at the end of this document.
         */
        vx_login_state_change_state state;

        /**
         * The handle returned from a successful account request.
         */
        VX_HANDLE account_handle;

        /**
         * The code used to identify why a state change has been made.
         */
        int status_code;

        /**
         * Text (in English) used to describe the status code.
         */
        char* status_string;

        /**
         * The originating login request cookie.
         * This is here because the login_state_logging_in state change event comes before the response with the handle.
         */
        VX_COOKIE cookie;

        /**
         * The originating login request cookie (non-marshallable).
         * This is here because the login_state_logging_in state change event comes before the response with the handle.
         */
        void* vcookie;
    } vx_evt_account_login_state_change_t;

    /**
     * Presented when a buddy has issued presence information.
     * \ingroup buddy
     */
    typedef struct vx_evt_buddy_presence {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        vx_buddy_presence_state state;

        /**
         * The handle returned from a successful login request.
         */
        VX_HANDLE account_handle;

        /**
         * The URI of the sender of the message.
         */
        char* buddy_uri;

        /**
         * The new presence of the buddy.
         * Refer to the codes in table \ref vx_buddy_presence_state
         */
        vx_buddy_presence_state presence;

        /**
         * A custom message string when presence is set to "custom".
         */
        char* custom_message;

        /**
         * The displayname if the buddy_uri had a displayname.
         */
        char* displayname;

        /**
         * The application of the buddy whose presence is being reported.
         * This can be NULL or empty.
         */
        char* application;

        /**
         * The contact address (URI) of the buddy whose presence is being reported.
         * This can be NULL or empty.
         */
        char* contact;

        /**
         * RESERVED FOR FUTURE USE
         * The priority of the buddy whose presence is being reported.
         * This can be NULL or empty.
         */
        char* priority;

        /**
         * The unique ID of the instance of the buddy whose presence is being reported.
         * This can be NULL or empty.
         */
        char* id;

        /**
         * The unique ID of the instance of the buddy whose presence is being reported.
         * This is used to distinguish between the same buddy when they are logged in on different devices.
         * This can be NULL or empty.
         * \note V5 only. In V4, this is always NULL.
         */
        char* encoded_uri_with_tag;
    } vx_evt_buddy_presence_t;

    /**
     * Generated when a buddy wants to request presence visibility.
     * This event is not presented if an auto-accept or auto-block rule matches the requesting buddy_uri.
     * Typically, the application uses this event to prompt a user to explicitly accept or deny the request for presence.
     * Optionally, the application might create and store an auto-accept or auto-block rule based on the user's selection.
     * The application should generate a vx_req_account_send_subscription_reply_t request based on application logic and/or end-user response.
     * The subscription_handle value must be extracted and returned as a parameter to vx_req_account_send_subscription_reply_t.
     * \see vx_req_account_buddy_set
     * \ingroup buddy
     */
    typedef struct vx_evt_subscription {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful login request.
         */
        VX_HANDLE account_handle;

        /**
         * The URI of the buddy whose presence is being sent.
         */
        char* buddy_uri;

        /**
         * The identifier of the subscription event.
         * Used when forming a reply with vx_req_account_send_subscription_reply_t.
         */
        char* subscription_handle;

        /**
         * subscription_presence is currently the only supported value.
         */
        vx_subscription_type subscription_type;

        /**
         * The displayname, if the buddy_uri had a displayname.
         */
        char* displayname;

        /**
         * The application of the buddy whose subscription is being reported.
         * This can be NULL or empty.
         */
        char* application;

        /**
         * NOT CURRENTLY IMPLEMENTED
         * An optional message supplied by the initiating user on vx_req_account_buddy_set_t.
         */
        char* message;
    } vx_evt_subscription_t;

    /**
     * Received when another user has started or stopped typing, or has raised or lowered their hand,
     * within the context of a session.
     * \ingroup session
     */
    typedef struct vx_evt_session_notification {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        vx_session_notification_state state;

        /**
         * The handle of the session to which this event applies.
         */
        VX_HANDLE session_handle;

        /**
         * The URI of the buddy whose presence is being sent.
         */
        char* participant_uri;

        /**
         * The new notification type from the buddy.
         * Refer to the codes in table \ref vx_notification_type
         */
        vx_notification_type notification_type;

        /**
         * The encoded URI for the user with the tag.
         * This uniquely identifies users that might appear multiple times in a channel.
         */
        char* encoded_uri_with_tag;

        /**
         * Indicates whether the message is from the current logged in user.
         */
        int is_current_user;
    } vx_evt_session_notification_t;

    /**
     * Presented when an incoming message has arrived from a participant in an open session with text enabled.
     * \ingroup session
     */
    typedef struct vx_evt_message {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        vx_message_state state;

        /**
         * The handle returned from a successful session group create request.
         * \see vx_req_sessiongroup_create
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The handle returned from a successful session add request.
         * \see vx_req_sessiongroup_add_session
         */
        VX_HANDLE session_handle;

        /**
         * The URI of the sender of the message.
         */
        char* participant_uri;

        /**
         * The content type of the message.
         */
        char* message_header;

        /**
         * The contents of the message.
         */
        char* message_body;

        /**
         * The displayname, if the participant_uri had a displayname.
         */
        char* participant_displayname;

        /**
         * The application of the entity who is sending the message.
         * This can be NULL or empty.
         */
        char* application;

        /**
         * The identity that the original sender wanted to present.
         * \note This is different than the participant_uri, which is the actual internal Vivox identity of the original sender.
         */
        char* alias_username;

        /**
         * The encoded URI for the user with the tag.
         * This uniquely identifies users that might appear multiple times in a channel.
         */
        char* encoded_uri_with_tag;

        /**
         * Indicates whether the message is from the current logged in user.
         */
        int is_current_user;

        /**
         * The language (default NULL, implies "en").
         * \note V5 only. In V4, this is always NULL.
         */
        char* language;

        /**
         * The namespace of the custom application stanza (optional, default NULL).
         * \note V5 only. In V4, this is always NULL.
         */
        char* application_stanza_namespace;

        /**
         * The custom application stanza body (optional, default NULL).
         * \note V5 only. In V4, this is always NULL.
         */
        char* application_stanza_body;
    } vx_evt_message_t;
#ifndef DOXYGEN_MAM_SKIP
    /**
     * Presented when a message is found in response to a vx_req_session_archive_query request.
     * This event is triggered for every message that is found.
     * \note V5 only.
     * \ingroup session
     */
    typedef struct vx_evt_session_archive_message {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle used in vx_req_sessiongroup_addsession.
         * \see vx_req_sessiongroup_addsession
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The handle returned from a successful session add request.
         * \see vx_req_sessiongroup_add_session
         */
        VX_HANDLE session_handle;

        /**
         * The ID of the query in progress.
         * This ID is returned for a successfully started query in a vx_resp_session_archive_query response.
         */
        char* query_id;

        /**
         * The time stamp of the message in the format specified in XEP-0082.
         */
        char* time_stamp;

        /**
         * The URI of the sender of this message.
         */
        char* participant_uri;

        /**
         * The content of the message, UTF-8 encoded.
         */
        char* message_body;

        /**
         * The server-assigned ID of the message used for paging through large result sets.
         */
        char* message_id;

        /**
         * The encoded URI for the sending user with the tag.
         * This uniquely identifies users that might be logged in with the same account name from multiple devices (Multi-Login).
         * \note These users can be joined to a channel from only one device at any given moment of time (no Multi-Join).
         */
        char* encoded_uri_with_tag;

        /**
         * Indicates whether the message is from the current logged in user.
         */
        int is_current_user;

        /**
         * The language (default NULL, implies "en").
         */
        char* language;
    } vx_evt_session_archive_message_t;
#endif
    /**
     * Presented when a message is found in response to a vx_req_session_chat_history_query request.
     * This event is triggered for every message that is found.
     * \note V5 only.
     * \ingroup session
     */
    typedef struct vx_evt_session_chat_history_message {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle used in vx_req_sessiongroup_addsession.
         * \see vx_req_sessiongroup_addsession
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The handle returned from a successful session add request.
         * \see vx_req_sessiongroup_add_session
         */
        VX_HANDLE session_handle;

        /**
         * The ID of the query in progress.
         * This ID is returned for a successfully started query in a vx_resp_session_chat_history_query response.
         */
        char* query_id;

        /**
         * The time stamp of the message in the format specified in XEP-0082.
         */
        char* time_stamp;

        /**
         * The URI of the sender of this message.
         */
        char* participant_uri;

        /**
         * The content of the message, UTF-8 encoded.
         */
        char* message_body;

        /**
         * The server-assigned ID of the message used for paging through large result sets.
         */
        char* message_id;

        /**
         * The encoded URI for the sending user with the tag.
         * This uniquely identifies users that might be logged in with the same account name from multiple devices (Multi-Login).
         * \note These users can be joined to a channel from only one device at any given moment of time (no Multi-Join).
         */
        char* encoded_uri_with_tag;

        /**
         * Indicates whether the message is from the current logged in user.
         */
        int is_current_user;

        /**
         * The language (default NULL, implies "en").
         */
        char* language;
    } vx_evt_session_chat_history_message_t;
    /**
     * Presented when an incoming transcribed text has arrived from a participant in an open session.
     * \ingroup session
     */
    typedef struct vx_evt_transcribed_message {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;
        /**
         * The handle used in vx_req_sessiongroup_addsession.
         * \see vx_req_sessiongroup_addsession
         */
        VX_HANDLE sessiongroup_handle;
        /**
         * The handle returned from successful session add request.
         * \see vx_req_sessiongroup_add_session
         */
        VX_HANDLE session_handle;
        /**
         * The URI of the speaker.
         */
        char* participant_uri;
        /**
         * The transcribed text, UTF-8 encoded.
         */
        char* text;
        /**
         * The language (default NULL, implies "en").
         */
        char* language;
        /**
         * Indicates whether the message is from the current logged in user.
         */
        int is_current_user;
        /**
         * The displayname, if the participant_uri had a displayname.
         */
        char* participant_displayname;
    } vx_evt_transcribed_message_t;
#ifndef DOXYGEN_MAM_SKIP
    /**
     * Presented when a channel history query is completed.
     * There is one vx_evt_session_archive_query_end event for every query started with a vx_req_session_archive_query request.
     * \note V5 only.
     * \ingroup session
     */
    typedef struct vx_evt_session_archive_query_end {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle used in vx_req_sessiongroup_addsession.
         * \see vx_req_sessiongroup_addsession
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The handle returned from a successful session add request.
         * \see vx_req_sessiongroup_add_session
         */
        VX_HANDLE session_handle;

        /**
         * The ID of the query in progress.
         * This ID is returned for a successfully started query in a vx_resp_session_archive_query response.
         */
        char* query_id;

        /**
         * The query result code.
         * This is similar to a response result_code.
         */
        int return_code;

        /**
         * The query status code.
         * This is similar to a response status_code.
         */
        int status_code;

        /**
         * The first returned message ID.
         * This ID can be used for paging.
         */
        char* first_id;

        /**
         * The last returned message ID.
         * This ID can be used for paging.
         */
        char* last_id;

        /**
         * The index of the first matching message reported with a vx_evt_session_archive_message event.
         */
        unsigned int first_index;

        /**
         * The total number of messages matching the criteria specified in the vx_req_session_archive_query request.
         * This is the total size of the result set.
         */
        unsigned int count;
    } vx_evt_session_archive_query_end_t;
#endif

    /**
     * Presented when a channel history query is completed.
     * There is one vx_evt_session_chat_history_query_end event for every query started with a vx_req_session_chat_history_query request.
     * \note V5 only.
     * \ingroup session
     */
    typedef struct vx_evt_session_chat_history_query_end {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle used in vx_req_sessiongroup_addsession.
         * \see vx_req_sessiongroup_addsession
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The handle returned from a successful session add request.
         * \see vx_req_sessiongroup_add_session
         */
        VX_HANDLE session_handle;

        /**
         * The ID of the query in progress.
         * This ID is returned for a successfully started query in a vx_resp_session_chat_history_query response.
         */
        char* query_id;

        /**
         * The query result code.
         * This is similar to a response result_code.
         */
        int return_code;

        /**
         * The query status code.
         * This is similar to a response status_code.
         */
        int status_code;

        /**
         * The first returned message ID.
         * This ID can be used for paging.
         */
        char* first_id;

        /**
         * The last returned message ID.
         * This ID can be used for paging.
         */
        char* last_id;

        /**
         * The index of the first matching message reported with a vx_evt_session_chat_history_message event.
         */
        unsigned int first_index;

        /**
         * The total number of messages matching the criteria specified in the vx_req_session_chat_history_query request.
         * This is the total size of the result set.
         */
        unsigned int count;
    } vx_evt_session_chat_history_query_end_t;

    /**
     * Used by the SDK sound system to present audio information to the application,
     * which can be used to create a visual representation of the speaker (for example, a "VU" meter).
     * These events are presented at one half the rate of the audio capture rate.
     * \ingroup devices
     */
    typedef struct vx_evt_aux_audio_properties {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        vx_aux_audio_properties_state state;

        /**
         * A flag used to determine whether the mic is active.
         * - 1 indicates that the capture device is detecting speech activity
         *     (as determined by the built-in Vivox Voice Activity Detector).
         * - 0 indicates that no speech energy has been detected.
         */
        int mic_is_active;

        /**
         * Indicates the current value of the master microphone volume, which is set by using the "set mic volume" method.
         * This is a non-negative integer value between 0 and 100 (inclusive).
         */
        int mic_volume;

        /**
         * The instantaneous (fast) energy at the capture device.
         * This is a value from 0.0 to 1.0, which when graphed, show behavior similar to an analog VU Meter.
         * \note For an unsmoothed dBFS value of fast energy, see fast_energy_meter and its companion *_meter values.
         */
        double mic_energy;

        /**
         * Indicates the current value of the master speaker volume, which is set by using the "set speaker volume" method.
         * This is a non-negative integer value between 0 and 100 (inclusive).
         */
        int speaker_volume;

        /**
         * The energy associated with any rendered audio.
         */
        double speaker_energy;

        /**
         * Indicates whether voice is detected in the rendered audio stream at this moment.
         */
        int speaker_is_active;

        /**
         * The instantaneous (fast) energy at the capture device.
         * This is a floating point number between 0 and 1, which is logarithmically spaced representing -Inf dBFS to +0dBFS.
         */
        double fast_energy_meter;

        /**
         * The current noise floor estimate.
         * This is a floating point number between 0 and 1, which is logarithmically spaced representing -Inf dBFS to +0dBFS.
         */
        double noise_floor_meter;

        /**
         * The current magnitude that "fast energy" must surpass to activate speech.
         * This ranges between noise_floor and -9dBFS.
         * This is a floating point number between 0 and 1, which is logarithmically spaced representing -Inf dBFS to +0dBFS.
         */
        double speech_threshold_meter;
    } vx_evt_aux_audio_properties_t;

    /**
     * For vx_evt_buddy_changed_t and vx_evt_buddy_group_changed_t objects, indicates whether the object was set (added or updated) or deleted.
     * \ingroup buddy
     */
    typedef enum {
        /**
         * The buddy or group was added or updated.
         */
        change_type_set = 1,

        /**
         * The buddy or group was deleted
         */
        change_type_delete = 2
    } vx_change_type_t;

    /**
     * Presented when a buddy is either set (added or updated) or removed.
     * \ingroup buddy
     */
    typedef struct vx_evt_buddy_changed {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful login request.
         */
        VX_HANDLE account_handle;

        /**
         * Indicates the change type (set or delete).
         */
        vx_change_type_t change_type;

        /**
         * The URI of the buddy.
         */
        char* buddy_uri;

        /**
         * The display name of the buddy.
         */
        char* display_name;

        /**
         * Application-specific buddy data.
         */
        char* buddy_data;

        /**
         * The group that the buddy belongs to.
         */
        int group_id;

        /**
         * \deprecated This is deprecated and should not be used.
         * The account ID of the buddy.
         * @deprecated
         */
        int account_id;
    } vx_evt_buddy_changed_t;

    /**
     * Presented when a buddy group is set (added or updated) or removed.
     * \ingroup buddy
     */
    typedef struct vx_evt_buddy_group_changed {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful login request.
         */
        VX_HANDLE account_handle;

        /**
         * Indicates the change type (set or delete).
         */
        vx_change_type_t change_type;

        /**
         * The ID for the group.
         */
        int group_id;

        /**
         * The display name for the group.
         */
        char* group_name;

        /**
         * Application-specific group data.
         */
        char* group_data;
    } vx_evt_buddy_group_changed_t;

    /**
     * Presented when the buddy or group list undergoes a significant change.
     * This event is always received after login, and can be used to build the initial buddy and group UI.
     * \ingroup buddy
     */
    typedef struct vx_evt_buddy_and_group_list_changed {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful login request.
         */
        VX_HANDLE account_handle;

        /**
         * The count of the number of buddies.
         */
        int buddy_count;

        /**
         * An array of pointers to buddies.
         */
        vx_buddy_t** buddies;

        /**
         * The count of the number of groups.
         */
        int group_count;

        /**
         * An array of buddy group pointers.
         */
        vx_group_t** groups;
    } vx_evt_buddy_and_group_list_changed_t;

    /**
     * Raised to indicate to the application that a particular
     * keyboard/mouse button combination has been pressed or cleared.
     * \ingroup devices
     * \attention Not supported on the iPhone platform.
     */
    typedef struct vx_evt_keyboard_mouse {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The name of the binding as set in vx_req_aux_global_monitor_keyboard_mouse_t.
         */
        char* name;

        /**
         * 1 if the key/mouse button combination corresponding to this name is down.
         * 0 if the key/mouse button combination corresponding to this name has been cleared.
         */
        int is_down;
    } vx_evt_keyboard_mouse_t;

    /**
     * Raised to indicate to the application that the user has transitioned between
     * an idle and non-idle state (in either order).
     * \ingroup devices
     * \attention Not supported on the iPhone platform.
     */
    typedef struct vx_evt_idle_state_changed {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * 1 if the user is idle.
         * 0 if the user is not idle.
         */
        int is_idle;
    } vx_evt_idle_state_changed_t;

    /**
     * The common structure for holding call-related statistics.
     */
    typedef struct vx_call_stats {
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
         * An indication of the network quality in the range of 1-5, with 5 indicating the best quality.
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
         * RESERVED FOR FUTURE USE
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
         * \note Mobile platforms only.
         */
        int render_device_underruns;

        /**
         * The number of render device overruns.
         * \note Mobile platforms only.
         */
        int render_device_overruns;

        /**
         * The number of render device errors.
         * \note Mobile platforms only.
         */
        int render_device_errors;

        /**
         * The SIP call ID.
         */
        char* call_id;

        /**
         * A flag that indicates whether packet loss concealment (error correction) has happened.
         */
        int plc_on;

        /**
         * The number of 10ms synthetic frames generated by packet loss concealment.
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
         * The minimum network latency detected in seconds.
         * This is zero if no latency measurements are made.
         */
        double min_latency;

        /**
         * The maximum network latency detected in seconds.
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
         * The number of times that latency packet were received where their prior expected response was not received.
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
         * The number of latency measurement response packets lost.
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
         * The beginning of the sample period in fractional seconds since midnight January 1, 1970 GMT.
         */
        double sample_interval_begin;

        /**
         * The end of the sample period in fractional seconds since midnight January 1, 1970 GMT.
         */
        double sample_interval_end;

        /**
         * The number of intervals where 0, 1, 2, 3, or 4 or greater audio frames were read from the capture device.
         */
        int capture_device_consecutively_read_count[5];

        /**
         * The OPUS bit rate that was used for encoding the last transmitted OPUS packet.
         * This is -1 if no OPUS packets were transmitted.
         */
        int current_opus_bit_rate;

        /**
         * The OPUS complexity that was used for encoding the last transmitted OPUS packet.
         * This is -1 if no OPUS packets were transmitted.
         */
        int current_opus_complexity;

        /**
         * The OPUS VBR mode (vx_opus_vbr_mode) that was used for encoding the last transmitted OPUS packet.
         * This is -1 if no OPUS packets were transmitted.
         */
        int current_opus_vbr_mode;

        /**
         * The OPUS bandwith (vx_opus_bandwidth) that was used for encoding the last transmitted OPUS packet.
         * This is -1 if no OPUS packets were transmitted.
         */
        int current_opus_bandwidth;

        /**
         * The OPUS max packet size limit that was used for encoding the last transmitted OPUS packet.
         * This is -1 if no OPUS packets were transmitted.
         */
        int current_opus_max_packet_size;
    } vx_call_stats_t;

    /**
     * Sent when session media has been altered.
     * \ingroup session
     */
    typedef struct vx_evt_media_stream_updated {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle created for the session group.
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The handle created for the session.
         */
        VX_HANDLE session_handle;

        /**
         * The code used to identify why a state change has been made.
         * This code is only useful if the state is equal to session_media_disconnected.
         * In this case, the following rules apply:
         * - 1. Any code < 400 can be ignored.
         * - 2. 401 - A password is needed to join this channel. Typically, an application presents a password dialog at this point. You can retry the request if you obtain a password from the user.
         * - 3. 403 - If the call is to a channel, the user does not have sufficient privilege to join the channel. Otherwise, the call has been declined.
         * - 4. 404 - The destination (either a channel or other user) does not exist.
         * - 5. 408 - The remote user did not answer the call. You can retry the request after a 10s delay.
         * - 6. 480 - The remote user is temporarily offline. You can retry the request after a 10s delay.
         * - 7. 486 - The remote user is busy (on another call). You can retry the request after a 10s delay.
         * - 8. 503 - The server is busy (overloaded). You can retry the request after a 10s delay.
         * - 9. 603 - The remote user has declined the call.
         * The application should only retry a failed request if there is a chance the retry will succeed, as indicated in the preceding list.
         * It is recommended that the status_string field only be displayed as diagnostic information for status codes > 400, and not the codes in the preceding list.
         * This status_string is often generated by the network, which can also include public PSTN networks.
         * This can result in status_string values that are informative to a technician, but not to an end user, and can be subject to change.
         * Applications should not depend on the value of this field.
         * Applications should present an application-specific message for each of the status codes outlined in the preceding list.
         */
        int status_code;

        /**
         * Text (in English) to describe the status code.
         * For more information, refer to the vx_evt_media_stream_updated status_code description.
         */
        char* status_string;

        /**
         * The new state of the entity.
         * Refer to the codes in table \ref vx_session_media_state
         */
        vx_session_media_state state;

        /**
         * Indicates whether this is an incoming call.
         */
        int incoming;

        /**
         * The durable media identifier used to access value add services.
         */
        char* durable_media_id;

        /**
         * The current media probe server.
         */
        char* media_probe_server;

        /**
         * NULL, except for state session_media_disconnected.
         */
        vx_call_stats_t* call_stats;
    } vx_evt_media_stream_updated_t;

    /**
     * Sent when the session text has been altered.
     * \ingroup session
     */
    typedef struct vx_evt_text_stream_updated {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle created for the session group.
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The handle created for the session.
         */
        VX_HANDLE session_handle;

        /**
         * Indicates whether text is enabled on the session.
         */
        int enabled;

        /**
         * Indicates the state of text (connected or disconnected).
         */
        vx_session_text_state state;

        /**
         * Indicates whether this is incoming.
         */
        int incoming;

        /**
         * Code used to identify why a state change has been made.
         * These codes are only useful for when the state is equal to session_text_disconnected.
         * For a description of these status codes, see \ref vx_evt_media_stream_updated
         */
        int status_code;

        /**
         * Text (in English) used to describe the status code.
         * For guidelines on using this field, see \ref vx_evt_media_stream_updated
         */
        char* status_string;
    } vx_evt_text_stream_updated_t;

    /**
     * Sent when a session group is added.
     * \ingroup sessiongroup
     */
    typedef struct vx_evt_sessiongroup_added {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * Returned from a successful session group create request.
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * Returned from a successful session group login request.
         */
        VX_HANDLE account_handle;

        /**
         * The session group type.
         */
        vx_sessiongroup_type type;

        /**
         * The identity that is presented on all subsequent communications from this session group to a remote user.
         */
        char* alias_username;
    } vx_evt_sessiongroup_added_t;

    /**
     * Sent when a session group is removed.
     * \ingroup sessiongroup
     */
    typedef struct vx_evt_sessiongroup_removed {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * Returned from a successful session group create request.
         */
        VX_HANDLE sessiongroup_handle;
    } vx_evt_sessiongroup_removed_t;

    /**
     * Sent when a session is added.
     * \ingroup session
     */
    typedef struct vx_evt_session_added {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful session group create request.
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The handle returned from a successful session add request.
         */
        VX_HANDLE session_handle;

        /**
         * The full URI of the session (user/channel).
         */
        char* uri;

        /**
         * Set to 1 if this session relates to a channel.
         * Set to 0 if this session is not related to a channel.
         */
        int is_channel;

        /**
         * Set to 1 if this is a session that was added because it was an incoming call.
         * Set to 0 for all other cases.
         */
        int incoming;

        /**
         * The name of the channel, if passed in when the channel is created.
         * This is always empty for incoming sessions.
         */
        char* channel_name;

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        char* displayname;

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        char* application;

        /**
         * The identity of the remote user if P2P, or null if a channel call.
         * \note This is different than the participant_uri, which is the actual internal Vivox identity of the remote user.
         */
        char* alias_username;
    } vx_evt_session_added_t;

    /**
     * Sent when a session is removed.
     * \ingroup session
     */
    typedef struct vx_evt_session_removed {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful session group create request.
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The handle returned from a successful session add request.
         */
        VX_HANDLE session_handle;

        /**
         * The full URI of the session (user/channel).
         */
        char* uri;
    } vx_evt_session_removed_t;

    /**
     * Presented when a participant is added to a session.
     * When joining a channel, a participant added event is raised for all active participants in the channel.
     * \ingroup session
     */
    typedef struct vx_evt_participant_added {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful session group create request.
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The handle returned from a successful session create request.
         */
        VX_HANDLE session_handle;

        /**
         * The URI of the participant whose state has changed.
         */
        char* participant_uri;

        /**
         * The account name of the participant.
         */
        char* account_name;

        /**
         * \deprecated Use displayname instead.
         * @deprecated
         */
        char* display_name;

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        int participant_type;

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        char* application;

        /**
         * Indicates whether the user is an authenticated user (0) or is logged in anonymously as a guest (1).
         * \note This is only supported on channel calls.
         */
        int is_anonymous_login;

        /**
         * The display name of the participant if in a channel or a P2P-initiated session.
         * \note This field is not populated for the callee in a text-initiated P2P session.
         * This field will contain one of the following values (in order), based on availability:
         * - 1) The buddy display name
         * - 2) The SIP display name (only available for the callee, not available for the caller)
         * - 3) The account name (not available if the account is out of domain)
         * - 4) The URI without the SIP (ex: username@foo.vivox.com)
         */
        char* displayname;

        /**
         * The identity of the user if P2P, or null if a channel call.
         * \note This is different than the participant_uri, which is the actual internal Vivox identity of the remote user.
         */
        char* alias_username;

        /**
         * The encoded URI for the user with the tag.
         * This uniquely identifies users that might appear multiple times in a channel.
         */
        char* encoded_uri_with_tag;

        /**
         * Indicates whether the message is from the current logged in user.
         */
        int is_current_user;
    } vx_evt_participant_added_t;

    /**
     * Presented when a participant is removed from a session.
     * \ingroup session
     */
    typedef struct vx_evt_participant_removed {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful session group create request.
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The handle returned from a successful session create request.
         */
        VX_HANDLE session_handle;

        /**
         * The URI of the participant whose state has changed.
         */
        char* participant_uri;

        /**
         * The account name of the participant.
         */
        char* account_name;

        /**
         * The reason why the participant was removed from the session.
         * The default is "left". See \ref vx_participant_removed_reason
         */
        vx_participant_removed_reason reason;

        /**
         * The identity of the user if P2P, or null if a channel call.
         * \note This is different than the participant_uri, which is the actual internal Vivox identity of the original sender.
         */
        char* alias_username;

        /**
         * The encoded URI for the user with the tag.
         * This uniquely identifies users that might appear multiple times in a channel.
         */
        char* encoded_uri_with_tag;

        /**
         * Indicates whether the message is from the current logged in user.
         */
        int is_current_user;
    } vx_evt_participant_removed_t;

    /**
     * The special state of the local voice participant that is used to indicate that the participant
     * is attemping to speak while the system is in a state that will not transmit the participant's audio.
     */
    typedef enum {
        participant_diagnostic_state_speaking_while_mic_muted = 1,
        participant_diagnostic_state_speaking_while_mic_volume_zero = 2,
        participant_diagnostic_state_no_capture_device = 3,
        participant_diagnostic_state_no_render_device = 4,
        participant_diagnostic_state_capture_device_read_errors = 5,
        participant_diagnostic_state_render_device_write_errors = 6
    } vx_participant_diagnostic_state_t;

    /**
     * Received when the properties of the participant change
     * For example: mod muted, speaking, volume, energy, or typing notifications.
     * \ingroup session
     */
    typedef struct vx_evt_participant_updated {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful session group create request.
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The handle returned from a successful session create request.
         */
        VX_HANDLE session_handle;

        /**
         * The URI of the participant whose properties are being updated.
         */
        char* participant_uri;

        /**
         * Used to determine if the user has been muted by the moderator.
         * - 0 indicates the user was not muted.
         * - 1 indicates the user was muted.
         */
        int is_moderator_muted;

        /**
         * Indicates if the participant is speaking.
         */
        int is_speaking;

        /**
         * This is the volume level that has been set by the user.
         * This is a non-negative integer value between 0 and 100 (inclusive), and should not change often.
         */
        int volume;

        /**
         * The energy, or the intensity, of the participant audio.
         * This is used to determine how loud the user is speaking.
         * This is a value between 0 and 1.
         */
        double energy;

        /**
         * This indicates which media the user is participating in.
         * See #VX_MEDIA_FLAGS_AUDIO and #VX_MEDIA_FLAGS_TEXT
         */
        int active_media;

        /**
         * Indicates whether the participant's audio is locally muted for the user.
         */
        int is_muted_for_me;

        /**
         * Indicates whether the participant's text is locally muted for the user.
         */
        int is_text_muted_for_me;

        /**
         * Used to determine if the user's text has been muted by the moderator.
         * - 0 indicates the text was not muted.
         * - 1 indicates the text was muted.
         */
        int is_moderator_text_muted;

        /**
         * The type of the participant.
         * \see vx_participant_type
         */
        vx_participant_type type;

        /**
         * A list of diagnostic states, which tells the application the following information:
         * - The participant is attempting to speak, but the system is not in a state to propogate that speech (for example, the mic is muted).
         * - The participant has unavailable capture or render devices due to certain causes.
         */
        vx_participant_diagnostic_state_t* diagnostic_states;

        /**
         * The total number of diagnostic states.
         */
        int diagnostic_state_count;

        /**
         * The identity of the user if P2P, or NULL if a channel call.
         * \note This is different than the participant_uri, which is the actual internal Vivox identity of the original sender.
         */
        char* alias_username;

        /**
         * The encoded URI for the user with the tag.
         * This uniquely identifies users that might appear multiple times in a channel.
         */
        char* encoded_uri_with_tag;

        /**
         * Indicates whether the message is from the current logged in user.
         */
        int is_current_user;

        /**
         * Indicates if the participant's capture device is unavailable due to reasons other than muting.
         * Check the event's diagnostic_states for the cause (available for local participants only).
         * - If the participant's render device is still operating, then the participant is "listen only".
         * - If both the capture and render devices are unavailable, then the participant is "unavailable"/"on hold".
         */
        int has_unavailable_capture_device;

        /**
         * Indicates if the participant's render device is unavailable.
         * Check the event's diagnostic_states for the cause (available for local participants only).
         * - If the participant's capture device is still operating, then the participant is "speak only"/"deaf".
         * - If both the capture and render devices are unavailable, then the participant is "unavailable"/"on hold".
         */
        int has_unavailable_render_device;
    } vx_evt_participant_updated_t;

    /**
     * Posted after a frame has been played.
     * When playback has been stopped by the application, the first, current, and total frames are equal to zero.
     * \ingroup csr
     */
    typedef struct vx_evt_sessiongroup_playback_frame_played {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful session group create request.
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The sequence number of the first frame.
         */
        int first_frame;

        /**
         * The current frame sequences number.
         */
        int current_frame;

        /**
         * The total number of frames available.
         */
        int total_frames;
    } vx_evt_sessiongroup_playback_frame_played_t;

    /**
     * Sent when a session is updated.
     * \ingroup session
     */
    typedef struct vx_evt_session_updated {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful session group create request.
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The handle returned from a successful session add request.
         */
        VX_HANDLE session_handle;

        /**
         * The full URI of the session.
         */
        char* uri;

        /**
         * Indicates whether the session's audio is muted.
         */
        int is_muted;

        /**
         * The volume of this session.
         */
        int volume;

        /**
         * Indicates whether the session is transmitting.
         */
        int transmit_enabled;

        /**
         * Indicates whether the session has focus.
         */
        int is_focused;

        /**
         * The position of the virtual "mouth".
         * This three vector is a right handed Cartesian coordinate, with the positive axis pointing towards the speaker's right,
         * the positive Y axis pointing up, and the positive Z axis pointing towards the speaker.
         */
        double speaker_position[3];  // {x, y, z}

        /**
         * The ID of the session font applied to this session.
         * 0 = none.
         */
        int session_font_id;

        /**
         * Indicates whether the session's text is muted.
         */
        int is_text_muted;

        /**
         * Indicates whether there is an audio ad playing in this session.
         */
        int is_ad_playing;
    } vx_evt_session_updated_t;

    /**
     * Sent when a session group is updated.
     * \ingroup sessiongroup
     */
    typedef struct vx_evt_sessiongroup_updated {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful session group create request.
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * \deprecated This is deprecated and should not be used.
         * Indicates whether in delayed playback.
         * When in delayed playback, the mic is not active.
         * \ingroup obsolete
         * @deprecated
         */
        int in_delayed_playback;

        /**
         * \deprecated This is deprecated and should not be used.
         * Indicates the playback speed.
         * \ingroup obsolete
         * @deprecated
         */
        double current_playback_speed;

        /**
         * \deprecated This is deprecated and should not be used.
         * Indicates the playback mode.
         * \ingroup obsolete
         * @deprecated
         */
        vx_sessiongroup_playback_mode current_playback_mode;

        /**
         * \deprecated This is deprecated and should not be used.
         * Indicates whether playback is paused.
         * \ingroup obsolete
         * @deprecated
         */
        int playback_paused;

        /**
         * \deprecated This is deprecated and should not be used.
         * The total capacity of the loop buffer.
         * \ingroup obsolete
         * @deprecated
         */
        int loop_buffer_capacity;

        /**
         * \deprecated This is deprecated and should not be used.
         * The sequence number of first frame in the loop buffer.
         * This starts increasing when the loop buffer fills.
         * \ingroup obsolete
         * @deprecated
         */
        int first_loop_frame;

        /**
         * \deprecated This is deprecated and should not be used.
         * The total number of frames captured to the loop buffer since recording started.
         * This peaks when the loop buffer fills.
         * \ingroup obsolete
         * @deprecated
         */
        int total_loop_frames_captured;

        /**
         * \deprecated This is deprecated and should not be used.
         * The sequence number of the last frame played.
         * \ingroup obsolete
         * @deprecated
         */
        int last_loop_frame_played;

        /**
         * \deprecated This is deprecated and should not be used.
         * The filename currently being recorded.
         * This is empty if no file is being recorded.
         * \ingroup obsolete
         * @deprecated
         */
        char* current_recording_filename;

        /**
         * \deprecated This is deprecated and should not be used.
         * The total number of frames recorded to file.
         * \ingroup obsolete
         * @deprecated
         */
        int total_recorded_frames;

        /**
         * \deprecated This is deprecated and should not be used.
         * The timestamp associated with the first frame in microseconds.
         * - On non-Windows platforms, this is computed from gettimeofday().
         * - On Windows platforms, this is computed from GetSystemTimeAsFileTime()
         * \note This is for file-based recording only.
         * \ingroup obsolete
         * @deprecated
         */
        long long first_frame_timestamp_us;
    } vx_evt_sessiongroup_updated_t;

    /**
     * Received when certain media requests have completed
     *
     * \ingroup sessiongroup
     */
    typedef struct vx_evt_media_completion {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful session group create request.
         * This field stays empty if the completion type is 'aux_*'.
         * \see vx_req_sessiongroup_create
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The type of media that has completed.
         */
        vx_media_completion_type completion_type;
    } vx_evt_media_completion_t;

    /**
     * The server can send messages to the SDK that the SDK does not need to consume.
     * These messages are propagated to the application through this event.
     * The application can choose to parse and consume these messages or to ignore them.
     */
    typedef struct vx_evt_server_app_data {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful account login request.
         * \see vx_req_account_login
         */
        VX_HANDLE account_handle;

        /**
         * The type of the incoming data.
         */
        char* content_type;

        /**
         * The content of the message being received from the server.
         */
        char* content;
    } vx_evt_server_app_data_t;

    /**
     * Raised when a message from another user is received.
     * \note This is not to be confused with IMs - this is a P2P communication mechanism for applications to communicate custom content.
     * \see vx_req_account_send_user_app_data
     */
    typedef struct vx_evt_user_app_data {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful account login request.
         * \see vx_req_account_login
         */
        VX_HANDLE account_handle;

        /**
         * The URI of the account sending the message.
         */
        char* from_uri;

        /**
         * The type of the incoming data.
         */
        char* content_type;

        /**
         * The content of the message being received from the specified account.
         */
        char* content;
    } vx_evt_user_app_data_t;

    typedef enum {
        /**
         * The message that was sent when the target user was offline.
         */
        vx_evt_network_message_type_offline_message = 1,
        vx_evt_network_message_type_admin_message = 2,
        vx_evt_network_message_type_sessionless_message = 3
    } vx_evt_network_message_type;

    /**
     * Raised when the network sends a message to a user (as opposed to a user to user message).
     * This includes messages that were stored and forwarded on behalf the user, and generic admin messages.
     */
    typedef struct vx_evt_network_message {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful account login request.
         * \see vx_req_account_login
         */
        VX_HANDLE account_handle;

        /**
         * The type of the message.
         */
        vx_evt_network_message_type network_message_type;

        /**
         * The type of the incoming data.
         */
        char* content_type;

        /**
         * The content of the message being received from the server.
         */
        char* content;

        /**
         * The sender of the message.
         */
        char* sender_uri;

        /**
         * The sender display name.
         */
        char* sender_display_name;

        /**
         * The identity that the original sender wanted to present.
         * \note This is different than the participant_uri, which is the actual internal Vivox identity of the original sender.
         */
        char* sender_alias_username;

        /**
         * The identity that the original sender wanted to send to.
         * \note This is different than the participant_uri, which is the actual internal Vivox identity of the original sender.
         */
        char* receiver_alias_username;
    } vx_evt_network_message_t;

    /**
     * Raised when the SDK is running out of process and the connection state of the Vivox Voice Service (VVS) changes.
     * Sent when the connection is made and when the connection is lost.
     * Alerts the application so the VVS can be restarted, if needed.
     */
    typedef struct vx_evt_voice_service_connection_state_changed {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * Indicates whether the voice service connection state is connected.
         */
        int connected;

        /**
         * The platform of the machine that the voice service is running on
         */
        char* platform;

        /**
         * The version of the voice service.
         */
        char* version;

        /**
         * The data directory.
         */
        char* data_directory;

        /**
         * Indicates whether the network test ran.
         */
        int network_test_run;

        /**
         * Indicates whether the network test completed.
         */
        int network_test_completed;

        /**
         * Indicates whether the network test has passed or failed.
         * This can change depending on the network connection and the power state of the machine.
         */
        int network_test_state;

        /**
         * Indicates if the network is down.
         */
        int network_is_down;
    } vx_evt_voice_service_connection_state_changed_t;

    typedef enum {
        /**
         * On some platforms (WinXP) with some drivers, polling to find out which devices has changed can take a long time.
         * When the SDK finds that polling can take a long time, it stops looking for device changes.
         * When this happens, vx_evt_audio_device_hot_swap is raised with event_type set to vx_audio_device_hot_swap_event_type_disabled_due_to_platform_constraints.
         */
        vx_audio_device_hot_swap_event_type_disabled_due_to_platform_constraints = 0,
        /**
         * When the active render device changes, vx_evt_audio_device_hot_swap is raised with event_type set to vx_audio_device_hot_swap_event_type_active_render_device_changed.
         */
        vx_audio_device_hot_swap_event_type_active_render_device_changed = 1,
        /**
         * When the active capture device changes, vx_evt_audio_device_hot_swap is raised with event_type set to vx_audio_device_hot_swap_event_type_active_capture_device_changed.
         */
        vx_audio_device_hot_swap_event_type_active_capture_device_changed = 2,
        /**
         * @future
         */
        vx_audio_device_hot_swap_event_type_audio_device_added = 3,
        /**
         * @future
         */
        vx_audio_device_hot_swap_event_type_audio_device_removed = 4
    } vx_audio_device_hot_swap_event_type_t;

    /**
     * Raised when the publication state has changed.
     * \ingroup buddy
     */
    typedef struct vx_evt_publication_state_changed {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful login request.
         */
        VX_HANDLE account_handle;

        /**
         * The alias associated with this publication.
         */
        char* alias_username;

        /**
         * The state of the publication.
         */
        vx_publication_state_change_state state;

        /**
         * The presence code.
         * The following list details possible values:
         * - 0 - buddy_presence_offline
         * - 2 - buddy_presence_online
         * - 3 - buddy_presence_busy
         * - 4 - buddy_presence_brb
         * - 5 - buddy_presence_away
         * - 6 - buddy_presence_onthephone
         * - 7 - buddy_presence_outtolunch
         */
        vx_buddy_presence_state presence;

        /**
         * A custom message string when presence is set.
         */
        char* custom_message;

        /**
         * Code used to identify why a state change has been made.
         */
        int status_code;

        /**
         * Text (in English) used to describe the status code.
         */
        char* status_string;
    } vx_evt_publication_state_changed_t;

    /**
     * Raised when audio device changes are made that impact the audio capture or rendering experience, or when other audio devices are added or removed.
     */
    typedef struct vx_evt_audio_device_hot_swap {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The type of hot swap event.
         */
        vx_audio_device_hot_swap_event_type_t event_type;

        /**
         * In the case of vx_audio_device_hot_swap_event_type_active_render_device_changed or vx_audio_device_hot_swap_event_type_active_capture_device_changed,
         * the new active device.
         */
        vx_device_t* relevant_device;
        /**
         * The account handle of the user whose device was changed as a result of the hot swap event.
         * If no user is logged in, this field is a null pointer.
         */
        VX_HANDLE account_handle;
    } vx_evt_audio_device_hot_swap_t;

    /**
     * Raised when a message from another user is received.
     * \see vx_req_account_send_message
     * \note V5 only.
     * \ingroup account
     */
    typedef struct vx_evt_user_to_user_message {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful account login request.
         * \see vx_req_account_anonymous_login
         */
        VX_HANDLE account_handle;

        /**
         * The URI of the account sending the message.
         */
        char* from_uri;

        /**
         * The encoded URI for the sending user with the tag.
         * This uniquely identifies users that might be logged in with the same account name from multiple devices (Multi-Login).
         */
        char* encoded_uri_with_tag;

        /**
         * The content of the message being received, UTF-8 encoded.
         */
        char* message_body;

        /**
         * The language (default NULL, implies "en").
         */
        char* language;

        /**
         * The namespace of the custom application stanza (optional, default NULL).
         */
        char* application_stanza_namespace;

        /**
         * The custom application stanza body (optional, default NULL).
         */
        char* application_stanza_body;

        /**
         * The displayname, if the from_uri had a displayname.
         */
        char* from_displayname;
    } vx_evt_user_to_user_message_t;
#ifndef DOXYGEN_MAM_SKIP
    /**
     * Presented when a message is found in response to vx_req_account_archive_query request.
     * This event is triggered for every message found.
     * \note V5 only.
     * \ingroup account
     */
    typedef struct vx_evt_account_archive_message {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful account login request.
         * \see vx_req_account_anonymous_login
         */
        VX_HANDLE account_handle;

        /**
         * The ID of the query in progress.
         * This ID is returned for a successfully started query in a vx_resp_account_archive_query response.
         */
        char* query_id;

        /**
         * The time stamp of the message in the format specified in XEP-0082.
         */
        char* time_stamp;

        /**
         * The URI of the channel that this message was exchanged in.
         * \note Mutually exclusive with participant_uri.
         */
        char* channel_uri;

        /**
         * The URI of the sender/receiver of the message for inbound/outbound messages, respectively.
         * \note Mutually exclusive with channel_uri.
         */
        char* participant_uri;

        /**
         * The message direction: 1 for inbound, and 0 for outbound.
         */
        int is_inbound;

        /**
         * The content of the message, UTF-8 encoded.
         */
        char* message_body;

        /**
         * The server-assigned ID of the message used for paging through large result sets.
         */
        char* message_id;

        /**
         * The encoded URI for the sending user with the tag.
         * This uniquely identifies users that might be logged in with the same account name from multiple devices (Multi-Login).
         * \note These users can be joined to a channel from only one device at any given moment of time (no Multi-Join).
         */
        char* encoded_uri_with_tag;

        /**
         * The language (default NULL, implies "en").
         */
        char* language;
    } vx_evt_account_archive_message_t;

    /**
     * Presented when a message is found in response to vx_req_account_chat_history_query request.
     * This event is triggered for every message found.
     * \note V5 only.
     * \ingroup account
     */
    typedef struct vx_evt_account_chat_history_message {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful account login request.
         * \see vx_req_account_anonymous_login
         */
        VX_HANDLE account_handle;

        /**
         * The ID of the query in progress.
         * This ID is returned for a successfully started query in a vx_resp_account_chat_history_query response.
         */
        char* query_id;

        /**
         * The time stamp of the message in the format specified in XEP-0082.
         */
        char* time_stamp;

        /**
         * The URI of the channel that this message was exchanged in.
         * \note Mutually exclusive with participant_uri.
         */
        char* channel_uri;

        /**
         * The URI of the sender/receiver of the message for inbound/outbound messages, respectively.
         * \note Mutually exclusive with channel_uri.
         */
        char* participant_uri;

        /**
         * The message direction: 1 for inbound, and 0 for outbound.
         */
        int is_inbound;

        /**
         * The content of the message, UTF-8 encoded.
         */
        char* message_body;

        /**
         * The server-assigned ID of the message used for paging through large result sets.
         */
        char* message_id;

        /**
         * The encoded URI for the sending user with the tag.
         * This uniquely identifies users that might be logged in with the same account name from multiple devices (Multi-Login).
         * \note These users can be joined to a channel from only one device at any given moment of time (no Multi-Join).
         */
        char* encoded_uri_with_tag;

        /**
         * The language (default NULL, implies "en").
         */
        char* language;
    } vx_evt_account_chat_history_message_t;

#ifndef DOXYGEN_MAM_SKIP
    /**
     * Presented when an account message archive query is completed.
     * There is one vx_evt_account_archive_query_end event for every query started with vx_req_account_archive_query request.
     * \note V5 only.
     * \ingroup account
     */
    typedef struct vx_evt_account_archive_query_end {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful account login request.
         * \see vx_req_account_anonymous_login
         */
        VX_HANDLE account_handle;

        /**
         * The ID of the query in progress.
         * This ID is returned for a successfully started query in a vx_resp_account_archive_query response.
         */
        char* query_id;

        /**
         * The query result code.
         * This is similar to a response result_code.
         */
        int return_code;

        /**
         * The query status code.
         * This is similar to a response status_code.
         */
        int status_code;

        /**
         * The first returned message ID.
         * This ID can be used for paging.
         */
        char* first_id;

        /**
         * The last returned message ID.
         * This ID can be used for paging.
         */
        char* last_id;

        /**
         * The index of the first matching message reported with a vx_evt_account_archive_message event.
         */
        unsigned int first_index;

        /**
         * The total number of messages matching the criteria specified in the vx_req_account_archive_query request.
         * This is the total size of the result set.
         */
        unsigned int count;
    } vx_evt_account_archive_query_end_t;
#endif
    /**
     * Presented when an account message archive query is completed.
     * There is one vx_evt_account_chat_history_query_end event for every query started with vx_req_account_chat_history_query request.
     * \note V5 only.
     * \ingroup account
     */
    typedef struct vx_evt_account_chat_history_query_end {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful account login request.
         * \see vx_req_account_anonymous_login
         */
        VX_HANDLE account_handle;

        /**
         * The ID of the query in progress.
         * This ID is returned for a successfully started query in a vx_resp_account_chat_history_query response.
         */
        char* query_id;

        /**
         * The query result code.
         * This is similar to a response result_code.
         */
        int return_code;

        /**
         * The query status code.
         * This is similar to a response status_code.
         */
        int status_code;

        /**
         * The first returned message ID.
         * This ID can be used for paging.
         */
        char* first_id;

        /**
         * The last returned message ID.
         * This ID can be used for paging.
         */
        char* last_id;

        /**
         * The index of the first matching message reported with a vx_evt_account_chat_history_message event.
         */
        unsigned int first_index;

        /**
         * The total number of messages matching the criteria specified in the vx_req_account_chat_history_query request.
         * This is the total size of the result set.
         */
        unsigned int count;
    } vx_evt_account_chat_history_query_end_t;
#endif
    /**
     * Raised when a server reports a directed message send failure.
     * \see vx_req_account_send_message
     * \note V5 only.
     * \ingroup account
     */
    typedef struct vx_evt_account_send_message_failed {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful account login request.
         * \see vx_req_account_anonymous_login
         */
        VX_HANDLE account_handle;

        /**
         * The ID of the query in progress.
         * This ID is returned for a successfully started query in a vx_resp_account_send_message response.
         * \see vx_resp_account_send_message
         */
        char* request_id;

        /**
         * The status code.
         * This is similar to a response status_code.
         */
        int status_code;
    } vx_evt_account_send_message_failed_t;

    /**
    * Raised when a text-to-speech (TTS) message injection has started.
    * \note V5 only.
    * \ingroup texttospeech
    */
    typedef struct vx_evt_tts_injection_started {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The number of consumers (active sessions and/or local playback players) to which the message is about to get injected to.
         */
        unsigned int num_consumers;

        /**
         * The ID of the utterance that this event relates to.
         */
        unsigned int utterance_id;

        /**
         * The duration in seconds of the utterance.
         */
        double utterance_duration;

        /**
         * The destination to which the utterance was injected to.
         */
        unsigned int tts_destination;
    } vx_evt_tts_injection_started_t;


    /**
     * Raised when an injection of a text-to-speech (TTS) message has ended.
     * \note V5 only.
     * \ingroup texttospeech
     */
    typedef struct vx_evt_tts_injection_ended {
        /**
          * The common properties for all events.
          */
        vx_evt_base_t base;

        /**
         * The number of consumers (active sessions and/or local playback players) to which the message was injected to.
         */
        unsigned int num_consumers;

        /**
         * The ID of the utterance that this event relates to.
         */
        unsigned int utterance_id;

        /**
         * The destination to which the utterance was injected to.
         */
        unsigned int tts_destination;
    } vx_evt_tts_injection_ended_t;

    /**
     * Raised when an injection of a text-to-speech (TTS) message has failed.
     * \note V5 only.
     * \ingroup texttospeech
     */
    typedef struct vx_evt_tts_injection_failed {
        /**
          * The common properties for all events.
          */
        vx_evt_base_t base;

        /**
         * The failed injection's resultant error code.
         */
        unsigned int status;

        /**
         * The ID of the utterance that this event relates to.
         */
        unsigned int utterance_id;

        /**
         * The destination to which the utterance was injected to.
         */
        unsigned int tts_destination;
    } vx_evt_tts_injection_failed_t;

    /**
     * Raised when the transcription (STT) service has a failure.
     * \note V5 only.
     * \ingroup speechtotext
     */
    typedef struct vx_evt_stt_failed
    {
        /**
         * The common properties for all events.
         */
        vx_evt_base_t base;

        /**
         * The handle returned from a successful session group create request.
         * \see vx_req_sessiongroup_create
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The handle returned from a successful session add request.
         * \see vx_req_sessiongroup_add_session
         */
        VX_HANDLE session_handle;

        /**
         * The transcription failure error code.
         */
        int status_code;

        /**
         * Text (in English) used to describe the status code.
         */
        char* status_string;
    } vx_evt_stt_failed_t;


    /**
     * Free any event of any type.
     * \ingroup memorymanagement
     */
#ifndef VIVOX_TYPES_ONLY
    VIVOXSDK_DLLEXPORT int destroy_evt(vx_evt_base_t* pCmd);
#endif

#ifdef __cplusplus
}
#endif

#pragma pack(pop)