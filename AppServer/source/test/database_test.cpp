//
// Created by juan on 05/04/16.
//

#include "include/database_test.h"
#include "DataBase.h"

TEST(DataBaseWrapper, ReadAndWriteString) {
    DataBase* db = DataBase::getInstance();
    db->open("/tmp/testdb10");
    std::string value = "Valor", key = "Clave", retrivedValue;
    db->set(key, value);
    db->get(key, &retrivedValue);
    EXPECT_EQ(value.compare(retrivedValue), 0);
}

TEST(DataBaseWrapper, UpdateString) {
    DataBase* db = DataBase::getInstance();
    db->open("/tmp/testdb2");
    std::string value = "ValorUno", key = "ClaveUno", retrivedValue, retrievedValueAfterUpdate;
    db->set(key, value);
    db->get(key, &retrivedValue);
    EXPECT_EQ(value.compare(retrivedValue), 0);
    value = "ValorDos";
    db->remove(key);
    db->set(key, value);
    db->get(key, &retrievedValueAfterUpdate);
    EXPECT_EQ(value.compare(retrievedValueAfterUpdate), 0);
}

TEST(DataBaseWrapper, DeleteString) {
    DataBase* db = DataBase::getInstance();
    db->open("/tmp/testdb3");
    std::string value = "ValorUno", key = "ClaveUno", retrivedValue;
    db->set(key, value);
    EXPECT_TRUE(db->remove(key));
    EXPECT_FALSE(db->get(key, &retrivedValue));
}

TEST(DataBaseWrapper, ReadStringWhichIsNotPresent) {
    DataBase* db = DataBase::getInstance();
    db->open("/tmp/testdb4");
    std::string key = "ClaveUno", retrivedValue;
    EXPECT_FALSE(db->get(key, &retrivedValue));
}

TEST(DataBaseWrapper, DeleteStringWithDataBaseCreationFailing) {
    DataBase* db = DataBase::getInstance();
    db->open("");
    std::string key = "ClaveUno";
    EXPECT_FALSE(db->remove(key));
}

TEST(DataBaseWrapper, WriteStringWithDataBaseCreationFailing) {
    DataBase* db = DataBase::getInstance();
    db->open("");
    std::string value = "ValorUno", key = "ClaveUno";
    EXPECT_FALSE(db->set(key, value));
}

TEST(DataBaseWrapper, ReadStringWithDataBaseCreationFailing) {
    DataBase* db = DataBase::getInstance();
    db->open("");
    std::string key = "ClaveUno", retrivedValue;
    EXPECT_FALSE(db->get(key, &retrivedValue));
}