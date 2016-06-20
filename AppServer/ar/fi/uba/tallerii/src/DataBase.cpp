//
// Copyright 2016 FiUBA
//

#include <unordered_map>
#include <string>
#include <iostream>
#include "DataBase.h"
#include <map>

using namespace std;
typedef std::map<std::string, std::string> registers;

DataBase :: DataBase(const std::string & full_path) {
    rocksdb::Options options;
    options.create_if_missing = true;
    options.error_if_exists = false;
    rocksdb::Status status = rocksdb::DB::Open(options, full_path, &this->database);
    if (!status.ok()) {
        delete this->database;
        this->database = NULL;
    }
}

bool DataBase :: is_open() {
    return this->database != NULL;
}

bool DataBase :: get(const std::string key, std::string *value) {
    if (!this->is_open()) {
        return false;
    }

    std::string retrivedValue;
    rocksdb::Status read_operation_result = database->Get(rocksdb::ReadOptions(), key, &retrivedValue);
    if (read_operation_result.ok()) {
        *value = retrivedValue;
        return true;
    }

    return false;
}

bool DataBase :: set(const std::string key, const std::string value) {
    if (!this->is_open()) {
        return false;
    }

    rocksdb::Status put_opreation_result = database->Put(rocksdb::WriteOptions(), key, value);
    return put_opreation_result.ok();
}

bool DataBase::remove(const std::string key) {
    if (!this->is_open()) {
        return false;
    }

    rocksdb::Status delete_opreation_result =  database->Delete(rocksdb::WriteOptions(), key);
    return delete_opreation_result.ok();
}

registers* DataBase::getAll() {
    rocksdb::Iterator* it = database->NewIterator(rocksdb::ReadOptions());
    registers* all;
    all = new registers();
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        all->emplace(it->key().ToString(), it->value().ToString());
        cout << it->key().ToString() << ": " << it->value().ToString() << endl;
    }
    //assert(it->status().ok()); // Check for any errors found during the scan
    delete it;
    return all;
};



DataBase :: ~DataBase() {
    if (this->is_open()) {
        delete(this->database);
        this->database = NULL;
    }
}
