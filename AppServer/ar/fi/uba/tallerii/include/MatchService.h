//
// Copyright 2016 FiUBA
//

#ifndef TINDER_MATCHSERVICE_H
#define TINDER_MATCHSERVICE_H
#include "DataBase.h"

class MatchService {
public:
    MatchService(DataBase & db);
    ~MatchService();

private:
    DataBase* database;
};

#endif //TINDER_MATCHSERVICE_H
