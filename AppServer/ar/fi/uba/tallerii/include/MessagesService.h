//
// Copyright 2016 FiUBA
//

#ifndef TINDER_MESSAGESSERVICE_H
#define TINDER_MESSAGESSERVICE_H
#include "DataBase.h"
#include "Message.h"
#include <string>
#include <vector>

class MessagesService {
public:
    MessagesService(DataBase & db);
    ~MessagesService();
    virtual bool addMessage(Message message);
    virtual std::vector<Message> getMessages(std::string userA, std::string userB);
    virtual Message getLastMessage(std::string sender, std::string reciever);
private:
    DataBase* database;
};

#endif //TINDER_MESSAGESSERVICE_H
