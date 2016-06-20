//
// Copyright 2016 FiUBA
//


#ifndef TINDER_CONSTANT_H
#define TINDER_CONSTANT_H
#include <string>


class Constant {
public:
    static std::string server_port;
    static std::string database_path;
    static std::string security_token_prefix;
    static std::size_t random_characters_quantity;
    static std::string filters_prefix;
    static std::string likes_prefix;
    static std::string dislikes_prefix;
    static std::string matches_prefix;
    static char likes_separator;
    static std::string update_user_info_url;
    static std::string get_user_info_url;
    static std::string male;
    static std::string female;
    static std::string defaultAge;
    static std::string defaultBirthday;
    static int DB_ERROR;
    static std::string GLOG_INFO_PATH;
    static std::string GLOG_ERROR_PATH;
    static std::string GLOG_FATAL_PATH;
    static std::string GLOG_WARNING_PATH;
private:
    Constant();
};


#endif //TINDER_CONSTANT_H
