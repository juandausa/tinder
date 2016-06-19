/* Copyright 2016 FiUBA */

#include "DataBase.h"
#include "Constant.h"
#include <unistd.h>
#include <glog/logging.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

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

void clearDatabase(DataBase *database) {
    database->~DataBase();
    std::string command = "rm -r " + Constant::database_path + "/*";
    system(command.c_str());
    DataBase db(Constant::database_path);
    database = &db;
    if (database->is_open()) {
        LOG(INFO) << "Database cleared.";
        std::cout << "Database cleared." << std::endl;
    } else {
        std::cout << "Error clearing database." << std::endl;
        LOG(ERROR) << "Error clearing database.";
    }
}

int main(int argc, char **args) {
    google::SetLogDestination(google::GLOG_INFO, "/tmp/dbaccess.log");
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
        std::cout << "Type exit to quit." << std::endl;
        while (true) {
            std::string key;
            std::getline(std::cin, key);
            if (key.compare("exit") == 0) {
                break;
            } else if (key.compare("clear") == 0) {
                clearDatabase(&db);
            } else {
                std::string value;
                if (db.get(key, &value)) {
                    std::cout << "Value: '" + value + "'" << std::endl;
                } else {
                    std::cout << "Key not found." << std::endl;
                }
            }
        }
    }

    LOG(INFO) << "Access to database project finished.";
    google::ShutdownGoogleLogging();
    return 0;
}


