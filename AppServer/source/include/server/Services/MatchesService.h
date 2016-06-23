//
// Copyright 2016 FiUBA
//

#ifndef TINDER_MATCHSERVICE_H
#define TINDER_MATCHSERVICE_H
#include "DataBase.h"

class MatchesService {
public:
    MatchesService();
    std::string getMatchPhoto(std::string url);
    ~MatchesService();

private:
    DataBase* database;
};

#endif //TINDER_MATCHSERVICE_H
