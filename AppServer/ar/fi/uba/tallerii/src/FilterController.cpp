//
// Copyright 2016 FiUBA
//

#include <string>
#include "Mongoose.h"
#include "FilterController.h"
#include "Response.h"

FilterController :: FilterController(FilterService filter_service) : filter_service(filter_service) {
}

void FilterController :: handle_update_filters(struct mg_connection *nc, struct http_message *hm, Response response) {
    char user_id[255];
    mg_get_http_var(&hm->query_string, "userId", user_id, sizeof(user_id));
    std::string body(hm->body.p);
    if (this->filter_service.update_filters(user_id, body)) {
        response.SetCode(200);
    } else {
        response.SetCode(500);
    }

    response.SetBody(body);
    response.Send();
}
