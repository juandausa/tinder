//
// Created by juan on 05/04/16.
//

#ifndef TINDER_USERCONTROLLER_H
#define TINDER_USERCONTROLLER_H
#include "Mongoose.h"
#include "Response.h"

class UserController {
public:
    UserController();
    void handle_login(struct mg_connection *nc, struct http_message *hm, Response response);
private:
    std::string make_body(std::string user_id);
};


#endif //TINDER_USERCONTROLLER_H
