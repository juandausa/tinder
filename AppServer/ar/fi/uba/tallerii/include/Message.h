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
    virtual std::string toString();
    virtual void loadFromString(std::string sourceString);
    virtual std::string getSender();
    virtual std::string getReciever();
    virtual std::string getContent();
private:
    std::string sender;
    std::string reciever;
    std::string content;
};


#endif //TINDER_MESSAGE_H
