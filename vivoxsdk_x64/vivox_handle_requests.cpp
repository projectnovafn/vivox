#include "vivox.h"

static void handle_sessiongroup_add_session(vx_req_sessiongroup_add_session_t* request);

VIVOX_API int vx_issue_request(vx_req_base_t* request)
{
	switch (request->type) 
	{
	case req_sessiongroup_add_session:
		handle_sessiongroup_add_session(reinterpret_cast<vx_req_sessiongroup_add_session_t*>(request));
		break;

	default:
		return vivox_sdk::vx_issue_request(request);
	}

	return 0;
}

VIVOX_API int vx_issue_request3(vx_req_base_t* request, int* request_count)
{
	return vx_issue_request(request);
}

static void handle_sessiongroup_add_session(vx_req_sessiongroup_add_session_t* req)
{
	req->account_handle = vx_strdup(curr_account_handle);
	curr_sessiongroup_handle = vx_strdup(req->sessiongroup_handle);

	vivox_sdk::vx_issue_request(reinterpret_cast<vx_req_base_t*>(req));
}

VIVOX_API int vx_get_message(vx_message_base_t** out_message)
{
	auto res = vivox_sdk::vx_get_message(out_message);

	if (res == VX_GET_MESSAGE_AVAILABLE && *out_message)
	{
		auto message = *out_message;

		if (message->type == msg_response)
		{
			auto anonymous_login = (vx_resp_account_anonymous_login_t*)message;

			if (anonymous_login->base.type == resp_account_anonymous_login) 
			{ 
				curr_account_handle = vx_strdup(anonymous_login->account_handle);
			}
		}
		else if (message->type == msg_event)
		{
			auto media_stream_updated = (vx_evt_media_stream_updated_t*)message;

			if (media_stream_updated->base.type == evt_media_stream_updated)
			{
				media_stream_updated->sessiongroup_handle = vx_strdup(curr_sessiongroup_handle);

				if (IsBadReadPtr(media_stream_updated->status_string, 8))
					media_stream_updated->status_string = vx_strdup("");
			}
		}
	}

	return res;
}