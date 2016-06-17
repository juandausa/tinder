//
// Copyright 2016 FiUBA
//

#ifndef TINDER_MESSAGESSERVICE_H
#define TINDER_MESSAGESSERVICE_H
#include "DataBase.h"

class MessagesService {
public:
    MessagesService(DataBase & db);
    ~MessagesService();

private:
    DataBase* database;
};

#endif //TINDER_MESSAGESSERVICE_H
