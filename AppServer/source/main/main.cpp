/* Copyright 2016 FiUBA */

#include <unistd.h>
#include <glog/logging.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include "Server.h"
#include "DataBase.h"

void printCurrentDir() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        std::cout << "Current working dir: " << cwd << std::endl;
    else
        perror("getcwd() error");
}

std::vector<std::string> convert_parameters(int argc, char** args) {
    std::vector<std::string> parameters;
    for (int i = 0; i < argc; i++) {
        std::string parameter(args[i]);
        parameters.push_back(parameter);
    }

    return parameters;
}

int main(int argc, char** args) {
    google::SetLogDestination(google::GLOG_INFO, "/tmp/tinder.log");
    google::SetLogDestination(google::GLOG_ERROR, "");
    google::SetLogDestination(google::GLOG_FATAL, "");
    google::SetLogDestination(google::GLOG_WARNING, "");
    google::InitGoogleLogging(args[0]);
    DataBase* db = DataBase::getInstance();
    if (!db->open(Constant::database_path)){
        LOG(INFO) << "Open db error";
        return Constant::DB_ERROR;
    }
    LOG(INFO) << "App Server started.";
    printCurrentDir();
    Server tinderServer(convert_parameters(argc, args));
    tinderServer.start();
    delete(db);
    LOG(INFO) << "App Server finished.";
    google::ShutdownGoogleLogging();
    return 0;
}


