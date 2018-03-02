#include <iostream>
#include "libhttpserver/libhttpserver.h"
#include "webserver.h"

using namespace std;

using namespace rs::httpserver;


namespace kt {
    WebServer::WebServer()
    {
        
    }
    
    WebServer::~WebServer()
    {
    }

    void WebServer::process()
    {
        // the server will listen on all IPs on port 8880
        auto server = HttpServer::Create("0.0.0.0", 8880);
        
        // a lambda function which handles the request
        auto func = [](socket_ptr socket, request_ptr request, response_ptr response) {
            // get the request uri
            auto uri = request->getUri();
            cout << uri << endl;
            
            if (uri == "/") {
                // the uri was just /, redirect to /index.html
                response->Redirect("/index.html");
            } else {
                // use the uri file extension to determine the content type
                auto contentType = MimeTypes::GetContentType(uri);

                // we only respond if we got a content type
                if (contentType) {
                    // the content files are in the www sub-directory
                    uri = "www" + uri;

                    // open a stream on the file
                    FileStream stream(uri);
                    if (stream) {
                        // respond with the contents of the file
                        response->setContentType(contentType.get()).Send(stream);
                    }
                }
            }
        };
        server->Start(func);
    }
    
}
