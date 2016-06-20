//
// Copyright 2016 FiUBA
//

#include "Converter.h"
#include "Constant.h"
#include <time.h>
#include <sstream>
#include <string>

std::string Converter::validateTimeOrReturnDefault(std::string time) {
    struct tm convertedTime;;
    if (strptime(time.c_str(), "%d/%m/%Y", &convertedTime)) {
        return time;
    } else {
        return Constant::defaultBirthday;
    }
}

std::string Converter::validateGenderOrReturnDefault(std::string gender) {
    if (gender.compare(Constant::female) == 0) {
        return gender;
    }

    return Constant::male;
}

std::string Converter::calculateAge(std::string birthday) {
    struct tm convertedTime, localTime;
    time_t t = time(NULL);
    localtime_r(&t, &localTime);
    if (strptime(birthday.c_str(), "%d/%m/%Y", &convertedTime)) {
        return static_cast<std::ostringstream*>(&(std::ostringstream() << (localTime.tm_year - convertedTime.tm_year)))->str();
    }

    return Constant::defaultAge;
}

std::string Converter::intToString(int value) {
    std::ostringstream oss;
    // Works just like cout
    oss << value;
    // Return the underlying string
    return oss.str();
}
