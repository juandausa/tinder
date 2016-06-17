//
// Copyright 2016 FiUBA
//

#ifndef TINDER_MATCHSERVICE_H
#define TINDER_MATCHSERVICE_H
#include "DataBase.h"

class MatchesService {
public:
    MatchesService(DataBase & db);
    ~MatchesService();

private:
    DataBase* database;
};

#endif //TINDER_MATCHSERVICE_H
