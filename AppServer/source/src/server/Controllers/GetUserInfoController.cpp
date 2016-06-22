//
// Copyright 2016 FiUBA
//

#include "GetUserInfoController.h"
#include <string>

static std::string validateTimeOrReturnDefault(std::string time) {
    struct tm convertedTime;;
    if (strptime(time.c_str(), "%d/%m/%Y", &convertedTime)) {
        return time;
    } else {
        return Constant::defaultBirthday;
    }
}

static std::string calculateAge(std::string birthday) {
    struct tm convertedTime, localTime;
    time_t t = time(NULL);
    localtime_r(&t, &localTime);
    if (strptime(birthday.c_str(), "%d/%m/%Y", &convertedTime)) {
        return static_cast<std::ostringstream *>(&(std::ostringstream() <<
                                                   (localTime.tm_year - convertedTime.tm_year)))->str();
    }

    return Constant::defaultAge;
}

void GetUserInfoController::operation(Request &request, Response &response) {
    std::string readBuffer;
    std::string body;
    std::string userId = request.getResourceId();
    std::string externalUserId = this->userService.getExternalUserId(userId);
    LOG(INFO) << "Retrieving user info for user: '" << userId << "'";
    if ((userId.compare("") == 0) || (externalUserId.compare("") == 0)) {
        response.SetCode(500);
        response.SetBody("Bad Request, no userId detected.");
    } else {
        CurlWrapper curlWrapper = CurlWrapper();
        std::string url = "https://enigmatic-scrubland-75073.herokuapp.com/users/" + externalUserId;
        curlWrapper.set_post_url(url);
        curlWrapper.set_get_buffer(readBuffer);
        bool res = curlWrapper.perform_request();
        if (res) {
            response.SetCode(200);
            body = this->makeBodyForUserInfoResponse(userId, readBuffer);
            response.SetBody(body);
        } else {
            response.SetCode(500);
            response.SetBody("Bad Request");
        }
    }
    response.Send();
    return;
}

std::string GetUserInfoController::makeBodyForUserInfoResponse(const std::string appUserId,
                                                               const std::string userInfo) {
    Json::Value rootShared;
    Json::Value rootApp;
    Json::Value arrayInterests;
    bool parsingSuccessful = reader.parse(userInfo, rootShared, true);
    if (!parsingSuccessful) {
        return "Error parsing result";
    }
    rootApp["user_id"] = appUserId;
    rootApp["name"] = rootShared["user"].get("name", "");
    rootApp["alias"] = rootShared["user"].get("alias", "");
    std::string birthday = validateTimeOrReturnDefault(rootShared["user"].get("birthday", "").asString());
    rootApp["birthday"] = birthday;
    rootApp["age"] = calculateAge(birthday);
    rootApp["gender"] = rootShared["user"].get("sex", Constant::male);
    rootApp["photo_profile"] = rootShared["user"].get("photo_profile", "");
    Json::Value interests = rootShared["user"].get("interests", "");
    for (unsigned int j = 0; j < interests.size(); j++) {
        arrayInterests.append(interests[j]["value"]);
    }
    rootApp["interests"] = arrayInterests;
    rootApp["location"] = rootShared["user"].get("location", "");
    return fastWriter.write(rootApp);
}
