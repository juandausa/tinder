//
// Copyright 2016 FiUBA
//

#ifndef TINDER_LOG_H
#define TINDER_LOG_H

#include <glog/logging.h>
#include <string>
#include <iostream>
#include "Constant.h"
class Log{
public:

    static std::string INFO;
    static std::string ERROR;
    static std::string WARNING;
    static std::string FATAL;

    static Log* getInstance();
    void init(char *executableName);
    void writeAndPrintLog(const char msj[], const std::string level);
    void writeLog(const char msj[], const std::string level);
    void printLog(const char msj[], const std::string level);
    ~Log();
private:
    Log();  // Private so that it can  not be called
    Log(Log const&){};             // copy constructor is private
    // Log& operator=(Log const&){};  // assignment operator is private
    static Log* logInstance;
    std::string msj;
};

#endif //TINDER_LOG_H
