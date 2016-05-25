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
