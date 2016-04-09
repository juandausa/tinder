//
// Copyright 2016 FiUBA
//

#include <glog/logging.h>
#include <iostream>
#include <vector>
#include <string>
#include "Mongoose.h"
#include "Server.h"
#include "PlusController.h"
#include "UserController.h"
#include "Response.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;
static int s_sig_num = 0;

static void signal_handler(int sig_num) {
    signal(sig_num, signal_handler);
    s_sig_num = sig_num;
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;
    switch (ev) {
        case MG_EV_HTTP_REQUEST:
            if (mg_vcmp(&hm->uri, "/api/v1/sum") == 0) {
                /* Handle RESTful call */
                PlusController plus_controller;
                plus_controller.handle_sum_call(nc, hm);
            } else if ((mg_vcmp(&hm->uri, "/login") == 0) && mg_vcmp(&hm->method, "GET") == 0) {
                DataBase database("/tmp/tinderdb");
                if (!database.is_open()) {
                    LOG(FATAL) << "Can not create the database.";
                }
                Response response(nc);
                UserController user_controller(database);
                user_controller.handle_login(nc, hm, response);
                database.~DataBase();
            } else if (mg_vcmp(&hm->uri, "/printcontent") == 0) {
                char buf[100] = {0};
                memcpy(buf, hm->body.p,
                       sizeof(buf) - 1 < hm->body.len? sizeof(buf) - 1 : hm->body.len);
                printf("%s\n", buf);
            } else {
                mg_serve_http(nc, hm, s_http_server_opts);  /* Serve static content */
            }
            break;
        default:
            break;
    }
}

Server :: Server() {
    this->options = std::vector<std::string>();
}

void Server :: start() {
    struct mg_mgr mgr;
    struct mg_connection *nc;
    unsigned int i;
    unsigned int optionsLength = this->options.size();
#ifdef MG_ENABLE_SSL
    const char *ssl_cert = NULL;
#endif

    mg_mgr_init(&mgr, NULL);

    /* Process command line options to customize HTTP server */
    for (i = 1; i < optionsLength; i++) {
        if (strcmp(this->options[i].c_str(), "-D") == 0 && i + 1 < optionsLength) {
            mgr.hexdump_file = this->options[++i].c_str();
        } else if (strcmp(this->options[i].c_str(), "-d") == 0 && i + 1 < optionsLength) {
            s_http_server_opts.document_root = this->options[++i].c_str();
        } else if (strcmp(this->options[i].c_str(), "-p") == 0 && i + 1 < optionsLength) {
            s_http_port = this->options[++i].c_str();
        } else if (strcmp(this->options[i].c_str(), "-a") == 0 && i + 1 < optionsLength) {
            s_http_server_opts.auth_domain = this->options[++i].c_str();
#ifdef MG_ENABLE_JAVASCRIPT
            } else if (strcmp(this->options[i].c_str(), "-j") == 0 && i + 1 < optionsLength) {
      const char *init_file = this->options[++i].c_str();
      mg_enable_javascript(&mgr, v7_create(), init_file);
#endif
        } else if (strcmp(this->options[i].c_str(), "-P") == 0 && i + 1 < optionsLength) {
            s_http_server_opts.global_auth_file = this->options[++i].c_str();
        } else if (strcmp(this->options[i].c_str(), "-A") == 0 && i + 1 < optionsLength) {
            s_http_server_opts.per_directory_auth_file = this->options[++i].c_str();
        } else if (strcmp(this->options[i].c_str(), "-r") == 0 && i + 1 < optionsLength) {
            s_http_server_opts.url_rewrites = this->options[++i].c_str();
#ifndef MG_DISABLE_CGI
        } else if (strcmp(this->options[i].c_str(), "-i") == 0 && i + 1 < optionsLength) {
            s_http_server_opts.cgi_interpreter = this->options[++i].c_str();
#endif
#ifdef MG_ENABLE_SSL
        } else if (strcmp(this->options[i].c_str(), "-s") == 0 && i + 1 < optionsLength) {
            ssl_cert = this->options[++i].c_str();
#endif
        } else {
            fprintf(stderr, "Unknown option: [%s]\n", this->options[i].c_str());
            exit(1);
        }
    }

    /* Set HTTP server options */
    nc = mg_bind(&mgr, s_http_port, ev_handler);
    if (nc == NULL) {
        fprintf(stderr, "Error starting server on port %s\n", s_http_port);
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
    LOG(INFO) << "Starting RESTful server on port " << s_http_port;
    std::cout << "Starting RESTful server on port " << s_http_port;
    while (s_sig_num == 0) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return;
}

Server ::~Server() { }
