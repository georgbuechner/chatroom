/**
 * @author georgbuechner
 */

#include "server_frame.h"
#include "func.h"

using namespace httplib;

ServerFrame::ServerFrame() {
}

void ServerFrame::Start(int port) {
  std::cout << "Starting on Port: " << port << std::endl;
  
  //Serves css- and javascrit-files as well as images
  server_.Get("/", [&](const Request& req, Response& resp) { 
        resp.set_content(func::GetPage("web/index.html"), "text/html") ;});
  server_.Get("/registration", [&](const Request& req, Response& resp) { 
        resp.set_content(func::GetPage("web/registration.html"), "text/html") ;});

  server_.Get("/web/general.css", [&](const Request& req, Response& resp) { 
        resp.set_content(func::GetPage("web/general.css"), "text/css") ;});
  server_.Get("/web/registration.js", [&](const Request& req, Response& resp) { 
        resp.set_content(func::GetPage("web/registration.js"), 
            "application/javascript") ;});

  std::cout << "C++ Api server startup successfull!" << std::endl;
  server_.listen("0.0.0.0", port);
}

void ServerFrame::Stop() {
  server_.stop();
}

bool ServerFrame::IsRunning() {
  return server_.is_running();
}

ServerFrame::~ServerFrame() {
  Stop();
}
