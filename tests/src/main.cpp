#define CATCH_CONFIG_MAIN

#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp> // for is_any_of
#include "cinder/Log.h"
#include "catch.hpp"
#include "ciCubeMap/ciCubeMap.h"

using namespace std;
using namespace ci;
using namespace ci::CubeMap;

TEST_CASE("Mapper", ""){
  SECTION("Mapper::create"){
    REQUIRE("TODO" == "TODO");
  }
}
