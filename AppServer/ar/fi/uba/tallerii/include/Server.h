//
// Created by juanchi on 22/03/16.
//

#ifndef TINDER_SEVER_H
#define TINDER_SEVER_H
#include <vector>
#include <cstring>
#include "Mongoose.h"

class Server {
public:
    Server();
    Server(std::vector<std::string> options);
    ~Server();
    void start();
private:
    std::vector<std::string> options;
    std::string port;
    static void ev_handler(struct mg_connection *nc, int ev, void *ev_data);
};

#endif //TINDER_SEVER_H
