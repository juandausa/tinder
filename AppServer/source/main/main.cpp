/* Copyright 2016 FiUBA */

#include <unistd.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include "Server.h"
#include "DataBase.h"
#include "Log.h"

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
    DataBase *db = DataBase::getInstance();
    Log *log = Log::getInstance();
    log->init(args[0]);
    
    if (!db->open(Constant::database_path)){
        log->writeAndPrintLog("Open db error.", Log::FATAL);
        return Constant::DB_ERROR;
    }
    
    log->writeAndPrintLog("App Server started.",Log::INFO);
    printCurrentDir();
    
    Server tinderServer(convert_parameters(argc, args));
    tinderServer.start();

    log->writeAndPrintLog("App Server finished.",Log::INFO);
    delete db;
    delete log;
    
    return 0;
}


