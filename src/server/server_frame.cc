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

  //Post-Requests
  server_.Post("/api/registration", [&](const Request& req, Response& resp) { 
      try{ 
        DoRegistration(req, resp);
      }
      catch (std::exception& e) {
        std::cout << "api/registration: " << e.what() << std::endl;
      }
    });
  
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

void ServerFrame::DoRegistration(const Request& req, Response& resp) {

  //Try to parse json.
  nlohmann::json request;
  try { request = nlohmann::json::parse(req.body); }
  catch (std::exception& e) {
    resp.status = 401;
    resp.set_content("Error parsing Json!", "application/json");
    return;
  }

  //Try to read necessary values
  std::string username, password1, password2;
  try { 
    username = request["username"];
    password1 = request["password1"];
    password2 = request["password2"];
  }
  catch (std::exception& e) {
    resp.status = 401;
    resp.set_content("Wrong json format: missing entries!", "application/json");
    return;
  }

  //If all is okay, do actual registration
  resp.status = 200;
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
