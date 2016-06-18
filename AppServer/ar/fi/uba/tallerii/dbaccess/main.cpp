/* Copyright 2016 FiUBA */

#include <unistd.h>
#include <glog/logging.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include "Server.h"

void printCurrentDir() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        std::cout << "Current working dir: " << cwd << std::endl;
    else
        perror("getcwd() error");
}

std::vector<std::string> convert_parameters(int argc, char **args) {
    std::vector<std::string> parameters;
    for (int i = 0; i < argc; i++) {
        std::string parameter(args[i]);
        parameters.push_back(parameter);
    }

    return parameters;
}

int main(int argc, char **args) {
    google::SetLogDestination(google::GLOG_INFO, "/tmp/tinder.log");
    google::SetLogDestination(google::GLOG_ERROR, "");
    google::SetLogDestination(google::GLOG_FATAL, "");
    google::SetLogDestination(google::GLOG_WARNING, "");
    google::InitGoogleLogging(args[0]);

    LOG(INFO) << "Access to database project started.";
    printCurrentDir();
    DataBase db(Constant::database_path);
    if (db.is_open()) {
        LOG(INFO) << "The Database is open.";
        std::cout << "The Database is open." << std::endl;
        std::cout << "Type exit for quit." << std::endl;
        while (true) {
            std::string key;
            std::getline(std::cin, key);
            if (key.compare("exit") == 0) {
                break;
            }
            std::string value;
            if (db.get(key, &value)) {
                std::cout << "Value: '" + value + "'" << std::endl;
            } else {
                std::cout << "Key not found.";
            }
        }
    }

    LOG(INFO) << "Access to database project finished.";
    google::ShutdownGoogleLogging();
    return 0;
}


