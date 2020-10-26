/**
 * @author georgbuechner
 */

#define CATCH_CONFIG_MAIN

#include <fstream>
#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>

#include "user_manager.h"

TEST_CASE ("User manager can add a user", "[add_user]") {

  UserManager user_manager;
  nlohmann::json json;
  json["username"] = "jan";
  json["password1"] = "password1234";
  json["password2"] = "password1234"; 

  nlohmann::json answer = user_manager.AddUser(json);
  REQUIRE(answer["success"] == true);
  REQUIRE(user_manager.GetUserByUsername(json["username"]) != nullptr);

  answer = user_manager.AddUser(json);
  REQUIRE(answer["error"] == "Username already exists.");

  json["username"] = "alex";
  json["password2"] = "password123";
  answer = user_manager.AddUser(json);
  REQUIRE(answer["error"] == "Passwords don't match.");
  REQUIRE(user_manager.GetUserByUsername(json["username"]) == nullptr);

  json["password1"] = "password";
  json["password2"] = "password";
  answer = user_manager.AddUser(json);
  REQUIRE(answer["error"] == "Strength insufficient.");
  REQUIRE(user_manager.GetUserByUsername(json["username"]) == nullptr);

  json["password1"] = "passwordpasswordpassword";
  json["password2"] = "passwordpasswordpassword";
  answer = user_manager.AddUser(json);
  REQUIRE(answer["success"] == true);
  REQUIRE(user_manager.GetUserByUsername(json["username"]) != nullptr);
}
