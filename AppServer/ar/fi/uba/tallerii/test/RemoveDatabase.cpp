//
// Created by juan on 17/06/16.
//

#include "include/RemoveDatabase.h"
#include <stdlib.h>

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