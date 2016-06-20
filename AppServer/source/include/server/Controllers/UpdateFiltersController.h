//
// Copyright 2016 FiUBA
//

#ifndef TINDER_UPDATE_FILTERS_CONTROLLER_H
#define TINDER_UPDATE_FILTERS_CONTROLLER_H

#include "GenericController.h"
#include "FilterService.h"

class UpdateFiltersController: public GenericController {
	
public:
    void operation(Request &request, Response &response);
private:
    FilterService filterService;
};

#endif //TINDER_UPDATE_FILTERS_CONTROLLER_H
