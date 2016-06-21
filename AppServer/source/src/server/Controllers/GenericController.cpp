//
// Copyright 2016 FiUBA
//

#include "GenericController.h"
#include <string>

GenericController::GenericController() {
    this->log = Log::getInstance();
}

GenericController::~GenericController() { }

void GenericController::operation(Request &request, Response &response) {
    log->writeAndPrintLog("GenericController", Log::INFO);
}

std::string GenericController::getErrorResponseBody() {
    Json::Value errorResponse;
    errorResponse["status_code"] = 500;
    return this->fastWriter.write(errorResponse);
}

std::string GenericController::getSucceedResponseBody() {
    Json::Value succeedResponse;
    succeedResponse["status_code"] = 200;
    return this->fastWriter.write(succeedResponse);
}
