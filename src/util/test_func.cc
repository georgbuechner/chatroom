/**
 * @author georgbuechner
 */

#define CATCH_CONFIG_MAIN

#include <fstream>
#include <catch2/catch.hpp>

#include "func.h"

TEST_CASE ("Pages are loaded from disc", "[get_page]") {

  SECTION("trying to load non-existing file returns empty string") {
    REQUIRE(func::GetPage("") == "");
  }
  SECTION("Loading test-file returns expected output") {
    REQUIRE(func::GetPage("../src/util/test.html") == "<html>");
  }
}
