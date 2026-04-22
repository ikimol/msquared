// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include <msquared/core/size2.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("size2") {
    SECTION("construction") {
        msq::Size2i s1;
        REQUIRE(s1.w == 0);
        REQUIRE(s1.h == 0);

        msq::Size2i s2(3, 4);
        REQUIRE(s2.w == 3);
        REQUIRE(s2.h == 4);

        msq::Size2f s3(5.5f, 6.5f);
        msq::Size2i s4(s3);
        REQUIRE(s4.w == 5);
        REQUIRE(s4.h == 6);

        msq::Vector2i v(7, 8);
        msq::Size2i s5(v);
        REQUIRE(s5.w == 7);
        REQUIRE(s5.h == 8);
    }

    SECTION("member functions") {
        msq::Size2i s(3, 4);
        REQUIRE_FALSE(s.is_zero());

        msq::Size2i s2(0, 4);
        REQUIRE(s2.is_zero());

        msq::Size2i s3(3, 0);
        REQUIRE(s3.is_zero());

        s.reset();
        REQUIRE(s.w == 0);
        REQUIRE(s.h == 0);

        s.set(5, 6);
        REQUIRE(s.w == 5);
        REQUIRE(s.h == 6);

        REQUIRE(s[0] == 5);
        REQUIRE(s[1] == 6);
    }

    SECTION("conversion") {
        msq::Size2i s(3, 4);
        msq::Vector2i v = s;
        REQUIRE(v.x == 3);
        REQUIRE(v.y == 4);
    }

    SECTION("equality operators") {
        msq::Size2i s1(3, 4);
        msq::Size2i s2(3, 4);
        msq::Size2i s3(5, 6);

        REQUIRE(s1 == s2);
        REQUIRE(s1 != s3);
    }

    SECTION("comparison operators") {
        msq::Size2i s1(2, 3);
        msq::Size2i s2(3, 1); // wider w takes precedence
        msq::Size2i s3(2, 5); // same w, larger h
        msq::Size2i s4(2, 3); // equal to s1

        REQUIRE(s1 < s2);
        REQUIRE(s1 < s3);
        REQUIRE(s2 > s1);
        REQUIRE(s3 > s1);
        REQUIRE(s1 <= s4);
        REQUIRE(s1 >= s4);
    }

    SECTION("arithmetic operators") {
        msq::Size2i s(3, 4);

        auto scaled = s * 2;
        REQUIRE(scaled.w == 6);
        REQUIRE(scaled.h == 8);

        auto scaled2 = 3 * s;
        REQUIRE(scaled2.w == 9);
        REQUIRE(scaled2.h == 12);

        auto divided = s / 2;
        REQUIRE(divided.w == 1);
        REQUIRE(divided.h == 2);
    }

    SECTION("compound assignment operators") {
        msq::Size2i s(3, 4);

        s *= 2;
        REQUIRE(s.w == 6);
        REQUIRE(s.h == 8);

        s /= 2;
        REQUIRE(s.w == 3);
        REQUIRE(s.h == 4);
    }
}
