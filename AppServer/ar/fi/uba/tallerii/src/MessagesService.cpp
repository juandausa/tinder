//
// Copyright 2016 FiUBA
//

#include "MessagesService.h"
#include "DataBase.h"
#include "Message.h"
#include "Constant.h"
#include <vector>
#include <glog/logging.h>

MessagesService::MessagesService(DataBase &db) : database(&db) {
}

bool addMessageToDatabase(Message &message, std::string key, DataBase *database) {
    std::string previousMessages("");
    database->get(key, &previousMessages);

    bool result;
    if (previousMessages.length() != 0) {
        previousMessages += Constant::messagesSeparator;
        previousMessages.append(message.toString());
        result = database->set(key, previousMessages);
    } else {
        result = database->set(key, message.toString());
    }

    return result;
}

bool MessagesService::addMessage(Message message) {
    LOG(INFO) << "Adding messages between users '" + message.getSender() + "' and '" + message.getReciever() + "'.";
    if (this->database->is_open()) {
        std::string messagesKeySender = Constant::messagesPrefix + message.getSender() + message.getReciever();
        std::string messagesKeyReciever = Constant::messagesPrefix + message.getSender() + message.getReciever();
        bool result = addMessageToDatabase(message, messagesKeySender, this->database) &&
                      addMessageToDatabase(message, messagesKeyReciever, this->database);

        return result;
    } else {
        LOG(WARNING) << "Adding message. The database is closed.";
        return false;
    }
}

std::vector<std::string> splitMessages(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }

    return elems;
}

std::vector<Message> convertInVectorOfMessages(std::string in) {
    std::vector<std::string> out = splitMessages(in, Constant::messagesSeparator);
    std::vector<Message> messages;
    for (size_t i = 0; i < out.size(); ++i) {
        Message m;
        m.loadFromString(out[i]);
        messages.push_back(m);
    }

    return messages;
}

std::vector<Message> MessagesService::getMessages(std::string userA, std::string userB) {
    LOG(INFO) << "Getting messages between users '" + userA + "' and '" + userB + "'.";
    std::string messages;
    std::string messagesKeySender = Constant::messagesPrefix + userA + userB;
    this->database->get(messagesKeySender, &messages);
    if (messages.length() != 0) {
        return convertInVectorOfMessages(messages);
    }

    std::vector<Message> empty;
    return empty;
}

MessagesService::~MessagesService() {
}
