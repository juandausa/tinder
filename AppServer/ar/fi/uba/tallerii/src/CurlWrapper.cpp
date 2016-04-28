//
// Copyright 2016 FiUBA
// Created by jasmina on 23/04/16.
//

#include "CurlWrapper.h"
#include <string>
#include <iostream>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append(reinterpret_cast<char*>contents, size * nmemb);
    return size * nmemb;
}

CurlWrapper::CurlWrapper() {
    curl_global_init(CURL_GLOBAL_ALL);
    /* get a curl handle */
    curl = curl_easy_init();
}

CurlWrapper::~CurlWrapper() {
}

void CurlWrapper::set_post_url(const std::string url) {
    if (curl) {
        /* First set the URL that is about to receive our POST. This URL can
           just as well be a https:// URL if that is what should receive the
           data. */
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    }
}

void CurlWrapper::set_post_data(const std::string data) {
    if (curl) {
        /* Now specify the POST data */
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    }
}


void CurlWrapper::set_get_buffer(const std::string readBuffer) {
    if (curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    }
}

bool CurlWrapper::perform_request() {
    if (curl) {
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            return false;
        }
        /* always cleanup */
        curl_easy_cleanup(curl);
        return true;
    }
    return false;
}

void CurlWrapper::clean() {
    curl_global_cleanup();
}
