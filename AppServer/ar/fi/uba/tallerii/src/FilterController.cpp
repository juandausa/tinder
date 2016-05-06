//
// Copyright 2016 FiUBA
//

#include <string>
#include "Mongoose.h"
#include "FilterController.h"
#include "Response.h"

FilterController :: FilterController(FilterService filter_service) : filter_service(filter_service) {
}

void FilterController :: handle_update_filters(RequestParser requestParser, Response response) {
    std::string userId = requestParser.getResourceId();
    std::string body = requestParser.getBody();
    if (this->filter_service.update_filters(userId, body)) {
        response.SetCode(200);
    } else {
        response.SetCode(500);
    }

    response.SetBody(body);
    response.Send();
}

void FilterController :: handle_get_filters(RequestParser requestParser, Response response) {
    std::string userId = requestParser.getResourceId();
    std::string body = this->filter_service.get_filters(userId);
    response.SetCode(200);
    response.SetBody(body);
    response.Send();
}
