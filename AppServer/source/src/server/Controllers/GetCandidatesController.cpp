//
// Copyright 2016 FiUBA
//

#include "GetCandidatesController.h"
#include <string>

bool GetCandidatesController::isInMyArrayOfInterest(Json::Value interest, Json::Value myArrayOfInterests) {
    std::string theirInterest = fastWriter.write(interest);
    if (theirInterest.compare("") != 0) {
        theirInterest = theirInterest.substr(1, theirInterest.size() - 3);
    }
    // Para no tener en cuenta si tiene mismas preferencias de gender:
    if (theirInterest.compare("male") == 0 || theirInterest.compare("female") == 0 || theirInterest.compare("male|female") == 0){
        return false;
    }
    for (unsigned int i = 0; i < myArrayOfInterests.size(); i++) {
        std::string myInterest = fastWriter.write(myArrayOfInterests[i]);
        myInterest = myInterest.substr(1, myInterest.size() - 3);
        if (theirInterest.compare(myInterest) == 0) {
            return true;
        }
    }
    return false;
}

void GetCandidatesController::operation(Request &request, Response &response) {
    Json::Value rootShared;
    Json::Value myArrayOfInterests;
    std::string userId = request.getResourceId();
    LOG(INFO) << "Proccesing show candidates for user: '" << userId << "'";
    if (this->userService.isUserRegistered(userId)) {
        std::string responseBody = getUserInfoWithOutResponse(request, response);
        bool parsingSuccessful = reader.parse(responseBody, rootShared, true);
        if (!parsingSuccessful) {
            std::cout << "Error parsing result" << std::endl;
        }
        std::string myGender = fastWriter.write(rootShared.get("sex", Constant::male));
        myGender = myGender.substr(1, myGender.size() - 3);
        myArrayOfInterests = rootShared.get("interests", "");
        std::string genderOfMyInterest = this->userService.getShowGender(userId);
        Json::Value body = makeBodyForShowCandidatesResponse(rootShared, myGender, genderOfMyInterest,
                                                             myArrayOfInterests);
        std::string sendBody = fastWriter.write(body);
        if ((sendBody.compare("null\n") == 0)) {
            sendBody = "{}";
        }
        response.SetCode(200);
        response.SetBody(sendBody);
        response.Send();
    } else {
        response.SetCode(400);
        response.SetBody("{}");
        response.Send();
        LOG(INFO) << "Show Candidates failed for user: '" << userId << "'";
    }
}

std::string GetCandidatesController::getUserInfoWithOutResponse(Request &request, Response &response) {
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

    return body;
}


std::string GetCandidatesController::makeBodyForUserInfoResponse(const std::string appUserId,
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
    std::string birthday = Converter::validateTimeOrReturnDefault(rootShared["user"].get("birthday", "").asString());
    rootApp["birthday"] = birthday;
    rootApp["age"] = Converter::calculateAge(birthday);
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

Json::Value GetCandidatesController::makeBodyForShowCandidatesResponse(Json::Value userData, std::string myGender,
                                                                       std::string genderOfMyInterest,
                                                                       Json::Value myArrayOfInterests) {
    Json::Value event;
    Json::Value root;
    Json::Value arrayUsers;
    std::string readBuffer;
    std::string genderOfInterest;
    std::unordered_map<std::string, std::string> usersLikes = std::unordered_map<std::string, std::string>();
    std::unordered_map<std::string, Json::Value> usersData = std::unordered_map<std::string, Json::Value>();

    CurlWrapper curlWrapper = CurlWrapper();
    std::string url = "https://enigmatic-scrubland-75073.herokuapp.com/users";
    curlWrapper.set_post_url(url);
    curlWrapper.set_get_buffer(readBuffer);
    curlWrapper.perform_request();
    reader.parse(readBuffer, root, true);

    Json::Value users = root["users"];
    CandidatesService candidatesService;
    for (unsigned int i = 0; i < users.size(); i++) {
        int interestInCommon = 0;
        std::string gender = fastWriter.write(users[i]["user"].get("gender", "male"));
        gender = gender.substr(1, gender.size() - 3);
        std::string sharedUserId = fastWriter.write(users[i]["user"].get("id", ""));

        sharedUserId = sharedUserId.substr(0, sharedUserId.size() - 1);
        std::string appUserId = this->userService.getAppUserId(sharedUserId);
        if (genderOfMyInterest.compare("male|female") == 0 ||
                (genderOfMyInterest.compare(gender) == 0 /*&& genderOfTheirInterest.compare(myGender) == 0) ||
                (genderOfMyInterest.compare(gender) == 0 && genderOfTheirInterest.compare("male|female") == 0)*/)) {
            Json::Value user;
            Json::Value arrayInterests;
            user["user_id"] = appUserId;
            user["alias"] = users[i]["user"].get("alias", "");
            std::string birthday = Converter::validateTimeOrReturnDefault(
                    users[i]["user"].get("birthday", "").asString());
            user["birthday"] = birthday;
            user["age"] = Converter::calculateAge(birthday);
            user["gender"] = Converter::validateGenderOrReturnDefault(users[i]["user"].get("gender", "").asString());
            user["photo_profile"] = url + "/" + sharedUserId + "/photo";
            Json::Value interests = users[i]["user"].get("interests", "");
            /* TODO: Cuando se solucione el problema en CandidatesService usar esto*/
//            if (candidatesService.filterCandidates(userData,user, interests,myArrayOfInterests)) {
//                user["interests"] = candidatesService.getArrayInterests();
//                arrayUsers.append(user);
//            }
            for (unsigned int j = 0; j < interests.size(); j++) {
                arrayInterests.append(interests[j]["value"]);
                if (isInMyArrayOfInterest(interests[j]["value"], myArrayOfInterests)) {
                    interestInCommon++;
                }
            }
            user["interests"] = arrayInterests;
            if (interestInCommon >= 1) {
                usersData.emplace(sharedUserId, user);
                usersLikes.emplace(sharedUserId, this->userService.getCountLikes(sharedUserId));
            }
        }
    }
    onePercentRule(usersData, usersLikes);
    fillUsersArray(usersData, arrayUsers);
    if (arrayUsers.size() != 0) {
        event["candidates"] = arrayUsers;
    }
    return event;
}

std::string GetCandidatesController::genderOfMyPreference(Json::Value myArrayOfInterests) {
    bool male = false;
    bool female = false;
    for (unsigned int i = 0; i < myArrayOfInterests.size(); i++) {
        if ((fastWriter.write(myArrayOfInterests[i])).compare("male")) {
            male = true;
        }
        if ((fastWriter.write(myArrayOfInterests[i])).compare("female")) {
            female = true;
        }
    }
    if (male && female) {
        return "male|female";
    } else if (female) {
        return "female";
    } else {
        return "male";
    }
}

void GetCandidatesController::onePercentRule(std::unordered_map<std::string, Json::Value> &usersData,
                                             std::unordered_map<std::string, std::string> &usersLikes) {
    if (usersData.size() <= 1) {
        return;
    }
    std::unordered_map<std::string, std::string>::const_iterator iter;
    std::unordered_map<std::string, Json::Value>::iterator iterData;
    int max = 0;
    std::string maxUserId = "";
    for (iter = usersLikes.begin(); iter != usersLikes.end(); ++iter) {
        if (((*iter).second).compare("") != 0) {
            if (atoi(((*iter).second).c_str()) >= max) {
                max = atoi(((*iter).second).c_str());
                maxUserId = (*iter).first;
            }
        }
    }
    if (maxUserId.compare("") != 0) {
        iterData = usersData.find(maxUserId);
        usersData.erase(iterData);
    }
}

void GetCandidatesController::fillUsersArray(std::unordered_map<std::string, Json::Value> &usersData,
                                             Json::Value &arrayUsers) {
    std::unordered_map<std::string, Json::Value>::const_iterator iter;
    for (iter = usersData.begin(); iter != usersData.end(); ++iter) {
        arrayUsers.append((*iter).second);
    }
}
