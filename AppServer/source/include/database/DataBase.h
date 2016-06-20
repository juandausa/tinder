//
// Copyright 2016 FiUBA
//

#ifndef TINDER_DATABASE_H
#define TINDER_DATABASE_H

#include <rocksdb/db.h>
#include <string>

class DataBase{
public:
   	static DataBase* getInstance();
   	bool is_open();
    bool set(const std::string key, const std::string value);
    bool get(const std::string key, std::string *value);
    bool remove(const std::string key);
    bool open(const std::string path);
    bool close();
   	~DataBase();
private:
   DataBase();  // Private so that it can  not be called
   DataBase(DataBase const&){};             // copy constructor is private
   // DataBase& operator=(DataBase const&){};  // assignment operator is private
   static DataBase* dbInstance;
   rocksdb::DB *database;
};

#endif //TINDER_DATABASE_H
