//
// Copyright 2016 FiUBA
//

#include <jsoncpp/json/json.h>
#include "UserController.h"
#include "CurlWrapper.h"
#include "Response.h"
#include "DataBase.h"
#include <glog/logging.h>


UserController :: UserController(UserService userService) : userService(userService) {
}

/* Private methods declaration */
Json::Value make_body_for_login_response(const std::string user_id, const std::string token);
Json::Value make_body_for_registration_post(Json::Value root);
Json::Value create_json_array(Json::Value array);

/* End private methods */

void UserController :: handle_login(struct mg_connection *nc, struct http_message *hm, Response response) {
    std::string userId;
    Json::Value root;
    Json::Reader reader;
    Json::FastWriter fastWriter;
    mg_get_http_var(&hm->query_string, "userId",(char*)userId.c_str(), sizeof(userId));
    LOG(INFO) << "Proccesing login for user: '" << userId << "'";
    if (this->userService.isUserRegistered(userId)) {
        response.SetCode(200);
        std::string token = userService.getSecurityToken(userId);
        Json::Value event = make_body_for_login_response(userId, token);

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

void UserController :: handle_registration(struct mg_connection *nc, struct http_message *hm, Response response) {
    Json::Value root;
    Json::Reader reader;
    Json::FastWriter fastWriter;
    bool parsingSuccessful = reader.parse(hm->body.p, root, true);
    if (!parsingSuccessful) {
        std::cout  << "Failed to parse configuration\n";
        return;
    }

    Json::Value event = make_body_for_registration_post(root);
    std::string data = fastWriter.write(event);
    CurlWrapper curlWrapper = CurlWrapper();
//    std::string url = "https://enigmatic-scrubland-75073.herokuapp.com/users";
    std::string url = "localhost:5000/users";
    curlWrapper.set_post_url(url);
    curlWrapper.set_post_data(data);
    bool res = curlWrapper.perform_request();
    curlWrapper.clean();
    LOG(INFO) << "Proccesing registration for user: ";
    if (res) {
        response.SetCode(200);
        response.SetBody("");
        response.Send();
        LOG(INFO) << "Login succeeded";
    } else {
        response.SetCode(304);
        response.Send();
        LOG(INFO) << "Login failed";
    }
}

void UserController :: handle_update_user_info(struct mg_connection *nc, struct http_message *hm, Response response) {
    response.SetCode(200);
    response.SetBody("Not implemented");
    response.Send();
}

void UserController :: handle_get_user_info(struct mg_connection *nc, struct http_message *hm, Response response) {
    response.SetCode(200);
    response.SetBody("Not implemented");
    response.Send();
}

Json::Value make_body_for_login_response(const std::string user_id, const std::string token) {
    Json::Value event;
    return event;
}

Json::Value make_body_for_registration_post(Json::Value root) {
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

    for (unsigned int i = 0; i < music.size(); ++i){
        interest["category"] = "music";
        interest["value"] = music[i];
        interests.append(interest);
    }
    for (unsigned int i = 0; i < movies.size(); ++i){
        interest["category"] = "movies";
        interest["value"] = movies[i];
        interests.append(interest);
    }
    for (unsigned int i = 0; i < likes.size(); ++i){
        interest["category"] = "likes";
        interest["value"] = likes[i];
        interests.append(interest);
    }
    for (unsigned int i = 0; i < television.size(); ++i){
        interest["category"] = "television";
        interest["value"] = television[i];
        interests.append(interest);
    }
    for (unsigned int i = 0; i < games.size(); ++i){
        interest["category"] = "games";
        interest["value"] = games[i];
        interests.append(interest);
    }
    for (unsigned int i = 0; i < books.size(); ++i){
        interest["category"] = "books";
        interest["value"] = books[i];
        interests.append(interest);
    }

    user["interests"] = interests;
    event["user"] = user;
    return event;
}


