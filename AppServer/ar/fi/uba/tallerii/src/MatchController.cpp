//
// Created by juan on 26/05/16.
//

#include "MatchController.h"

MatchController ::MatchController(MatchService match_service, UserService user_service) : match_service(match_service), user_service(user_service) {
}

void MatchController :: handle_get_candidates(RequestParser requestParser, Response response) {
    response.SetCode(200);
    response.SetBody("DummyResponse");
    response.Send();
}