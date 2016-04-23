//
// Created by jasmina on 23/04/16.
//

#ifndef TINDER_CURL_H
#define TINDER_CURL_H


class Curl {
private:
    CURL *curl;
    CURLcode res;

public:
    Curl();
    ~Curl();
    void set_post_url(const std::string url);
    void set_post_data(const std::string data);
    bool perform_request();
    void clean();
};



#endif //TINDER_CURL_H
