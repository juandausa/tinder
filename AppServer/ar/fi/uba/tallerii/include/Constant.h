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
private:
    Constant();
};


#endif //TINDER_CONSTANT_H