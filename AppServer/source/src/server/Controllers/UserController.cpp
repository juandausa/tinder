//
// Copyright 2016 FiUBA
//

#include "UserController.h"
#include <time.h>
#include <string>


UserController :: UserController(UserService userService) : userService(userService) {
}

std::string validateTimeOrReturnDefault(std::string time) {
    struct tm convertedTime;;
    if (strptime(time.c_str(), "%d/%m/%Y", &convertedTime)) {
        return time;
    } else {
        return Constant::defaultBirthday;
    }
}

std::string validateGenderOrReturnDefault(std::string gender) {
    if (gender.compare(Constant::female) == 0) {
        return gender;
    }

    return Constant::male;
}

std::string calculateAge(std::string birthday) {
    struct tm convertedTime, localTime;
    time_t t = time(NULL);
    localtime_r(&t, &localTime);
    if (strptime(birthday.c_str(), "%d/%m/%Y", &convertedTime)) {
        return static_cast<std::ostringstream*>(&(std::ostringstream() << (localTime.tm_year - convertedTime.tm_year)))->str();
    }

    return Constant::defaultAge;
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
        return;
    }

    Json::Value event = this->makeBodyForRegistrationPost(root);
    std::string appUserId = root.get("user_id", "").asString();

    std::string data = fastWriter.write(event);
    postInterests(event);
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
        response.SetCode(304);
        response.Send();
        LOG(INFO) << "Registration failed";
    }
}

void UserController :: handleUpdateUserInfo(RequestParser requestParser, Response response) {
    std::string userId = requestParser.getResourceId();
    std::string externalUserId = this->userService.getExternalUserId(userId);
    LOG(INFO) << "Updating user info for user: '" << userId<< "'";
    std::string body = this->makeBodyUserInfoForUpdate(requestParser.getBody(), externalUserId);
    if ((userId.compare("") == 0) || (externalUserId.compare("") == 0) || (body.compare("") == 0)) {
        response.SetCode(400);
        response.SetBody("Bad Request.");
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
        } else {
            LOG(INFO) << "Requesting url: '" << url << " ' has respond: " << readBuffer;
            response.SetCode(200);
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
        std::cout << "fast: " << fastWriter.write(rootShared) << std::endl;
        std::string genderOfMyInterest = Constant::male;
        myArrayOfInterests = rootShared.get("interests", "");
        Json::Value body = makeBodyForShowCandidatesResponse(rootShared, genderOfMyInterest, myArrayOfInterests);
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

void UserController::handleGetMatches(RequestParser requestParser, Response response) {
    response.SetCode(200);
    response.SetBody(this->fakeResponseForUserMatches());
    response.Send();
}

void UserController::handleAddLike(RequestParser requestParser, Response response) {
    std::string fromUserId = requestParser.getResourceId();
    std::string toUserId = this->getUserTo(requestParser.getBody());
    LOG(INFO) << "Adding like from user: '" << fromUserId << "' to user: '" << toUserId << "'";
    if ((fromUserId.length() == 0) || (toUserId.length() == 0)) {
        response.SetCode(500);
        response.SetBody("Bad Request, no fromUserId or toUserId detected.");
        LOG(WARNING) << "Bad request for addLike. User: '" << fromUserId << "' or user: '" << toUserId << "'";
    } else if ((!userService.isUserRegistered(fromUserId)) || (!userService.isUserRegistered(toUserId))) {
        response.SetCode(500);
        response.SetBody("Bad Request, fromUserId '" + fromUserId + "' or toUserId '" + toUserId + " is not registered.");
        LOG(WARNING) << "Error for addLike. User: '" << fromUserId << "' or user: '" << toUserId << "' is not registered";
    } else {
        if (this->userService.addLike(fromUserId, toUserId)) {
            response.SetCode(200);
            LOG(INFO) << "Like from user: '" << fromUserId << "' to user: '" << toUserId << "' added";
        } else {
            response.SetCode(500);
            response.SetBody("Error for addLike, error on save.");
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
        response.SetBody("Bad Request, no fromUserId or toUserId detected.");
        LOG(WARNING) << "Bad request for addDislike. User: '" << fromUserId << "' or user: '" << toUserId << "'";
    } else if ((!userService.isUserRegistered(fromUserId)) || (!userService.isUserRegistered(toUserId))) {
        response.SetCode(500);
        response.SetBody("Bad Request, fromUserId '" + fromUserId + "' or toUserId '" + toUserId + " is not registered.");
        LOG(WARNING) << "Error for addDislike. User: '" << fromUserId << "' or user: '" << toUserId << "' is not registered";
    } else {
        if (this->userService.addDislike(fromUserId, toUserId)) {
            response.SetCode(200);
            LOG(INFO) << "Dislike from user: '" << fromUserId << "' to user: '" << toUserId << "' added";
        } else {
            response.SetCode(500);
            response.SetBody("Error for addDislike, error on save.");
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
    return event;
}

Json::Value UserController::makeBodyForRegistrationPost(Json::Value root) {
    std::string name = root.get("name", "").asString();
    std::string alias = root.get("alias", "").asString();
    std::string email = root.get("email", "").asString();
    std::string birthday = validateTimeOrReturnDefault(root.get("birthday", "").asString());
    std::string gender = validateGenderOrReturnDefault(root.get("gender", Constant::male).asString());
    std::string photo_profile = root.get("photo_profile", "").asString();
    Json::Value music = root["interests"]["music"];
    Json::Value movies = root["interests"]["movies"];
    Json::Value likes = root["interests"]["likes"];
    Json::Value television = root["interests"]["television"];
    Json::Value games = root["interests"]["games"];
    Json::Value books = root["interests"]["books"];

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

    user["interests"] = interests;
    event["user"] = user;
    return event;
}


void UserController::postInterests(Json::Value root) {
    std::string readBuffer;
    Json::Value interests = root["user"]["interests"];
    for (unsigned int i = 0; i < interests.size(); i++) {
        Json::Value postData;
        postData["interest"] = interests[i];
        postData["metadata"]["version"] = "0.1";
        postData["metadata"]["count"] = "1";
        std::string data = fastWriter.write(postData);
        std::cout << data << std::endl;
        CurlWrapper curlWrapper = CurlWrapper();
        std::string url = "https://enigmatic-scrubland-75073.herokuapp.com/interests";
//        std::string url = "10.1.86.224:5000/interests";
//        std::string url = "190.244.18.3:5000/interests";
        curlWrapper.set_post_url(url);
        curlWrapper.set_post_data(data, readBuffer);
        bool res = curlWrapper.perform_request();
        if (!res) {
            std::cout << "Failed to post new interests\n";
        }
        curlWrapper.clean();
    }
}

std::string UserController::fakeResponseForUserMatches() {
    Json::Value fakeInfo;
    Json::Value match, otherMatch;
    Json::Value message1, message2, message3, message4;
    match["user_id"] = "22";
    match["alias"] = "Josecito";
    match["age"] = "25";
    match["photo_profile"] = "";
    match["interests"] = Json::arrayValue;
    match["messages"] = Json::arrayValue;
    message1["0"] = "Hola, como estas?";
    message2["1"] = "Bien, y tu?";
    message3["1"] = "Que frio no?";
    match["messages"][0] = message1;
    match["messages"][1] = message2;
    match["messages"][2] = message3,
    otherMatch["user_id"] = "111";
    otherMatch["alias"] = "Juanita";
    otherMatch["age"] = "32";
    otherMatch["photo_profile"] = "";
    otherMatch["interests"] = Json::arrayValue;
    otherMatch["messages"] = Json::arrayValue;
    message4["0"] = "Hola, alguien ahi?";
    otherMatch["messages"][0] = message4;
    fakeInfo["matches"] = Json::arrayValue;
    fakeInfo["matches"][0] = match;
    fakeInfo["matches"][1] = otherMatch;
    return fastWriter.write(fakeInfo);
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

std::string UserController::getUserTo(const std::string body) {
    Json::Value userInfo;
    bool parsingSuccessful = reader.parse(body, userInfo, true);
    if (!parsingSuccessful) {
        return "";
    }

    return userInfo.get("to_user_id", "").asString();
}

Json::Value UserController::makeBodyForShowCandidatesResponse(Json::Value userData, std::string genderOfMyInterest,
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
