//
// Created by juan on 05/04/16.
//

#include "include/database_test.h"
#include "DataBase.h"

TEST(DataBaseWrapper, ReadAndWriteString) {
    DataBase db("/tmp/testdb10");
    std::string value = "Valor", key = "Clave", retrivedValue;
    db.Set(key, value);
    db.Get(key, &retrivedValue);
    EXPECT_EQ(value.compare(retrivedValue), 0);
}

TEST(DataBaseWrapper, UpdateString) {
    DataBase db("/tmp/testdb2");
    std::string value = "ValorUno", key = "ClaveUno", retrivedValue;
    db.Set(key, value);
    db.Get(key, &retrivedValue);
    EXPECT_EQ(value.compare(retrivedValue), 0);
    value = "ValorDos";
    db.Set(key, value);
    db.Get(key, &retrivedValue);
    EXPECT_EQ(value.compare(retrivedValue), 0);
}

TEST(DataBaseWrapper, DeleteString) {
    DataBase db("/tmp/testdb3");
    std::string value = "ValorUno", key = "ClaveUno", retrivedValue;
    db.Set(key, value);
    EXPECT_TRUE(db.Delete(key));
    EXPECT_FALSE(db.Get(key, &retrivedValue));
}

TEST(DataBaseWrapper, WriteStringWithDataBaseCreationFailing) {
    DataBase db("/noexiste/testdb3");
    std::string value = "ValorUno", key = "ClaveUno";
    EXPECT_FALSE(db.Set(key, value));
}

TEST(DataBaseWrapper, ReadStringWithDataBaseCreationFailing) {
    DataBase db("/noexiste/testdb3");
    std::string key = "ClaveUno", retrivedValue;
    EXPECT_FALSE(db.Get(key, &retrivedValue));
}

TEST(DataBaseWrapper, DeleteStringWithDataBaseCreationFailing) {
    DataBase db("/noexiste/testdb3");
    std::string key = "ClaveUno";
    EXPECT_FALSE(db.Delete(key));
}


