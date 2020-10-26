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
  std::string username = "jan";
  std::string password1 = "password1234";
  std::string password2 = "password1234"; 

  nlohmann::json answer = user_manager.AddUser(username, password1, password2);
  REQUIRE(answer["success"] == true);
  REQUIRE(user_manager.GetUserByUsername(username) != nullptr);

  answer = user_manager.AddUser(username, password1, password2);
  REQUIRE(answer["error"] == "Username already exists.");

  username = "alex";
  password2 = "password123";
  answer = user_manager.AddUser(username, password1, password2);
  REQUIRE(answer["error"] == "Passwords don't match.");
  REQUIRE(user_manager.GetUserByUsername(username) == nullptr);

  password1 = "password";
  password2 = "password";
  answer = user_manager.AddUser(username, password1, password2);
  REQUIRE(answer["error"] == "Strength insufficient.");
  REQUIRE(user_manager.GetUserByUsername(username== nullptr);

  password1 = "passwordpasswordpassword";
  password2 = "passwordpasswordpassword";
  answer = user_manager.AddUser(username, password1, password2);
  REQUIRE(answer["success"] == true);
  REQUIRE(user_manager.GetUserByUsername(username) != nullptr);
}
