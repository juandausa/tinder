//
// Copyright 2016 FiUBA
//

#include "PlusController.h"

PlusController :: PlusController() {
}

void PlusController :: handle_sum_call(struct mg_connection *nc, struct http_message *hm) {
    char n1[100], n2[100];
    double result;

    /* Get form variables */
    mg_get_http_var(&hm->body, "n1", n1, sizeof(n1));
    mg_get_http_var(&hm->body, "n2", n2, sizeof(n2));

    /* Send headers */
    mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

    /* Compute the result and send it back as a JSON object */
    result = strtod(n1, NULL) + strtod(n2, NULL);
    mg_printf_http_chunk(nc, "{ \"result\": %lf }", result);
    mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
}
