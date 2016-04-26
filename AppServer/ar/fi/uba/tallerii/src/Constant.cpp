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
std::string Constant :: update_user_info_url = "https://enigmatic-scrubland-75073.herokuapp.com/users/";
std::string Constant :: get_user_info_url = "https://enigmatic-scrubland-75073.herokuapp.com/users/";
