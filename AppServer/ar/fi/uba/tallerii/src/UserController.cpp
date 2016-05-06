//
// Copyright 2016 FiUBA
//


#include "UserController.h"
#include <string>


UserController :: UserController(UserService userService) : userService(userService) {
}



void UserController :: handleLogin(RequestParser requestParser, Response response) {
    std::cout << "handle_login" << std::endl;
    std::string userId = requestParser.getResourceId();
    Json::FastWriter fastWriter;
    LOG(INFO) << "Proccesing login for user: '" << userId << "'";
    if (this->userService.isUserRegistered(userId)) {
        response.SetCode(200);
        Json::Value event = this->makeBodyForLoginResponse(userId);
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
    Json::Reader reader;
    Json::FastWriter fastWriter;
    bool parsingSuccessful = reader.parse(requestParser.getBody(), root, true);
    if (!parsingSuccessful) {
        std::cout  << "Failed to parse configuration\n";
        return;
    }

    Json::Value event = this->makeBodyForRegistrationPost(root);
    std::string data = fastWriter.write(event);
    CurlWrapper curlWrapper = CurlWrapper();
    std::string url = "https://enigmatic-scrubland-75073.herokuapp.com/users";
//    std::string url = "localhost:5000/users";
    curlWrapper.set_post_url(url);
    curlWrapper.set_post_data(data);
    bool res = curlWrapper.perform_request();
    curlWrapper.clean();
    LOG(INFO) << "Proccesing registration for user: ";
    if (res) {
        response.SetCode(200);
        response.SetBody("");
        response.Send();
        LOG(INFO) << "Registration succeeded";
    } else {
        response.SetCode(304);
        response.Send();
        LOG(INFO) << "Registration failed";
    }
}

void UserController::handleShowCandidates(RequestParser requestParser, Response response) {
    Json::FastWriter fastWriter;
    std::string userId = requestParser.getResourceId();
    LOG(INFO) << "Proccesing show candidates for user: '" << userId << "'";
    if (this->userService.isUserRegistered(userId)) {
        response.SetCode(200);
        Json::Value event = this->makeBodyForShowCandidatesResponse();
        std::string data = fastWriter.write(event);
        response.SetBody(data);
        response.Send();
        LOG(INFO) << "Show Candidates succeeded for user: '" << userId<< "'";
    } else {
        response.SetCode(304);
        response.Send();
        LOG(INFO) << "Show Candidates failed for user: '" << userId<< "'";
    }
}


void UserController :: handleUpdateUserInfo(RequestParser requestParser, Response response) {
    response.SetCode(200);
    response.SetBody("Not implemented");
    response.Send();
}

void UserController :: handleGetUserInfo(RequestParser requestParser, Response response) {
    response.SetCode(200);
    std::string userId = requestParser.getResourceId();
    response.SetBody(this->fakeResponseForUserInfo(userId));
    response.Send();
}

void UserController :: handleGetMatches(RequestParser requestParser, Response response) {
    response.SetCode(200);
    response.SetBody(this->fakeResponseForUserMatches());
    response.Send();
}

Json::Value UserController::makeBodyForLoginResponse(const std::string userId) {
    Json::Value event;
    std::string token = this->userService.getSecurityToken(userId);
    event["user"]["userId"] = userId;
    event["user"]["token"] = token;
    return event;
}

Json::Value UserController::makeBodyForShowCandidatesResponse() {
    Json::Value event;
    Json::Value arrayUsers(Json::arrayValue);
    std::string readBuffer;

    CurlWrapper curlWrapper = CurlWrapper();
    std::string url = "https://enigmatic-scrubland-75073.herokuapp.com/users";
    curlWrapper.set_post_url(url);
    // TODO(jasmina): ver si funciona el GET asi configurado.
    curlWrapper.set_get_buffer(readBuffer);
    bool res = curlWrapper.perform_request();
    curlWrapper.clean();
    std::cout << readBuffer << std::endl;
    // TODO(jasmina): armar el json que tenga adentro de candidates la lista de usuarios.
    // arrayUsers["algo"] = algo;
    event["candidates"] = arrayUsers;
    return event;
}

Json::Value UserController::makeBodyForRegistrationPost(Json::Value root) {
    std::string name = root.get("name", "").asString();
    std::string alias = root.get("alias", "").asString();
    std::string email = root.get("email", "").asString();
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
    Json::FastWriter fastWriter;
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
        curlWrapper.set_post_data(data);
        bool res = curlWrapper.perform_request();
        if (!res) {
            std::cout << "Failed to post new interests\n";
        }
        curlWrapper.clean();
    }
}

std::string UserController::fakeResponseForUserInfo(std::string userId) {
    Json::FastWriter fastWriter;
    Json::Value fakeInfo;
    fakeInfo["user_id"] = userId;
    fakeInfo["name"] = "NombreMock";
    fakeInfo["alias"] = "AliasMock";
    fakeInfo["age"] = "1";
    fakeInfo["gender"] = "male";
    fakeInfo["photo_profile"] = "";
    fakeInfo["interests"]= Json::arrayValue;
    Json::Value fakeLocation;
    fakeLocation["latitude"] = -121.45356;
    fakeLocation["longitude"] = 46.51119;
    fakeInfo["location"] = fakeLocation;
    return fastWriter.write(fakeInfo);
}

std::string UserController::fakeResponseForUserMatches() {
    Json::FastWriter fastWriter;
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
