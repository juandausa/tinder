//
// Created by agu on 27/04/16.
//

#include "RequestParser.h"



void RequestParser::parse(struct http_message *hm){
    this->method = std::string((char*)hm->method.p).substr(0,hm->method.len);
    this->body = std::string((char*)hm->body.p).substr(0,hm->body.len);
    std::string completeUrl = std::string((char*)hm->uri.p).substr(0,hm->uri.len);
    this->uri = completeUrl.substr(0,completeUrl.find("/",1));
    this->resourceId = completeUrl.substr(completeUrl.find("/",1)+1,completeUrl.length());
    return;
}
std::string RequestParser::getUrl(){
    return this->uri;
}
std::string RequestParser::getResourceId(){
    return this->resourceId;
}
std::string RequestParser::getMethod(){
    return this->method;
}
std::string RequestParser::getBody(){
    return this->body;
}



bool RequestParser::isUserLoginRequest(){
    return (this->uri == "/login" && this->method == "GET");
}

bool RequestParser::isUserRegisterRequest(){
    return (this->uri == "/register" && this->method == "POST");
}

bool RequestParser::isUserInfoRequest(){
    return (this->uri == "/user" && this->method == "GET");
}

bool RequestParser::isUserUpdateRequest(){
    return (this->uri == "/user" && this->method == "PUT");
}

bool RequestParser::isFiltersGetRequest(){
    return (this->uri == "/filters" && this->method == "GET");
}

bool RequestParser::isFiltersPostRequest(){
    return (this->uri == "/filters" && this->method == "POST");
}