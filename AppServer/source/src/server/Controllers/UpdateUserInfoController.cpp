//
// Copyright 2016 FiUBA
//

#include "UpdateUserInfoController.h"
#include <string>

/*static std::string validateTimeOrReturnDefault(std::string time) {
    struct tm convertedTime;;
    if (strptime(time.c_str(), "%d/%m/%Y", &convertedTime)) {
        return time;
    } else {
        return Constant::defaultBirthday;
    }
}*/

static std::string validateGenderOrReturnDefault(std::string gender) {
    if (gender.compare(Constant::female) == 0) {
        return gender;
    }

    return Constant::male;
}


void UpdateUserInfoController::operation(Request &request, Response &response) {
    std::string appUserId = request.getResourceId();
    std::string externalUserId = this->userService.getExternalUserId(appUserId);
    std::cout << "External user id" << externalUserId << std::endl;
    LOG(INFO) << "Updating user info for user: '" << appUserId << "'";
    std::string body = this->makeBodyUserInfoForUpdate(request.getBody(), externalUserId, appUserId);
    
    if ((appUserId.compare("") == 0) || (externalUserId.compare("") == 0) || (body.compare("") == 0)) {
        response.SetCode(400);
        response.SetBody("Bad request.");
    } else {
        std::string url = "http://enigmatic-scrubland-75073.herokuapp.com/users/" + externalUserId;
        LOG(INFO) << "Requesting url: " << url;
        CurlWrapper curlWrapper = CurlWrapper();
        std::string readBuffer;
        curlWrapper.set_post_url(url);
        curlWrapper.set_put_data(body, readBuffer);
        bool requestResult = curlWrapper.perform_request();
        if (!requestResult) {
            LOG(WARNING) << "Error requesting url: '" << url << "' with body: " << body << ". Response: " <<
            readBuffer;
            response.SetCode(500);
            response.SetBody(getErrorResponseBody());
        } else {
            LOG(INFO) << "Requesting url: '" << url << " ' has respond: " << readBuffer;
            response.SetCode(200);
            response.SetBody(getSucceedResponseBody());
        }
        curlWrapper.clean();
    }
    response.Send();
}

void UpdateUserInfoController::makeBodyForRegistrationPost(const Json::Value &root, std::string appUserId,
                                                                            Json::Value &userData, int userId) {
    std::string name = root.get("name", "").asString();
    std::string alias = root.get("alias", "").asString();
    int age = root.get("age", "").asInt();
    std::string gender = validateGenderOrReturnDefault(root.get("gender", Constant::male).asString());
    std::string photo_profile = root.get("photo_profile", "").asString();

    Json::Value event;
    Json::Value user;
    Json::Value interest;
    Json::Value interests;

    userData["user"]["id"] = userId;
    userData["user"]["name"] = name;
    userData["user"]["alias"] = alias;
    userData["user"]["sex"] = gender;
    userData["user"]["photo_profile"] = photo_profile;
    userData["user"]["age"] = age;
    
    std::cout << fastWriter.write(userData) << std::endl;
}

std::string UpdateUserInfoController::makeBodyUserInfoForUpdate(const std::string info, const std::string userId,
                                                                const std::string appUserId) {
    std::string url = "http://enigmatic-scrubland-75073.herokuapp.com/users/" + userId;
    LOG(INFO) << "Requesting url: " << url;
    std::cout << "Requesting url: " << url << std::endl;
    CurlWrapper curlWrapper = CurlWrapper();
    std::string userProfileData;
    curlWrapper.set_get_url(url);
    curlWrapper.set_get_buffer(userProfileData);
    bool requestResult = curlWrapper.perform_request();
    if (!requestResult) {
        return "";
    }

    std::cout << "User data " << userProfileData << std::endl;
    
    Json::Value userData;
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(info, root, true);
    if (!parsingSuccessful) {
        return "";
    }

    Json::Reader otherReader;
    parsingSuccessful = otherReader.parse(userProfileData, userData, true);
    std::cout << "User data json" << fastWriter.write(userData) << std::endl;

    userProfileData.erase();
    if (!parsingSuccessful) {
        return "";
    }
    try {
        this->makeBodyForRegistrationPost(root, appUserId, userData, std::atoi(userId.c_str()));
    } catch (std::exception const &e) {
        LOG(WARNING) << "Error parsing user extrenal id, which is: '" << userId << "'";
        return "";
    }
    return fastWriter.write(userData);
}
