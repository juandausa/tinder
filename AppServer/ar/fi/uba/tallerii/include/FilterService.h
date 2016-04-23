//
// Copyright 2016 FiUBA
//

#ifndef TINDER_FILTERSERVICE_H
#define TINDER_FILTERSERVICE_H
#include "DataBase.h"

class FilterService {
public:
    FilterService(DataBase & database);
private:
    DataBase * database;
};

#endif //TINDER_FILTERSERVICE_H
