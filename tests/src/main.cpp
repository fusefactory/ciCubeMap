#define CATCH_CONFIG_MAIN

#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp> // for is_any_of
#include "cinder/Log.h"
#include "catch.hpp"
#include "ciCubeMap/ciCubeMap.h"

using namespace std;
using namespace ci;
// using namespace ci::CubeMap;

TEST_CASE("Mapper", ""){
  SECTION("Mapper::create initializes like an FboCubeMap"){

    // TODO; initialize OpenGL context first

    auto mapperRef = CubeMap::Mapper::create();
    REQUIRE(mapperRef->getFboCubeMap()->getWidth() == 1024);
    REQUIRE(mapperRef->getFboCubeMap()->getHeight() == 1024);

    mapperRef = CubeMap::Mapper::create(2048, 2048);
    REQUIRE(mapperRef->getFboCubeMap()->getWidth() == 2048);
    REQUIRE(mapperRef->getFboCubeMap()->getHeight() == 2048);

    auto fmt = ci::gl::FboCubeMap::Format();
    mapperRef = CubeMap::Mapper::create(512, 512, fmt);
    REQUIRE(mapperRef->getFboCubeMap()->getWidth() == 512);
    REQUIRE(mapperRef->getFboCubeMap()->getHeight() == 512);
  }
}
