//
// Copyright 2016 FiUBA
//

#ifndef TINDER_MESSAGESSERVICE_H
#define TINDER_MESSAGESSERVICE_H
#include "DataBase.h"
#include "Message.h"
#include <string>
#include <vector>
#include "Log.h"
class MessagesService {
public:
    MessagesService();
    ~MessagesService();
    bool addMessage(Message message);
    std::vector<Message> getMessages(std::string userA, std::string userB);
    Message getLastMessage(std::string sender, std::string reciever);
private:
    DataBase* database;
    Log *log;
    bool addMessageToDatabase(Message message, std::string key);
};

#endif //TINDER_MESSAGESSERVICE_H
