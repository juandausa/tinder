//
// Created by juan on 08/04/16.
//

#ifndef TINDER_USER_SERVICE_TEST_H
#define TINDER_USER_SERVICE_TEST_H

#include "UserService.h"
#include "DataBase.h"
#include <gtest/gtest.h>
#include <sys/types.h>
#include <sys/stat.h>

bool fileExists(std::string pathname) {
    struct stat info;

    if( stat( pathname.c_str(), &info ) != 0 )
        return false;
    else if( info.st_mode & S_IFDIR )  // S_ISDIR() doesn't exist on my windows
        return true;
    else
        return true;
}

void removeDataBase(std::string name) {
    if (fileExists(name)) {
        std::string command = "rm -r " + name + "/*";
        system(command.c_str());
    }
}

#endif //TINDER_USER_SERVICE_TEST_H
