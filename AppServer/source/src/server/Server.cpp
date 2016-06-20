//
// Copyright 2016 FiUBA
//

#include <signal.h>
#include <iostream>
#include <vector>
#include <string>
#include "Mongoose.h"
#include "Server.h"
#include "Response.h"
#include "Constant.h"
#include "Log.h"
#include "UserService.h"


Server :: Server(std::vector<std::string> options) : options(options), port(Constant::server_port) {
}

Server :: Server() : options(std::vector<std::string>()), port(Constant::server_port) {
}


static struct mg_serve_http_opts s_http_server_opts;
static int s_sig_num = 0;

static void signal_handler(int sig_num) {
    signal(sig_num, signal_handler);
    s_sig_num = sig_num;
}


void Server::ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;
    switch (ev) {
        case MG_EV_HTTP_REQUEST:
        {
            UserService user_service;
            Response response(nc);
            Request request(response);
            request.parse(hm);
            Log* log = Log::getInstance();
            log->writeAndPrintLog(std::string("Url: ") + request.getUrl() 
                                    +  std::string("Method: ") + request.getMethod(),Log::INFO);
            SecurityManager security(user_service);
            security.filter_request(nc, hm, response);

            request.handleOperation();
            request.execute();

            break;
        }
        default:
            break;
    }
}



void Server :: start() {
    struct mg_mgr mgr;
    struct mg_connection *nc;
    this->port = Constant :: server_port;

    mg_mgr_init(&mgr, NULL);

    Log* log = Log::getInstance();
    
    /* Set HTTP server options */
    nc = mg_bind(&mgr, this->port.c_str(), Server::ev_handler);
    if (nc == NULL) {
        log->writeAndPrintLog(std::string("Error starting server on port ") + this->port, Log::FATAL);
        exit(1);
    }

    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = ".";
    s_http_server_opts.enable_directory_listing = "yes";

    /* Use current binary directory as document root */
    s_http_server_opts.document_root = "../files/";

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    log->writeAndPrintLog(std::string("Starting RESTful server on port") + this->port ,Log::INFO);
    while (s_sig_num == 0) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);
    log->writeAndPrintLog(std::string("Finishing RESTful server on port") + this->port ,Log::INFO);
    return;
}

Server ::~Server() { }
