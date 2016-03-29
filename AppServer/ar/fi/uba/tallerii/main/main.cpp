/* Copyright 2016 FiUBA */

#include <unistd.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstring>
#include <glog/logging.h>
#include "Server.h"
#include "Lock.h"

void printCurrentDir() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        std::cout << "Current working dir: " << cwd << std::endl;
    else
        perror("getcwd() error");
}

int main(int arg, char** args) {
    google::SetLogDestination(google::GLOG_INFO, "/tmp/tinder.log");
    google::SetLogDestination(google::GLOG_ERROR, "");
    google::SetLogDestination(google::GLOG_FATAL, "");
    google::SetLogDestination(google::GLOG_WARNING, "");
    google::InitGoogleLogging(args[0]);

    LOG(INFO) << "App Server started. INFO MESSAGE";
    LOG(WARNING) << "App Server started. WARNING MESSAGE";

    std::cout << "Esto es un programa hecho con Clion." << std::endl;
    printCurrentDir();
    Server tinderServer;
    tinderServer.start();
    LOG(INFO) << "App Server finished. INFO MESSAGE";
    return 0;
}
