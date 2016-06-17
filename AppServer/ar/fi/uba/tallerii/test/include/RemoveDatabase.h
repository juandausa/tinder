//
// Created by juan on 17/06/16.
//

#ifndef TINDER_REMOVEDATABASE_H
#define TINDER_REMOVEDATABASE_H
#include <sys/types.h>
#include <sys/stat.h>
#include <string>

bool fileExists(std::string pathname);

void removeDataBase(std::string name);

#endif //TINDER_REMOVEDATABASE_H
