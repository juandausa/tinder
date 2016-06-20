#include "GetCandidatesController.h"

/*AUX FUNCTIONS: SACAR*/
bool GetCandidatesController::isInMyArrayOfInterest(Json::Value interest, Json::Value myArrayOfInterests) {
    std::string theirInterest = fastWriter.write(interest);
    for (unsigned int i = 0; i < myArrayOfInterests.size(); i++) {
        std::string myInterest = fastWriter.write(myArrayOfInterests[i]);
        if (theirInterest.compare(myInterest) == 0) {
            return true;
        }
    }
    return false;
}

static std::string validateTimeOrReturnDefault(std::string time) {
    struct tm convertedTime;;
    if (strptime(time.c_str(), "%d/%m/%Y", &convertedTime)) {
        return time;
    } else {
        return Constant::defaultBirthday;
    }
}

static std::string validateGenderOrReturnDefault(std::string gender) {
    if (gender.compare(Constant::female) == 0) {
        return gender;
    }

    return Constant::male;
}

static std::string calculateAge(std::string birthday) {
    struct tm convertedTime, localTime;
    time_t t = time(NULL);
    localtime_r(&t, &localTime);
    if (strptime(birthday.c_str(), "%d/%m/%Y", &convertedTime)) {
        return static_cast<std::ostringstream*>(&(std::ostringstream() << (localTime.tm_year - convertedTime.tm_year)))->str();
    }

    return Constant::defaultAge;
}



void GetCandidatesController::operation(Request &request, Response &response) {
  Json::Value rootShared;
    Json::Value myArrayOfInterests;
    std::string userId = request.getResourceId();
    LOG(INFO) << "Proccesing show candidates for user: '" << userId << "'";
    if (this->userService.isUserRegistered(userId)) {
        std::string responseBody = this->getUserInfoWithOutResponse(request, response);
        bool parsingSuccessful = reader.parse(responseBody, rootShared, true);
        if (!parsingSuccessful) {
            std::cout << "Error parsing result" << std::endl;
        }
        std::string myGender = fastWriter.write(rootShared.get("gender", "male"));
        std::cout << "fast: " << fastWriter.write(rootShared) << std::endl;
        std::string genderOfMyInterest = Constant::male;
        myArrayOfInterests = rootShared.get("interests", "");
        Json::Value body = this->makeBodyForShowCandidatesResponse(rootShared, genderOfMyInterest, myArrayOfInterests);
        response.SetCode(200);
        response.SetBody(fastWriter.write(body));
        response.Send();
    } else {
        response.SetCode(400);
        response.SetBody("{ \"response\": \"DummyUserNotRegistered\" }");
        response.Send();
        LOG(INFO) << "Show Candidates failed for user: '" << userId<< "'";
    }
}

std::string GetCandidatesController::getUserInfoWithOutResponse(Request &request, Response &response) {
    std::string readBuffer;
    std::string body;
    std::string userId = request.getResourceId();
    std::string externalUserId = this->userService.getExternalUserId(userId);
    LOG(INFO) << "Retrieving user info for user: '" << userId<< "'";
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
    
    return body;
}


std::string GetCandidatesController::makeBodyForUserInfoResponse(const std::string appUserId, const std::string userInfo) {
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
    rootApp["gender"] = rootShared["user"].get("gender", "male");
    rootApp["photo_profile"] = rootShared["user"].get("photo_profile", "");
    Json::Value interests = rootShared["user"].get("interests", "");
    for (unsigned int j = 0; j < interests.size(); j++) {
        arrayInterests.append(interests[j]["value"]);
    }
    rootApp["interests"] = arrayInterests;
    rootApp["location"] = rootShared["user"].get("location", "");
    return fastWriter.write(rootApp);
}

Json::Value GetCandidatesController::makeBodyForShowCandidatesResponse(Json::Value userData, std::string genderOfMyInterest,
                                                              Json::Value myArrayOfInterests) {
    Json::Value event;
    Json::Value root;
    Json::Value arrayUsers;
    std::string readBuffer;
    std::string genderOfInterest;

    CurlWrapper curlWrapper = CurlWrapper();
    std::string url = "https://enigmatic-scrubland-75073.herokuapp.com/users";
    curlWrapper.set_post_url(url);
    curlWrapper.set_get_buffer(readBuffer);
    curlWrapper.perform_request();
    reader.parse(readBuffer, root, true);
    std::cout << readBuffer << std::endl;

    Json::Value users = root["users"];
    CandidatesService candidatesService;
    for (unsigned int i = 0; i < users.size(); i++) {
        int interestInCommon = 0;
        std::string gender = fastWriter.write(users[i]["user"].get("gender", "male"));
        gender = gender.substr(1, gender.size()-3);
        if (genderOfMyInterest.compare(gender) == 0) {
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
            /* TODO: Cuando se solucione el problema en CandidatesService usar esto*/
//            if (candidatesService.filterCandidates(userData,user, interests,myArrayOfInterests)) {
//                user["interests"] = candidatesService.getArrayInterests();
//                arrayUsers.append(user);
//            }
            LOG(INFO) << "asdasds";
            for (unsigned int j = 0; j < interests.size(); j++) {
                arrayInterests.append(interests[j]["value"]);
                if (isInMyArrayOfInterest(interests[j]["value"], myArrayOfInterests)) {
                    interestInCommon++;
                }
            }
            user["interests"] = arrayInterests;
            if (interestInCommon >= 1) {
                arrayUsers.append(user);
            }
        }
    }
    event["candidates"] = arrayUsers;
    return event;
}

