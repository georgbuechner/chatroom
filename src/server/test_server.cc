/**
 * @author georgbuechner
 */

#include <chrono>
#include <iostream>
#include <thread>

#include <catch2/catch.hpp>
#include <httplib.h>

#include "server_frame.h"

TEST_CASE ("server frame can handle post and get requests", "[requests]" ) {

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
          auto resp = cl.Get("/humbug");
          REQUIRE(resp->status == 404);

          resp = cl.Get("/");
          REQUIRE(resp->status == 200);
          REQUIRE(resp->body.length() > 0);
        }
        SECTION("Post-Requests to handle registration, works") {
          auto resp = cl.Post("/api/registration", {}, "{\"username\":\"jan\", \"password1\":\"0408\", \"password2\":\"0408\"}", "application/x-www-form-urlencoded");
          REQUIRE(resp->status == 200);

          resp = cl.Post("/api/registration", {}, "{}", "application/x-www-form-urlencoded");
          REQUIRE(resp->status == 401);
          REQUIRE(resp->body == "Wrong json format: missing entries!");

          resp = cl.Post("/api/registration", {}, "{password:xxx}", 
              "application/x-www-form-urlencoded");
          REQUIRE(resp->status == 401);
          REQUIRE(resp->body == "Error parsing Json!");
        }
        server.Stop();
    });
  t1.join();
  t2.join();
} 
