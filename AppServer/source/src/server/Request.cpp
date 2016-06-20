//
// // Copyright 2016 FiUBA
//

#include "Request.h"
#include <string>
#include "AddLikeController.h"
#include "AddDisLikeController.h"
#include "UserLoginController.h"
#include "UserRegisterController.h"
#include "GetCandidatesController.h"
#include "GetUserInfoController.h"
#include "UpdateUserInfoController.h"
#include "GetFiltersController.h"
#include "UpdateFiltersController.h"
#include "MatchesController.h"
#include "AddMessagesController.h"
#include "GetMessagesController.h"

Request::Request(Response &response):response(response){}

Request ::~Request() { 
    if (this->genericController){
        delete this->genericController;
    }
}


void Request::parse(struct http_message *hm) {
    this->method = std::string(reinterpret_cast<const char*>(hm->method.p)).substr(0 , hm->method.len);
    this->body = std::string(reinterpret_cast<const char*>(hm->body.p)).substr(0 , hm->body.len);
    std::string completeUrl = std::string(reinterpret_cast<const char*>(hm->uri.p)).substr(0 , hm->uri.len);
    this->uri = completeUrl.substr(0 , completeUrl.find("/" , 1));
    this->resourceId = completeUrl.substr(completeUrl.find("/" , 1)+1, completeUrl.length());
}

std::string Request::getUrl() {
    return this->uri;
}

std::string Request::getResourceId() {
    return this->resourceId;
}

std::string Request::getMethod() {
    return this->method;
}

std::string Request::getBody() {
    return this->body;
}

void Request::execute(){
    std::cout << this->uri << this->method << std::endl;
    
    this->genericController->operation(*this,response);
}

void Request::handleOperation(){
    if (this->isUserLoginRequest()) {
        this->genericController = new UserLoginController();
    } else if (this->isUserRegisterRequest()) {
        this->genericController = new UserRegisterController();
    } else if (this->isUserInfoRequest()) {
        this->genericController = new GetUserInfoController();
    } else if (this->isCandidatesGetRequest()) {
        this->genericController = new GetCandidatesController();
    } else if (this->isUserUpdateRequest()) {
        this->genericController = new UpdateUserInfoController();
    } else if (this->isFiltersPostRequest()) {
        this->genericController = new UpdateFiltersController();
    } else if (this->isMatchesGetRequest()) {
        this->genericController = new MatchesController();
    } else if (this->isFiltersGetRequest()) {
        this->genericController = new GetFiltersController();
    } else if (this->isAddLikeRequest()) {
        this->genericController = new AddLikeController();
    } else if (this->isAddDislikeRequest()) {
        this->genericController = new AddDisLikeController();
    } else if (this->isAddMessagesRequest()) {
        this->genericController = new AddMessagesController();
    } else if (this->isGetMessagesRequest()) {
        this->genericController = new GetMessagesController();
    }
}

bool Request::isUserLoginRequest() {
    return (this->uri == "/login" && this->method == "GET");
}

bool Request::isUserRegisterRequest() {
    return (this->uri == "/register" && this->method == "POST");
}

bool Request::isUserInfoRequest() {
    return (this->uri == "/user" && this->method == "GET");
}

bool Request::isUserUpdateRequest() {
    return (this->uri == "/user" && this->method == "PUT");
}

bool Request::isFiltersGetRequest() {
    return (this->uri == "/filters" && this->method == "GET");
}

bool Request::isFiltersPostRequest() {
    return (this->uri == "/filters" && this->method == "POST");
}

bool Request::isCandidatesGetRequest() {
    return (this->uri == "/candidates" && this->method == "GET");
}

bool Request::isMatchesGetRequest() {
    return (this->uri == "/matches" && this->method == "GET");
}

bool Request::isAddLikeRequest() {
    return (this->uri == "/likes" && this->method == "POST");
}

bool Request::isAddDislikeRequest() {
    return (this->uri == "/dislikes" && this->method == "POST");
}

bool Request::isAddMessagesRequest() {
    return (this->uri == "/sendmessage" && this->method == "POST");
}

bool Request::isGetMessagesRequest() {
    return (this->uri == "/getmessage" && this->method == "POST");
}
