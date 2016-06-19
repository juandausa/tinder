//
// Copyright 2016 FiUBA
//

#include <string>
#include "Mongoose.h"
#include "FilterController.h"
#include "Response.h"

FilterController::FilterController(FilterService filter_service) : filter_service(filter_service) {
}

void FilterController::handle_update_filters(RequestParser requestParser, Response response) {
    std::string userId = requestParser.getResourceId();
    std::string body = requestParser.getBody();
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(body, root, true);
    if (!parsingSuccessful) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
    } else {
        if (this->filter_service.update_filters(userId, body)) {
            response.SetCode(200);
            response.SetBody(this->getSucceedResponseBody());
        } else {
            response.SetCode(500);
            response.SetBody(this->getErrorResponseBody());
        }
    }

    response.Send();
}

void FilterController::handle_get_filters(RequestParser requestParser, Response response) {
    std::string userId = requestParser.getResourceId();
    std::string body = this->filter_service.get_filters(userId);
    if (body.length() == 0) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
        response.Send();
    } else {
        response.SetCode(200);
        response.SetBody(this->makeResponseBodyForGet(body));
        response.Send();
    }
}

std::string FilterController::makeResponseBodyForGet(const std::string info) {
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(info, root, true);
    if (!parsingSuccessful) {
        return this->getErrorResponseBody();
    }

    root["status_code"] = 200;
    return fastWriter.write(root);
}

std::string FilterController::getErrorResponseBody() {
    Json::Value errorResponse;
    errorResponse["status_code"] = 500;
    return this->fastWriter.write(errorResponse);
}

std::string FilterController::getSucceedResponseBody() {
    Json::Value succeedResponse;
    succeedResponse["status_code"] = 200;
    return this->fastWriter.write(succeedResponse);
}
