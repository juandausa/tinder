//
// Copyright 2016 FiUBA
//

#include "UserController.h"
#include <glog/logging.h>
UserController :: UserController() {}

void UserController :: handle_login(struct mg_connection *nc, struct http_message *hm) {
    char user_id[255], password[255];

    /* Get form variables */
    mg_get_http_var(&hm->query_string, "userId", user_id, sizeof(user_id));
    LOG(INFO) << "Proccesing login for user: " << user_id << ".";
    /* Send headers */
    mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

    /* Compute the result and send it back as a JSON object */
    mg_printf_http_chunk(nc, "{ \"user\": { \"userId\" : \"%s\" } }", user_id, password);
    mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
    LOG(INFO) << "Login succeeded for user: " << user_id << ".";
}
