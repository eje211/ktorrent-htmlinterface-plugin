#include "webserver.h"
#include <iostream>

using namespace std;

extern "C"
{    
    static void httpeventhandler(struct mg_connection *c, int ev, void *ev_data) {
        cout << "Event:    " << ev << endl;
        if (ev == MG_EV_HTTP_REQUEST)
        {
            cout << "Response: " << ((struct http_message *) ev_data)->resp_code << endl;
            cout << "page!" << endl;
//             struct mg_serve_http_opts opts;
// 
//             memset(&opts, 0, sizeof(opts));  // Reset all options to defaults
//             opts.document_root = "/home/eje211/src/ktorrent/plugins/htmlinterface/";       // Serve files from the current directory
// 
//             mg_serve_http(c, (struct http_message *) ev_data, opts);
//             cout << ((struct http_message *) ev_data)->body.p << endl;
        }
    }

}

namespace kt {
    WebServer::WebServer()
    {
        
    }
    
    WebServer::~WebServer()
    {
        mg_mgr_free(&mgr);
    }

    void WebServer::process()
    {
        struct mg_connection *c;

        mg_mgr_init(&mgr, NULL);
        c = mg_bind(&mgr, "8880", httpeventhandler);
        while (true) {
            mg_mgr_poll(&mgr, 1000);
        }
    }
}
