//
// Created by juan on 20/06/16.
//

#ifndef TINDER_CONVERTER_H
#define TINDER_CONVERTER_H
#include <string>

class Converter {
public:
    static std::string validateTimeOrReturnDefault(std::string time);
    static std::string validateGenderOrReturnDefault(std::string gender);
    static std::string calculateAge(std::string birthday);
    static std::string intToString(int value);
};

#endif //TINDER_CONVERTER_H
