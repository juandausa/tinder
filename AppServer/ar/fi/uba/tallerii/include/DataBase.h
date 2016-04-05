//
// Copyright 2016 FiUBA
//

#ifndef TINDER_DATABASE_H
#define TINDER_DATABASE_H

#include <rocksdb/db.h>
#include <string>

class DataBase {
public:
    DataBase(const std::string & full_path);
    bool Set(const std::string key, const std::string value);
    bool Get(const std::string key, std::string *value);
    bool Delete(const std::string key);
    ~DataBase();

private:
    rocksdb::DB *database;
};


#endif //TINDER_DATABASE_H
