//
// Created by jasmina on 23/04/16.
//

#ifndef TINDER_CURL_H
#define TINDER_CURL_H

#include <stdio.h>
#include <string>
#include <curl/curl.h>
#include <curl/easy.h>



class CurlWrapper {
private:
    CURL *curl;
    CURLcode res;

public:
    CurlWrapper();
    ~CurlWrapper();
    void set_post_url(const std::string url);
    void set_post_data(const std::string data, std::string &readBuffer);
    void set_get_buffer(const std::string &readBuffer);
    bool perform_request();
    void clean();
};



#endif //TINDER_CURL_H
