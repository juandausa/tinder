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
    Json::Value messages(Json::arrayValue);
    bool parsingSuccessful = this->reader.parse(previousMessages, messages, true);
    if (!parsingSuccessful) {
        log->writeAndPrintLog("Adding message. Parser error", Log::WARNING);
    }
    Json::Value jsonMessage;
    jsonMessage["sender"] = message.getSender();
    jsonMessage["reciever"] = message.getReciever();
    jsonMessage["content"] = message.getContent();
    bool result;
    if (previousMessages.length() != 0) {
        messages[messages.size()] = jsonMessage;
        result = this->database->set(key, messages.toStyledString());
    } else {
        messages[0] = jsonMessage;
        result = this->database->set(key, messages.toStyledString());
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
        log->writeAndPrintLog("Adding message. The database is closed.", Log::WARNING);
        return false;
    }
}


std::vector<Message> convertInVectorOfMessages(Json::Value jsonMessages) {
    std::vector<Message> messages;
    for (unsigned int i = 0; i < jsonMessages.size(); ++i) {
        Message m;
        Json::Value jsonMessage = jsonMessages[i];
        Message message(jsonMessage["sender"].asString(),jsonMessage["reciever"].asString(),jsonMessage["content"].asString());
        messages.push_back(m);
    }

    return messages;
}

std::vector<Message> MessagesService::getMessages(std::string userA, std::string userB) {
    if (!this->database->is_open()) {
        log->writeAndPrintLog("Adding message. The database is closed.", Log::WARNING);
        std::vector<Message> empty;
        return empty;
    }
    log->writeAndPrintLog(std::string("Getting messages between users '") + userA
                          + std::string("' and '") + userB + std::string("'."), Log::INFO);
    std::string messages;
    std::string messagesKeySender = Constant::messagesPrefix + userA + userB;
    std::string lastMessageKey = Constant::lastMessagesPrefix + userA + userB;
    this->database->get(messagesKeySender, &messages);
    this->database->set(lastMessageKey, "");
    if (messages.length() != 0) {
        Json::Value jsonMessages(Json::arrayValue);
        bool parsingSuccessful = this->reader.parse(messages, jsonMessages, true);
        if (!parsingSuccessful) {
            log->writeAndPrintLog("Adding message. Parser error", Log::WARNING);
        }

        return convertInVectorOfMessages(jsonMessages);
    }

    std::vector<Message> empty;
    return empty;
}

Message MessagesService::getLastMessage(std::string sender, std::string reciever) {
    if (!this->database->is_open()) {
        log->writeAndPrintLog("Adding message. The database is closed.", Log::WARNING);
        Message empty;
        return empty;
    }

    log->writeAndPrintLog(std::string("Getting messages between users '") + sender
                          + std::string("' and '") + reciever + std::string("'."), Log::INFO);
    std::string messages;
    std::string lastMessageKey = Constant::lastMessagesPrefix + sender + reciever;
    this->database->get(lastMessageKey, &messages);
    if (messages.length() != 0) {
        Json::Value jsonMessages(Json::arrayValue);
        bool parsingSuccessful = this->reader.parse(messages, jsonMessages, true);
        if (!parsingSuccessful) {
            log->writeAndPrintLog("Adding message. Parser error", Log::WARNING);
        }
        Json::Value jsonMessage = jsonMessages[jsonMessages.size()-1];
        Message message(jsonMessage["sender"].asString(),jsonMessage["reciever"].asString(),jsonMessage["content"].asString());
        jsonMessages.resize(jsonMessages.size()-1);
        std::string lastMessages(jsonMessages.toStyledString());
        database->set(lastMessageKey, lastMessages);
        return message;
    } else {
        Message empty;
        return empty;
    }
}

MessagesService::~MessagesService() {
}
