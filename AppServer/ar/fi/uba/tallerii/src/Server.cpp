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
            if (mg_vcmp(&hm->uri, "/api/v1/sum") == 0) {
                PlusController plus_controller;
                plus_controller.handle_sum_call(nc, hm);
            } else if ((mg_vcmp(&hm->uri, "/login") == 0) && mg_vcmp(&hm->method, "GET") == 0) {
                DataBase db(Constant::database_path);
                UserService user_service(db);
                Response response(nc);
                UserController user_controller(user_service);
                user_controller.handle_login(nc, hm, response);
            } else if ((mg_vcmp(&hm->uri, "/register") == 0) && mg_vcmp(&hm->method, "POST") == 0) {
                DataBase db(Constant::database_path);
                UserService user_service(db);
                Response response(nc);
                UserController user_controller(user_service);
                user_controller.handle_registration(nc, hm, response);
            } else if ((mg_vcmp(&hm->uri, "/filters") == 0) && mg_vcmp(&hm->method, "POST") == 0) {
                DataBase db(Constant::database_path);
                FilterService filter_service(db);
                Response response(nc);
                FilterController filter_controller(filter_service);
                filter_controller.handle_update_filters(nc, hm, response);
            } else if (mg_vcmp(&hm->uri, "/printcontent") == 0) {
                handle_print_content(hm);
            } else {
                mg_serve_http(nc, hm, s_http_server_opts);  /* Serve static content */
            }
            break;
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
    unsigned int i;
    this->port = Constant :: server_port;
#ifdef MG_ENABLE_SSL
    const char *ssl_cert = NULL;
#endif

    mg_mgr_init(&mgr, NULL);

    /* Process command line options to customize HTTP server */
    for (i = 1; i < this->options.size(); i++) {
        if (strcmp(this->options[i].c_str(), "-D") == 0 && i + 1 < this->options.size()) {
            mgr.hexdump_file = this->options[++i].c_str();
        } else if (strcmp(this->options[i].c_str(), "-d") == 0 && i + 1 < this->options.size()) {
            s_http_server_opts.document_root = this->options[++i].c_str();
        } else if (strcmp(this->options[i].c_str(), "-a") == 0 && i + 1 < this->options.size()) {
            s_http_server_opts.auth_domain = this->options[++i].c_str();
#ifdef MG_ENABLE_JAVASCRIPT
            } else if (strcmp(this->options[i].c_str(), "-j") == 0 && i + 1 < this->options.size()) {
      const char *init_file = this->options[++i].c_str();
      mg_enable_javascript(&mgr, v7_create(), init_file);
#endif
        } else if (strcmp(this->options[i].c_str(), "-P") == 0 && i + 1 < this->options.size()) {
            s_http_server_opts.global_auth_file = this->options[++i].c_str();
        } else if (strcmp(this->options[i].c_str(), "-A") == 0 && i + 1 < this->options.size()) {
            s_http_server_opts.per_directory_auth_file = this->options[++i].c_str();
        } else if (strcmp(this->options[i].c_str(), "-r") == 0 && i + 1 < this->options.size()) {
            s_http_server_opts.url_rewrites = this->options[++i].c_str();
#ifndef MG_DISABLE_CGI
        } else if (strcmp(this->options[i].c_str(), "-i") == 0 && i + 1 < this->options.size()) {
            s_http_server_opts.cgi_interpreter = this->options[++i].c_str();
#endif
#ifdef MG_ENABLE_SSL
        } else if (strcmp(this->options[i].c_str(), "-s") == 0 && i + 1 < this->options.size()) {
            ssl_cert = this->options[++i].c_str();
#endif
        } else {
            fprintf(stderr, "Unknown option: [%s]\n", this->options[i].c_str());
            exit(1);
        }
    }

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
