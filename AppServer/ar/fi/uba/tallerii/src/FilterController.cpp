//
// Copyright 2016 FiUBA
//

#include <string>
#include "Mongoose.h"
#include "FilterController.h"
#include "Response.h"

FilterController :: FilterController(FilterService filter_service) {
}

void FilterController :: handle_update_filters(struct mg_connection *nc, struct http_message *hm, Response response) {
    response.SetCode(200);
    std::string body(hm->body.p);
    response.SetBody(body);
    response.Send();
}
