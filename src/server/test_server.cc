/**
 * @author georgbuechner
 */

#include <chrono>
#include <filesystem>
#include <iostream>
#include <thread>

#include <catch2/catch.hpp>
#include <httplib.h>

#include "server_frame.h"

void del_test_user(std::string username) {
  //If already exists, delete test data.
  try{
    std::filesystem::remove("../data/users/" + username + ".json");
  }
  catch(...) {return; }
  std::cout << username << " deleted." << std::endl;
}  

TEST_CASE ("server frame can handle post and get requests", "[requests]" ) {
  
  del_test_user("test3");
  del_test_user("test4");
 
  ServerFrame server;

  std::thread t1([&server]() {
    server.Start(4444);
  });

  std::thread t2([&server]() {
        while (!server.IsRunning()) {
          std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }

        httplib::Client cl("localhost", 4444);
        cl.set_connection_timeout(2);

        SECTION("Get-request serving files works!") {
          //Non-existing page should return status 404 not found.
          auto resp = cl.Get("/humbug");
          REQUIRE(resp->status == 404);

          //Existing page should return status 200 and content should be set.
          resp = cl.Get("/");
          REQUIRE(resp->status == 200);
          REQUIRE(resp->body.length() > 0);
        }

        SECTION("Post-Requests to handle registration works") {

          //Check for correkt response when sending registration-request.
          //try to create test-user
          auto resp = cl.Post("/api/registration", {}, "{\"username\":\"test3\", "
              "\"password1\":\"password0408\", \"password2\":\"password0408\"}", 
              "application/x-www-form-urlencoded");
          REQUIRE(resp->status == 200);

          //Check if cookie has been sent
          REQUIRE(resp->get_header_value("Set-Cookie").length() > 32);

          //Check if user can be found with this cookie
          std::string cookie = resp->get_header_value("Set-Cookie");
          cookie = cookie.substr(0, cookie.find(";"));
          REQUIRE(server.user_manager().GetUsernameFromCookie(cookie.c_str()) != "");

          //Check for Response with missing json entries
          resp = cl.Post("/api/registration", {}, "{}", 
              "application/x-www-form-urlencoded");
          REQUIRE(resp->status == 401);
          REQUIRE(resp->body == "Wrong json format: missing entries!");

          //Check for respsonse with corrupted json (different error-codes).
          resp = cl.Post("/api/registration", {}, "{password:xxx}", 
              "application/x-www-form-urlencoded");
          REQUIRE(resp->status == 401);
          REQUIRE(resp->body == "Error parsing Json!");
        }

        SECTION("Post-Requests to handle login works") {

          //Require that at least test-data 2 is loaded correctly 
          //Delete potential existing test-user2
          del_test_user("test3");
          //Create test-user3
          auto resp = cl.Post("/api/registration", {}, "{\"username\":\"test4\", "
              "\"password1\":\"password0408\", \"password2\":\"password0408\"}", 
              "application/x-www-form-urlencoded");
          REQUIRE(resp->status == 200);

          REQUIRE(server.user_manager().GetUserByUsername("test4") != nullptr);
          //User cannot log in with wrong password.
          resp = cl.Post("/api/login", {}, "{\"username\":\"test4\", "
              "\"password\":\"password08\"}", 
              "application/x-www-form-urlencoded");
          REQUIRE(resp->status == 401);

          //User can log in with correct password and user-data.
          resp = cl.Post("/api/login", {}, "{\"username\":\"test4\", "
              "\"password\":\"password0408\"}", 
              "application/x-www-form-urlencoded");
          REQUIRE(resp->status == 200);
          
          //Check if cookie has been sent
          REQUIRE(resp->get_header_value("Set-Cookie").length() > 32);

          //Check if user can be found with this cookie
          std::string cookie = resp->get_header_value("Set-Cookie");
          cookie = cookie.substr(0, cookie.find(";"));
          REQUIRE(server.user_manager().GetUsernameFromCookie(cookie.c_str()) != "");

          //Log this user out.
          httplib::Headers headers = { { "Cookie", cookie } };
          std::cout << "Logging out............" << std::endl;
          resp = cl.Post("/api/logout", headers, "", "application/x-www-form-urlencoded");
          std::cout << "done." << std::endl;
          REQUIRE(resp->status == 200);
          REQUIRE(server.user_manager().GetUsernameFromCookie(cookie.c_str()) == "");
        }

        SECTION("Post-Requests to handle login works") {
          //Require that user will be redirected to login-page, when not logged.
          auto resp = cl.Get("/chatroom");
          REQUIRE(resp->status == 302);
        }

        SECTION("Post-Requests to send user-msg works") {
          auto resp = cl.Post("/api/send_msg", {}, "Hello, you", 
              "application/x-www-form-urlencoded");
          REQUIRE(resp->status == 200);
        }
        server.Stop();
    });
  t1.join();
  t2.join();
} 
