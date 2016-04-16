//
// Copyright 2016 FiUBA
//

#include "Response.h"
#include "Mongoose.h"
#include <string>
#include <utility>
#include <vector>
#include <map>

Response :: Response(struct mg_connection *nc) : connection(nc) {
    this->statusCodes[200] = "200 OK";
    this->statusCodes[201] = "201 Created";
    this->statusCodes[202] = "201 Accepted";
    this->statusCodes[300] = "300 Multiple Choices";
    this->statusCodes[301] = "301 Moved Permanently";
    this->statusCodes[302] = "302 Found";
    this->statusCodes[304] = "304 Not Modified";
    this->statusCodes[400] = "400 Bad Request";
    this->statusCodes[401] = "401 Unauthorized";
    this->statusCodes[404] = "404 Not Found";
    this->statusCodes[405] = "405 Method Not Allowed";
    this->statusCodes[500] = "500 Internal Server Error";
    this->statusCodes[501] = "501 Not Implemented";
    this->statusCodes[503] = "503 Service Unavailable";
}

void Response :: SetCode(int code) {
    if ( this->statusCodes.count(code) != 0 ) {
        this->code = code;
    } else {
        this->code = DEFAUTLRESPONSE;
    }
}

int Response ::GetCode() {
    return this->code;
}

void Response :: AddHeader(std::string key, std::string value) {
    std::pair<std::string, std::string> header(key, value);
    this->headers.push_back(header);
}

std::vector<std::pair<std::string, std::string>> Response ::GetHeaders() {
    return this->headers;
}

void Response :: SetBody(std::string body) {
    this->body = body;
}

std::string Response ::GetBody() {
    return this->body;
}

void Response :: Send() {
    // TODO(juandausa): AddHeaders
    std::string header("HTTP/1.1 " + this->statusCodes[this->code] + "\r\nTransfer-Encoding: chunked\r\n\r\n");
    mg_printf(this->connection, "%s", header.c_str());
    mg_printf_http_chunk(this->connection, this->body.c_str());
    mg_send_http_chunk(this->connection, "", 0);
}
