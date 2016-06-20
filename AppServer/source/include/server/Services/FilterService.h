//
// Copyright 2016 FiUBA
//

#ifndef TINDER_FILTERSERVICE_H
#define TINDER_FILTERSERVICE_H
#include "DataBase.h"

class FilterService {
public:
    FilterService();
    virtual bool update_filters(const std::string user_id, const std::string filters);
    virtual std::string get_filters(const std::string user_id);
private:
    DataBase * database;
};

#endif //TINDER_FILTERSERVICE_H
