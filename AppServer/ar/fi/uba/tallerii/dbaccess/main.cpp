/* Copyright 2016 FiUBA */

#include "DataBase.h"
#include "Constant.h"
#include "RandomTextGenerator.h"
#include <unistd.h>
#include <glog/logging.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <map>
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


void getAll(DataBase *dataBase) {
    std::map<std::string, std::string>* allData = dataBase->getAll();
    for ( auto it = allData->begin(); it != allData->end(); it++ ) {
        cout << it->first << ": " << it->second << endl;
    }
    delete allData;
}


std::string getAppKey(const std::string userId) {
    std::size_t random_characters_quantity = 5;
    RandomTextGenerator rnd;
    std::string random_string = rnd.generate(random_characters_quantity);
    return random_string;
}

void saveAppKey(std::string sharedId, std::string appId, DataBase* db) {
    if (db->is_open()) {
        db->set(sharedId, appId);
        db->set(appId, sharedId);
    }
}

void addNewUser(std::string sharedId, DataBase* db) {
    std::string appId = getAppKey(sharedId);
    saveAppKey(sharedId, appId, db);
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
        std::cout << "Command list" << std::endl;
        std::cout << "  all         - Gets all the data in the database." << std::endl;
        std::cout << "  clear       - Clear the database." << std::endl;
        std::cout << "  new_user    - Adds a new user inserting its shared server id." << std::endl;
        std::cout << "  exit        - exits the program." << std::endl;
        std::cout << "  Any other thing entered that its not these commands, will be searched in the database as a key." << std::endl;
        std::cout << "Enter your command or data" << std::endl;
        while (true) {
            std::string key;
            std::getline(std::cin, key);
            if (key.compare("exit") == 0) {
                break;
            } else if (key.compare("all") == 0) {
                getAll(&db);
            } else if (key.compare("clear") == 0) {
                clearDatabase(&db);
            } else if (key.compare("new_user") == 0) {
                std::string key;
                std::getline(std::cin, key);
                addNewUser(key, &db);
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


