//
// Created by juan on 05/04/16.
//

#ifndef TINDER_USERCONTROLLER_H
#define TINDER_USERCONTROLLER_H


class UserController {
public:
    UserController();
    void handle_login(struct mg_connection *nc, struct http_message *hm);
};


#endif //TINDER_USERCONTROLLER_H
