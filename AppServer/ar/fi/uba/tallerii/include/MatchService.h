//
// Created by juan on 26/05/16.
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
