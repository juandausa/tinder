//
// Copyright 2016 FiUBA
//

#include "UserController.h"
#include "Converter.h"
#include <time.h>
#include <string>
#include <unordered_map>
#include <thread>
#include <vector>

UserController :: UserController(UserService userService) : userService(userService) {
    postInterestsThread = NULL;
}

UserController :: ~UserController() {
    if (postInterestsThread) {
        delete postInterestsThread;
    }
    postInterestsThread = NULL;
}

void UserController :: handleLogin(RequestParser requestParser, Response response) {
    std::cout << "handle_login" << std::endl;
    std::string userId = requestParser.getResourceId();
    LOG(INFO) << "Proccesing login for user: '" << userId << "'";
    if (this->userService.isUserRegistered(userId)) {
        response.SetCode(200);
        Json::Value event = this->makeBodyAndTokenForLoginResponse(userId);
        std::string data = fastWriter.write(event);
        response.SetBody(data);
        response.Send();
        LOG(INFO) << "Login succeeded for user: '" << userId<< "'";
    } else {
        response.SetCode(304);
        response.Send();
        LOG(INFO) << "Login failed for user: '" << userId<< "'";
    }
}

void UserController::handleRegistration(RequestParser requestParser, Response response) {
    std::cout << "handleRegistration" << std::endl;;
    Json::Value root;
    Json::Value responseShared;
    std::string readBuffer;

    bool parsingSuccessful = reader.parse(requestParser.getBody(), root, true);
    if (!parsingSuccessful) {
        std::cout  << "Failed to parse configuration\n";
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
        response.Send();
    }

    Json::Value event = this->makeBodyForRegistrationPost(root);
    std::string appUserId = root.get("user_id", "").asString();
    std::string data = fastWriter.write(event);
    // Lanzo thread de posteo de intereses
    postInterestsThread = new std::thread(&UserController::postInterests, this, event);

    CurlWrapper curlWrapper = CurlWrapper();
    std::string url = "https://enigmatic-scrubland-75073.herokuapp.com/users";
//    std::string url = "localhost:5000/users";
    curlWrapper.set_post_url(url);
    curlWrapper.set_post_data(data, readBuffer);
    bool res = curlWrapper.perform_request();
    reader.parse(readBuffer, responseShared, true);
    Json::Value sharedUserId = responseShared["user"].get("id", "");
    std::string sharedUserIdString = fastWriter.write(sharedUserId);
    sharedUserIdString.erase(sharedUserIdString.size() - 1);

    LOG(INFO) << "Proccesing registration for user: ";
    if (res) {
        Json::Value response_body = this->makeBodyAndTokenForRegistrationResponse(appUserId);
        this->userService.registerUser(appUserId, sharedUserIdString);
        std::string body = fastWriter.write(response_body);
        response.SetCode(200);
        response.SetBody(body);
        response.Send();
        LOG(INFO) << "Registration succeeded";
    } else {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
        response.Send();
        LOG(INFO) << "Registration failed";
    }
    postInterestsThread->detach();
    std::cout << "Thread Join" << std::endl;
}

void UserController :: handleUpdateUserInfo(RequestParser requestParser, Response response) {
    std::string userId = requestParser.getResourceId();
    std::string externalUserId = this->userService.getExternalUserId(userId);
    LOG(INFO) << "Updating user info for user: '" << userId<< "'";
    std::string body = this->makeBodyUserInfoForUpdate(requestParser.getBody(), externalUserId);
    if ((userId.compare("") == 0) || (externalUserId.compare("") == 0) || (body.compare("") == 0)) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
    } else {
        std::string url = "http://enigmatic-scrubland-75073.herokuapp.com/users/" + externalUserId;
        LOG(INFO) << "Requesting url: " << url;
        CurlWrapper curlWrapper = CurlWrapper();
        std::string readBuffer;
        curlWrapper.set_post_url(url);
        curlWrapper.set_put_data(body, readBuffer);
        bool requestResult = curlWrapper.perform_request();
        if (!requestResult) {
            LOG(WARNING) << "Error requesting url: '" << url << "' whith body: " << body << ". Response: " << readBuffer;
            response.SetCode(500);
            response.SetBody(this->getErrorResponseBody());
        } else {
            LOG(INFO) << "Requesting url: '" << url << " ' has respond: " << readBuffer;
            response.SetCode(200);
            response.SetBody(this->getSucceedResponseBody());
        }
        curlWrapper.clean();
    }

    response.Send();
}

std::string UserController :: handleGetUserInfo(RequestParser requestParser, Response response, bool send) {
    std::string readBuffer;
    std::string body;
    std::string userId = requestParser.getResourceId();
    std::string externalUserId = this->userService.getExternalUserId(userId);
    LOG(INFO) << "Retrieving user info for user: '" << userId<< "'";
    if ((userId.compare("") == 0) || (externalUserId.compare("") == 0)) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
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
            response.SetBody(this->getErrorResponseBody());
        }
    }
    if (send) {
        response.Send();
    }
    return body;
}

void UserController :: handleGetCandidates(RequestParser requestParser, Response response) {
    Json::Value rootShared;
    Json::Value myArrayOfInterests;
    std::string userId = requestParser.getResourceId();
    LOG(INFO) << "Proccesing show candidates for user: '" << userId << "'";
    if (this->userService.isUserRegistered(userId)) {
        std::string responseBody = handleGetUserInfo(requestParser, response, false);
        bool parsingSuccessful = reader.parse(responseBody, rootShared, true);
        if (!parsingSuccessful) {
            std::cout << "Error parsing result" << std::endl;
        }
        std::string myGender = fastWriter.write(rootShared.get("gender", "male"));
        myGender = myGender.substr(1, myGender.size()-3);
        myArrayOfInterests = rootShared.get("interests", "");
        std::string genderOfMyInterest = this->userService.getShowGender(userId);
        Json::Value body = makeBodyForShowCandidatesResponse(rootShared, myGender, genderOfMyInterest, myArrayOfInterests);
        std::string sendBody = fastWriter.write(body);
        if (sendBody.compare("null\n") == 0) {
            sendBody = "{}";
        }
        response.SetCode(200);
        response.SetBody(sendBody);
        response.Send();
    } else {
        response.SetCode(400);
        response.SetBody("{}");
        response.Send();
        LOG(INFO) << "Show Candidates failed for user: '" << userId<< "'";
    }
}

void UserController::handleAddLike(RequestParser requestParser, Response response) {
    std::string fromUserId = requestParser.getResourceId();
    std::string toUserId = this->getUserTo(requestParser.getBody());
    LOG(INFO) << "Adding like from user: '" << fromUserId << "' to user: '" << toUserId << "'";
    if ((fromUserId.length() == 0) || (toUserId.length() == 0)) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
        LOG(WARNING) << "Bad request for addLike. User: '" << fromUserId << "' or user: '" << toUserId << "'";
    } else if ((!userService.isUserRegistered(fromUserId)) || (!userService.isUserRegistered(toUserId))) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
        LOG(WARNING) << "Error for addLike. User: '" << fromUserId << "' or user: '" << toUserId << "' is not registered";
    } else {
        if (this->userService.addLike(fromUserId, toUserId)) {
            response.SetCode(200);
            response.SetBody(this->getSucceedResponseBody());
            LOG(INFO) << "Like from user: '" << fromUserId << "' to user: '" << toUserId << "' added";
        } else {
            response.SetCode(500);
            response.SetBody(this->getErrorResponseBody());
            LOG(WARNING) << "Error for addLike, error on save. From user: '" << fromUserId << "' to user: '" << toUserId << "'";
        }
    }

    response.Send();
}

void UserController::handleAddDislike(RequestParser requestParser, Response response) {
    std::string fromUserId = requestParser.getResourceId();
    std::string toUserId = this->getUserTo(requestParser.getBody());
    LOG(INFO) << "Adding dislike from user: '" << fromUserId << "' to user: '" << toUserId << "'";
    if ((fromUserId.length() == 0) || (toUserId.length() == 0)) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
        LOG(WARNING) << "Bad request for addDislike. User: '" << fromUserId << "' or user: '" << toUserId << "'";
    } else if ((!userService.isUserRegistered(fromUserId)) || (!userService.isUserRegistered(toUserId))) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
        LOG(WARNING) << "Error for addDislike. User: '" << fromUserId << "' or user: '" << toUserId << "' is not registered";
    } else {
        if (this->userService.addDislike(fromUserId, toUserId)) {
            response.SetCode(200);
            response.SetBody(this->getSucceedResponseBody());
            LOG(INFO) << "Dislike from user: '" << fromUserId << "' to user: '" << toUserId << "' added";
        } else {
            response.SetCode(500);
            response.SetBody(this->getErrorResponseBody());
            LOG(WARNING) << "Error for addDislike, error on save. From user: '" << fromUserId << "' to user: '" << toUserId << "'";
        }
    }

    response.Send();
}

Json::Value UserController::makeBodyAndTokenForLoginResponse(const std::string userId) {
    Json::Value event;
    std::string token = this->userService.getSecurityToken(userId);
    event["user"]["token"] = token;
    return event;
}

Json::Value UserController::makeBodyAndTokenForRegistrationResponse(const std::string userId) {
    Json::Value event;
    std::string token = this->userService.getSecurityToken(userId);
    event["user"]["userId"] = userId;
    event["user"]["token"] = token;
    event["status_code"] = 200;
    return event;
}

Json::Value UserController::makeBodyForRegistrationPost(Json::Value root) {
    std::string appUserId = root.get("user_id", "").asString();
    std::string name = root.get("name", "").asString();
    std::string alias = root.get("alias", "").asString();
    std::string email = root.get("email", "").asString();
    std::string birthday = Converter::validateTimeOrReturnDefault(root.get("birthday", "").asString());
    std::string gender = Converter::validateGenderOrReturnDefault(root.get("gender", Constant::male).asString());
    std::string photo_profile = root.get("photo_profile", "").asString();
    Json::Value music = root["interests"]["music"];
    Json::Value movies = root["interests"]["movies"];
    Json::Value likes = root["interests"]["likes"];
    Json::Value television = root["interests"]["television"];
    Json::Value games = root["interests"]["games"];
    Json::Value books = root["interests"]["books"];
    std::string discovering_distance = fastWriter.write(root.get("discovering_distance", "0"));
    this->userService.setDiscoveringDistance(appUserId, discovering_distance);
    this->userService.setShowGender(appUserId, "male|female");

    double latitude = root["location"].get("latitude", 0).asDouble();
    double longitude = root["location"].get("longitude", 0).asDouble();

    Json::Value event;
    Json::Value user;
    Json::Value interest;
    Json::Value interests;

    user["name"] = name;
    user["alias"] = alias;
    user["email"] = email;
    user["birthday"] = birthday;
    user["gender"] = gender;
    user["photo_profile"] = photo_profile;
    user["location"]["latitude"] = latitude;
    user["location"]["longitude"] = longitude;

    for (unsigned int i = 0; i < music.size(); ++i) {
        interest["category"] = "music";
        interest["value"] = music[i];
        interests.append(interest);
    }
    for (unsigned int i = 0; i < movies.size(); ++i) {
        interest["category"] = "movies";
        interest["value"] = movies[i];
        interests.append(interest);
    }
    for (unsigned int i = 0; i < likes.size(); ++i) {
        interest["category"] = "likes";
        interest["value"] = likes[i];
        interests.append(interest);
    }
    for (unsigned int i = 0; i < television.size(); ++i) {
        interest["category"] = "television";
        interest["value"] = television[i];
        interests.append(interest);
    }
    for (unsigned int i = 0; i < games.size(); ++i) {
        interest["category"] = "games";
        interest["value"] = games[i];
        interests.append(interest);
    }
    for (unsigned int i = 0; i < books.size(); ++i) {
        interest["category"] = "books";
        interest["value"] = books[i];
        interests.append(interest);
    }

    interest["category"] = "gender";
    interest["value"] = "female";
    interests.append(interest);
    interest["category"] = "gender";
    interest["value"] = "male";
    interests.append(interest);

    user["interests"] = interests;
    event["user"] = user;
    return event;
}

void UserController::postInterests(Json::Value root) {
    std::cout << "Posting Interest" << std::endl;
    std::vector<std::string*> readBuffers;
    std::vector<CurlWrapper*> curlWrappers;
    std::vector<Json::FastWriter*> writers;
    Json::Value original_interests = root["user"]["interests"];
    Json::Value interests(original_interests);
    CurlWrapper curlWrapper;
    std::string url = "https://enigmatic-scrubland-75073.herokuapp.com/interests";
    // std::string url = "10.1.86.224:5000/interests";
    // std::string url = "190.244.18.3:5000/interests";
    for (unsigned int i = 0; i < interests.size(); i++) {
        Json::Value postData;
        postData["interest"] = interests[i];
        postData["metadata"]["version"] = "0.1";
        postData["metadata"]["count"] = "1";
        Json::FastWriter* writer = new Json::FastWriter();
        std::string data = writer->write(postData);
        writers.push_back(writer);
        CurlWrapper* curlWrapper = new CurlWrapper();
        std::string url = "https://enigmatic-scrubland-75073.herokuapp.com/interests";
//        std::string url = "10.1.86.224:5000/interests";
//        std::string url = "190.244.18.3:5000/interests";
        curlWrapper->set_post_url(url);
        std::string* readBuffer = new std::string();
        readBuffers.push_back(readBuffer);
        curlWrapper->set_post_data(data, readBuffer);
        bool res = curlWrapper->perform_request();
        if (!res) {
            std::cout << "Failed to post new interests\n";
            return;
        }
        curlWrappers.push_back(curlWrapper);
    }

    for (size_t i = 0; i < readBuffers.size(); i++) {
        // std::string* readBuff = readBuffers.back();
        // readBuffers.pop_back();
        CurlWrapper* wrapper = curlWrappers.back();
        curlWrappers.pop_back();
        wrapper->clean();
        // delete readBuff;
        delete wrapper;
        // FALTA DESTRUIR LOS WRITERS
    }
}

std::string UserController :: makeBodyUserInfoForUpdate(const std::string info, const std::string userId) {
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(info, root, true);
    if (!parsingSuccessful) {
        return "";
    }

    Json::Value parsedUserInfo;
    parsedUserInfo = this->makeBodyForRegistrationPost(root);
    try {
        parsedUserInfo["user"]["id"] = std::atoi(userId.c_str());
    } catch(std::exception const & e) {
        LOG(WARNING) << "Error parsing user extrenal id, which is: '" << userId << "'";
        return "";
    }
    parsedUserInfo["metadata"]["version"] = "0.1";
    return fastWriter.write(parsedUserInfo);
}

std::string UserController :: makeBodyForUserInfoResponse(const std::string appUserId, const std::string userInfo) {
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

std::string UserController::getUserTo(const std::string body) {
    Json::Value userInfo;
    bool parsingSuccessful = reader.parse(body, userInfo, true);
    if (!parsingSuccessful) {
        return "";
    }

    return userInfo.get("to_user_id", "").asString();
}

Json::Value UserController::makeBodyForShowCandidatesResponse(Json::Value userData, std::string myGender,
                                                              std::string genderOfMyInterest,
                                                              Json::Value myArrayOfInterests) {
    Json::Value event;
    Json::Value root;
    Json::Value arrayUsers;
    std::string readBuffer;
    std::string genderOfInterest;
    std::unordered_map<string, string> usersLikes = std::unordered_map<string, string>();
    std::unordered_map<string, Json::Value> usersData = std::unordered_map<string, Json::Value>();

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
        gender = gender.substr(1, gender.size()-3);
        std::string sharedUserId = fastWriter.write(users[i]["user"].get("id", ""));
        sharedUserId = sharedUserId.substr(0, sharedUserId.size()-1);
        std::string appUserId = this->userService.getAppUserId(sharedUserId);
        std::string genderOfTheirInterest = this->userService.getShowGender(appUserId);
        if (genderOfMyInterest.compare("male|female") == 0 ||
                (genderOfMyInterest.compare(gender) == 0 && genderOfTheirInterest.compare(myGender) == 0) ||
                (genderOfMyInterest.compare(gender) == 0 && genderOfTheirInterest.compare("male|female") == 0)) {
            Json::Value user;
            Json::Value arrayInterests;
            user["user_id"] = appUserId;
            user["alias"] = users[i]["user"].get("alias", "");
            std::string birthday = Converter::validateTimeOrReturnDefault(users[i]["user"].get("birthday", "").asString());
            user["birthday"] = birthday;
            user["age"] = Converter::calculateAge(birthday);
            user["gender"] = Converter::validateGenderOrReturnDefault(users[i]["user"].get("gender", "").asString());
            std::cout << fastWriter.write(users[i]["user"]) << std::endl;
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

bool UserController::isInMyArrayOfInterest(Json::Value interest, Json::Value myArrayOfInterests) {
    std::string theirInterest = fastWriter.write(interest);
    for (unsigned int i = 0; i < myArrayOfInterests.size(); i++) {
        std::string myInterest = fastWriter.write(myArrayOfInterests[i]);
        if (theirInterest.compare(myInterest) == 0) {
            return true;
        }
    }
    return false;
}

std::string UserController::genderOfMyPreference(Json::Value myArrayOfInterests) {
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

void UserController::onePercentRule(std::unordered_map<string, Json::Value> &usersData, std::unordered_map<string, string> &usersLikes) {
    if (usersData.size() <= 1) {
        return;
    }
    std::unordered_map<string, string>::const_iterator iter;
    std::unordered_map<string, Json::Value>::iterator iterData;
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

void UserController::fillUsersArray(std::unordered_map<string, Json::Value> &usersData, Json::Value &arrayUsers) {
    std::unordered_map<string, Json::Value>::const_iterator iter;
    for (iter = usersData.begin(); iter != usersData.end(); ++iter) {
        arrayUsers.append((*iter).second);
    }
}

std::string UserController::getErrorResponseBody() {
    Json::Value errorResponse;
    errorResponse["status_code"] = 500;
    return this->fastWriter.write(errorResponse);
}

std::string UserController::getSucceedResponseBody() {
    Json::Value succeedResponse;
    succeedResponse["status_code"] = 200;
    return this->fastWriter.write(succeedResponse);
}


void UserController::handle_update_filters(RequestParser requestParser, Response response) {
    std::string userId = requestParser.getResourceId();
    std::string body = requestParser.getBody();
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(body, root, true);
    if (!parsingSuccessful) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
    } else {
        if (this->userService.update_filters(userId, body)) {
            response.SetCode(200);
            response.SetBody(this->getSucceedResponseBody());
        } else {
            response.SetCode(500);
            response.SetBody(this->getErrorResponseBody());
        }
    }
    response.Send();
}
