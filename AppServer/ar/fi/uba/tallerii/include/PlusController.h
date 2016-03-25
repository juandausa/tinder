//
// Copyright 2016 FiUBA
//

#ifndef TINDER_PLUSCONTROLLER_H
#define TINDER_PLUSCONTROLLER_H
#include "Mongoose.h"


class PlusController {
public:
    PlusController();
    void handle_sum_call(struct mg_connection *nc, struct http_message *hm);
};


#endif //TINDER_PLUSCONTROLLER_H
