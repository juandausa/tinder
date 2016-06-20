//
// Copyright 2016 FiUBA
//

#include "MatchesController.h"
#include <string>

MatchesController::MatchesController(MatchesService matches_service, UserService user_service) :
        matchesService(matches_service), userService(user_service) {
}

void MatchesController::handleGetMatches(RequestParser requestParser, Response response) {
    /*
     * Pedir todos los usuarios.
     * Filtrar los matcheados
     * Agregarle la lista de mensajes
     */

    std::string userId = requestParser.getResourceId();
    LOG(INFO) << "Proccesing show matches for user: '" << userId << "'";
    if (!this->userService.isUserRegistered(userId)) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
        response.Send();
        LOG(INFO) << "Show matches has returned no users for user: '" << userId<< "'";
        return;
    }
}

std::string MatchesController::getErrorResponseBody() {
    Json::Value errorResponse;
    errorResponse["matches"] = Json::arrayValue;
    return this->fastWriter.write(errorResponse);
}

