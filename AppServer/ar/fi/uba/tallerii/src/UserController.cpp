//
// Copyright 2016 FiUBA
//

#include <jsoncpp/json/json.h>
#include "UserController.h"
#include "CurlWrapper.h"
#include <jsoncpp/json/json.h>
#include "Response.h"
#include "DataBase.h"
#include <glog/logging.h>
#include <string>


UserController :: UserController(UserService user_service) : user_service(user_service) {
}

/* Private methods declaration */
std::string make_body_for_login_response(const std::string user_id, const std::string token);
Json::Value create_json_array(Json::Value array);

/* End private methods */

void UserController :: handle_login(struct mg_connection *nc, struct http_message *hm, Response response) {
    char user_id[255];
    mg_get_http_var(&hm->query_string, "userId", user_id, sizeof(user_id));
    LOG(INFO) << "Proccesing login for user: '" << user_id << "'";
    if (this->user_service.is_user_registered(user_id)) {
        response.SetCode(200);
        std::string token = user_service.get_securiry_token(user_id);
        response.SetBody(make_body_for_login_response(user_id, token));
        response.Send();
        LOG(INFO) << "Login succeeded for user: '" << user_id << "'";
    } else {
        response.SetCode(304);
        response.Send();
        LOG(INFO) << "Login failed for user: '" << user_id << "'";
    }
}

void UserController :: handle_registration(struct mg_connection *nc, struct http_message *hm, Response response) {
    Json::Value root;
    Json::Reader reader;

    bool parsingSuccessful = reader.parse(hm->body.p, root, true);
    if (!parsingSuccessful) {
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration\n";
//        return;
    }

    std::string user_id = root.get("user_id", "").asString();
    std::string name = root.get("name", "").asString();
    std::string birthday = root.get("birthday", "").asString();
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


    std::cout << music << std::endl;
    std::cout << music.size() << std::endl;
    std::cout << music[0] << std::endl;
    std::cout << music[1] << std::endl;

    Json::Value event;
    Json::Value music_array(Json::arrayValue);
    Json::Value movies_array(Json::arrayValue);
    Json::Value likes_array(Json::arrayValue);
    Json::Value television_array(Json::arrayValue);
    Json::Value games_array(Json::arrayValue);
    Json::Value books_array(Json::arrayValue);

    music_array.append(Json::Value("radiohead"));
    music_array.append(Json::Value("eminem"));
    movies_array.append(Json::Value("Robocop"));
    likes_array.append(Json::Value("Robots"));
    television_array.append(Json::Value("the simpsons"));
    games_array.append(Json::Value("Counter Strike"));
    books_array.append(Json::Value("Steve Jobs"));

    event["user_id"] = user_id;
    event["name"] = name;
    event["birthday"] = birthday;
    event["alias"] = alias;
    event["email"] = email;
    event["photo_profile"] = photo_profile;
    event["interest"]["music"] = music_array;
    event["interest"]["movies"] = movies_array;
    event["interest"]["likes"] = likes_array;
    event["interest"]["television"] = television_array;
    event["interest"]["games"] = games_array;
    event["interest"]["books"] = books_array;
    event["location"]["latitude"] = latitude;
    event["location"]["longitude"] = longitude;
    std::cout << event << std::endl;

//    event["user_id"] = user_id;
//    event["name"] = name;
//    event["birthday"] = birthday;
//    event["alias"] = alias;
//    event["email"] = email;
//    event["photo_profile"] = photo_profile;
//    event["interest"]["music"] = create_json_array(music);
//    event["interest"]["movies"] = create_json_array(movies);
//    event["interest"]["likes"] = create_json_array(likes);
//    event["interest"]["television"] = create_json_array(television);
//    event["interest"]["games"] = create_json_array(games);
//    event["interest"]["books"] = create_json_array(books);
//    event["location"]["latitude"] = latitude;
//    event["location"]["longitude"] = longitude;
//    std::cout << event << std::endl;


    CurlWrapper curlWrapper = CurlWrapper();
    std::string url = "https://enigmatic-scrubland-75073.herokuapp.com/users";
    curlWrapper.set_post_url(url);
    curlWrapper.set_post_data(user_id);
    bool res = curlWrapper.perform_request();
    curlWrapper.clean();
    LOG(INFO) << "Proccesing registration for user: ";
    if (res) {
        response.SetCode(200);
        response.SetBody(user_id);
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

std::string make_body_for_login_response(const std::string user_id, const std::string token) {
    std::string body("{ \"user\": { \"userId\" : \"");
    body.append(user_id).append("\" , \"token\" : \"");
    body.append(token).append("\" } }");
    return body;
}

Json::Value create_json_array(Json::Value array) {
    Json::Value json_array(Json::arrayValue);
    for (unsigned int i = 0; i < array.size(); i++) {
        json_array.append(Json::Value(array[i]));
    }
    std::cout << json_array << std::endl;
    return json_array;
}
