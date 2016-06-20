//
// Copyright 2016 FiUBA
//

#include "Constant.h"
#include <string>

std::string Constant :: server_port = "8000";
std::string Constant :: database_path = "/tmp/tinderdb";
std::string Constant :: security_token_prefix = "token-";
std::size_t Constant :: random_characters_quantity = 5;
std::string Constant :: filters_prefix = "preferences-";
std::string Constant :: likes_prefix = "likes-";
std::string Constant :: dislikes_prefix = "dislikes-";
std::string Constant :: matches_prefix = "matches-";
char Constant :: likes_separator = ' ';
std::string Constant :: update_user_info_url = "http://enigmatic-scrubland-75073.herokuapp.com/users/";
std::string Constant :: get_user_info_url = "http://enigmatic-scrubland-75073.herokuapp.com/users/";
std::string Constant :: male = "male";
std::string Constant :: female = "female";
std::string Constant :: defaultAge = "0";
std::string Constant :: defaultBirthday = "01/01/1970";
int Constant::DB_ERROR = 666;
std::string Constant::GLOG_INFO_PATH = "/tmp/tinder_info.log";
std::string Constant::GLOG_ERROR_PATH = "/tmp/tinder_error.log";
std::string Constant::GLOG_FATAL_PATH = "/tmp/tinder_fatal.log";
std::string Constant::GLOG_WARNING_PATH = "/tmp/tinder_warning.log";
std::string Constant :: messageComponentDivider = "N_N";
char Constant :: messagesSeparator = ';';
std::string Constant :: messagesPrefix = "messages-";
std::string Constant :: distancePrefix = "distance-";
std::string Constant :: showGenderPrefix = "showGender-";
std::string Constant :: lastMessagesPrefix = "lastmessage";
std::string Constant :: getUsersUrl = "http://enigmatic-scrubland-75073.herokuapp.com/users";
std::string Constant :: count_likes_prefix = "countLikes-";