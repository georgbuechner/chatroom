/**
 * @author georgbuechner
 */

#include <iostream>
#include <string>

#include <httplib.h>

#include "func.h"

using namespace httplib;

int main() {
  //Creates server
  Server srv;

  int start_port = std::stoi("4444");
  std::cout << "Starting on port: " << start_port << std::endl;

  srv.Get("/", [&](const Request& req, Response& resp) { 
        resp.set_content(func::GetPage("web/index.html"), "text/html") ;});

  //Serves css- and javascrit-files as well as images
  srv.Get("/web/general.css", [&](const Request& req, Response& resp) { 
        resp.set_content(func::GetPage("web/general.css"), "text/css") ;});

  std::cout << "C++ Api server startup successfull!" << std::endl;

  srv.listen("0.0.0.0", start_port);
  return 0;
}

