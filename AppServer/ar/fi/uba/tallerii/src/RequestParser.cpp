//
// // Copyright 2016 FiUBA
//

#include "RequestParser.h"
#include <string>


void RequestParser::parse(struct http_message *hm) {
    this->method = std::string(reinterpret_cast<const char*>(hm->method.p)).substr(0 , hm->method.len);
    this->body = std::string(reinterpret_cast<const char*>(hm->body.p)).substr(0 , hm->body.len);
    std::string completeUrl = std::string(reinterpret_cast<const char*>(hm->uri.p)).substr(0 , hm->uri.len);
    this->uri = completeUrl.substr(0 , completeUrl.find("/" , 1));
    this->resourceId = completeUrl.substr(completeUrl.find("/" , 1)+1, completeUrl.length());
    return;
}

std::string RequestParser::getUrl() {
    return this->uri;
}

std::string RequestParser::getResourceId() {
    return this->resourceId;
}

std::string RequestParser::getMethod() {
    return this->method;
}

std::string RequestParser::getBody() {
    return this->body;
}

bool RequestParser::isUserLoginRequest() {
    return (this->uri == "/login" && this->method == "GET");
}

bool RequestParser::isUserRegisterRequest() {
    return (this->uri == "/register" && this->method == "POST");
}

bool RequestParser::isUserInfoRequest() {
    return (this->uri == "/user" && this->method == "GET");
}

bool RequestParser::isUserUpdateRequest() {
    return (this->uri == "/user" && this->method == "PUT");
}

bool RequestParser::isFiltersGetRequest() {
    return (this->uri == "/filters" && this->method == "GET");
}

bool RequestParser::isFiltersPostRequest() {
    return (this->uri == "/filters" && this->method == "POST");
}

bool RequestParser::isCandidatesGetRequest() {
    return (this->uri == "/candidates" && this->method == "GET");
}

bool RequestParser::isMatchesGetRequest() {
    return (this->uri == "/matches" && this->method == "GET");
}

bool RequestParser::isAddLikeRequest() {
    return (this->uri == "/likes" && this->method == "POST");
}

bool RequestParser::isAddDislikeRequest() {
    return (this->uri == "/dislikes" && this->method == "POST");
}

bool RequestParser::isAddMessagesRequest() {
    return (this->uri == "/message" && this->method == "POST");
}

bool RequestParser::isGetMessagesRequest() {
    return (this->uri == "/message" && this->method == "GET");
}