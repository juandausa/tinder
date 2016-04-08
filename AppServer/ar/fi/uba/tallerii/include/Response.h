//
// Copyright 2016 FiUBA
//

#ifndef TINDER_REPONSE_H
#define TINDER_REPONSE_H
#ifndef DEFAUTLRESPONSE
#define DEFAUTLRESPONSE 500
#endif

#include <string>
#include <utility>
#include <vector>
#include <map>

class Response {
    /*
     * This class represents a response.
     */
public:
    Response(struct mg_connection *nc);
    void SetCode(int code);
    void AddHeader(std::string key, std::string value);
    void SetBody(std::string body);
    void Send();
private:
    struct mg_connection *connection;
    int code;
    std::string method;
    std::vector<std::pair<std::string, std::string>> headers;
    std::string body;
    std::map<int, std::string> statusCodes;
};


#endif //TINDER_REPONSE_H
