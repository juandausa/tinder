//
// Created by juanchi on 22/03/16.
//

#include <iostream>
#include <vector>
#include <cstring>
#include "Mongoose.h"
#include "Sever.h"

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;
static int s_sig_num = 0;

static void signal_handler(int sig_num) {
    signal(sig_num, signal_handler);
    s_sig_num = sig_num;
}

static void handle_sum_call(struct mg_connection *nc, struct http_message *hm) {
    char n1[100], n2[100];
    double result;

    /* Get form variables */
    mg_get_http_var(&hm->body, "n1", n1, sizeof(n1));
    mg_get_http_var(&hm->body, "n2", n2, sizeof(n2));

    /* Send headers */
    mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

    /* Compute the result and send it back as a JSON object */
    result = strtod(n1, NULL) + strtod(n2, NULL);
    mg_printf_http_chunk(nc, "{ \"result\": %lf }", result);
    mg_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    switch (ev) {
        case MG_EV_HTTP_REQUEST:
            if (mg_vcmp(&hm->uri, "/api/v1/sum") == 0) {
                handle_sum_call(nc, hm);                    /* Handle RESTful call */
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

void Server :: start(std::vector<std::string> options) {
    struct mg_mgr mgr;
    struct mg_connection *nc;
    unsigned int i;
    char *cp;
    unsigned int optionsLength = options.size();
#ifdef MG_ENABLE_SSL
    const char *ssl_cert = NULL;
#endif

    mg_mgr_init(&mgr, NULL);

    /* Process command line options to customize HTTP server */
    for (i = 1; i < optionsLength; i++) {
        if (strcmp(options[i].c_str(), "-D") == 0 && i + 1 < optionsLength) {
            mgr.hexdump_file = options[++i].c_str();
        } else if (strcmp(options[i].c_str(), "-d") == 0 && i + 1 < optionsLength) {
            s_http_server_opts.document_root = options[++i].c_str();
        } else if (strcmp(options[i].c_str(), "-p") == 0 && i + 1 < optionsLength) {
            s_http_port = options[++i].c_str();
        } else if (strcmp(options[i].c_str(), "-a") == 0 && i + 1 < optionsLength) {
            s_http_server_opts.auth_domain = options[++i].c_str();
#ifdef MG_ENABLE_JAVASCRIPT
            } else if (strcmp(options[i].c_str(), "-j") == 0 && i + 1 < optionsLength) {
      const char *init_file = options[++i].c_str();
      mg_enable_javascript(&mgr, v7_create(), init_file);
#endif
        } else if (strcmp(options[i].c_str(), "-P") == 0 && i + 1 < optionsLength) {
            s_http_server_opts.global_auth_file = options[++i].c_str();
        } else if (strcmp(options[i].c_str(), "-A") == 0 && i + 1 < optionsLength) {
            s_http_server_opts.per_directory_auth_file = options[++i].c_str();
        } else if (strcmp(options[i].c_str(), "-r") == 0 && i + 1 < optionsLength) {
            s_http_server_opts.url_rewrites = options[++i].c_str();
#ifndef MG_DISABLE_CGI
        } else if (strcmp(options[i].c_str(), "-i") == 0 && i + 1 < optionsLength) {
            s_http_server_opts.cgi_interpreter = options[++i].c_str();
#endif
#ifdef MG_ENABLE_SSL
        } else if (strcmp(options[i].c_str(), "-s") == 0 && i + 1 < optionsLength) {
            ssl_cert = options[++i].c_str();
#endif
        } else {
            fprintf(stderr, "Unknown option: [%s]\n", options[i].c_str());
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
    const char* first_option = options[0].c_str();
    if (optionsLength > 0 && ((cp = (char*) strrchr(first_option, '/')) != NULL ||
                     (cp = (char*) strrchr(options[0].c_str(), '/')) != NULL)) {
        *cp = '\0';
        s_http_server_opts.document_root = options[0].c_str();
    }

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    printf("Starting RESTful server on port %s\n", s_http_port);
    while (s_sig_num == 0) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return;
}
