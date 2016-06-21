//
// Copyright 2016 FiUBA
//

#include "UpdateUserInfoController.h"
#include <string>

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


void UpdateUserInfoController::operation(Request &request, Response &response) {
    std::string userId = request.getResourceId();
    std::string externalUserId = this->userService.getExternalUserId(userId);
    LOG(INFO) << "Updating user info for user: '" << userId << "'";
    std::string body = this->makeBodyUserInfoForUpdate(request.getBody(), externalUserId);
    if ((userId.compare("") == 0) || (externalUserId.compare("") == 0) || (body.compare("") == 0)) {
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
            LOG(WARNING) << "Error requesting url: '" << url << "' whith body: " << body << ". Response: " <<
            readBuffer;
            response.SetCode(500);
        } else {
            LOG(INFO) << "Requesting url: '" << url << " ' has respond: " << readBuffer;
            response.SetCode(200);
        }
        curlWrapper.clean();
    }

    response.Send();
}

Json::Value UpdateUserInfoController::makeBodyForRegistrationPost(Json::Value root) {
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

std::string UpdateUserInfoController::makeBodyUserInfoForUpdate(const std::string info, const std::string userId) {
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
    } catch (std::exception const &e) {
        LOG(WARNING) << "Error parsing user extrenal id, which is: '" << userId << "'";
        return "";
    }
    parsedUserInfo["metadata"]["version"] = "0.1";
    return fastWriter.write(parsedUserInfo);
}
