//
// Copyright 2016 FiUBA
//

#include "MatchController.h"
#include <string>

MatchController ::MatchController(MatchService match_service, UserService user_service) :
        matchService(match_service), userService(user_service) {
}

void MatchController :: handleGetCandidates(RequestParser requestParser, Response response) {
    std::string userId = requestParser.getResourceId();
    LOG(INFO) << "Proccesing show candidates for user: '" << userId << "'";
    if (this->userService.isUserRegistered(userId)) {
        response.SetCode(200);
        response.SetBody("{ \"response\": \"DummyUserRegistered\" }");
        response.Send();
        LOG(INFO) << "Show Candidates succeeded for user: '" << userId<< "'";
    } else {
        response.SetCode(400);
        response.SetBody("{ \"response\": \"DummyUserNotRegistered\" }");
        response.Send();
        LOG(INFO) << "Show Candidates failed for user: '" << userId<< "'";
    }
}

/*
 * EJEMPLO
 *
 * Json::Value UserController::makeBodyForShowCandidatesResponse() {
    Json::Value event;
    Json::Value root;
    Json::Value arrayUsers;
    std::string readBuffer;

    CurlWrapper curlWrapper = CurlWrapper();
    std::string url = "https://enigmatic-scrubland-75073.herokuapp.com/users";
    curlWrapper.set_post_url(url);
    curlWrapper.set_get_buffer(readBuffer);
    curlWrapper.perform_request();
    reader.parse(readBuffer, root, true);
    std::cout << readBuffer << std::endl;
    Json::Value users = root["users"];
    for (unsigned int i = 0; i < users.size(); i++) {
        Json::Value user;
        Json::Value arrayInterests;
        std::string sharedUserId = fastWriter.write(users[i]["user"].get("id", ""));
        user["user_id"] = this->userService.getAppUserId(sharedUserId);
        user["alias"] = users[i]["user"].get("alias", "");
        std::string birthday = validateTimeOrReturnDefault(users[i]["user"].get("birthday", "").asString());
        user["birthday"] = birthday;
        user["age"] = calculateAge(birthday);
        user["gender"] = validateGenderOrReturnDefault(users[i]["user"].get("gender", "").asString());
        user["photo_profile"] = users[i]["user"].get("photo_profile", "");
        Json::Value interests = users[i]["user"].get("interests", "");
        for (unsigned int j = 0; j < interests.size(); j++) {
            arrayInterests.append(interests[j]["value"]);
        }
        user["interests"] = arrayInterests;
        arrayUsers.append(user);
    }
    event["candidates"] = arrayUsers;
    return event;
}
 */
