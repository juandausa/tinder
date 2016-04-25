//
// Copyright 2016 FiUBA
//

#ifndef TINDER_FILTERCONTROLLER_H
#define TINDER_FILTERCONTROLLER_H

#include "Mongoose.h"
#include "FilterService.h"
#include "Response.h"

class FilterController {
public:
    FilterController(FilterService filter_service);
    virtual void handle_update_filters(struct mg_connection *nc, struct http_message *hm, Response response);
    virtual void handle_get_filters(struct mg_connection *nc, struct http_message *hm, Response response);
private:
    FilterService filter_service;
};

#endif //TINDER_FILTERCONTROLLER_H
