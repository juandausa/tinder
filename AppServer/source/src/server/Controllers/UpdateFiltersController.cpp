//
// Copyright 2016 FiUBA
//

#include "UpdateFiltersController.h"

void UpdateFiltersController::operation(Request &request, Response &response) {
    std::string userId = request.getResourceId();
    std::string body = request.getBody();
    if (this->filterService.update_filters(userId, body)) {
        response.SetCode(200);
    } else {
        response.SetCode(500);
    }

    response.SetBody(body);
    response.Send();
}
