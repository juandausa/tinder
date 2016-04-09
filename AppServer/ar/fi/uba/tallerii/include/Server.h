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
    ~Server();
    void start();
private:
    std::vector<std::string> options;
};

#endif //TINDER_SEVER_H
