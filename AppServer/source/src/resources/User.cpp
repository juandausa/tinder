//
// Copyright 2016 FiUBA
//

#include "User.h"

User::User() {
    this->userId = "";
    this->name = "";
    this->gender = "";
    this->birthday = "";
    this->alias = "";
    this->email = "";
    this->urlPhotoProfile = "";

    interests.emplace("music", std::vector<std::string>());
    interests.emplace("movies", std::vector<std::string>());
    interests.emplace("likes", std::vector<std::string>());
    interests.emplace("television", std::vector<std::string>());
    interests.emplace("games", std::vector<std::string>());
    interests.emplace("books", std::vector<std::string>());
}

/*TODO: Faltaria agregar validacion de campos del json*/
User::User(Json::Value root){
    this->name = root.get("name", "").asString();
    this->alias = root.get("alias", "").asString();
    this->email = root.get("email", "").asString();
    this->birthday = this->validateTimeOrReturnDefault(root.get("birthday", "").asString());
    this->gender = this->validateGenderOrReturnDefault(root.get("gender", Constant::male).asString());
    this->urlPhotoProfile = root.get("photo_profile", "").asString();
    
    Json::Value music = root["interests"]["music"];
    Json::Value movies = root["interests"]["movies"];
    Json::Value likes = root["interests"]["likes"];
    Json::Value television = root["interests"]["television"];
    Json::Value games = root["interests"]["games"];
    Json::Value books = root["interests"]["books"];

    for (unsigned int i = 0; i < music.size(); i++) {
        interests["music"].push_back(music[i].asString());
    }
    for (unsigned int i = 0; i < movies.size(); i++) {
        interests["movies"].push_back(movies[i].asString());
    }
    for (unsigned int i = 0; i < likes.size(); i++) {
        interests["likes"].push_back(likes[i].asString());
    }
    for (unsigned int i = 0; i < games.size(); i++) {
        interests["games"].push_back(games[i].asString());
    }
    for (unsigned int i = 0; i < books.size(); i++) {
        interests["books"].push_back(books[i].asString());
    }

    this->location.setLatitude(root["location"].get("latitude", 0).asDouble());
    this->location.setLongitude(root["location"].get("longitude", 0).asDouble());

}


std::string User::validateTimeOrReturnDefault(std::string time) {
    struct tm convertedTime;;
    if (strptime(time.c_str(), "%d/%m/%Y", &convertedTime)) {
        return time;
    } else {
        return Constant::defaultBirthday;
    }
}

std::string User::validateGenderOrReturnDefault(std::string gender) {
    if (gender.compare(Constant::female) == 0) {
        return gender;
    }

    return Constant::male;
}

std::string User::calculateAge(std::string birthday) {
    struct tm convertedTime, localTime;
    time_t t = time(NULL);
    localtime_r(&t, &localTime);
    if (strptime(birthday.c_str(), "%d/%m/%Y", &convertedTime)) {
        // return static_cast<std::ostringstream*>(&(std::ostringstream() << (localTime.tm_year - convertedTime.tm_year)))->str();
        int age = localTime.tm_year - convertedTime.tm_year;
        std::stringstream convert; // stringstream used for the conversion
        convert << age;//add the value of Number to the characters in the stream
        return convert.str();
    }

    return Constant::defaultAge;
}

User::~User() {
}
