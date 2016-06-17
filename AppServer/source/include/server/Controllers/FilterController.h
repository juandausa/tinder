//
// Copyright 2016 FiUBA
//

#ifndef TINDER_FILTERCONTROLLER_H
#define TINDER_FILTERCONTROLLER_H

#include "Mongoose.h"
#include "FilterService.h"
#include "Response.h"
#include "RequestParser.h"

class FilterController {
public:
    FilterController(FilterService filter_service);
    virtual void handle_update_filters(RequestParser requestParser, Response response);
    virtual void handle_get_filters(RequestParser requestParser, Response response);
private:
    FilterService filter_service;
};

#endif //TINDER_FILTERCONTROLLER_H
