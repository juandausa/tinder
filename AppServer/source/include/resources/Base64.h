//
// Created by fabrizio on 22/06/16.
//

#ifndef TINDER_BASE64_H
#define TINDER_BASE64_H

#include <string>
using namespace std;


class Base64 {
public:
    static std::string encode(unsigned char const* bytes_to_encode, unsigned int in_len);
    static std::string decode(std::string const& encoded_string);
};


#endif //TINDER_BASE64_H
