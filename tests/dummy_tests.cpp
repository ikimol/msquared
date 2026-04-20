// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include <catch2/catch_test_macros.hpp>

TEST_CASE("dummy") {
    SECTION("one") { CHECK(3 % 2 == 1); }
    SECTION("two") { REQUIRE(true); }
}
