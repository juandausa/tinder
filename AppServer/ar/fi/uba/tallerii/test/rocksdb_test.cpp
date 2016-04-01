//
// Copyright 2016 juanchi
//

#include <rocksdb/db.h>
#include "include/rocksdb_test.h"

rocksdb::DB* create_database() {
    rocksdb::DB *db;
    rocksdb::Options options;
    options.create_if_missing = true;
    options.error_if_exists = false;
    rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/testdb", &db);
    if (status.ok()) {
        return db;
    } else {
        delete db;
        return NULL;
    }
}

TEST(RocksDB, ReadAndWriteString) {
    rocksdb::DB *database = create_database();
    if (database == NULL) {
        return;
    }
    std::string value = "Valor", key = "Clave", retrivedValue;
    rocksdb::Status put_opreation_result = database->Put(rocksdb::WriteOptions(), key, value);
    rocksdb::Status read_operation_result = database->Get(rocksdb::ReadOptions(), key, &retrivedValue);
    EXPECT_EQ(value.compare(retrivedValue), 0);
}

