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
      DoRegistration(req, resp); });

  server_.Post("/api/login", [&](const Request& req, Response& resp) { 
      DoLogin(req, resp); });
  
  //Serves css- and javascrit-files as well as images
  server_.Get("/", [&](const Request& req, Response& resp) { 
        resp.set_content(func::GetPage("web/index.html"), "text/html") ;});
  server_.Get("/login", [&](const Request& req, Response& resp) { 
        if (!CheckLoggedIn(req))
          resp.set_content(func::GetPage("web/login.html"), "text/html");
        else {
          resp.status = 302;
          resp.set_header("Location", "/chatroom");
        }
      });
  server_.Get("/registration", [&](const Request& req, Response& resp) { 
        resp.set_content(func::GetPage("web/registration.html"), "text/html") ;});
  server_.Get("/chatroom", [&](const Request& req, Response& resp) { 
        if (CheckLoggedIn(req))
          resp.set_content(func::GetPage("web/chatroom.html"), "text/html") ;
        else {
          resp.status = 302;
          resp.set_header("Location", "/login");
        }
      });
  server_.Get("/web/general.css", [&](const Request& req, Response& resp) { 
        resp.set_content(func::GetPage("web/general.css"), "text/css") ;});
  server_.Get("/web/login.js", [&](const Request& req, Response& resp) { 
        resp.set_content(func::GetPage("web/login.js"), 
            "application/javascript") ;});
  server_.Get("/web/registration.js", [&](const Request& req, Response& resp) { 
        resp.set_content(func::GetPage("web/registration.js"), 
            "application/javascript") ;});

  std::cout << "C++ Api server startup successfull!" << std::endl;
  server_.listen("0.0.0.0", port);
}

void ServerFrame::DoLogin(const Request& req, Response& resp) {
  //Try to parse json.
  nlohmann::json request;
  try { request = nlohmann::json::parse(req.body); }
  catch (std::exception& e) {
    resp.status = 401;
    resp.set_content("Error parsing Json!", "application/json");
    std::cout << "DoLogin: Parsing failed." << std::endl;
    return;
  }

  //Try to read necessary values
  std::string username, password;
  try { 
    username = request["username"];
    password = request["password"];
  }
  catch (std::exception& e) {
    resp.status = 401;
    resp.set_content("Wrong json format: missing entries!", "application/json");
    return;
  }

  //Check if users exists
  std::unique_lock ul(shared_mutex_user_manager_);
  if (user_manager_.DoLogin(username, password) == false) {
    resp.status = 401;
    resp.set_content("Login failed.", "application/json");
  }
  else {
    resp.status = 200;
    std::string cookie = "SESSID=" + user_manager_.GenerateCookie(username)                         
       + "; Path=/";
    resp.set_header("Set-Cookie", cookie.c_str());  
  }
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

  //If all is okay, do actual registration.
  std::unique_lock ul(shared_mutex_user_manager_);
  nlohmann::json answer = user_manager_.AddUser(username, password1, password2);
  ul.unlock();

  //If registration failes, send error-code.
  if (answer.count("error") > 0) {
    resp.status = 401;
    resp.set_content(answer["error"], "application/json");
  }
  //Genrate cookie and thus log user in.
  else {
    ul.lock();
    std::string cookie = "SESSID=" + user_manager_.GenerateCookie(username)                         
       + "; Path=/";
    ul.unlock();
    resp.set_header("Set-Cookie", cookie.c_str());
    resp.status = 200;
  }
}

bool ServerFrame::CheckLoggedIn(const Request& req) {
  //Try to get username from cookie
  const char* ptr = get_header_value(req.headers, "Cookie");
  std::shared_lock sl(shared_mutex_user_manager_);
  std::string username = user_manager_.GetUsernameFromCookie(ptr);
  sl.unlock();

  //Return true when username is not empty.
  return username != "";
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
