//
// Copyright 2016 juanchi
//

#include <rocksdb/db.h>
#include "include/rocksdb_test.h"

rocksdb::DB* create_database(std::string name) {
    rocksdb::DB *db;
    rocksdb::Options options;
    options.create_if_missing = true;
    options.error_if_exists = false;
    rocksdb::Status status = rocksdb::DB::Open(options, name, &db);
    if (status.ok()) {
        return db;
    } else {
        delete db;
        return NULL;
    }
}

TEST(RocksDB, ReadAndWriteString) {
    rocksdb::DB *database = create_database("/tmp/rdb1");
    if (database == NULL) {
        return;
    }
    std::string value = "Valor", key = "Clave", retrivedValue;
    database->Put(rocksdb::WriteOptions(), key, value);
    database->Get(rocksdb::ReadOptions(), key, &retrivedValue);
    delete database;
    EXPECT_EQ(value.compare(retrivedValue), 0);
}

TEST(RocksDB, UpdateString) {
    rocksdb::DB *database = create_database("/tmp/rdb2");
    if (database == NULL) {
        return;
    }
    std::string value = "ValorUno", key = "ClaveUno", retrivedValue;
    rocksdb::Status put_opreation_result = database->Put(rocksdb::WriteOptions(), key, value);
    value = "ValorDos";
    database->Put(rocksdb::WriteOptions(), key, value);
    database->Get(rocksdb::ReadOptions(), key, &retrivedValue);
    delete database;
    EXPECT_EQ(value.compare(retrivedValue), 0);
}

TEST(RocksDB, DeleteString) {
    rocksdb::DB *database = create_database("/tmp/rdb3");
    if (database == NULL) {
        return;
    }
    std::string value = "ValorUno", key = "ClaveUno", retrivedValue;
    database->Put(rocksdb::WriteOptions(), key, value);
    database->Delete(rocksdb::WriteOptions(), key);
    rocksdb::Status read_operation_result = database->Get(rocksdb::ReadOptions(), key, &retrivedValue);
    delete database;
    EXPECT_TRUE(!read_operation_result.ok());
}
