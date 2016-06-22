//
//

#ifndef TINDER_GET_CANDIDATES_CONTROLLER_H
#define TINDER_GET_CANDIDATES_CONTROLLER_H

#include <unordered_map>
#include "GenericController.h"
#include "UserService.h"
#include "CandidatesService.h"

class GetCandidatesController: public GenericController {

public:
    void operation(Request &request, Response &response);
	std::string makeBodyForUserInfoResponse(const std::string appUserId, const std::string userInfo);

private:
    UserService userService;
    Json::Value makeBodyForShowCandidatesResponse(Json::Value userData, std::string myGender,
                                                              std::string genderOfMyInterest,
                                                              Json::Value myArrayOfInterests);
    std::string getUserInfoWithOutResponse(Request &request, Response &response);
    bool isInMyArrayOfInterest(Json::Value interest, Json::Value myArrayOfInterests);
    void onePercentRule(std::unordered_map<std::string, Json::Value> &usersData,
    	std::unordered_map<std::string, std::string> &usersLikes);
    void fillUsersArray(std::unordered_map<std::string, Json::Value> &usersData, 
    	Json::Value &arrayUsers);
    std::string genderOfMyPreference(Json::Value myArrayOfInterests);
};


#endif //TINDER_GET_CANDIDATES_CONTROLLER_H
