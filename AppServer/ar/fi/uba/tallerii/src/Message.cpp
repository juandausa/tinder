//
// Copyright 2016 FiUBA
//

#include "Message.h"
#include <string>
#include <Constant.h>

Message::Message(const std::string sender, const std::string reciever, const std::string content) : sender(sender),
                                                                                                    reciever(reciever),
                                                                                                    content(content) {
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

void Message::loadFromString(std::string sourceString) { }
