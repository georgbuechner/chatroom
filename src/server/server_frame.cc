/**
 * @author georgbuechner
 */

#include "server_frame.cc"

void ServerFrame::ServerFrame(int port) {
  std::cout << "Starting on Port: " << port << std::endl;
  
  //Serves css- and javascrit-files as well as images
  srv.Get("/", [&](const Request& req, Response& resp) { 
        resp.set_content(func::GetPage("web/index.html"), "text/html") ;});
  srv.Get("/registration", [&](const Request& req, Response& resp) { 
        resp.set_content(func::GetPage("web/registration.html"), "text/html") ;});

  srv.Get("/web/general.css", [&](const Request& req, Response& resp) { 
        resp.set_content(func::GetPage("web/general.css"), "text/css") ;});
  srv.Get("/web/registration.js", [&](const Request& req, Response& resp) { 
        resp.set_content(func::GetPage("web/registration.js"), 
            "application/javascript") ;});

  std::cout << "C++ Api server startup successfull!" << std::endl;
  srv.listen("0.0.0.0", port);
}

void ServerFrame::~ServerFrame() {
  Stop();
}

void ServerFrame::Stop() {
  server_.stop();
}


