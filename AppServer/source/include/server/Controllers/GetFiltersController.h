//
// Copyright 2016 FiUBA
//

#ifndef TINDER_GET_FILTERS_CONTROLLER_H
#define TINDER_GET_FILTERS_CONTROLLER_H

#include "GenericController.h"
#include "FilterService.h"

class GetFiltersController: public GenericController {
	
public:
    void operation(Request &request, Response &response);
private:
    FilterService filterService;
};

#endif //TINDER_GET_FILTERS_CONTROLLER_H
