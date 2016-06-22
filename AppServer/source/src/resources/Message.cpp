//
// Copyright 2016 FiUBA
//

#include "Message.h"
#include <string>
#include "Constant.h"
#include <vector>

Message::Message(const std::string sender, const std::string reciever, const std::string content) : sender(sender),
                                                                                                    reciever(reciever),
                                                                                                    content(content) {
}

Message::Message() : Message("", "", "") {
}

std::string Message::getContent() {
    return this->content;
}

std::string Message::getReciever() {
    return this->reciever;
}

std::string Message::getSender() {
    return this->sender;
}

std::string Message::toString() {
    return this->getSender() + Constant::messageComponentDivider + this->getReciever() +
           Constant::messageComponentDivider + this->getContent();
}

static std::vector<std::string> splitString(const std::string unparsed, const std::string delimiter) {
    std::string stringToParse(unparsed);
    std::vector<std::string> parsed;
    size_t pos = 0;
    std::string token;
    while ((pos = stringToParse.find(delimiter)) != std::string::npos) {
        token = stringToParse.substr(0, pos);
        parsed.push_back(token);
        stringToParse.erase(0, pos + delimiter.length());
    }

    parsed.push_back(stringToParse);
    return parsed;
}


void Message::loadFromString(std::string sourceString) {
    std::vector<std::string> message = splitString(sourceString, Constant::messageComponentDivider);
    if (message.size() == 3) {
        this->sender = message[0];
        this->reciever = message[1];
        this->content = message[2];
    }
}
