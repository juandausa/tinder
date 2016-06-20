//
// Copyright 2016 FiUBA
//

#include "FilterService.h"
#include <glog/logging.h>
#include <string>
#include "Constant.h"

FilterService :: FilterService(){
    this->database = DataBase::getInstance();
}

bool FilterService :: update_filters(const std::string user_id, const std::string filters) {
    if (this->database->is_open()) {
        return this->database->set(Constant::filters_prefix + user_id, filters);
    }

    LOG(WARNING) << "The database is closed";
    return false;
}

std::string FilterService :: get_filters(const std::string user_id) {
    std::string filters("");
    if (!this->database->is_open()) {
        LOG(WARNING) << "The database is closed";
        return "";
    }

    if (!this->database->get(Constant::filters_prefix + user_id, &filters)) {
        LOG(WARNING) << "Filters for user: '" << user_id << "' were not found.";
        return "";
    }

    return filters;
}

