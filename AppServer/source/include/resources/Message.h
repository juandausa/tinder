//
// Created by juan on 17/06/16.
//

#ifndef TINDER_MESSAGE_H
#define TINDER_MESSAGE_H

#include <string>

class Message {
public:
    Message(const std::string sender, const std::string reciever, const std::string content);
    Message();
    std::string toString();
    void loadFromString(std::string sourceString);
    std::string getSender();
    std::string getReciever();
    std::string getContent();
private:
    std::string sender;
    std::string reciever;
    std::string content;
};


#endif //TINDER_MESSAGE_H
