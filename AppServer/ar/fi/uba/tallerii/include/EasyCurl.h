//
// Copyright 2016 FiUBA
//

#ifndef TINDER_EASY_CURL_H
#define TINDER_EASY_CURL_H

#include <curl/curl.h>
#include <string.h>
#include <string>
#include <fstream>
#include <cstdlib>

using std::ifstream;
using std::ostream;
using std::istream;
using std::string;


class EasyCurl {

public:
    EasyCurl() {
        m_curl = curl_easy_init();
        error = new char[CURL_ERROR_SIZE];
        curl_easy_setopt(m_curl, CURLOPT_ERRORBUFFER, error);
        Init();
    }

    EasyCurl(CURL *curl) {
        m_curl = curl_easy_duphandle(curl);
        Init();
    }

    EasyCurl(const string &host) {
        m_curl = curl_easy_init();
        if (m_url) free(m_url);
        const char *hostUrl = host.c_str();
        m_url = strdup(hostUrl);
        curl_easy_setopt(m_curl, CURLOPT_URL, m_url);
        Init();
    }

    EasyCurl(const EasyCurl &rhs) {
        //copy ctor for duplicating the handle so you can close the otherone
        m_curl = curl_easy_duphandle(rhs.m_curl);
        m_location = rhs.m_location;
        m_url = rhs.m_url;
        m_file = rhs.m_file;
        error = new char[CURL_ERROR_SIZE];
        strncpy(error, rhs.error, CURL_ERROR_SIZE);

    }

    ~EasyCurl() {
        if (m_file) {
            CloseFile(m_file);
        }
        curl_easy_cleanup(m_curl);
        ReleaseResources();
    }


    friend ostream &operator<<(ostream &output, const EasyCurl &curl) {
        /* Original line
        output << curl.m_url ? curl.m_url : "empty";
         */
        if (curl.m_url) {
            output << curl.m_url;
        } else {
            output << "empty";
        }

        return output;
    }

    bool IsOk() {
        return m_curl != NULL;
    }

    long GetCode() {
        long code;
        curl_easy_getinfo(m_curl, CURLINFO_HTTP_CODE, &code);
        return code;
    }

    string GetLastEffectiveUrl() {
        char *url;
        string ret;
        curl_easy_getinfo(m_curl, CURLINFO_EFFECTIVE_URL, &url);
        if (url) ret = url;
        return ret;
    }


    double GetDoubleInfo(CURLINFO opt) {
        double d;
        curl_easy_getinfo(m_curl, opt, &d);
        return d;
    }


    string GetStringInfo(CURLINFO opt) {
        char *info;
        curl_easy_getinfo(m_curl, opt, &info);
        string ret;
        if (info) ret = info;
        curl_free(info);
        return ret;
    }

    long GetLongInfo(CURLINFO opt) {
        long l;
        curl_easy_getinfo(m_curl, opt, &l);
        return l;

    }

    CURL *GetHandle() { return m_curl; }

    string GetFileLocation() { return m_location; }

    string GetLastError() { return error ? error : "No error information"; }

    bool UseCookieEngine() {
        return curl_easy_setopt(m_curl, CURLOPT_COOKIEFILE, "Q:\\asdfiw48rjasd-93jasj9f842rf90sdj.98r.34.as4.") ==
               CURLE_OK;
        // cheesy i know, but we need a fake name, VC6 complains and fails in debug mode setting it blank
    }

    bool SetCookieFile(const string &file) {

        return curl_easy_setopt(m_curl, CURLOPT_COOKIEFILE, file.c_str()) == CURLE_OK;
    }

    bool SetCookie(char *cookie) {
        return curl_easy_setopt(m_curl, CURLOPT_COOKIE, cookie) == CURLE_OK;
    }

    bool SetCookieJar(const string &_cookiejar) {
        if (m_cookiejar) free(m_cookiejar);
        m_cookiejar = strdup(_cookiejar.c_str());
        return curl_easy_setopt(m_curl, CURLOPT_COOKIEJAR, m_cookiejar) == CURLE_OK;
    }

    bool SetOpt(CURLoption opt, const string &value) {
        return curl_easy_setopt(m_curl, opt, value.c_str()) == CURLE_OK;
    }

    bool SetOpt(CURLoption opt, long value) {
        return curl_easy_setopt(m_curl, opt, value) == CURLE_OK;
    }

    bool SetUrl(const string &_url) {
        if (m_url != nullptr) {
            free(m_url);
        }
        m_url = strdup(_url.c_str());

        return curl_easy_setopt(m_curl, CURLOPT_URL, m_url) == CURLE_OK;
    }

    bool SetTimeout(long val) {
        return curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, val) == CURLE_OK;
    }

    bool SetTimeout(string val) {
        return curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, atol(val.c_str())) == CURLE_OK;
    }

    bool SetFile(FILE *file) {
        return curl_easy_setopt(m_curl, CURLOPT_FILE, file) == CURLE_OK;
    }

    bool SetFile(const string &location) {
        m_location = location;
        if (m_file) CloseFile(m_file);
        m_file = nullptr;
        m_file = fopen(location.c_str(), "w");
        return curl_easy_setopt(m_curl, CURLOPT_FILE, m_file) == CURLE_OK;
    }


    string ReadFile() {
        string buffer, line;
        if (m_file) CloseFile(m_file);
        ifstream in(m_location.c_str());
        if (in.good()) {
            while (!in.eof()) {
                std::getline(in, line);
                buffer += line;
            }
            in.close();
            return buffer;
        }
        in.close();
        return "error";
    }


    bool SetReferer(const string &referer) {
        return curl_easy_setopt(m_curl, CURLOPT_REFERER, referer.c_str()) == CURLE_OK;
    }

    bool SetUserAgent(const string &agent) {
        return curl_easy_setopt(m_curl, CURLOPT_USERAGENT, agent.c_str()) == CURLE_OK;
    }

    bool SetParms(const string &_parms) {
        if (m_parms) free(m_parms);
        m_parms = strdup(_parms.c_str());
        return curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, m_parms) == CURLE_OK;
    }

    bool SetProxy(const string &_proxy) {
        m_proxy = strdup(_proxy.c_str());
        return curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, m_proxy) == CURLE_OK;
    }

    bool SetRedirect(bool re) {
        return curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, re) == CURLE_OK;
    }

    bool SetMultipartForm(struct HttpPost *post) {
        return curl_easy_setopt(m_curl, CURLOPT_HTTPPOST, post) == CURLE_OK;
    }

    bool SSLVerifyPeer(bool b) {
        return curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, b) == CURLE_OK;
    }

    bool SSLVerifyHost(bool b) {
        return curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, b) == CURLE_OK;
    }


    bool SetInterface(string inter) {
        return curl_easy_setopt(m_curl, CURLOPT_INTERFACE, inter.c_str()) == CURLE_OK;
    }

    bool SetUserPassword(string data) {
        return curl_easy_setopt(m_curl, CURLOPT_USERPWD, data.c_str()) == CURLE_OK;
    }

    bool ForceGet() {
        return curl_easy_setopt(m_curl, CURLOPT_HTTPGET, 1) == CURLE_OK;
    }

    bool ForcePost() {
        return curl_easy_setopt(m_curl, CURLOPT_POST, 1) == CURLE_OK;
    }

    bool Perform() {
        return curl_easy_perform(m_curl) == CURLE_OK;
    }

    string StringPerform() {
        string temp = GetFileLocation() != "" ? GetFileLocation() : "none";
        SetFile("__curl__temp");
        if (!Perform()) {
            if (temp != "none") SetFile(temp); //return to normal
            return "error";
        }
        else {
            string html = ReadFile();
            if (temp != "none") SetFile(temp); //return to normal
            return html;
        }
    }

    bool Reset() {
        curl_easy_cleanup(m_curl);
        m_curl = NULL;

        if (m_url) free(m_url);
        if (m_cookiejar) free(m_cookiejar);
        if (m_proxy) free(m_proxy);
        if (m_parms) free(m_parms);

        Init();

        m_curl = curl_easy_init();
        curl_easy_setopt(m_curl, CURLOPT_ERRORBUFFER, error);
        return true;
    }

    void CloseFile() { if (m_file) CloseFile(m_file); }

    bool FollowRedirect() {
        return curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1) == CURLE_OK;
    }

    static string Escape(const char *data) {
        if (!data) return "";
        else {
            char *x = curl_escape(data, 0);
            string ret;
            if (x) ret = x;
            curl_free(x);
            return ret;
        }
    }

    static curl_slist *SlistAppend(struct curl_slist *list, const char *string) {
        return curl_slist_append(list, string);
    }

    bool SetVerbose(bool v) {
        return curl_easy_setopt(m_curl, CURLOPT_VERBOSE, v) == CURLE_OK;

    }


private:
    void Init() {
        ReleaseResources();
        m_url = nullptr;
        m_parms = nullptr;
        m_proxy = nullptr;
        m_file = nullptr;
        m_cookiejar = nullptr;
    }

    void ReleaseResources() {
        if (error != nullptr) {
            free(error);
        }
        if (m_url != nullptr) {
            free(m_url);
        }
        if (m_parms != nullptr) {
            free(m_parms);
        }
        if (m_proxy != nullptr) {
            free(m_proxy);
        }
        if (m_proxy != nullptr) {
            free(m_cookiejar);
        }
    }

    void CloseFile(FILE* & file) {
        if(file) {
            fclose(file);
            file = nullptr;
        }
    }

    CURL *m_curl = nullptr;
    FILE *m_file = nullptr;
    char *error = nullptr;
    char *m_url = nullptr;
    char *m_parms = nullptr;
    char *m_proxy = nullptr;
    char *m_cookiejar = nullptr;
    string m_location = "";
};

#endif //TINDER_EASY_CURL_H
