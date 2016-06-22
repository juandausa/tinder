//
// Copyright 2016 FiUBA
//

#include "UpdateFiltersController.h"
#include <string>

void UpdateFiltersController::operation(Request &request, Response &response) {
    std::string userId = request.getResourceId();
    std::string body = request.getBody();
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(body, root, true);
    if (!parsingSuccessful) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
    } else {
        if (this->filterService.update_filters(userId, body)) {
            response.SetCode(200);
            response.SetBody(this->getSucceedResponseBody());
        } else {
            response.SetCode(500);
            response.SetBody(this->getErrorResponseBody());
        }
    }
    response.Send();
}
