/**
 * @author Jan van Dick
 */

#include <iostream>
#include <string>

#include <httplib.h>

#include "func.h"

using namespace httplib;

int main() {
  //Create server
  Server srv;

  int start_port = std::stoi("4444");
  std::cout << "Starting on port: " << start_port << std::endl;

  srv.Get("/", [&](const Request& req, Response& resp) 
      { 
        try{ resp.set_content(func::GetPage("web/index.html"), "text/html") ;}
        catch(std::exception& e) {std::cout << e.what() << std::endl;}
      });

  std::cout << "C++ Api server startup successfull!" << std::endl;

  srv.listen("0.0.0.0", start_port);
  return 0;
}

