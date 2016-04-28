//
// Copyright 2016 FiUBA
//

#include <glog/logging.h>
#include <signal.h>
#include <iostream>
#include <vector>
#include <string>
#include "Mongoose.h"
#include "Server.h"
#include "PlusController.h"
#include "UserController.h"
#include "FilterController.h"
#include "Response.h"
#include "DataBase.h"
#include "Constant.h"
#include "UserService.h"
#include "FilterService.h"
#include "SecurityManager.h"

static struct mg_serve_http_opts s_http_server_opts;
static int s_sig_num = 0;

static void signal_handler(int sig_num) {
    signal(sig_num, signal_handler);
    s_sig_num = sig_num;
}

void handle_print_content(struct http_message *hm) {
    char buf[100] = {0};
    memcpy(buf, hm->body.p,
           sizeof(buf) - 1 < hm->body.len? sizeof(buf) - 1 : hm->body.len);
    printf("%s\n", buf);
}

void Server :: ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;
    switch (ev) {
        case MG_EV_HTTP_REQUEST:
        {
            DataBase db(Constant::database_path);
            UserService user_service(db);
            SecurityManager security(user_service);
            Response response(nc);
            RequestParser requestParser;
            requestParser.parse(hm);
            std::cout << "Url: " << requestParser.getUrl() << "Method: " << requestParser.getMethod() << std::endl;

            security.filter_request(nc, hm, response);
            if (requestParser.isUserLoginRequest()) {
                UserController user_controller(user_service);
                user_controller.handleLogin(nc, hm, response);
            } else if (requestParser.isUserRegisterRequest()) {
                UserController user_controller(user_service);
                user_controller.handleRegistration(nc, hm, response);
            } else if (requestParser.isUserInfoRequest()) {
                UserController user_controller(user_service);
                user_controller.handleGetUserInfo(nc, hm, response);
            } else if (requestParser.isCandidatesGetRequest()) {
                UserController user_controller(user_service);
                user_controller.handleShowCandidates(nc, hm, response);
            } else if (requestParser.isUserUpdateRequest()) {
                UserController user_controller(user_service);
                user_controller.handleUpdateUserInfo(nc, hm, response);
            } else if (requestParser.isFiltersPostRequest()) {
                FilterService filter_service(db);
                FilterController filter_controller(filter_service);
                filter_controller.handle_update_filters(nc, hm, response);
            } else if (requestParser.isMatchesGetRequest()) {
                UserController user_controller(user_service);
                user_controller.handleGetMatches(nc, hm, response);
            } else if (requestParser.isFiltersGetRequest()) {
                FilterService filter_service(db);
                FilterController filter_controller(filter_service);
                filter_controller.handle_get_filters(nc, hm, response);
            }

            break;
        }
        default:
            break;
    }
}

Server :: Server(std::vector<std::string> options) : options(options), port(Constant::server_port) {
}

Server :: Server() : options(std::vector<std::string>()), port(Constant::server_port) {
}

void Server :: start() {
    struct mg_mgr mgr;
    struct mg_connection *nc;
    this->port = Constant :: server_port;

    mg_mgr_init(&mgr, NULL);

    /* Set HTTP server options */
    nc = mg_bind(&mgr, this->port.c_str(), Server :: ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Error starting server on port %s\n", this->port.c_str());
        exit(1);
    }

#ifdef MG_ENABLE_SSL
    if (ssl_cert != NULL) {
    const char *err_str = mg_set_ssl(nc, ssl_cert, NULL);
    if (err_str != NULL) {
      fprintf(stderr, "Error loading SSL cert: %s\n", err_str);
      exit(1);
    }
  }
#endif

    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = ".";
    s_http_server_opts.enable_directory_listing = "yes";

    /* Use current binary directory as document root */
    s_http_server_opts.document_root = "../files/";

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    LOG(INFO) << "Starting RESTful server on port " << this->port;
    std::cout << "Starting RESTful server on port " << this->port << std::endl;
    while (s_sig_num == 0) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    std::cout << "Finishing RESTful server on port " << this->port << std::endl;
    return;
}

Server ::~Server() { }
