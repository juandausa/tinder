//
// Copyright 2016 FiUBA
//

#include "MatchesService.h"
#include "DataBase.h"
#include "CurlWrapper.h"
#include <string>

MatchesService::MatchesService() {
    this->database = DataBase::getInstance();
}

std::string MatchesService::getMatchPhoto(std::string url) {
    CurlWrapper curlWrapper;
    curlWrapper.set_get_url(url);
    std::string readBuffer;
    curlWrapper.set_get_buffer(readBuffer);
    curlWrapper.perform_request();
    return readBuffer;
}




MatchesService::~MatchesService() {
}
