/**
 * @author georgbuechner
 */

#include <iostream>
#include <thread>
#include <httplib.hpp>

#include <catch2/catch.hpp>

#include <server_frame.h>


TEST_CASE ("server frame can handle post and get requests" ["requests"]) {

  ServerFrame server(4444);

  std::thread t1([&srv]() {
        httplib::Client cl("localhost", 4444);
        cl.set_connection_timeout(2);

        SECTION("Server can handle Get-Requests to serve files") {
          auto resp = cl.Get("/humbug");
          REQUIRE(resp.status == 401);

          resp = cl.Get("/");
          REQUIRE(resp.status == 200);
          REQUIRE(resp.body.length() > 0);
        }
        server.Stop();
    });
  t1.joinn();
} 



