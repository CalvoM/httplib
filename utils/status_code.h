#ifndef STATUS_CODE_H_
#define STATUS_CODE_H_
enum class StatusCode{
    info_continue = 100,
    info_switching_protocol,
    info_processing,
    info_early_hints,
    success_ok = 200,
    success_created,
    success_accepted,
    success_non_authoritative_info,
    success_no_content,
    success_reset_content,
    success_partial_content,
    success_multi_status,
    success_already_reported,
    success_im_used,
    redirection_multiple_choice = 300,
    redirection_moved_permanently,
    redirection_found,
    redirection_see_other,
    redirection_not_modified,
    redirection_use_proxy,
    redirection_temporary_redirect=307,
    redirection_permanent_redirect,
    client_error_bad_request=400,
    client_error_unauthorized,
    client_error_payment_required,
    client_error_forbidden,
    client_error_not_found,
    client_error_method_not_allowed,
    client_error_not_acceptable,
    client_error_proxy_authentication_required  
};

#endif