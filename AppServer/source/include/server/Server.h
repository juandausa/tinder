//
// Created by juanchi on 22/03/16.
//

#ifndef TINDER_SEVER_H
#define TINDER_SEVER_H
#include <vector>
#include <cstring>
#include <glog/logging.h>
#include <signal.h>
#include <iostream>
#include "RequestParser.h"
#include "UserController.h"
#include "FilterController.h"
#include "Constant.h"
#include "SecurityManager.h"
#include "Mongoose.h"


class Server {
public:
    Server();
    Server(std::vector<std::string> options);
    void start();
    ~Server();
private:
    std::vector<std::string> options;
    std::string port;
    static void ev_handler(struct mg_connection *nc, int ev, void *ev_data);
};

#endif //TINDER_SEVER_H
