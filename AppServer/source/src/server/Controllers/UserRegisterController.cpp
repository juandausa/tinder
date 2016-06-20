#include "UserRegisterController.h"

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

void UserRegisterController::operation(Request &request, Response &response) {
    std::cout << "handleRegistration" << std::endl;;
    Json::Value root;
    Json::Value responseShared;
    std::string readBuffer;
    bool parsingSuccessful = reader.parse(request.getBody(), root, true);
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

Json::Value UserRegisterController::makeBodyForRegistrationPost(Json::Value root) {
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

Json::Value UserRegisterController::makeBodyAndTokenForRegistrationResponse(const std::string userId) {
    Json::Value event;
    std::string token = this->userService.getSecurityToken(userId);
    event["user"]["userId"] = userId;
    event["user"]["token"] = token;
    return event;
}

void UserRegisterController::postInterests(Json::Value root) {
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
