//
// Copyright 2016 FiUBA
//

#include "GetFiltersController.h"


void GetFiltersController::operation(Request &request, Response &response) {
    std::string userId = request.getResourceId();
    std::string body = this->filterService.get_filters(userId);
    response.SetCode(200);
    response.SetBody(body);
    response.Send();
}
