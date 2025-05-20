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
    /* The Vivox request structs.
     * All of these structs begin with a vx_req (request), which is used for identification purposes.
     */

     /**
      * The maximum length of the session URI.
      */
#define MAX_CHANNEL_URI_LENGTH 1024

      /**
       * Connect the application to the Vivox service.
       * \see vx_resp_connector_create
       * \ingroup connector
       */
    typedef struct vx_req_connector_create {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * \deprecated Do not use.
         * @deprecated
         */
        char* client_name;

        /**
         * The URL for the Vivox account management server.
         * \note This value is provided by Vivox.
         */
        char* acct_mgmt_server;

        /**
         * An optional parameter that specifies the minimum UDP source port for the SDK to use.
         * If the value is 0 (the recommended setting), then the Vivox SDK uses ephemeral ports assigned by the operating system.
         * If a range of ports on the client needs to be specified (this is not recommended), then enter
         * the minimum port number and the maximum port number to create a range of ports for the Vivox SDK.
         * - The specified range must be at least 32 ports.
         * - Only ports above 1024 are allowed.
         * \note minimum_port and maximum port should both be set to 0 or both be set to a specific port range.
         */
        int minimum_port;

        /**
         * An optional parameter that specifies the maximum UDP source port for the SDK to use.
         * If the value is 0 (the recommended setting), then the Vivox SDK uses ephemeral ports assigned by the operating system.
         * If a range of ports on the client needs to be specified (this is not recommended), then enter
         * the minimum port number and the maximum port number to create a range of ports for the Vivox SDK.
         * - The specified range must be at least 32 ports.
         * - Only ports above 1024 are allowed.
         * \note minimum_port and maximum port should both be set to 0 or both be set to a specific port range.
         */
        int maximum_port;

        /**
         * Control how the SDK attempts to traverse NAT devices.
         */
        vx_attempt_stun attempt_stun;

        /**
         * Specify which mode to start the connector in: connector_mode_legacy or connector_mode_normal.
         * The default setting is connector_mode_normal.
         */
        vx_connector_mode mode;

        /**
         * The folder where logs are created.
         */
        char* log_folder;

        /**
         * The prefix that is prepended to each log file.
         */
        char* log_filename_prefix;

        /**
         * The suffix or extension that is appended to each log file.
         */
        char* log_filename_suffix;

        /**
         * Specify the log level for the Vivox SDK to use.
         * - -1: NONE - No logging.
         * - 0: ERROR - Log errors only.
         * - 1: WARNING - Log errors and warnings.
         * - 2: INFO - Log errors, warnings, and info.
         * - 3: DEBUG - Log errors, warnings, info, and debug.
         * - 4: TRACE - Verbose logging. Likely to have significant performance implications.
         * - 5: ALL - Log almost everything. Very likely to have significant performance implications.
         */
        int log_level;

        /**
         * The type of session handle to generate.
         */
        vx_session_handle_type session_handle_type;

        /**
         * A unique string value that identifies the application that is integrated with the SDK.
         * \note This is an optional value that is provided by Vivox.
         * Any value passed in on this field is present on events received by others that pertain to your identity:
         * - vx_evt_message_t
         * - vx_evt_subscription_t
         * - vx_evt_buddy_presence_t
         * - vx_evt_session_added_t
         */
        char* application;

        /**
         * The maximum number of calls that can be active at any one time.
         * - The default is 3
         * - The minimum is 2
         * - The maximum is 1000
         * Each call is preallocated at a cost of 56K per call.
         */
        int max_calls;

        /**
         * Determine whether to allow cross-domain logins.
         */
        int allow_cross_domain_logins;

        /**
         * \deprecated Use the configured_codecs field instead.
         * The default codec.
         * @deprecated
         */
        int default_codec;

        /**
         * A unique alphanumeric-only string value that identifies the application that is integrated with the SDK.
         * \attention Do not set this value unless instructed to by your Vivox representative.
         * \note This is an optional value.
         * This value is restricted to alphanumeric characters only, and is limited to three characters.
         * Any value passed in on this field is present on SIP messages in the user agent string.
         */
        char* user_agent_id;

        /**
         * Enter a server by using the following format:
         * ip-address:starting-port
         */
        char* media_probe_server;

        /**
         * The DNS name of an HTTP proxy server to use to successfully connect to the account management server.
         */
        char* http_proxy_server_name;

        /**
         * The port that the HTTP proxy server is listening on.
         * If no value is set, then this defaults to 80.
         */
        int http_proxy_server_port;

        /**
         * \deprecated This is deprecated and should not be used.
         * Handle multiple participants with the same SIP URI more gracefully in a channel.
         * @deprecated
         */
        int enable_duplicate_participant_uris;

        /**
         * The preferred connector handle.
         * \attention This cannot match any existing handle (for example, account_handle or session_handle).
         * This is a string.
         * This must include at least one non-numeric character.
         * If this is empty, then a handle is automatically generated.
         */
        char* connector_handle;

        /**
         * A bitmask that specifies the set of codecs that this application permits.
         * This should be one or a combination of values from the vx_codec enumeration.
         */
        unsigned int configured_codecs;
    } vx_req_connector_create_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_connector_create object.
     * \ingroup connector
     */
    VIVOXSDK_DLLEXPORT int vx_req_connector_create_create(vx_req_connector_create_t** req);
#endif

    /**
     * Call this when the application is shutting down to gracefully release resources.
     * \see vx_resp_connector_initiate_shutdown
     * \ingroup connector
     */
    typedef struct vx_req_connector_initiate_shutdown {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;
        /**
         * The handle returned from a successful vx_req_connector_create request.
         */
        VX_HANDLE connector_handle;
        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        char* client_name;
    } vx_req_connector_initiate_shutdown_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_connector_initiate_shutdown object.
     * \ingroup connector
     */
    VIVOXSDK_DLLEXPORT int vx_req_connector_initiate_shutdown_create(vx_req_connector_initiate_shutdown_t** req);
#endif

    /**
     * \deprecated Use vx_req_account_anonymous_login instead.
     * Log in and log out of specific user accounts.
     * \note This can only be called after connector initialization has successfully completed.
     * \see vx_resp_account_login\n
     * \ingroup login
     * @deprecated
     */
    typedef struct vx_req_account_login {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_connector_create request.
         */
        VX_HANDLE connector_handle;

        /**
         * The user's account name.
         */
        char* acct_name;

        /**
         * The user's account password.
         */
        char* acct_password;

        /**
         * Control how the SDK responds to incoming voice calls.
         * - mode_verify_answer - the default setting.
         * - mode_auto_answer - this setting is deprecated and should not be used.
         * - mode_busy_answer - automatically answer every call with a 486 busy.
         */
        vx_session_answer_mode answer_mode;

        /**
         * Determine whether the user will enable text for all sessions.
         * - text_mode_enabled - text will be enabled.
         * - text_mode_disabled - text will not be enabled.
         * The default value is text_mode_enabled.
         */
        vx_text_mode enable_text;

        /**
         * An integer that specifies the maximum number of participant property events the SDK sends while in a channel.
         * If this is set, then the SDK attempts to generate an event at the given frequency, but does not generate two identical events in a row.
         * If this is not set, then the default is "on state change", which means that events are sent when the participant
         * starts talking, stops talking, is muted, or is unmuted.
         * The following list details valid values for this integer:
         * - 0 - Never
         * - 5 - 10 times per second
         * - 10 - 5 times per second
         * - 50 - 1 time per second
         * - 100 - On participant state change (this is the default value)
         */
        int participant_property_frequency;

        /**
         * An integer that determines whether to enable and allow buddy and presence information.
         * If this is set to 0 (the default value), then buddy lists and presence status are not retrieved by the SDK,
         * and any command relating to buddies or presence that is submitted to the SDK is rejected.
         * Setting this to 1 enables buddy and presence functionality.
         */
        int enable_buddies_and_presence;

        /**
         * Determine how the SDK handles incoming buddy subscriptions.
         * The following list details valid values:
         * - 0 - mode_auto_accept
         * - 1 - mode_auto_add
         * - 2 - mode_block
         * - 3 - mode_hide
         * - 4 - mode_application
         */
        vx_buddy_management_mode buddy_management_mode;

        /**
         * \deprecated This flag does not affect anything.
         * @deprecated
         */
        int enable_client_ringback;

        /**
         * If this is set to 1, then the SDK posts crash dumps that occur on SDK threads to Vivox
         * so they can be automatically analyzed.
         */
        int autopost_crash_dumps;

        /**
         * Override the account management server set in vx_req_connector_create.
         * If this is set to NULL or empty, the account management server is set
         * to what is used in the vx_req_connector_create command.
         */
        char* acct_mgmt_server;

        /**
         * An application token that is provided by the developer.
         * \note This is required if the acct_mgmt_server is configured to require app tokens.
         * This ensures that one application cannot use the resources of another application when sharing the same backend.
         */
        char* application_token;

        /**
         * A unique string value that identifies the application that is integrated with the SDK.
         * \note This is an optional value that is provided by Vivox.
         * If this is set, then this overrides the corresponding value in connector create.
         * Any value passed in on this field is present on events received by others that pertain to your identity:
         * - vx_evt_message_t
         * - vx_evt_subscription_t
         * - vx_evt_buddy_presence_t
         * - vx_evt_session_added_t
         */
        char* application_override;

        /**
         * The actual client IP address to pass in requests to the Vivox network.
         * \note This is only supported in the server SDK, and is otherwise ignored.
         */
        char* client_ip_override;

        /**
         * Determine whether to enable presence persistence.
         * - When this is set to 1, the buddy and watchers list is downloaded from the Vivox backend.
         * - When this is set to 0, the application is responsible for setting buddies and watchers
         *   by using the appropriate requests.
         * The default value is 1.
         */
        int enable_presence_persistence;

        /**
         * The preferred account handle.
         * \attention This cannot match any existing handle (for example, account_handle or session_handle).
         * This is a string.
         * This must include at least one non-numeric character.
         * If this is empty, then a handle is automatically generated.
         */
        char* account_handle;
    } vx_req_account_login_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_login object.
     * \ingroup login
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_login_create(vx_req_account_login_t** req);
#endif

    /**
     * \deprecated Use vx_req_account_anonymous_login instead.
     * Log in to specific user accounts by using an authorization token (authtoken) that is retrieved from the Vivox server API.
     * \note This can only be called after connector initialization has successfully completed.
     * \see vx_resp_account_authtoken_login
     * \ingroup login
     * @deprecated
     */
    typedef struct vx_req_account_authtoken_login {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_connector_create request.
         */
        VX_HANDLE connector_handle;

        /**
         * The user's auth token.
         * The auth token is created by the client server that makes the viv_adm_auth.php call.
         */
        char* authtoken;

        /**
         * Determine whether the user will enable text for all sessions.
         * - text_mode_enabled - text will be enabled.
         * - text_mode_disabled - text will not be enabled.
         * The default value is text_mode_enabled.
         */
        vx_text_mode enable_text;

        /**
         * An integer that specifies the maximum number of participant property events the SDK sends while in a channel.
         * If this is set, then the SDK attempts to generate an event at the given frequency, but does not generate two identical events in a row.
         * If this is not set, then the default is "on state change", which means that events are sent when the participant
         * starts talking, stops talking, is muted, or is unmuted.
         * The following list details valid values for this integer:
         * - 0 - Never
         * - 5 - 10 times per second
         * - 10 - 5 times per second
         * - 50 - 1 time per second
         * - 100 - On participant state change (this is the default value)
         */
        int participant_property_frequency;

        /**
         * Determine whether to enable and allow buddy and presence information.
         * If this is set to 0 (the default value), then buddy lists and presence status are not retrieved by the SDK,
         * and any command relating to buddies or presence that is submitted to the SDK is rejected.
         * Setting this to 1 enables buddy and presence functionality.
         */
        int enable_buddies_and_presence;

        /**
         * Determine how the SDK handles incoming buddy subscriptions.
         * The following list details valid values:
         * - 0 - mode_auto_accept
         * - 1 - mode_auto_add
         * - 2 - mode_block
         * - 3 - mode_hide
         * - 4 - mode_application
         */
        vx_buddy_management_mode buddy_management_mode;

        /**
         * If this is set to 1, then the SDK posts crash dumps that occur on SDK threads to Vivox
         * so they can be automatically analyzed.
         */
        int autopost_crash_dumps;

        /**
         * Override the account management server set in vx_req_connector_create.
         * If this is set to NULL or empty, then the account management server is used in the vx_req_connector_create command.
         */
        char* acct_mgmt_server;

        /**
         * An application token that is provided by the developer.
         * \note This is required if the acct_mgmt_server is configured to require app tokens.
         * This ensures that one application cannot use the resources of another application when sharing the same backend.
         */
        char* application_token;

        /**
         * A unique string value that identifies the application that is integrated with the SDK.
         * \note This is an optional value that is provided by Vivox.
         * If this is set, then this overrides the corresponding value in connector create.
         * Any value passed in on this field is present on events received by others that pertain to your identity:
         * - vx_evt_message_t
         * - vx_evt_subscription_t
         * - vx_evt_buddy_presence_t
         * - vx_evt_session_added_t
         */
        char* application_override;

        /**
         * Control how the SDK responds to incoming voice calls.
         * - mode_verify_answer - the default setting.
         * - mode_auto_answer - this setting is deprecated and should not be used.
         * - mode_busy_answer - automatically answer every call with a 486 busy.
         */
        vx_session_answer_mode answer_mode;

        /**
         * The actual client IP address to pass in requests to the Vivox network.
         * \note This is only supported in the server SDK, and is otherwise ignored.
         */
        char* client_ip_override;

        /**
         * Determine whether to enable presence persistence.
         * - When this is set to 1, the buddy and watchers list is downloaded from the Vivox backend.
         * - When this is set to 0, the application is responsible for setting buddies and watchers
         *   by using the appropriate requests.
         * The default value is 1.
         */
        int enable_presence_persistence;

        /**
         * The preferred account handle.
         * \attention This cannot match any existing handle (for example, account_handle or session_handle).
         * This is a string.
         * This must include at least one non-numeric character.
         * If this is empty, then a handle is automatically generated.
         */
        char* account_handle;
    } vx_req_account_authtoken_login_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_authtoken_login object.
     * \ingroup login
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_authtoken_login_create(vx_req_account_authtoken_login_t** req);
#endif

    /**
     * Log in anonymously to the Vivox network.
     * This allows a user to log in and receive a temporary SIP URI and a user-generated display name, if supplied.
     * \note This can only be called after connector initialization has successfully completed.
     * \see vx_resp_account_anonymous_login\n
     * \ingroup login
     */
    typedef struct vx_req_account_anonymous_login {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_connector_create request.
         */
        VX_HANDLE connector_handle;

        /**
         * The user's display name.
         * This is the display name that is seen by others.
         */
        char* displayname;

        /**
         * An integer that specifies the maximum number of participant property events the SDK sends while in a channel.
         * If this is set, then the SDK attempts to generate an event at the given frequency, but does not generate two identical events in a row.
         * If this is not set, then the default is "on state change", which means that events are sent when the participant
         * starts talking, stops talking, is muted, or is unmuted.
         * The following list details valid values for this integer:
         * - 0 - Never
         * - 5 - 10 times per second
         * - 10 - 5 times per second
         * - 50 - 1 time per second
         * - 100 - On participant state change (this is the default)
         */
        int participant_property_frequency;

        /**
         * RESERVED FOR FUTURE USE
         * Determine whether to enable and allow buddy and presence information.
         * If this is set to 0 (the default value), then buddy lists and presence status are not retrieved by the SDK,
         * and any command relating to buddies or presence submitted to the SDK is rejected.
         * Setting this to 1 enables buddy and presence functionality.
         */
        int enable_buddies_and_presence;

        /**
         * RESERVED FOR FUTURE USE
         * Determine how the SDK handles incoming buddy subscriptions.
         */
        vx_buddy_management_mode buddy_management_mode;

        /**
         * If this is set to 1, then the SDK posts crash dumps that occur on SDK threads to Vivox
         * so they can be automatically analyzed.
         */
        int autopost_crash_dumps;

        /**
         * Override the account management server set in vx_req_connector_create.
         * If this is set to NULL or empty, then the account management server is used in the vx_req_connector_create command.
         */
        char* acct_mgmt_server;

        /**
         * An application token that is provided by the developer.
         * \note This is required if the acct_mgmt_server is configured to require app tokens.
         * This ensures that one application cannot use the resources of another application when sharing the same backend.
         */
        char* application_token;

        /**
         * A unique string value that identifies the application that is integrated with the SDK.
         * \note This is an optional value that is provided by Vivox.
         * If this is set, this overrides the corresponding value in connector create.
         * Any value that is passed in on this field is present on events received by others that pertain to your identity:
         * - vx_evt_message_t
         * - vx_evt_subscription_t
         * - vx_evt_buddy_presence_t
         * - vx_evt_session_added_t
         */
        char* application_override;

        /**
         * The actual client IP address to pass in requests to the Vivox network.
         * \note This is only supported in the server SDK, and is otherwise ignored.
         */
        char* client_ip_override;

        /**
         * When set to 1, the buddy and watchers list is downloaded from the Vivox backend.
         * When set to 0, the application is responsible for setting buddies and watchers by using the appropriate requests.
         * The default value is 1.
         */
        int enable_presence_persistence;

        /**
         * The preferred account handle.
         * \attention This cannot match any existing handle (for example, account_handle or session_handle).
         * This is a string.
         * This must include at least one non-numeric character.
         * If this is empty, then a handle is automatically generated.
         */
        char* account_handle;

        /**
         * The username portion of the participant URI.
         * acct_name has the following restrictions:
         * - The name must start and end with a period (.)
         * - Only alpha-numeric, spaces, and the following characters are allowed: = + - _ . ! ~ ( )
         * - The length of acct_name is limited to a maximum of 63 bytes.
         * - Multiple adjacent spaces are not permitted.
         */
        char* acct_name;

        /**
         * A Vivox Access Token to authorize the operation.
         */
        char* access_token;

        /**
         * An initial list of buddy URIs.
         * This must be allocated by using vx_allocate().
         * This can be NULL.
         * If this is non-null, then the last item must be NULL.
         * \note V5 only. In V4, this is always equal to NULL.
         */
        char** initial_buddy_uris;

        /**
         * An initial list of blocked URIs.
         * This must be allocated by using vx_allocate().
         * This can be NULL.
         * If this is non-null, then the last item must be NULL.
         * \note V5 only. In V4, this is always equal to NULL.
         */
        char** initial_blocked_uris;

        /**
         * An initial list of blocked URIs for presence only.
         * This must be allocated by using vx_allocate().
         * This can be NULL.
         * If this is non-null, then the last item must be NULL.
         * \note V5 only. In V4, this always equal to NULL.
         */
        char** initial_blocked_uris_presence_only;

        /**
         * An initial list of allowed URIs.
         * This must be allocated by using vx_allocate().
         * This can be NULL.
         * If this is non-null, then the last item must be NULL.
         * \note V5 only. In V4, this is always equal to NULL.
         */
        char** initial_allowed_uris;

        /**
         * A comma-separated list of languages that the user prefers.
         * \note This is optional.
         * \attention Adding a list of languages might impact speech-to-text output for some users.
         * You can specify up to three languages in order of preference.
         * The default is NULL, which implies "en".
         * Languages are identified by tags specified in BCP-47.
         * Example inputs: "en", "en,zh"
         */
        char* languages;
    } vx_req_account_anonymous_login_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_anonymous_login object.
     * \ingroup login
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_anonymous_login_create(vx_req_account_anonymous_login_t** req);
#endif

    /**
     * Log a user out of the Vivox system.
     * \see vx_resp_account_logout
     * \ingroup login
     */
    typedef struct vx_req_account_logout {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * \deprecated This is deprecated and should not be used.
         * A generic string that is returned in the logout event.
         * Applications can use this to determine the reason for logout, if needed.
         * @deprecated
         */
        char* logout_reason;
    } vx_req_account_logout_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_logout object.
     * \ingroup login
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_logout_create(vx_req_account_logout_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Set some of the properties passed in on the login command.
     * \see vx_resp_account_set_login_properties
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_req_account_set_login_properties {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful login request.
         */
        VX_HANDLE account_handle;

        /**
         * Control how the SDK responds to incoming voice calls.
         * The default value is mode_verify_answer.
         */
        vx_session_answer_mode answer_mode;

        /**
         * An integer that specifies the maximum number of participant property events the SDK sends while in a channel.
         * If this is set, then the SDK attempts to generate an event at the given frequency, but does not generate two identical events in a row.
         * If this is not set, then the default is "on state change", which means that events are sent when the participant
         * starts talking, stops talking, is muted, or is unmuted.
         * The following list details valid values for this integer:
         * - 0 - Never
         * - 5 - 10 times per second
         * - 10 - 5 times per second
         * - 50 - 1 time per second
         * - 100 - On participant state change (this is the default)
         */
        int participant_property_frequency;
    } vx_req_account_set_login_properties_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * \deprecated This is deprecated and should not be used.
     * Allocate and initialize a vx_req_account_set_login_properties object.
     * \ingroup obsolete
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_set_login_properties_create(vx_req_account_set_login_properties_t** req);
#endif

    /**
     * The type of password hash algorithm to use when joining password-protected channels.
     */
    typedef enum {
        /**
         * The password is sent in cleartext.
         */
        password_hash_algorithm_cleartext = 0,

        /**
         * The password is sent as a SHA1 hash of the password and SIP URI of the user,
         * Base64-encoded, with any trailing '=' characters stripped off.
         */
        password_hash_algorithm_sha1_username_hash = 1
    } vx_password_hash_algorithm_t;

    /**
     * \deprecated This is deprecated and should not be used.
     * A session group is a container object that holds one or more sessions.
     * Session groups are used to support multi-channel mode.
     * A session group is local to an application and does not imply symmetrical association or view for other participants in individual channels.
     * If the client application needs to provide the ability for users to listen to multiple channels at the same time,
     * then the session group is used to add or remove channels (sessions).
     * An example of multi-channel use is an MMO with a hierarchical organizational structure, such as fleets, nested groups, or gangs.
     * As another example, a multi-channel mode can be used to provide one channel to talk to others located near a user,
     * and a second channel to bridge non-proximate participants from various regions in a virtual world.
     * A session group is also used to manage the channels in a session group.
     * There are cases where one channel might need to be the focus channel, and all other channels are in the background
     * (which makes the focus channel louder and the other channels quieter).
     * \note A session group handle is required to change these aspects within the session group.
     * If the session create command is used, a session group is automatically created.
     * \see vx_resp_sessiongroup_create\n
     * \ingroup sessiongroup
     * @deprecated
     */
    typedef struct vx_req_sessiongroup_create {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The session group type.
         * \see vx_sessiongroup_type
         */
        vx_sessiongroup_type type;

        /**
         * The number of seconds of audio to keep on the client.
         * This creates a feature similar to a DVR, but for audio.
         * For applications that need delayed playback, this is the number of seconds
         * of historical conversation that is kept (relative to now).
         * If loop mode is not needed, then set this to zero.
         * The default value is 0.
         */
        int loop_mode_duration_seconds;

        /**
         * \deprecated This field is ignored.
         * @deprecated
         */
        char* capture_device_id;
        /**
         * \deprecated This field is ignored.
         * @deprecated
         */
        char* render_device_id;

        /**
         * \deprecated This field is deprecated and should not be used.
         * @deprecated
         */
        char* alias_username;

        /**
         * The preferred session group handle.
         * \attention This cannot match any existing handle (for example, account_handle or session_handle).
         * This is a string.
         * This must include at least one non-numeric character.
         * If this is empty, then a handle is automatically generated.
         */
        char* sessiongroup_handle;
    } vx_req_sessiongroup_create_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * \deprecated This is deprecated and should not be used.
     * Allocate and initialize a vx_req_sessiongroup_create object.
     * \ingroup sessiongroup
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT int vx_req_sessiongroup_create_create(vx_req_sessiongroup_create_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Terminate a session group.
     * This also ends any established sessions within the session group.
     * \see vx_resp_sessiongroup_terminate
     * \ingroup sessiongroup
     * @deprecated
     */
    typedef struct vx_req_sessiongroup_terminate {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * \deprecated This field is ignored.
         * The handle returned from a successful vx_req_sessiongroup_create request.
         * @deprecated
         */
        VX_HANDLE sessiongroup_handle;
    } vx_req_sessiongroup_terminate_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_sessiongroup_terminate object.
     * \ingroup sessiongroup
     */
    VIVOXSDK_DLLEXPORT int vx_req_sessiongroup_terminate_create(vx_req_sessiongroup_terminate_t** req);
#endif

    /**
     * Sessions represent a connection to a media session with one or more participants.
     * Sessions can be connected to session audio, text chat, or both session audio and text chat.
     * \see vx_resp_sessiongroup_add_session
     * \ingroup sessiongroup
     */
    typedef struct vx_req_sessiongroup_add_session {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The preferred session group handle.
         * \attention This cannot match any existing handle (for example, account_handle or session_handle), but can be an existing sessiongroup_handle.
         * This is a string.
         * This must include at least one non-numeric character.
         * If this is empty, then a handle is automatically generated.
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The URI of the terminating point of the session (who or what is being called).
         * URIs must be valid, and URI length cannot exceed MAX_CHANNEL_URI_LENGTH.
         * Characters must use the following criteria:
         * - Valid alphanumeric characters: abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890
         * - Valid non-alphanumeric characters: -_.!~*'()&=+$,;?/
         * - Escape sequence: Percent (%) followed by two hex characters (0-9 or A-F),
         *   which represent the ASCII value of the character that is being encoded. For example:
         *   - 1) space - %20
         *   - 2) @     - %40
         *   - 3) :     - %3A
         */
        char* uri;

        /**
         * \deprecated This is deprecated and should not be used.
         * The display name of the entity being called (user or channel).
         * @deprecated
         */
        char* name;

        /**
         * \deprecated This is deprecated and should not be used.
         * The password that is used if the user is joining a password-protected channel.
         * @deprecated
         */
        char* password;

        /**
         * Determines whether the session will connect to session audio.
         * - 1 indicates that the session will connect to session audio.
         * - 0 indicates that the session will not connect to session audio.
         * The default value is 0.
         */
        int connect_audio;

        /**
         * \deprecated This is deprecated and should not be used.
         * Indicates the hashing algorithm used on the password that is passed in to the SDK.
         * This can be password_hash_algorithm_cleartext or password_hash_algorithm_sha1_username_hash.
         * - For password_hash_algorithm_cleartext, the password that is passed in is in cleartext.
         * - For password_hash_algorithm_sha1_username_hash, the password that is passed in is the SHA1 hash of the password
         *   and the SIP URI of the user, Base64-encoded, with any trailing '=' characters stripped off.
         * @deprecated
         */
        vx_password_hash_algorithm_t password_hash_algorithm;

        /**
         * \deprecated This is deprecated and should not be used.
         * The ID of the voice font to apply to the session.
         * You can obtain a list of available voice font IDs with vx_req_account_get_session_fonts.
         * Set to 0 for none.
         * @deprecated
         */
        int session_font_id;

        /**
         * Determine whether the session will connect to text chat.
         * - 1 indicates that the session will connect to text chat.
         * - 0 indicates that the session will not connect to text chat.
         * The default value is 0.
         */
        int connect_text;

        /**
         * The jitter buffer compensation for the SIP session.
         * This integer value represents the amount of compensation in milliseconds (ms)
         * to apply to counteract network jitter.
         * Valid values are 1-150 ms.
         * If this field is not initialized, or if it is set to 1,
         * then the SDK applies the default values for the given type of session.
         */
        int jitter_compensation;

        /**
         * The preferred session handle.
         * \attention This cannot match any existing handle (for example, account_handle or session_handle).
         * This is a string.
         * This must include at least one non-numeric character.
         * If this is empty, then a handle is automatically generated.
         */
        char* session_handle;

        /**
         * A Vivox Access Token that is used to authorize the operation.
         * For more information, see the Access Token Developer Guide.
         */
        char* access_token;

        /**
         * The account handle used in the vx_req_account_anonymous_login request.
         * A user must be logged in to create a session.
         * When a player logs out, all sessions are destroyed.
         * \note V5 only. This is ignored by V4.
         */
        VX_HANDLE account_handle;
    } vx_req_sessiongroup_add_session_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_sessiongroup_add_session object.
     * \ingroup sessiongroup
     */
    VIVOXSDK_DLLEXPORT int vx_req_sessiongroup_add_session_create(vx_req_sessiongroup_add_session_t** req);
#endif

    /**
     * End an established session (hang-up or disconnect).
     * \see vx_resp_sessiongroup_remove_session
     * \ingroup sessiongroup
     */
    typedef struct vx_req_sessiongroup_remove_session {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE sessiongroup_handle;
    } vx_req_sessiongroup_remove_session_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_sessiongroup_remove_session object.
     */
    VIVOXSDK_DLLEXPORT int vx_req_sessiongroup_remove_session_create(vx_req_sessiongroup_remove_session_t** req);
#endif

    /**
     * Set the audio focus of a session when there are multiple sessions in a session group.
     * The effect of this request is to bring the specific session within the group to the foreground.
     * The audible volume is relatively raised with respect to the channels that are not in focus.
     * To set all of the sessions to be equal (for example, to have no specific focus), make an Unset Focus request.
     * \see vx_resp_sessiongroup_set_focus
     * \ingroup sessiongroup
     */
    typedef struct vx_req_sessiongroup_set_focus {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * \deprecated This field is ignored.
         * The handle returned from a successful vx_req_sessiongroup_create request.
         * @deprecated
         */
        VX_HANDLE sessiongroup_handle;
    } vx_req_sessiongroup_set_focus_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_sessiongroup_set_focus object.
     * \ingroup sessiongroup
     */
    VIVOXSDK_DLLEXPORT int vx_req_sessiongroup_set_focus_create(vx_req_sessiongroup_set_focus_t** req);
#endif

    /**
     * Unset the focus of a specific channel that previously was set to have focus.
     * \see vx_resp_sessiongroup_unset_focus
     * \ingroup sessiongroup
     */
    typedef struct vx_req_sessiongroup_unset_focus {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * \deprecated This field is ignored.
         * The handle returned from a successful vx_req_sessiongroup_create request.
         * @deprecated
         */
        VX_HANDLE sessiongroup_handle;
    } vx_req_sessiongroup_unset_focus_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_sessiongroup_unset_focus object.
     * \ingroup sessiongroup
     */
    VIVOXSDK_DLLEXPORT int vx_req_sessiongroup_unset_focus_create(vx_req_sessiongroup_unset_focus_t** req);
#endif

    /**
     * Reset all sessions in a group so they have equal priority or focus.
     * \see vx_resp_sessiongroup_reset_focus
     * \ingroup sessiongroup
     */
    typedef struct vx_req_sessiongroup_reset_focus {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE sessiongroup_handle;
    } vx_req_sessiongroup_reset_focus_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_sessiongroup_reset_focus object.
     * \ingroup sessiongroup
     */
    VIVOXSDK_DLLEXPORT int vx_req_sessiongroup_reset_focus_create(vx_req_sessiongroup_reset_focus_t** req);
#endif

    /**
     * Set the session within the session group to which to user's voice is transmitted.
     * If the user is currently transmitting to all sessions, then using this command
     * forces transmission to only the specified session.
     * \see vx_resp_sessiongroup_set_tx_session
     * \ingroup sessiongroup
     */
    typedef struct vx_req_sessiongroup_set_tx_session {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * \deprecated This field is ignored.
         * The handle returned from a successful vx_req_sessiongroup_create request.
         * @deprecated
         */
        VX_HANDLE sessiongroup_handle;
    } vx_req_sessiongroup_set_tx_session_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_sessiongroup_set_tx_session object.
     * \ingroup sessiongroup
     */
    VIVOXSDK_DLLEXPORT int vx_req_sessiongroup_set_tx_session_create(vx_req_sessiongroup_set_tx_session_t** req);
#endif

    /**
     * Transmit the user's voice to all sessions within the specified session group.
     * \see vx_resp_sessiongroup_set_tx_all_sessions
     * \ingroup sessiongroup
     */
    typedef struct vx_req_sessiongroup_set_tx_all_sessions {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * \deprecated This field is ignored.
         * The handle returned from a successful vx_req_sessiongroup_create request.
         * @deprecated
         */
        VX_HANDLE sessiongroup_handle;
    } vx_req_sessiongroup_set_tx_all_sessions_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_sessiongroup_set_tx_all_sessions object.
     * \ingroup sessiongroup
     */
    VIVOXSDK_DLLEXPORT int vx_req_sessiongroup_set_tx_all_sessions_create(vx_req_sessiongroup_set_tx_all_sessions_t** req);
#endif

    /**
     * Disables transmission to all sessions within a session group.
     * \see vx_resp_sessiongroup_set_tx_no_session
     * \ingroup sessiongroup
     */
    typedef struct vx_req_sessiongroup_set_tx_no_session {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * \deprecated This field is ignored.
         * The handle returned from a successful vx_req_sessiongroup_create request.
         * @deprecated
         */
        VX_HANDLE sessiongroup_handle;
    } vx_req_sessiongroup_set_tx_no_session_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_sessiongroup_set_tx_no_session object.
     * \ingroup sessiongroup
     */
    VIVOXSDK_DLLEXPORT int vx_req_sessiongroup_set_tx_no_session_create(vx_req_sessiongroup_set_tx_no_session_t** req);
#endif

    /**
     * Set the position of any entire channel so all audio from that channel sounds like it comes from that position.
     * \see vx_resp_sessiongroup_set_session_3d_position
     * \ingroup sessiongroup
     */
    typedef struct vx_req_sessiongroup_set_session_3d_position {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * \deprecated This field is ignored.
         * The handle returned from a successful vx_req_sessiongroup_create request.
         * @deprecated
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The position of the virtual "mouth".
         * This is the position where the audio originates from for the user.
         * This 3-vector is a right-handed Cartesian coordinate, with the positive x-axis pointing towards the speaker's right,
         * the positive y-axis pointing up, and the positive z-axis pointing towards the speaker.
         */
        double speaker_position[3];  // {x, y, z}

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        double speaker_at_orientation[3];  // {x, y, z}
    } vx_req_sessiongroup_set_session_3d_position_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_sessiongroup_set_session_3d_position object.
     * \ingroup sessiongroup
     */
    VIVOXSDK_DLLEXPORT int vx_req_sessiongroup_set_session_3d_position_create(vx_req_sessiongroup_set_session_3d_position_t** req);
#endif

    /**
     * Start or stop session group audio injection.
     * \see vx_resp_sessiongroup_control_audio_injection
     * \ingroup adi
     */
    typedef struct vx_req_sessiongroup_control_audio_injection {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * Determine whether to start or stop audio injection.
         */
        vx_sessiongroup_audio_injection_control_type audio_injection_control_type;

        /**
         * \deprecated This field is ignored.
         * The handle returned from a successful vx_req_sessiongroup_create request.
         * @deprecated
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * The full pathname for the .wav file to use for audio injection.
         * The pathname must be single channel, 16-bit PCM, with the same sample rate as the negotiated audio codec.
         */
        char* filename;
    } vx_req_sessiongroup_control_audio_injection_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_sessiongroup_control_audio_injection object.
     * \ingroup adi
     */
    VIVOXSDK_DLLEXPORT int vx_req_sessiongroup_control_audio_injection_create(vx_req_sessiongroup_control_audio_injection_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Generate an outbound call to another user or channel.
     * Sessions typically represent a connection to a media session with one or more participants.
     * The specifics depend on the media types involved.
     * A session handle is required to control local user functions within the session
     * (or remote users, if the current account has the appropriate rights).
     * \note Creating a session automatically connects to the audio media, and you do not need to call Session.Connect.
     * This request can be used as a shortcut to creating a session group and then adding a session to the session group.
     * This request creates a new session group, creates a new session, and then returns the handles to both in the response.
     * @deprecated
     */
    typedef struct vx_req_session_create {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The display name of the entity being called (user or channel).
         */
        char* name;

        /**
         * The URI of the terminating point of the session (who or what is being called).
         * URIs must be valid.
         * Characters must use the following criteria:
         * - Valid alphanumeric characters: abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890
         * - Valid non-alphanumeric characters: -_.!~*'()&=+$,;?/
         * - Escape sequence: Percent (%) followed by two hex characters (0-9 or A-F),
         *   which represent the ASCII value of the character that is being encoded. For example:
         *   - 1) space - %20
         *   - 2) @     - %40
         *   - 3) :     - %3A
         */
        char* uri;

        /**
         * The password that is used if the user is joining a password-protected channel.
         */
        char* password;

        /**
         * Determine whether the session will join audio.
         * - 1 indicates that the session will join audio.
         * - 0 indicates that the session will not join audio.
         * The default value is 1.
         */
        int connect_audio;

        /**
         * \deprecated Replaced with connect_audio.
         * Determine whether the session will join audio.
         * - 1 indicates that audio will be joined.
         * - 0 indicates that audio will not be joined.
         * The default value is 1.
         * @deprecated
         */
        int join_audio;

        /**
         * \deprecated Replaced with connect_text. Text is now enabled at the account level and the default is to have text enabled.
         * Determine whether the session is going to join text.
         * - 1 indicates that text will be joined
         * - 0 indicates that text will not be joined.
         * The default value is 0.
         * @deprecated
         */
        int join_text;

        /**
         * Indicates the hashing algorithm used on the password that is passed in to the SDK.
         * This can be password_hash_algorithm_cleartext or password_hash_algorithm_sha1_username_hash.
         * - For password_hash_algorithm_cleartext, the password that is passed in is in cleartext.
         * - For password_hash_algorithm_sha1_username_hash, the password that is passed in is the SHA1 hash of the password
         *   and the SIP URI of the user, Base64-encoded, with any trailing '=' characters stripped off.
         */
        vx_password_hash_algorithm_t password_hash_algorithm;

        /**
         * Determine whether the session is going to join text.
         * - 1 indicates that text will be joined
         * - 0 indicates that text will not be joined.
         * The default value is 1.
         */
        int connect_text;

        /**
         * The ID of the voice font to apply to the session.
         * You can obtain a list of available voice font IDs with vx_req_account_get_session_fonts.
         * Set to 0 for none.
         */
        int session_font_id;

        /**
         * The jitter buffer compensation for the SIP session.
         * This integer value represents the amount of compensation in milliseconds (ms)
         * to apply to counteract network jitter.
         * Valid values are 1-150 ms.
         * If this field is not initialized, or if it is set to 1,
         * then the SDK applies the default values for the given type of session.
         */
        int jitter_compensation;

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        char* alias_username;

        /**
         * The preferred session group handle.
         * \attention This cannot match any existing handle (for example, account_handle or session_handle), but can be an existing sessiongroup_handle.
         * This is a string.
         * This must include at least one non-numeric character.
         * If this is empty, then a handle is automatically generated.
         */
        char* sessiongroup_handle;

        /**
         * The preferred session handle.
         * \attention This cannot match any existing handle (for example, account_handle or session_handle).
         * This is a string.
         * This must include at least one non-numeric character.
         * If this is empty, then a handle is automatically generated.
         */
        char* session_handle;

        /**
         * A Vivox Access Token to authorize the operation.
         */
        char* access_token;
    } vx_req_session_create_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * \deprecated This is deprecated and should not be used.
     * Allocate and initialize a vx_req_session_create object.
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_create_create(vx_req_session_create_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Connect media (audio) in a session
     * \note To use this request, a session must have already been created.
     * This can also be used to make an outbound call or to answer an inbound call.
     * For inbound sessions (based on event status), this request is used to answer a call for audio only
     * (text sessions do not need to be explicitly answered).
     * \see vx_resp_session_media_connect
     * \ingroup session
     * @deprecated
     */
    typedef struct vx_req_session_media_connect {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * \deprecated Do not use. This structure member is ignored.
         * @deprecated
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * Returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * The ID of the voice font to apply to the session.
         * You can obtain a list of available voice font IDs with vx_req_account_get_session_fonts.
         * Set to 0 for none.
         */
        int session_font_id;

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        vx_media_type media;

        /**
         * \deprecated Use vx_req_aux_set_capture_device to set the capture device instead.
         * The device ID of the capture device to use.
         * Use NULL or empty to use the last selected capture device.
         * @deprecated
         */
        char* capture_device_id;

        /**
         * \deprecated Use vx_req_aux_set_render_device to set the capture device instead.
         * The device ID of the render device to use.
         * Use NULL or empty to use the last selected render device.
         * @deprecated
         */
        char* render_device_id;

        /**
         * The jitter buffer compensation for the SIP session.
         * This integer value represents the amount of compensation in milliseconds (ms)
         * to apply to counteract network jitter.
         * Valid values are 1-150 ms.
         * If this field is not initialized, or if it is set to 1,
         * then the SDK applies the default values for the given type of session.
         */
        int jitter_compensation;

        /**
         * The number of seconds of audio to keep on the client.
         * This creates a feature similar to a DVR, but for audio.
         * For applications that need delayed playback, this is the number of seconds
         * of historical conversation that is kept (relative to now).
         * If loop mode is not needed, then set this to zero.
         * The default value is 0.
         */
        int loop_mode_duration_seconds;
    } vx_req_session_media_connect_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_session_media_connect object.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_media_connect_create(vx_req_session_media_connect_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Disconnect the media (audio) in the session.
     * \note To use this request, a session must have already been created and connected.
     * This can also be used to hang up a call that the user is in, or to refuse an incoming call.
     * \see vx_resp_session_media_disconnect
     * \ingroup session
     * @deprecated
     */
    typedef struct vx_req_session_media_disconnect {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * \deprecated Do not use. This structure member is ignored.
         * @deprecated
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * Returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        vx_media_type media;

        /**
         * The termination status of the request.
         */
        vx_termination_status termination_status;
    } vx_req_session_media_disconnect_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_session_media_disconnect object.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_media_disconnect_create(vx_req_session_media_disconnect_t** req);
#endif

    /**
     * Add text to a session.
     * \note To use this request, a session must have already been created.
     * \see vx_resp_session_text_connect
     * \ingroup session
     */
    typedef struct vx_req_session_text_connect {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * \deprecated Do not use. This structure member is ignored.
         * @deprecated
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * Returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;
    } vx_req_session_text_connect_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_session_text_connect object.
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_text_connect_create(vx_req_session_text_connect_t** req);
#endif

    /**
     * Disconnect text in a session.
     * \note To use this request, a session must have already been created and connected.
     * \see vx_req_session_text_disconnect
     * \ingroup session
     */
    typedef struct vx_req_session_text_disconnect {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * \deprecated Do not use. This structure member is ignored.
         * @deprecated
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * Returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;
    } vx_req_session_text_disconnect_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_session_text_disconnect object.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_text_disconnect_create(vx_req_session_text_disconnect_t** req);
#endif

    /**
     * End an established session (hang-up or disconnect).
     * \see vx_req_session_terminate
     * \ingroup session
     */
    typedef struct vx_req_session_terminate {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * Returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;
    } vx_req_session_terminate_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_session_terminate object.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_terminate_create(vx_req_session_terminate_t** req);
#endif

    /**
     * Mute or unmute the audio render or the incoming text messages
     * of the logged in user for the specified session.
     * \see vx_req_session_mute_local_speaker
     * \ingroup session
     */
    typedef struct vx_req_session_mute_local_speaker {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         * \see vx_resp_sessiongroup_add_session.
         */
        VX_HANDLE session_handle;

        /**
         * Specify mute or unmute for the media described in vx_mute_scope.
         * - 1 to mute
         * - 0 to unmute
         */
        int mute_level;

        /**
         * Specify the media that is affected by this request: audio, text, or both audio and text.
         */
        vx_mute_scope scope;
    } vx_req_session_mute_local_speaker_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_session_mute_local_speaker object.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_mute_local_speaker_create(vx_req_session_mute_local_speaker_t** req);
#endif

    /**
     * Set the audio render volume for the specified session.
     * \see vx_resp_session_set_local_render_volume
     * \ingroup session
     */
    typedef struct vx_req_session_set_local_render_volume {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * The level of the audio.
         * This is a non-negative integer value between 0 and 100 (inclusive).
         * The default value is 50.
         */
        int volume;
    } vx_req_session_set_local_render_volume_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_session_set_local_render_volume object.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_set_local_render_volume_create(vx_req_session_set_local_render_volume_t** req);
#endif

    /**
     * \deprecated Use vx_req_aux_set_speaker_level_t instead.
     * Set the speaker volume for the specified session.
     * \see vx_resp_session_set_local_speaker_volume
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_req_session_set_local_speaker_volume {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * The level of the audio.
         * This is a non-negative integer value between 0 and 100 (inclusive).
         * The default value is 50.
         */
        int volume;
    } vx_req_session_set_local_speaker_volume_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * \deprecated This is deprecated and should not be used.
     * Allocate and initialize a vx_req_session_set_local_speaker_volume object.
     * \ingroup obsolete
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_set_local_speaker_volume_create(vx_req_session_set_local_speaker_volume_t** req);
#endif

    /**
     * This command sends an invitation to a specified user to join the channel that corresponds to the provided session handle.
     * The user who sends the invite does not receive any feedback after the invite call is made, and does not know if the other user
     * received the invitation, if they are online, or if they rejected or ignored the invitation.
     * The user who sends the invitation can only determine whether an invitation was accepted
     * if they see the user who received the invitation enter the channel.
     * Sending an invite to a user is not the same as making a P2P call,
     * because you do not get the events that you would receive when a P2P call is made.
     * Invites work well for inviting PSTN callers into a channel.
     * \see vx_resp_session_channel_invite_user
     * \ingroup
     */
    typedef struct vx_req_session_channel_invite_user {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;
        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;
        /**
         * The SIP URI of the participant to invite.
         */
        char* participant_uri;
    } vx_req_session_channel_invite_user_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Create a vx_req_session_channel_invite_user_t request.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_channel_invite_user_create(vx_req_session_channel_invite_user_t** req);
#endif

    /**
     * Set the volume for a participant in the current session.
     * This only affects the audio that is heard locally, and does not change
     * the audio that is heard by any of the other participants.
     * These changes are only valid for the current session; if the participant with the audio that is set
     * leaves the session and rejoins, then the settings are lost.
     * \see vx_resp_session_set_participant_volume_for_me
     * \ingroup session
     */
    typedef struct vx_req_session_set_participant_volume_for_me {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * The fully specified URI of the participant.
         */
        char* participant_uri;

        /**
         * The volume level that has been set by the user, which should not often change.
         * This is a non-negative integer value between 0 and 100 (inclusive).
         * The default value is 50.
         */
        int volume;
    } vx_req_session_set_participant_volume_for_me_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_session_set_participant_volume_for_me object.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_set_participant_volume_for_me_create(vx_req_session_set_participant_volume_for_me_t** req);
#endif

    /**
     * Mute a participant in the current session.
     * This only affects the audio that is heard locally, and does not change
     * the audio that is heard by any of the other participants.
     * These changes are only valid for the current session; if the participant with the audio that is set
     * leaves the session and rejoins, then the settings are lost.
     * \note This command only applies to channels (3D and static), and is not applicable for person-to-person calls.
     * \see vx_resp_session_set_participant_mute_for_me
     * \ingroup session
     */
    typedef struct vx_req_session_set_participant_mute_for_me {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * The fully specified URI of the participant.
         */
        char* participant_uri;

        /**
         * Indicate whether to mute or unmute the specified participant.
         * - 1 to mute
         * - 0 to unmute
         * The default value is 0.
         */
        int mute;

        /**
         * The scope of the mute command.
         * The default setting is mute_scope_all.
         */
        vx_mute_scope scope;
    } vx_req_session_set_participant_mute_for_me_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_session_set_participant_mute_for_me object.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_set_participant_mute_for_me_create(vx_req_session_set_participant_mute_for_me_t** req);
#endif

    /**
     * Control whether the SDK returns a response for potential high volume requests,
     * specifically, a vx_req_session_set_3d_position_t request.
     */
    typedef enum {
        /**
         * Return a response to the application.
         */
        req_disposition_reply_required,

        /**
         * Do not return a response to the application.
         */
        req_disposition_no_reply_required
    } req_disposition_type_t;

    /**
     * Set and get the 3D position of the speaker and listener.
     * For most applications, it is expected that the speaker and listener positions are the same.
     * The SDK also supports the decoupling of these positions (for example, for the implementation of a camera audio zoom,
     * the virtual "mouth" is where the avatar is, and the virtual "ears" are where the camera view is).
     * \see vx_req_session_set_3d_position
     * \ingroup session
     */
    typedef struct vx_req_session_set_3d_position {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * The position of the virtual "mouth".
         * This 3-vector is a right-handed Cartesian coordinate, with the positive x-axis pointing towards the speaker's right,
         * the positive y-axis pointing up, and the positive z-axis pointing towards the speaker.
         */
        double speaker_position[3];  // {x, y, z}

        /**
         * The velocity of the virtual "mouth".
         * This 3-vector is a right-handed Cartesian coordinate, with the positive x-axis pointing towards the speaker's right,
         * the positive y-axis pointing up, and the positive z-axis pointing towards the speaker.
         */
        double speaker_velocity[3];  // {x, y, z}

        /**
         * This 3-vector is a unit or "direction" vector, which represents the direction or heading of the speaker.
         * The default value is [0 0 -1] (heading "forward" or "north").
         */
        double speaker_at_orientation[3];  // {x, y, z}

        /**
         * This 3-vector is a unit or "direction" vector, which represents the "up" direction of the speaker.
         * The default value is [0 1 0].
         */
        double speaker_up_orientation[3];  // {x, y, z}

        /**
         * This 3-vector is a unit or "direction" vector, which represents the "left" direction of the speaker.
         * The default value is [-1 0 0].
         */
        double speaker_left_orientation[3];  // {x, y, z}

        /**
         * The position of the virtual "ear".
         * This 3-vector is a right-handed Cartesian coordinate, with the positive x-axis pointing towards the speaker's right,
         * the positive y-axis pointing up, and the positive z-axis pointing towards the speaker.
         */
        double listener_position[3];  // {x, y, z}

        /**
         * The velocity of the virtual "ear".
         * This 3-vector is a right-handed Cartesian coordinate, with the positive x-axis pointing towards the speaker's right,
         * the positive y-axis pointing up, and the positive z-axis pointing towards the speaker.
         */
        double listener_velocity[3];  // {x, y, z}

        /**
         * This 3-vector is a unit or "direction" vector, which represents the direction or "heading" of the listener.
         * The default value is [0 0 -1] (heading "forward" or "north").
         */
        double listener_at_orientation[3];  // {x, y, z}

        /**
         * This 3-vector is a unit or "direction" vector, which represents the "up" direction of the listener.
         * The default value is [0 1 0].
         */
        double listener_up_orientation[3];  // {x, y, z}

        /**
         * This 3-vector is a unit or "direction" vector, which represents the "left" direction of the listener.
         * The default value is [-1 0 0].
         */
        double listener_left_orientation[3];  // {x, y, z}

        /**
         * RESERVED FOR FUTURE USE
         * An enum type.
         * The default value is 'orientation_default = 0'.
         */
        orientation_type type;

        /**
         * Control whether a response is sent back to the application for this request.
         */
        req_disposition_type_t req_disposition_type;
    } vx_req_session_set_3d_position_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_session_set_3d_position object.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_set_3d_position_create(vx_req_session_set_3d_position_t** req);
#endif

    /**
     * Apply a voice font to an already established voice session.
     * \see vx_resp_session_set_voice_font
     * \ingroup session
     */
    typedef struct vx_req_session_set_voice_font {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * The ID of the voice font to apply to the session.
         * You can obtain a list of available voice font IDs with vx_req_account_get_session_fonts.
         * Set to 0 for none.
         * The default value is 0.
         */
        int session_font_id;
    } vx_req_session_set_voice_font_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_session_set_voice_font object.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_set_voice_font_create(vx_req_session_set_voice_font_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Change ownership of a channel to a specified account.
     * \note This can only be performed by the current owner of the channel.
     * After the ownership change, the original owner remains a moderator of the channel.
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_req_account_channel_change_owner {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The channel that ownership is changing for.
         */
        char* channel_uri;

        /**
         * The URI of the target owner of the specified channel.
         */
        char* new_owner_uri;
    } vx_req_account_channel_change_owner_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * \deprecated This is deprecated and should not be used.
     * Allocate and initialize a vx_req_account_channel_change_owner object.
     * \ingroup obsolete
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_channel_change_owner_create(vx_req_account_channel_change_owner_t** req);
#endif

    /**
     * Send specified data directly to a user.
     * \see vx_evt_user_app_data
     */
    typedef struct vx_req_account_send_user_app_data {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The URI of the account to send the data to.
         */
        char* to_uri;

        /**
         * The type of the data being sent.
         * \note Multipart MIME types are not supported (for example, multipart/digest).
         */
        char* content_type;

        /**
         * The content of the message that is being sent.
         */
        char* content;
    } vx_req_account_send_user_app_data_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_send_user_app_data object.
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_send_user_app_data_create(vx_req_account_send_user_app_data_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Add accounts that are allowed to participate in the channel (access control list).
     * \see vx_resp_account_channel_add_acl
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_req_account_channel_add_acl {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The channel URI.
         */
        char* channel_uri;

        /**
         * The fully specified URI of the user being added to the channel access control list.
         */
        char* acl_uri;
    } vx_req_account_channel_add_acl_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * \deprecated This is deprecated and should not be used.
     * Allocate and initialize a vx_req_account_channel_add_acl object.
     * \ingroup obsolete
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_channel_add_acl_create(vx_req_account_channel_add_acl_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Remove an access control list entry from a channel.
     * \see vx_resp_account_channel_remove_acl
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_req_account_channel_remove_acl {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The channel URI.
         */
        char* channel_uri;

        /**
         * The fully specified URI of the user being removed from the channel access control list.
         */
        char* acl_uri;
    } vx_req_account_channel_remove_acl_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * \deprecated This is deprecated and should not be used.
     * Allocate and initialize a vx_req_account_channel_remove_acl object.
     * \ingroup obsolete
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_channel_remove_acl_create(vx_req_account_channel_remove_acl_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Retrieve the access control list for the specified channel.
     * \see vx_resp_account_channel_get_acl
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_req_account_channel_get_acl {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The channel URI.
         */
        char* channel_uri;
    } vx_req_account_channel_get_acl_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * \deprecated This is deprecated and should not be used.
     * Allocate and initialize a vx_req_account_channel_get_acl object.
     * \ingroup obsolete
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_channel_get_acl_create(vx_req_account_channel_get_acl_t** req);
#endif

    /**
     * Mute or unmute a participant in a specific channel.
     * This request mutes or unmutes the user for all users in the channel.
     * \note This request is only valid if the account making the request has moderator privileges on the target channel.
     * \see vx_resp_channel_mute_user
     * \ingroup channel
     */
    typedef struct vx_req_channel_mute_user {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * \deprecated This field is ignored.
         * The name of the channel.
         * @deprecated
         */
        char* channel_name;

        /**
         * The URI of the channel where the muting occurs.
         */
        char* channel_uri;

        /**
         * The URI of the participant to mute or unmute.
         */
        char* participant_uri;

        /**
         * Set to 1 to mute the user.
         * Set to 0 to unmute the user.
         * The default value is 0.
         */
        int set_muted;

        /**
         * The scope of the mute command.
         * The default setting is mute_scope_all.
         */
        vx_mute_scope scope;

        /**
         * A Vivox Access Token to authorize the operation.
         */
        char* access_token;
    } vx_req_channel_mute_user_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_channel_mute_user object.
     * \ingroup channel
     */
    VIVOXSDK_DLLEXPORT int vx_req_channel_mute_user_create(vx_req_channel_mute_user_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Ban a user from joining a channel, or un-ban a user if they have already been banned.
     * This kicks the user out from the channel and bans the user from rejoining the channel.
     * \note This request is only valid if the account that makes the request has moderator privileges on the target channel.
     * \see vx_resp_channel_ban_user
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_req_channel_ban_user {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * \deprecated This field is ignored.
         * The name of the channel.
         * @deprecated
         */
        char* channel_name;

        /**
         * The URI of the channel.
         */
        char* channel_uri;

        /**
         * The URI of the participant to ban or unban.
         */
        char* participant_uri;

        /**
         * Set to 1 to ban the user.
         * Set to 0 to unban the user.
         */
        int set_banned;
    } vx_req_channel_ban_user_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * \deprecated This is deprecated and should not be used.
     * Allocate and initialize a vx_req_channel_ban_user object.
     * \ingroup obsolete
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT int vx_req_channel_ban_user_create(vx_req_channel_ban_user_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Return a list of users who are banned from the specified channel.
     * \see vx_resp_channel_get_banned_users
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_req_channel_get_banned_users {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The channel URI.
         */
        char* channel_uri;
    } vx_req_channel_get_banned_users_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * \deprecated This is deprecated and should not be used.
     * Allocate and initialize a vx_req_channel_get_banned_users object.
     * \ingroup obsolete
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT int vx_req_channel_get_banned_users_create(vx_req_channel_get_banned_users_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Kick a user out of a channel and automatically allow the user back in after 60 seconds.
     * \see vx_resp_channel_kick_user
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_req_channel_kick_user {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * \deprecated This field is ignored.
         * The name of the channel.
         * @deprecated
         */
        char* channel_name;

        /**
         * The URI of the channel.
         */
        char* channel_uri;

        /**
         * The participant URI.
         */
        char* participant_uri;

        /**
         * A Vivox Access Token to authorize the operation.
         */
        char* access_token;
    } vx_req_channel_kick_user_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * \deprecated This is deprecated and should not be used.
     * Allocate and initialize a vx_req_channel_kick_user object.
     * \ingroup obsolete
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT int vx_req_channel_kick_user_create(vx_req_channel_kick_user_t** req);
#endif

    /**
     * Mute or unmute all current users in a channel.
     * \note New users who join the channel are not muted.
     * \see vx_resp_channel_mute_all_users
     * \ingroup channel
     */
    typedef struct vx_req_channel_mute_all_users {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * \deprecated This field is ignored.
         * The name of the channel.
         * @deprecated
         */
        char* channel_name;

        /**
         * The URI of the channel.
         */
        char* channel_uri;

        /**
         * Set to 1 to mute.
         * Set to 0 to unmute.
         * The default value is 0.
         */
        int set_muted;

        /**
         * The scope of the mute command.
         * The default setting is mute_scope_all.
         */
        vx_mute_scope scope;

        /**
         * A Vivox Access Token to authorize the operation.
         */
        char* access_token;
    } vx_req_channel_mute_all_users_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_channel_mute_all_users object.
     * \ingroup channel
     */
    VIVOXSDK_DLLEXPORT int vx_req_channel_mute_all_users_create(vx_req_channel_mute_all_users_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Set the lock mode of a channel.
     * When a channel is locked, no additional participants can join the channel.
     * This command can also unlock the channel.
     * \note The user who issues this request must have moderator privileges.
     * A channel becomes unlocked when all participants have left the channel.
     * \see vx_resp_channel_set_lock_mode
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_req_channel_set_lock_mode
    {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The URI of the channel to set the lock status on.
         */
        char* channel_uri;

        /**
         * The channel lock mode.
         */
        vx_channel_lock_mode lock_mode;
    } vx_req_channel_set_lock_mode_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * \deprecated This is deprecated and should not be used.
     * Allocate and initialize a vx_req_channel_set_lock_mode object.
     * \ingroup obsolete
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT int vx_req_channel_set_lock_mode_create(vx_req_channel_set_lock_mode_t** req);
#endif

    /**
     * Mute or unmute the microphone.
     * \see vx_resp_connector_mute_local_mic
     * \ingroup devices
     */
    typedef struct vx_req_connector_mute_local_mic {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_connector_create request.
         */
        VX_HANDLE connector_handle;

        /**
         * - Set to 1 to mute.
         * - Set to 0 to unmute.
         */
        int mute_level;
        /**
         * An optional parameter that specifies the account handle of the user whose microphone will be muted or unmuted.
         * This must either be unset or the account_handle passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If this is unset, then the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_connector_mute_local_mic_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_connector_mute_local_mic object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_connector_mute_local_mic_create(vx_req_connector_mute_local_mic_t** req);
#endif

    /**
     * Mute or unmute the speaker (the render device of incoming audio).
     * \note This setting applies universally to all connected audio sessions.
     * \see vx_resp_connector_mute_local_speaker
     * \ingroup devices
     */
    typedef struct vx_req_connector_mute_local_speaker {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_connector_create request.
         */
        VX_HANDLE connector_handle;

        /**
         * - Set to 1 to mute.
         * - Set to 0 to unmute.
         */
        int mute_level;
        /**
         * An optional parameter that specifies the account handle of the user whose speaker will be muted or unmuted.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If this is unset, then the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_connector_mute_local_speaker_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_connector_mute_local_speaker object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_connector_mute_local_speaker_create(vx_req_connector_mute_local_speaker_t** req);
#endif

    /**
     * \deprecated Use vx_req_aux_set_mic_level_t instead.
     * Set the microphone volume.
     * Raising or lowering the boost applies to the speaking volume that is heard by others.
     * \note The setting applies to all connected audio sessions.
     * \see vx_resp_connector_set_local_mic_volume
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_req_connector_set_local_mic_volume {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * \deprecated This parameter is ignored.
         * The handle returned from a successful vx_req_connector_create request.
         * @deprecated
         */
        VX_HANDLE connector_handle;

        /**
         * The level of the audio.
         * This is a non-negative integer value between 0 and 100 (inclusive).
         * The default value is 50.
         */
        int volume;
        /**
         * An optional parameter that specifies the account handle of the user whose microphone volume will be set.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_connector_set_local_mic_volume_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * \deprecated This is deprecated and should not be used.
     * Allocate and initialize a vx_req_connector_set_local_mic_volume object.
     * \ingroup obsolete
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT int vx_req_connector_set_local_mic_volume_create(vx_req_connector_set_local_mic_volume_t** req);
#endif

    /**
     * \deprecated Use vx_req_aux_set_speaker_level_t instead.
     * Set the speaker volume.
     * This setting provides a relative volume that applies to all connected audio sessions.
     * \see vx_resp_connector_set_local_speaker_volume
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_req_connector_set_local_speaker_volume {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * \deprecated This parameter is ignored.
         * The handle returned from a successful vx_req_connector_create request.
         * @deprecated
         */
        VX_HANDLE connector_handle;

        /**
         * The level of the audio.
         * This is a non-negative integer value between 0 and 100 (inclusive).
         * The default value is 50.
         */
        int volume;
        /**
         * An optional parameter that specifies the account handle of the user whose speaker volume will be set.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_connector_set_local_speaker_volume_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * \deprecated This is deprecated and should not be used.
     * Allocate and initialize a vx_req_connector_set_local_speaker_volume object.
     * \ingroup obsolete
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT int vx_req_connector_set_local_speaker_volume_create(vx_req_connector_set_local_speaker_volume_t** req);
#endif

    /**
     * Retrieve the current volume and mute status of the local render and capture devices.
     * \see vx_resp_connector_get_local_audio_info
     * \ingroup devices
     */
    typedef struct vx_req_connector_get_local_audio_info {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * \deprecated This parameter is ignored.
         * The handle returned from a successful vx_req_connector_create request.
         * @deprecated
         */
        VX_HANDLE connector_handle;
        /**
         * An optional parameter that specifies the account handle of the user whose local audio information will be retrieved.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_connector_get_local_audio_info_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_connector_get_local_audio_info object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_connector_get_local_audio_info_create(vx_req_connector_get_local_audio_info_t** req);
#endif

    /**
     * Add a buddy to a buddy list or update the properties of a buddy.
     * The buddy is added to the account implied by the account_handle provided in the call.
     * All relevant data about a buddy must be supplied when updating the buddy.
     * If a display name is not specified when updating a the data field, the display name will be blank.
     * \see vx_resp_account_buddy_set
     * \see vx_evt_subscription_t
     * \ingroup buddies
     */
    typedef struct vx_req_account_buddy_set {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The identifier of the buddy to add to the list.
         */
        char* buddy_uri;

        /**
         * A readable name for display only.
         * \note This is not required.
         */
        char* display_name;

        /**
         * A place to store extra data about a buddy.
         * \note This is not required.
         */
        char* buddy_data;

        /**
         * The ID of the group to add the buddy to.
         * To remove the buddy from a group, set this to 0.
         */
        int group_id;

        /**
         * \attention This is not currently implemented.
         * A personalized message that the user sees if they receive a vx_evt_subscription_t event.
         * \note This is optional.
         * This is limited to a maximum of 256 characters.
         */
        char* message;
    } vx_req_account_buddy_set_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_buddy_set object.
     * \ingroup buddies
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_buddy_set_create(vx_req_account_buddy_set_t** req);
#endif

    /**
     * Delete a buddy from a user's buddy list.
     * \see vx_resp_account_buddy_delete
     * \ingroup buddies
     */
    typedef struct vx_req_account_buddy_delete {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The identifier of the buddy to remove from the user's buddy list.
         */
        char* buddy_uri;
    } vx_req_account_buddy_delete_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_buddy_delete object.
     * \ingroup buddies
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_buddy_delete_create(vx_req_account_buddy_delete_t** req);
#endif

    /**
     * Retrieve a list of all buddies and buddy groups for a given account.
     */
    typedef struct vx_req_account_list_buddies_and_groups {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * When set to 1, this interrogates the server for the list of buddies.
         * The default value is 0.
         * \note V5 only. This is ignored by V4.
         */
        int refresh;
    } vx_req_account_list_buddies_and_groups_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_list_buddies_and_groups object.
     * \ingroup buddies
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_list_buddies_and_groups_create(vx_req_account_list_buddies_and_groups_t** req);
#endif

    /**
     * Send a message to all participants in the session.
     * \see vx_resp_session_send_message
     * \ingroup session
     */
    typedef struct vx_req_session_send_message {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * The HTTP content type of the message.
         * If an empty string is passed in, this field defaults to "text/plain".
         * \note This field will be validated, so it must use a valid format. See the IETF documentation on RFC 2046.
         */
        char* message_header;

        /**
         * The contents of the message.
         * \note The message body cannot exceed the length specified by the server in its pre-login configuration.
         * The default maximum message length is 320 bytes (320 characters in UTF-8 encoding).
         */
        char* message_body;

        /**
         * The language.
         * The default setting is NULL, which implies "en".
         * \note V5 only. This is ignored by V4.
         */
        char* language;

        /**
         * A custom application stanza namespace.
         * This is optional.
         * The default setting is NULL.
         * \note V5 only. This is ignored by V4.
         */
        char* application_stanza_namespace;

        /**
         * A custom application stanza body.
         * This is optional.
         * The default setting is NULL.
         * \note V5 only. This is ignored by V4.
         */
        char* application_stanza_body;
    } vx_req_session_send_message_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_session_send_message object.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_send_message_create(vx_req_session_send_message_t** req);
#endif


#ifndef DOXYGEN_MAM_SKIP
    /**
     * Query messages that were archived by the server for the specified channel.
     * This includes all messages that are sent and received by using vx_req_session_send_message.
     * This does not include any message that is sent or received by using vx_req_account_send_message.
     * Messages can appear in the archive with a delay of up to several seconds after being sent or received.
     * To query P2P message history, use vx_req_account_archive_query.
     * \see vx_resp_session_archive_query
     * \ingroup session
     * \note V5 only.
     */
    typedef struct vx_req_session_archive_query {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * Exclude all messages before a specified date or time from the query results.
         * Specify the start time by using a format defined in XEP-0082.
         * This is optional.
         * The default setting is NULL.
         */
        char* time_start;

        /**
         * Exclude all messages after a specified date or time from the query results.
         * Specify the end time by using a format defined in XEP-0082.
         * This is optional.
         * The default setting is NULL.
         */
        char* time_end;

        /**
         * The text to find in the query.
         * Only messages that contain the specified text are returned.
         * This is optional.
         * The default setting is NULL.
         */
        char* search_text;

        /**
         * The fully specified URI of the participant.
         * Only messages to or from the specified participant are returned.
         * This is optional.
         * The default setting is NULL.
         */
        char* participant_uri;

        /**
         * The maximum number of messages to find in the query.
         * This is optional.
         * The default value is 10.
         * Set to 0 to get the total message count without retrieving the messages.
         */
        unsigned int max;

        /**
         * The message_id for paging backward through large query result sets.
         * The query results include messages that immediately precede the specified message in the result set.
         * \note This parameter cannot be used simultaneously with parameter after_id.
         * This is optional.
         * The default setting is NULL.
         */
        char* before_id;

        /**
         * The message_id for paging forward through large query result sets.
         * The query results include messages that immediately follow the specified message in the result set.
         * \note This parameter cannot be used simultaneously with parameter before_id.
         * This is optional.
         * The default setting is NULL.
         */
        char* after_id;

        /**
         * The index of the first message to retrieve from the query.
         * This is optional.
         * The default value is -1, which indicates to not use this parameter.
         * The first message in the result set always has an index of 0.
         */
        int first_message_index;

        /**
         * A custom application stanza namespace.
         * This is optional.
         * The default setting is NULL.
         */
        char* application_stanza_namespace;

        /**
         * A custom application stanza body.
         * This is optional.
         * The default setting is NULL.
         */
        char* application_stanza_body;
    } vx_req_session_archive_query_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_session_archive_query object.
     * \note V5 only.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_archive_query_create(vx_req_session_archive_query_t** req);
#endif
#endif

    /**
     * Query messages that were archived by the server for the specified channel.
     * This includes all messages that are sent and received by using vx_req_session_send_message.
     * This does not include any message that is sent or received by using vx_req_account_send_message.
     * Messages can appear in the archive with a delay of up to several seconds after being sent or received.
     * To query P2P message history, use vx_req_account_chat_history_query.
     * \see vx_resp_session_chat_history_query
     * \ingroup session
     * \note V5 only.
     */
    typedef struct vx_req_session_chat_history_query {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * Exclude all messages before a specified date or time from the query results.
         * Specify the start time by using a format defined in XEP-0082.
         * This is optional.
         * The default setting is NULL.
         */
        char* time_start;

        /**
         * Exclude all messages after a specified date or time from the query results.
         * Specify the end time by using a format defined in XEP-0082.
         * This is optional.
         * The default setting is NULL.
         */
        char* time_end;

        /**
         * Used to paginate through collections of data by setting the cursor parameter to a next_cursor attribute returned by a previous request's.
         */
        char* cursor;

        /**
         * The text to find in the query.
         * Only messages that contain the specified text are returned.
         * This is optional.
         * The default setting is NULL.
         */
        char* search_text;

        /**
         * The fully specified URI of the participant.
         * Only messages to or from the specified participant are returned.
         * This is optional.
         * The default setting is NULL.
         */
        char* participant_uri;

        /**
         * The maximum number of messages to find in the query.
         * This is optional.
         * The default value is 10.
         * Set to 0 to get the total message count without retrieving the messages.
         */
        unsigned int max;

        /**
         * The message_id for paging backward through large query result sets.
         * The query results include messages that immediately precede the specified message in the result set.
         * \note This parameter cannot be used simultaneously with parameter after_id.
         * This is optional.
         * The default setting is NULL.
         */
        char* before_id;

        /**
         * The message_id for paging forward through large query result sets.
         * The query results include messages that immediately follow the specified message in the result set.
         * \note This parameter cannot be used simultaneously with parameter before_id.
         * This is optional.
         * The default setting is NULL.
         */
        char* after_id;

        /**
         * The index of the first message to retrieve from the query.
         * This is optional.
         * The default value is -1, which indicates to not use this parameter.
         * The first message in the result set always has an index of 0.
         */
        int first_message_index;

        /**
         * A custom application stanza namespace.
         * This is optional.
         * The default setting is NULL.
         */
        char* application_stanza_namespace;

        /**
         * A custom application stanza body.
         * This is optional.
         * The default setting is NULL.
         */
        char* application_stanza_body;
    } vx_req_session_chat_history_query_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_session_chat_history_query object.
     * \note V5 only.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_chat_history_query_create(vx_req_session_chat_history_query_t** req);
#endif

    /**
     * Set the presence (online/offline status) of an account.
     * \see vx_resp_account_set_presence
     * \ingroup buddies
     */
    typedef struct vx_req_account_set_presence {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

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
         * A custom message string for when presence is set.
         */
        char* custom_message;

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        char* alias_username;
    } vx_req_account_set_presence_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_set_presence object.
     * \ingroup buddies
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_set_presence_create(vx_req_account_set_presence_t** req);
#endif

    /**
     * Respond to an incoming subscription event.
     * For example, a request from another user to put a user on their buddy list.
     * \see vx_resp_account_send_subscription_reply
     * \ingroup buddies
     */
    typedef struct vx_req_account_send_subscription_reply {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The presence rule type.
         * The following list details possible values:
         * - rule_allow
         * - rule_block
         * - rule_hide
         */
        vx_rule_type rule_type;

        /**
         * Determine whether the buddy will automatically be added to the account's buddy list (1 or 0).
         * The default value is 0.
         */
        int auto_accept;

        /**
         * The identifier of the buddy who sent the initial subscription.
         */
        char* buddy_uri;

        /**
         * The subscription identifier that was presented with the inbound subscription event.
         */
        char* subscription_handle;
    } vx_req_account_send_subscription_reply_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_send_subscription_reply object.
     * \ingroup buddies
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_send_subscription_reply_create(vx_req_account_send_subscription_reply_t** req);
#endif

    /**
     * Send a notification about the properties of the current session (for example, whether a user is typing).
     * \see vx_resp_session_send_notification
     * \ingroup session
     */
    typedef struct vx_req_session_send_notification {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * Used for typing notifications (text) and hand-raising (audio).
         * The default value is notification_not_typing.
         */
        vx_notification_type notification_type;
    } vx_req_session_send_notification_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_session_send_notification object.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_send_notification_create(vx_req_session_send_notification_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Send a dual-tone multi-frequency (DTMF) signal for a given session.
     * \see vx_resp_session_send_dtmf
     * \ingroup obsolete
     * @deprecated
     */
    typedef struct vx_req_session_send_dtmf {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;

        /**
         * The tone signal to send.
         * The following list details possible values:
         * - 0 - dtmf_0
         * - 1 - dtmf_1
         * - 2 - dtmf_2
         * - 3 - dtmf_3
         * - 4 - dtmf_4
         * - 5 - dtmf_5
         * - 6 - dtmf_6
         * - 7 - dtmf_7
         * - 8 - dtmf_8
         * - 9 - dtmf_9
         * - 10 - dtmf_pound
         * - 11 - dtmf_star
         * - 12 - dtmf_A
         * - 13 - dtmf_B
         * - 14 - dtmf_C
         * - 15 - dtmf_D
         */
        vx_dtmf_type dtmf_type;
    } vx_req_session_send_dtmf_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * \deprecated This is deprecated and should not be used.
     * Allocate and initialize a vx_req_session_send_dtmf object.
     * \ingroup obsolete
     * @deprecated
     */
    VIVOXSDK_DLLEXPORT int vx_req_session_send_dtmf_create(vx_req_session_send_dtmf_t** req);
#endif

    /**
     * Define rules to block individuals or groups of individuals.
     * \see vx_resp_account_create_block_rule
     * \ingroup buddies
     */
    typedef struct vx_req_account_create_block_rule {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The SIP URI of the buddy to block.
         */
        char* block_mask;

        /**
         * Blocks presence and/or communication visibility (1 or 0).
         * The default value is 0.
         */
        int presence_only;
    } vx_req_account_create_block_rule_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_create_block_rule object.
     * \ingroup buddies
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_create_block_rule_create(vx_req_account_create_block_rule_t** req);
#endif

    /**
     * Delete a block rule.
     * \see vx_resp_account_delete_block_rule
     * \ingroup buddies
     */
    typedef struct vx_req_account_delete_block_rule {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The SIP URI of the buddy.
         */
        char* block_mask;
    } vx_req_account_delete_block_rule_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_delete_block_rule object.
     * \ingroup buddies
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_delete_block_rule_create(vx_req_account_delete_block_rule_t** req);
#endif

    /**
     * Retrieve a list of block rules for a given account.
     * The order of rules returned in the list is unspecified.
     * The calling application must sequence the resultant data.
     * \see vx_resp_account_list_block_rules
     * \ingroup buddies
     */
    typedef struct vx_req_account_list_block_rules {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * When set to 1, this interrogates the server for the list of block rules.
         * The default value is 0.
         * \note V5 only. This is ignored by V4.
         */
        int refresh;
    } vx_req_account_list_block_rules_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_list_block_rules object.
     * \ingroup buddies
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_list_block_rules_create(vx_req_account_list_block_rules_t** req);
#endif

    /**
     * Set up rules to automatically accept individuals or groups of individuals when they request presence subscriptions.
     * \see vx_resp_account_create_auto_accept_rule
     * \ingroup buddies
     */
    typedef struct vx_req_account_create_auto_accept_rule {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The SIP URI of the buddy.
         */
        char* auto_accept_mask;

        /**
         * This causes a requesting buddy that matches this rule to automatically be added
         * to the buddy list associated with the account_handle (1 or 0).
         * The default setting is 0.
         */
        int auto_add_as_buddy;

        /**
         * Add the accept rule with this nickname.
         * This is optional.
         */
        char* auto_accept_nickname;
    } vx_req_account_create_auto_accept_rule_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_create_auto_accept_rule object.
     * \ingroup buddies
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_create_auto_accept_rule_create(vx_req_account_create_auto_accept_rule_t** req);
#endif

    /**
     * Delete an auto accept rule.
     * \see vx_resp_account_delete_auto_accept_rule
     * \ingroup buddies
     */
    typedef struct vx_req_account_delete_auto_accept_rule {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The SIP URI of the buddy.
         */
        char* auto_accept_mask;
    } vx_req_account_delete_auto_accept_rule_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_delete_auto_accept_rule object.
     * \ingroup buddies
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_delete_auto_accept_rule_create(vx_req_account_delete_auto_accept_rule_t** req);
#endif

    /**
     * Retrieve a list of auto accept rules for a given account.
     * The order of rules returned in the list is unspecified.
     * The calling application must sequence the resultant data.
     * \see vx_resp_account_list_auto_accept_rule
     * \ingroup buddies
     */
    typedef struct vx_req_account_list_auto_accept_rules {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;
    } vx_req_account_list_auto_accept_rules_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_list_auto_accept_rules object.
     * \ingroup buddies
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_list_auto_accept_rules_create(vx_req_account_list_auto_accept_rules_t** req);
#endif

    /**
     * \deprecated Use vx_req_account_web_call instead.
     * Update information about the currently logged in account.
     * \see vx_resp_account_update_account
     * @deprecated
     */
    typedef struct vx_req_account_update_account {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The display name for the account.
         */
        char* displayname;
    } vx_req_account_update_account_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_update_account object.
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_update_account_create(vx_req_account_update_account_t** req);
#endif

    /**
     * \deprecated Use vx_req_account_web_call instead.
     * Return basic information about the user's account.
     * \see vx_resp_account_get_account
     * @deprecated
     */
    typedef struct vx_req_account_get_account {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * \deprecated This field is not used.
         * @deprecated
         */
        char* uri;
    } vx_req_account_get_account_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_get_account object.
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_get_account_create(vx_req_account_get_account_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Send an SMS message to another user if that user's phone and carrier have been properly set.
     * If the recipient's phone or carrier is not set, a response is immediately returned with a return code of 1.
     * If the message could not be delivered for any other unforeseen reason downstream,
     * the error is not reported in the response.
     * \see vx_resp_account_send_sms
     * @deprecated
     */
    typedef struct vx_req_account_send_sms {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The URI of the intended receiver of the message.
         */
        char* recipient_uri;

        /**
         * The body of the message being sent.
         */
        char* content;
    } vx_req_account_send_sms_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_send_sms object.
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_send_sms_create(vx_req_account_send_sms_t** req);
#endif

    /**
     * Perform a network test.
     * This command probes the network and performs tests to determine if the application will have the connectivity
     * required to perform the tasks needed to send and receive presence, IM, and media information.
     * This call tests network connectivity issues, such as creating a "Network Troubleshooter" tool that can be standalone or integrated into an application.
     * This single call returns results for all of the tests that are performed, and the data can be displayed to the user.
     * \note The SDK ships with a sample Network Troubleshooter that can be used as is or as a reference to create a custom Network Troubleshooter.
     * \see vx_resp_aux_connectivity_info
     * \ingroup diagnostics
     */
    typedef struct vx_req_aux_connectivity_info {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * Provided by Vivox.
         */
        char* well_known_ip;

        /**
         * Provided by Vivox.
         */
        char* stun_server;

        /**
         * Provided by Vivox.
         */
        char* echo_server;

        /**
         * Provided by Vivox.
         */
        int echo_port;

        /**
         * Provided by Vivox.
         */
        int timeout;

        /**
         * If this is specified, then all other fields are ignored, and only the values obtained from the server are used.
         * These parameters are returned in the response.
         * If this field is NULL, then the specified fields are used to perform the network test.
         */
        char* acct_mgmt_server;
    } vx_req_aux_connectivity_info_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_connectivity_info object.
     * \ingroup diagnostics
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_connectivity_info_create(vx_req_aux_connectivity_info_t** req);
#endif

    /**
     * Retrieve a list of audio render devices for the current computer.
     * Most machines have at least one audio render device.
     * The application programmer can call this method without initializing the SDK or logging in
     * (similar to the network connectivity methods).
     * \note This list could be smaller than the list of all available render devices.
     * \see vx_resp_aux_get_render_devices
     * \ingroup devices
     */
    typedef struct vx_req_aux_get_render_devices {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * An optional parameter that specifies the account handle of the user whose render devices will be retrieved.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         * The list of all render devices returned in the render_devices list of the response is user-agnostic.
         * The other fields that indicate the devices in use under their respective contexts vary with the requested user.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_get_render_devices_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_get_render_devices object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_get_render_devices_create(vx_req_aux_get_render_devices_t** req);
#endif

    /**
     * Return a list of available audio capture devices.
     * \note This list could be smaller than the list of all available capture devices.
     * \see vx_resp_aux_get_capture_devices
     * \ingroup devices
     */
    typedef struct vx_req_aux_get_capture_devices {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * An optional parameter that specifies the account handle of the user whose capture device will be retrieved.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         * The list of all capture devices returned in the capture_devices list of the response is user-agnostic.
         * The other fields that indicate the devices in use under their respective contexts vary with the requested user.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_get_capture_devices_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_get_render_devices object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_get_capture_devices_create(vx_req_aux_get_capture_devices_t** req);
#endif

    /**
     * Instruct the Vivox SDK sound system to set the render device to a specific value.
     * The "render device specifier" is a string that must match the device string
     * of the vx_device_t structs that are returned from a "get render devices" call.
     * This value is retained across various voice sessions.
     * \note On PlayStation 4, the render_device_specifier can be the string representation of the user ID.
     * \see vx_resp_aux_set_render_device
     * \ingroup devices
     */
    typedef struct vx_req_aux_set_render_device {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * A string specifier that is returned by a Get Render Devices call.
         * \note This must be exactly the same as the device string of a vx_device_t object.
         * \note On PlayStation 4, this can be the string representation of the user ID. For example, "1", "2", "3", and so on.
         */
        char* render_device_specifier;
        /**
         * An optional parameter that specifies the account handle of the user whose render device will be set.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_set_render_device_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_set_render_device object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_set_render_device_create(vx_req_aux_set_render_device_t** req);
#endif

    /**
     * Instruct the Vivox SDK sound system to set the capture device to a specific value.
     * \see vx_resp_aux_set_capture_device
     * \ingroup devices
     */
    typedef struct vx_req_aux_set_capture_device {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * A string specifier that is returned by a "get capture devices" call.
         * \note This string must be exactly the same value as the device string of a vx_device_t object.
         * This value is retained across various voice sessions.
         * If this value is a nullptr or an empty string, then the default capture device is used.
         * \note On PlayStation 4, this value can be the string representation of the user ID.
         */
        char* capture_device_specifier;
        /**
         * An optional parameter that specifies the account handle of the user whose capture device will be set.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_set_capture_device_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_set_capture_device object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_set_capture_device_create(vx_req_aux_set_capture_device_t** req);
#endif

    /**
     * This method returns the master microphone (capture) level of the Vivox SDK sound system.
     * This is a non-negative integer value between 0 and 100 (inclusive).
     * The scale is logarithmic, which means that a level increase of 6 represents a doubling in energy,
     * and a level increase of 20 represents a ten-fold increase in energy.
     * The default value is 50.
     * \see vx_resp_aux_get_mic_level
     * \ingroup devices
     */
    typedef struct vx_req_aux_get_mic_level {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;
        /**
         * An optional parameter that specifies the account handle of the user whose microphone level will be retrieved.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_get_mic_level_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_get_mic_level object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_get_mic_level_create(vx_req_aux_get_mic_level_t** req);
#endif

    /**
     * This method returns the master speaker (render) level of the Vivox SDK sound system.
     * This is a non-negative integer value between 0 and 100 (inclusive).
     * The scale is logarithmic, which means that a level increase of 6 represents a doubling in energy,
     * and a level increase of 20 represents a ten-fold increase in energy.
     * The default value is 50.
     * \see vx_resp_aux_get_speaker_level
     * \ingroup devices
     */
    typedef struct vx_req_aux_get_speaker_level {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;
        /**
         * An optional parameter that specifies the account handle of the user whose speaker level will be retrieved.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_get_speaker_level_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_get_speaker_level object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_get_speaker_level_create(vx_req_aux_get_speaker_level_t** req);
#endif

    /**
     * Set the master microphone level of the Vivox SDK sound system.
     * Valid values are non-negative integers between 0 and 100 (inclusive).
     * The default value is 50.
     * \see vx_resp_aux_set_mic_level
     * \ingroup devices
     */
    typedef struct vx_req_aux_set_mic_level {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The master microphone level.
         * This is a non-negative integer value between 0 and 100 (inclusive).
         * The scale is logarithmic, which means that a level increase of 6 represents a doubling in energy,
         * and a level increase of 20 represents a ten-fold increase in energy.
         * The default value is 50.
         */
        int level;
        /**
         * An optional parameter that specifies the account handle of the user whose microphone level will be set.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_set_mic_level_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_set_mic_level object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_set_mic_level_create(vx_req_aux_set_mic_level_t** req);
#endif

    /**
     * Set the master speaker level of the Vivox SDK sound system.
     * Valid values are non-negative integers between 0 and 100 (inclusive).
     * The default value is 50.
     * \see vx_resp_aux_set_speaker_level
     * \ingroup devices
     */
    typedef struct vx_req_aux_set_speaker_level {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The master speaker level.
         * This is a non-negative integer value between 0 and 100 (inclusive).
         * The scale is logarithmic, which means that a level increase of 6 represents a doubling in energy,
         * and a level increase of 20 represents a ten-fold increase in energy.
         * The default value is 50.
         */
        int level;
        /**
         * An optional parameter that specifies the account handle of the user whose speaker level will be set.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_set_speaker_level_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_set_speaker_level object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_set_speaker_level_create(vx_req_aux_set_speaker_level_t** req);
#endif

    /**
     * Ensure that a specific selected render device is functioning properly.
     * The sound_file_path should point to a local directory path that contains a monaural .wav or .au sound file.
     * If the loop value is set to 1, then the sound system plays the file in a continuous loop
     * until the "render audio stop" method is called.
     * \see vx_resp_aux_render_audio_start
     * \ingroup devices
     */
    typedef struct vx_req_aux_render_audio_start {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * A local directory path name of a monaural .wav or .au sound file.
         */
        char* sound_file_path;

        /**
         * If set to 1, the sound system plays the file in a continuous loop until the "render audio stop" method is called.
         * If set to 0, the file plays once or until the "render audio stop" method is called.
         * The default value is 0.
         */
        int loop;

        /**
         * \deprecated Debug use only.
         * @deprecated
         */
        char* path;
        /**
         * An optional parameter that specifies the account handle of the user whose render device will be used.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_render_audio_start_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_render_audio_start object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_render_audio_start_create(vx_req_aux_render_audio_start_t** req);
#endif

    /**
     * Modify the applied font of the aux audio buffer that is rendering.
     * If no audio buffer is rendering, then the method immediately returns.
     */
    typedef struct vx_req_aux_render_audio_modify {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The updated font string to apply to the audio buffer that is playing.
         * Use NULL to play an audio font without changes.
         */
        char* font_str;
        /**
         * An optional parameter that specifies the account handle of the user whose audio font will be modified.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_render_audio_modify_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_render_audio_modify object.
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_render_audio_modify_create(vx_req_aux_render_audio_modify_t** req);
#endif

    /**
     * Get the connector VAD (Voice Activity Detector) properties.
     * \see vx_req_aux_get_vad_properties
     * \ingroup devices
     */
    typedef struct vx_req_aux_get_vad_properties {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;
        /**
         * An optional parameter that specifies the account handle of the user whose connector VAD properties will be retrieved.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_get_vad_properties_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_get_vad_properties object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_get_vad_properties_create(vx_req_aux_get_vad_properties_t** req);
#endif

    /**
     * Set the connector VAD (Voice Activity Detector) properties.
     * The following properties update when capture audio is active:
     * - vad_hangover
     * - vad_sensitivity
     * - vad_auto
     * The vad_noise_floor property requires capture audio restart to update
     * (for example, the update occurs after rejoining a voice channel).
     * \see vx_req_aux_set_vad_properties
     * \ingroup devices
     */
    typedef struct vx_req_aux_set_vad_properties {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The time in milliseconds that it takes for the VAD to switch back to silence from speech mode
         * after the last speech frame has been detected.
         */
        int vad_hangover;

        /**
         * A dimensionless value between 0 and 100 that indicates the sensitivity of the VAD.
         * Increasing this value corresponds to decreasing the sensitivity of the VAD.
         * 0 is the most sensitive, and 100 is the least sensitive.
         */
        int vad_sensitivity;

        /**
        * A dimensionless value between 0 and 20000 that controls the maximum level at which the noise floor
        * can be set to by the VAD's noise tracking.
        * The default value is 576.
        * Too low of a value can make noise tracking ineffective.
        * A value of 0 disables noise tracking, at which point the VAD must rely only on the sensitivity property.
        * Too high of a value can make long speech classifiable as noise.
        */
        int vad_noise_floor;

        /**
        * VAD automatic parameter selection.
        * If this mode is 1 (enabled), then vad_hangover, vad_sensitivity, and vad_noise_floor are ignored,
        * and the VAD automatically optimizes parameters.
        */
        int vad_auto;
        /**
         * An optional parameter that specifies the account handle of the user whose connector VAD properties will be set.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_set_vad_properties_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_set_vad_properties object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_set_vad_properties_create(vx_req_aux_set_vad_properties_t** req);
#endif

    /**
     * Get the derumbler (high-pass filter) properties.
     * \see vx_req_aux_get_derumbler_properties
     * \ingroup devices
     */
    typedef struct vx_req_aux_get_derumbler_properties {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;
        /**
         * An optional parameter that specifies the account handle of the user whose derumbler properties will be retrieved.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_get_derumbler_properties_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_get_derumbler_properties object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_get_derumbler_properties_create(vx_req_aux_get_derumbler_properties_t** req);
#endif

    /**
     * Set the derumbler (high-pass filter) properties.
     * \see vx_req_aux_set_derumbler_properties
     * \ingroup devices
     */
    typedef struct vx_req_aux_set_derumbler_properties {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * Determine whether the derumbler should be enabled (default=1) or disabled (0).
         */
        int enabled;

        /**
         * The frequency at which the derumbler high-pass filter enters into full attenuation.
         * All frequencies at and below this corner frequency are greatly reduced in amplitude.
         * Frequencies above this corner frequency remain at their original amplitude,
         * except for the frequencies that are just above the corner frequency.
         * Valid values are: 15, 60 (the default value), 100.
         */
        int stopband_corner_frequency;
        /**
         * An optional parameter that specifies the account handle of the user whose derumbler properties will be set.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_set_derumbler_properties_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_set_derumbler_properties object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_set_derumbler_properties_create(vx_req_aux_set_derumbler_properties_t** req);
#endif

    /**
     * Immediately stop audio render playback.
     * If no audio files are being played back, then the method immediately returns.
     * \see vx_resp_aux_render_audio_stop
     * \ingroup devices
     */
    typedef struct vx_req_aux_render_audio_stop {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;
        /**
         * An optional parameter that specifies the account handle of the user whose render device will be stopped.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_render_audio_stop_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_render_audio_stop object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_render_audio_stop_create(vx_req_aux_render_audio_stop_t** req);
#endif

    /**
     * Ensure that a specific selected capture device is functioning properly.
     * This can only be successfully invoked if the capture device is not currently in use (such as if it is in a voice session).
     * After the start audio capture method successfully completes, the Vivox SDK sound system starts sending VxAudioEvent_t events
     * at one half the capture frame rate.
     * \see vx_resp_aux_capture_audio_start
     * \ingroup devices
     */
    typedef struct vx_req_aux_capture_audio_start {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        int duration;

        /**
         * Loop audio to the selected render device.
         * The default value is 0.
         * To loop audio to a speaker, set this to 1.
         */
        int loop_to_render_device;
        /**
         * An optional parameter that specifies the account handle of the user whose capture device will be used.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_capture_audio_start_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_capture_audio_start object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_capture_audio_start_create(vx_req_aux_capture_audio_start_t** req);
#endif

    /**
     * Immediately stop audio capture.
     * If no audio files are being played back, then the method immediately returns.
     * \see vx_resp_aux_capture_audio_stop
     * \ingroup devices
     */
    typedef struct vx_req_aux_capture_audio_stop {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;
        /**
         * An optional parameter that specifies the account handle of the user whose capture device will be stopped.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_capture_audio_stop_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_capture_audio_stop object.
     * \ingroup devices
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_capture_audio_stop_create(vx_req_aux_capture_audio_stop_t** req);
#endif

    /**
     * Get the list of fonts that are eligible for use in a session by the current user.
     * \see vx_resp_account_get_session_fonts
     * \ingroup voicefonts
     */
    typedef struct vx_req_account_get_session_fonts {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;
    } vx_req_account_get_session_fonts_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_get_session_fonts object.
     * \ingroup voicefonts
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_get_session_fonts_create(vx_req_account_get_session_fonts_t** req);
#endif

    /**
     * Get the list of fonts that the user can "try", including all user fonts and free root fonts.
     * \see vx_resp_account_get_template_fonts
     * \ingroup voicefonts
     */
    typedef struct vx_req_account_get_template_fonts {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;
    } vx_req_account_get_template_fonts_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_get_template_fonts object.
     * \ingroup voicefonts
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_get_template_fonts_create(vx_req_account_get_template_fonts_t** req);
#endif

    /**
     * Start audio capture from the selected audio capture device.
     * Audio is captured to the SDK internal capture buffer until the vx_req_aux_capture_audio_stop command is issued,
     * or until 10 minutes has elapsed, whichever is earlier.
     * \see vx_resp_aux_start_buffer_capture
     * \ingroup adi
     */
    typedef struct vx_req_aux_start_buffer_capture {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;
        /**
         * An optional parameter that specifies the account handle of the user whose audio will be captured.
         * This must either be unset or the account_handle that was passed in to a vx_req_account_anonymous_login request that previously succeeded.
         * If unset, the default account_handle is used.
         */
        VX_HANDLE account_handle;
    } vx_req_aux_start_buffer_capture_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_start_buffer_capture object.
     * \ingroup adi
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_start_buffer_capture_create(vx_req_aux_start_buffer_capture_t** req);
#endif

    /**
     * Play a buffer from memory that was captured with the vx_req_aux_start_buffer_capture command.
     * To terminate playback, use vx_req_aux_render_audio_stop.
     * \see vx_resp_aux_play_audio_buffer
     * \ingroup adi
     */
    typedef struct vx_req_aux_play_audio_buffer {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The ID of the template font to apply to this buffer.
         * 0 = none.
         */
        int template_font_id;

        /**
         * The font delta to apply to the chosen template font.
         * This is ignored if no template_font_id is supplied.
         * Leave this as NULL to play the font without changes.
         */
        char* font_delta;
    } vx_req_aux_play_audio_buffer_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_play_audio_buffer object.
     * \ingroup adi
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_play_audio_buffer_create(vx_req_aux_play_audio_buffer_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Monitor the keyboard and mouse buttons when the application does not have focus.
     * When the vx_req_aux_global_monitor_keyboard_mouse_t request is issued to the SDK, the SDK raises
     * vx_evt_keyboard_mouse_t events when a key or mouse button combination is pressed or released.
     * This only supports the first three mouse buttons.
     * The request can be issued multiple times for different combinations of key codes.
     * \note On OSX, to use this feature, "Enable Access for Assistive Devices" must be enabled.
     * \see vx_resp_aux_global_monitor_keyboard_mouse
     * \ingroup devices
     * \attention This is not supported on the iPhone platform.
     * @deprecated
     */
    typedef struct vx_req_aux_global_monitor_keyboard_mouse {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * An application-defined name for the binding.
         * This name is returned in the vx_evt_keyboard_mouse_t event when the key combination is pressed or released.
         */
        char* name;

        /**
         * The number of valid key codes in the codes member.
         * If this is zero, then the binding for that name is cleared, and no more events are received for that binding.
         */
        int code_count;

        /**
         * The key codes that must be pressed to activate this binding.
         */
        int codes[10];
    } vx_req_aux_global_monitor_keyboard_mouse_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_global_monitor_keyboard_mouse object.
     * \ingroup devices
     * \attention This is not supported on the iPhone platform.
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_global_monitor_keyboard_mouse_create(vx_req_aux_global_monitor_keyboard_mouse_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Monitor the keyboard and mouse to detect when a user has been idle for a specific period of time.
     * To do this, issue a vx_req_aux_set_idle_timeout_t request, and the SDK then raises an vx_evt_idle_state_changed event
     * when the user transitions to and from an idle state.
     * \note Mouse movement events do not trigger the exit from idle condition.
     * \see vx_resp_aux_set_idle_timeout
     * \ingroup devices
     * \attention This is not supported on the iPhone platform.
     * @deprecated
     */
    typedef struct vx_req_aux_set_idle_timeout {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The number of contiguous seconds without keyboard or mouse activity that must occur
         * for the idle state to change to "1" (idle).
         */
        int seconds;
    } vx_req_aux_set_idle_timeout_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_set_idle_timeout object.
     * \ingroup devices
     * \attention This is not supported on the iPhone platform.
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_set_idle_timeout_create(vx_req_aux_set_idle_timeout_t** req);
#endif

    /**
     * Credentials for creating Vivox accounts.
     * \attention This is not supported on the iPhone platform.
     */
    typedef struct {
        /**
         * \attention This is not currently supported.
         * This must be NULL or empty.
         */
        char* admin_username;

        /**
         * \attention This is not currently supported.
         * This must be NULL or empty.
         */
        char* admin_password;

        /**
         * A signed XML grant document.
         */
        char* grant_document;

        /**
         * The URL of the Vivox account management server.
         */
        char* server_url;
    } vx_generic_credentials;

    /**
     * \deprecated This is deprecated and should not be used.
     * Create a new user account.
     * \see vx_resp_aux_create_account
     * \attention This is not supported on the iPhone platform.
     * @deprecated
     */
    typedef struct vx_req_aux_create_account {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The credentials to use to create the account.
         *
         * \attention This is not supported on the iPhone platform.
         */
        vx_generic_credentials credentials;

        /**
         * The user's username for the account.
         */
        char* user_name;

        /**
         * The user's password for the account.
         */
        char* password;

        /**
         * The user's email address.
         */
        char* email;

        /**
         * RESERVED FOR FUTURE USE
         */
        char* number;

        /**
         * RESERVED FOR FUTURE USE
         * The display name to use in the Vivox portal for the user.
         */
        char* displayname;

        /**
         * The first name to use in the Vivox portal for the user.
         */
        char* firstname;

        /**
         * The last name to use in the Vivox portal for the user.
         */
        char* lastname;

        /**
         * RESERVED FOR FUTURE USE
         * The user's phone number.
         */
        char* phone;

        /**
         * RESERVED FOR FUTURE USE
         * The user's primary language.
         */
        char* lang;

        /**
         * RESERVED FOR FUTURE USE
         * The user's age at the time of account creation.
         */
        char* age;

        /**
         * RESERVED FOR FUTURE USE
         * The user's gender.
         */
        char* gender;

        /**
         * RESERVED FOR FUTURE USE
         * The users's timezone.
         */
        char* timezone;

        /**
         * RESERVED FOR FUTURE USE
         */
        char* ext_profile;

        /**
         * RESERVED FOR FUTURE USE
         */
        char* ext_id;
    } vx_req_aux_create_account_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_create_account object.
     * \attention This is not supported on the iPhone platform.
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_create_account_create(vx_req_aux_create_account_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Reactivate an account that has been deactivated.
     * \see vx_resp_aux_reactivate_account
     * \attention This is not supported on the iPhone platform.
     * @deprecated
     */
    typedef struct vx_req_aux_reactivate_account {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The credentials to use to reactivate the account.
         * \attention This is not supported on the iPhone platform.
         */
        vx_generic_credentials credentials;

        /**
         * The username to reactivate.
         */
        char* user_name;
    } vx_req_aux_reactivate_account_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_create_account object.
     * \attention This is not supported on the iPhone platform.
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_reactivate_account_create(vx_req_aux_reactivate_account_t** req);
#endif

    /**
     * \deprecated This is deprecated and should not be used.
     * Deactivate an account.
     * \see vx_resp_aux_deactivate_account
     * \attention This is not supported on the iPhone platform.
     * @deprecated
     */
    typedef struct vx_req_aux_deactivate_account {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The credentials to use to deactivate the account.
         * \attention This is not supported on the iPhone platform.
         */
        vx_generic_credentials credentials;

        /**
         * The username to deactivate.
         */
        char* user_name;
    } vx_req_aux_deactivate_account_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_create_account object.
     * \attention This is not supported on the iPhone platform.
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_deactivate_account_create(vx_req_aux_deactivate_account_t** req);
#endif

    /**
     * Post crash dump data to the server.
     * \note This command is not an application to the XML interface.
     * \see vx_resp_account_post_crash_dump
     * \ingroup diagnostics
     * \attention This is not supported on the iPhone platform.
     */
    typedef struct vx_req_account_post_crash_dump {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The account to use when posting the crash dump.
         */
        VX_HANDLE account_handle;

        /**
         * The Base64-encoded crash dump.
         */
        char* crash_dump;
    } vx_req_account_post_crash_dump_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_post_crash_dump object.
     * \ingroup diagnostics
     * \attention This is not supported on the iPhone platform.
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_post_crash_dump_create(vx_req_account_post_crash_dump_t** req);
#endif

    /**
     * Reset a user's password.
     * \see vx_resp_aux_reset_password
     */
    typedef struct vx_req_aux_reset_password {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The URI of the account to reset the password for.
         */
        char* user_uri;

        /**
         * The email address associated with the account to reset the password for.
         */
        char* user_email;

        /**
         * The server to perform the password reset on.
         */
        char* server_url;
    } vx_req_aux_reset_password_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_reset_password object.
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_reset_password_create(vx_req_aux_reset_password_t** req);
#endif

    /**
     * Get the current state of the SDK.
     * Get the initial state when connecting to an out of process Vivox SDK that is already running.
     * \see vx_resp_aux_diagnostic_state_dump
     * \attention This is not supported on the iPhone platform.
     */
    typedef struct vx_req_aux_diagnostic_state_dump {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The level of detail to return.
         */
        vx_diagnostic_dump_level level;
    } vx_req_aux_diagnostic_state_dump_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_diagnostic_state_dump object.
     * \attention This is not supported on the iPhone platform.
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_diagnostic_state_dump_create(vx_req_aux_diagnostic_state_dump_t** req);
#endif

    /**
     * Submit a generic web request to the Vivox account management server.
     * \see vx_resp_account_web_call
     */
    typedef struct vx_req_account_web_call {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The relative path to the original account management URL.
         * For example: viv_chan_mod.php
         */
        char* relative_path;

        /**
         * The number of parameters.
         */
        int parameter_count;

        /**
         * The parameters for the web call.
         */
        vx_name_value_pairs_t parameters;
    } vx_req_account_web_call_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_web_call object.
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_web_call_create(vx_req_account_web_call_t** req);
#endif

    /**
     * Retrieve network-related statistics for the call associated with the specified session group.
     * \see vx_resp_sessiongroup_get_stats
     */
    typedef struct vx_req_sessiongroup_get_stats {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * \deprecated This field is ignored.
         * The handle returned from a successful vx_req_sessiongroup_create request.
         * @deprecated
         */
        VX_HANDLE sessiongroup_handle;

        /**
         * Reset the statistics.
         * - Use 1 to reset the statistics.
         * - Use 0 to let the statistics aggregrate.
         * The default value is 0.
         */
        int reset_stats;
    } vx_req_sessiongroup_get_stats_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_sessiongroup_get_stats object.
     *
     */
    VIVOXSDK_DLLEXPORT int vx_req_sessiongroup_get_stats_create(vx_req_sessiongroup_get_stats_t** req);
#endif

    /**
     * Send a message to a specific user.
     * \see vx_resp_account_send_message
     * \ingroup account
     */
    typedef struct vx_req_account_send_message {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful login request.
         */
        VX_HANDLE account_handle;

        /**
         * The destination URI.
         */
        char* user_uri;

        /**
         * The HTTP content type of the message.
         * If an empty string is passed in, then this field defaults to "text/plain".
         * \note This field will be validated, so it must use a valid format. See the IETF documentation on RFC 2046.
         */
        char* message_header;

        /**
         * The contents of the message.
         * \note The message body cannot exceed the length that is specified by the server in its pre-login configuration.
         * The default maximum message length is 320 bytes (320 characters in UTF-8 formatting).
         */
        char* message_body;

        /**
         * \deprecated This is deprecated and should not be used.
         * @deprecated
         */
        char* alias_username;

        /**
         * The language to use.
         * The default setting is NULL, which implies "en".
         * \note V5 only. This is ignored by V4.
         */
        char* language;

        /**
         * A custom application stanza namespace.
         * This is optional.
         * The default setting is NULL.
         * \note V5 only. This is ignored by V4.
         */
        char* application_stanza_namespace;

        /**
         * A custom application stanza body.
         * This is optional.
         * The default setting is NULL.
         * \note V5 only. This is ignored by V4.
         */
        char* application_stanza_body;
    } vx_req_account_send_message_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_session_send_message object.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_send_message_create(vx_req_account_send_message_t** req);
#endif
#ifndef DOXYGEN_MAM_SKIP
    /**
     * Query messages that were archived by the server for the specified account.
     * This includes all messages that are sent and received by this account, including directed messages and channel messages.
     * Messages can appear in the archive with a delay of up to several seconds after being sent or received.
     * To query a specific channel's history, use vx_req_session_archive_query.
     * \see vx_req_session_archive_query
     * \ingroup account
     * \note V5 only.
     */
    typedef struct vx_req_account_archive_query {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful login request.
         */
        VX_HANDLE account_handle;

        /**
         * Exclude all messages before a specified date or time from the query results.
         * Specify the start time by using a format defined in XEP-0082.
         * This is optional.
         * The default setting is NULL.
         */
        char* time_start;

        /**
         * Exclude all messages after a specified date or time from the query results.
         * Specify the end time by using a format defined in XEP-0082.
         * This is optional.
         * The default setting is NULL.
         */
        char* time_end;

        /**
         * The text to find in the query.
         * Only messages that contain the specified text are returned.
         * This is optional.
         * The default setting is NULL.
         */
        char* search_text;

        /**
         * The fully specified URI of the channel.
         * Only messages to or from the specified channel are returned.
         * This is optional.
         * The default setting is NULL.
         * \note This is mutually exclusive with participant_uri.
         */
        char* channel_uri;

        /**
         * The fully specified URI of the participant.
         * Only messages to or from the specified participant are returned.
         * This is optional.
         * The default setting is NULL.
         * \note This is mutually exclusive with channel_uri.
         */
        char* participant_uri;

        /**
         * The maximum number of messages to find in the query.
         * This is optional.
         * The default value is 10.
         * Set to 0 to get the total message count without retrieving the messages.
         */
        unsigned int max;

        /**
         * The message_id for paging backward through large query result sets.
         * The query results include messages that immediately precede the specified message in the result set.
         * \note This parameter cannot be used simultaneously with parameter after_id.
         * This is optional.
         * The default setting is NULL.
         */
        char* before_id;

        /**
         * The message_id for paging forward through large query result sets.
         * The query results include messages that immediately follow the specified message in the result set.
         * \note This parameter cannot be used simultaneously with parameter before_id.
         * This is optional.
         * The default setting is NULL.
         */
        char* after_id;

        /**
         * The index of the first message to retrieve.
         * This is optional.
         * The default setting is -1, which indicates to not use this parameter.
         * The first message in the result set always has an index of 0.
         */
        int first_message_index;

        /**
         * A custom application stanza namespace.
         * This is optional.
         * The default setting is NULL.
         */
        char* application_stanza_namespace;

        /**
         * A custom application stanza body.
         * This is optional.
         * The default setting is NULL.
         */
        char* application_stanza_body;
    } vx_req_account_archive_query_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_archive_query object.
     * \note V5 only.
     * \ingroup account
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_archive_query_create(vx_req_account_archive_query_t** req);
#endif
#endif

    /**
     * Query messages that were archived by the server for the specified account.
     * This includes all messages that are sent and received by this account, including directed messages and channel messages.
     * Messages can appear in the archive with a delay of up to several seconds after being sent or received.
     * To query a specific channel's history, use vx_req_session_chat_history_query.
     * \see vx_req_session_chat_history_query
     * \ingroup account
     * \note V5 only.
     */
    typedef struct vx_req_account_chat_history_query {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful login request.
         */
        VX_HANDLE account_handle;

        /**
         * Exclude all messages before a specified date or time from the query results.
         * Specify the start time by using a format defined in XEP-0082.
         * This is optional.
         * The default setting is NULL.
         */
        char* time_start;

        /**
         * Exclude all messages after a specified date or time from the query results.
         * Specify the end time by using a format defined in XEP-0082.
         * This is optional.
         * The default setting is NULL.
         */
        char* time_end;

        /**
         * Used to paginate through collections of data by setting the cursor parameter to a next_cursor attribute returned by a previous request's.
         */
        char* cursor;

        /**
         * The text to find in the query.
         * Only messages that contain the specified text are returned.
         * This is optional.
         * The default setting is NULL.
         */
        char* search_text;

        /**
         * The fully specified URI of the channel.
         * Only messages to or from the specified channel are returned.
         * This is optional.
         * The default setting is NULL.
         * \note This is mutually exclusive with participant_uri.
         */
        char* channel_uri;

        /**
         * The fully specified URI of the participant.
         * Only messages to or from the specified participant are returned.
         * This is optional.
         * The default setting is NULL.
         * \note This is mutually exclusive with channel_uri.
         */
        char* participant_uri;

        /**
         * The maximum number of messages to find in the query.
         * This is optional.
         * The default value is 10.
         * Set to 0 to get the total message count without retrieving the messages.
         */
        unsigned int max;

        /**
         * The message_id for paging backward through large query result sets.
         * The query results include messages that immediately precede the specified message in the result set.
         * \note This parameter cannot be used simultaneously with parameter after_id.
         * This is optional.
         * The default setting is NULL.
         */
        char* before_id;

        /**
         * The message_id for paging forward through large query result sets.
         * The query results include messages that immediately follow the specified message in the result set.
         * \note This parameter cannot be used simultaneously with parameter before_id.
         * This is optional.
         * The default setting is NULL.
         */
        char* after_id;

        /**
         * The index of the first message to retrieve.
         * This is optional.
         * The default setting is -1, which indicates to not use this parameter.
         * The first message in the result set always has an index of 0.
         */
        int first_message_index;

        /**
         * A custom application stanza namespace.
         * This is optional.
         * The default setting is NULL.
         */
        char* application_stanza_namespace;

        /**
         * A custom application stanza body.
         * This is optional.
         * The default setting is NULL.
         */
        char* application_stanza_body;
    } vx_req_account_chat_history_query_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_chat_history_query object.
     * \note V5 only.
     * \ingroup account
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_chat_history_query_create(vx_req_account_chat_history_query_t** req);
#endif

    /**
     * Notify the SDK when important application-level changes occur.
     * \see vx_resp_aux_notify_application_state_change
     */
    typedef struct vx_req_aux_notify_application_state_change {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The type of state change.
         */
        vx_application_state_notification_type_t notification_type;
    } vx_req_aux_notify_application_state_change_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_aux_notify_application_state_change object.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_aux_notify_application_state_change_create(vx_req_aux_notify_application_state_change_t** req);
#endif

    /**
     * Manage communication between users.
     * \see vx_resp_account_control_communications
     * \ingroup session
     */
    typedef struct vx_req_account_control_communications {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;

        /**
         * The handle returned from a successful vx_req_account_anonymous_login request.
         */
        VX_HANDLE account_handle;

        /**
         * The operation to perform: block, unblock, list, or clear.
         * \note This is a bi-directional block and should not be used in conjunction with vx_req_session_set_participant_mute_for_me, because the results can be unpredictable.
         */
        vx_control_communications_operation operation;

        /**
         * The list of linefeed-separated users to block or unblock.
         * This should be NULL for vx_control_communications_operation_list or vx_control_communciations_operation_clear operations.
         */
        char* user_uris;

        /**
        * The scope of the mute command.
        * The default setting is mute_scope_all.
        * This is only required for mute and unmute operations.
        * For block operations, this is ignored, and instead works as mute_scope_all.
        */
        vx_mute_scope scope;
    } vx_req_account_control_communications_t;
#ifndef VIVOX_TYPES_ONLY
    /**
     * Allocate and initialize a vx_req_account_control_communications object.
     * \ingroup session
     */
    VIVOXSDK_DLLEXPORT int vx_req_account_control_communications_create(vx_req_account_control_communications_t** req);
#endif

    /**
    * Enable or disable session transcription.
    * \ingroup session
    */
    typedef struct vx_req_session_transcription_control {
        /**
         * The common properties for all requests.
         */
        vx_req_base_t base;
        /**
         * Returned from a successful vx_req_sessiongroup_add_session request.
         */
        VX_HANDLE session_handle;
        /**
         * Enable or disable transcription.
         * Set to 0 to disable transcription.
         */
        int enable;
        /**
         * A Vivox Access Token to authorize the operation.
         */
        char* access_token;
    } vx_req_session_transcription_control_t;
#ifndef VIVOX_TYPES_ONLY
    /**
    * Allocate and initialize a vx_req_session_transcription_control object.
    * \ingroup session
    */
    VIVOXSDK_DLLEXPORT int vx_req_session_transcription_control_create(vx_req_session_transcription_control_t** req);
#endif

#ifndef VIVOX_TYPES_ONLY
    /**
     * Destroy a request of any type.
     * \ingroup memorymanagement
     */
    VIVOXSDK_DLLEXPORT int destroy_req(vx_req_base_t* pCmd);
#endif

#ifdef __cplusplus
}
#endif

#pragma pack(pop)