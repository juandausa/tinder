//
// Copyright 2016 FiUBA
//

#include "CurlWrapper.h"
#include "PhotoService.h"
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <iostream>
#include <string>

bool PhotoService::update(std::string userId, std::string photoBase64) {
    CurlWrapper *curlWrapper = new CurlWrapper();
    std::string url = "https://enigmatic-scrubland-75073.herokuapp.com/";
    curlWrapper->set_post_url(url+"users/"+userId+"/photo");
    std::string readBuffer;
    Json::Value photoData;
    photoData["photo"] = photoBase64;
    Json::FastWriter writer;
    std::string data = writer.write(photoData);
    curlWrapper->set_put_data(data, readBuffer);
    bool res = curlWrapper->perform_request();
    if (!res) {
        std::cout << "Failed to post new interests\n";
        return false;
    }
    return true;
}
