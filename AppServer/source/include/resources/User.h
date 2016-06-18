//
#ifndef TINDER_USER_H
#define TINDER_USER_H
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <jsoncpp/json/json.h>
#include <time.h>
#include "Location.h"
#include "Constant.h"
class User {
public:
    User();
    User(Json::Value root);
    void setLocation(Location &location);
    ~User();

private:
    std::string userId;
    std::string name;
    std::string gender;
    std::string birthday;
    std::string alias;
    std::string email;
    std::string urlPhotoProfile;
    std::unordered_map<std::string,std::vector<std::string>> interests;
    Location location;

    std::string calculateAge(std::string birthday);
    std::string validateGenderOrReturnDefault(std::string gender);
    std::string validateTimeOrReturnDefault(std::string time);
};

#endif //TINDER_USER_H
