//
//

#ifndef TINDER_GET_CANDIDATES_CONTROLLER_H
#define TINDER_GET_CANDIDATES_CONTROLLER_H

#include "GenericController.h"
#include "UserService.h"
#include "CandidatesService.h"
class GetCandidatesController: public GenericController {

public:
    void operation(Request &request, Response &response);

private:
    UserService userService;
    Json::Value makeBodyForShowCandidatesResponse(Json::Value userData, const std::string genderOfInterest, Json::Value myArrayOfInterests);
    std::string getUserInfoWithOutResponse(Request &request, Response &response);
    bool isInMyArrayOfInterest(Json::Value interest, Json::Value myArrayOfInterests);
    std::string makeBodyForUserInfoResponse(const std::string appUserId, const std::string userInfo);
};


#endif //TINDER_GET_CANDIDATES_CONTROLLER_H
