//
// Copyright 2016 FiUBA
//

#include "MessagesService.h"
#include "Message.h"
#include "Constant.h"

#include <vector>
#include <string>

MessagesService::MessagesService() {
    this->log = Log::getInstance();
    this->database = DataBase::getInstance();
}

bool MessagesService::addMessageToDatabase(Message message, std::string key) {
    std::string previousMessages("");
    this->database->get(key, &previousMessages);

    bool result;
    if (previousMessages.length() != 0) {
        /*Recuperar el mensaje como json array y parsearlo*/
        previousMessages += Constant::messagesSeparator;
        previousMessages.append(message.toString());
        result = this->database->set(key, previousMessages);
    } else {
        result = this->database->set(key, message.toString());
    }

    return result;
}

bool MessagesService::addMessage(Message message) {
    log->writeAndPrintLog(std::string("Adding messages between users '") + message.getSender()
                          + std::string("' and '") + message.getReciever() + std::string("'."), Log::INFO);
    if (this->database->is_open()) {
        std::string messagesKeySender = Constant::messagesPrefix + message.getSender() + message.getReciever();
        std::string messagesKeyReciever = Constant::messagesPrefix + message.getReciever() + message.getSender();
        std::string lastMessagesKey = Constant::lastMessagesPrefix + message.getSender() + message.getReciever();

        bool result = this->addMessageToDatabase(message, messagesKeySender) &&
                      this->addMessageToDatabase(message, messagesKeyReciever);
        if (result) {
            this->addMessageToDatabase(message, lastMessagesKey);
        }
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
    if (!this->database->is_open()) {
        LOG(WARNING) << "Getting messages. The database is closed.";
        std::vector<Message> empty;
        return empty;
    }

    LOG(INFO) << "Getting messages between users '" + userA + "' and '" + userB + "'.";
    std::string messages;
    std::string messagesKeySender = Constant::messagesPrefix + userA + userB;
    std::string lastMessageKey = Constant::lastMessagesPrefix + userA + userB;
    this->database->get(messagesKeySender, &messages);
    this->database->set(lastMessageKey, "");
    if (messages.length() != 0) {
        return convertInVectorOfMessages(messages);
    }

    std::vector<Message> empty;
    return empty;
}

Message MessagesService::getLastMessage(std::string sender, std::string reciever) {
    if (!this->database->is_open()) {
        LOG(WARNING) << "Getting last message. The database is closed.";
        Message empty;
        return empty;
    }

    LOG(INFO) << "Getting messages between users '" + sender + "' and '" + reciever + "'.";
    std::string messages;
    std::string lastMessageKey = Constant::lastMessagesPrefix + sender + reciever;
    std::cout << "' lastMessageKey  '" + lastMessageKey + "'." << std::endl;
    this->database->get(lastMessageKey, &messages);
    if (messages.length() != 0) {
        std::vector<Message> messageCollection = convertInVectorOfMessages(messages);
        Message message(messageCollection[0].getSender(), messageCollection[0].getReciever(),
                        messageCollection[0].getContent());
        messageCollection.erase(messageCollection.begin());
        std::string lastMessages;
        for (size_t i = 0; i < messageCollection.size(); i++) {
            lastMessages.append(messageCollection[i].toString());
            if (i + 1 != messageCollection.size()) {
                lastMessages += Constant::messagesSeparator;
            }
        }
        database->set(lastMessageKey, lastMessages);

        return message;
    } else {
        Message empty;
        return empty;
    }
}

MessagesService::~MessagesService() {
}
