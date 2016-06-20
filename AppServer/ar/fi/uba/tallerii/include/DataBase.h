//
// Copyright 2016 FiUBA
//

#ifndef TINDER_DATABASE_H
#define TINDER_DATABASE_H

#include <rocksdb/db.h>
#include <string>
#include <map>

using namespace std;

class DataBase {
public:
    DataBase(const std::string & full_path);
    bool is_open();
    bool set(const std::string key, const std::string value);
    bool get(const std::string key, std::string *value);
    std::map<std::string, std::string>* getAll();
    bool remove(const std::string key);
    ~DataBase();

private:
    rocksdb::DB *database;
};


#endif //TINDER_DATABASE_H
