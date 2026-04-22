// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include <msquared/core/rect2.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("rect2") {
    SECTION("construction") {
        msq::Rect2i r1;
        REQUIRE(r1.x == 0);
        REQUIRE(r1.y == 0);
        REQUIRE(r1.w == 0);
        REQUIRE(r1.h == 0);

        msq::Rect2i r2(1, 2, 10, 20);
        REQUIRE(r2.x == 1);
        REQUIRE(r2.y == 2);
        REQUIRE(r2.w == 10);
        REQUIRE(r2.h == 20);

        msq::Rect2f r3(1.5f, 2.5f, 10.f, 20.f);
        msq::Rect2i r4(r3);
        REQUIRE(r4.x == 1);
        REQUIRE(r4.y == 2);
        REQUIRE(r4.w == 10);
        REQUIRE(r4.h == 20);

        msq::Point2i p(1, 2);
        msq::Size2i s(10, 20);
        msq::Rect2i r5(p, s);
        REQUIRE(r5.x == 1);
        REQUIRE(r5.y == 2);
        REQUIRE(r5.w == 10);
        REQUIRE(r5.h == 20);

        msq::Point2i min(1, 2);
        msq::Point2i max(11, 22);
        msq::Rect2i r6(min, max);
        REQUIRE(r6.x == 1);
        REQUIRE(r6.y == 2);
        REQUIRE(r6.w == 10);
        REQUIRE(r6.h == 20);
    }

    SECTION("member functions") {
        msq::Rect2i r(2, 4, 10, 20);

        REQUIRE(r.center().x == 7);
        REQUIRE(r.center().y == 14);

        REQUIRE(r.position().x == 2);
        REQUIRE(r.position().y == 4);

        REQUIRE(r.size().w == 10);
        REQUIRE(r.size().h == 20);

        r.set_position(5, 6);
        REQUIRE(r.x == 5);
        REQUIRE(r.y == 6);

        r.set_position(msq::Point2i(7, 8));
        REQUIRE(r.x == 7);
        REQUIRE(r.y == 8);

        r.set_size(30, 40);
        REQUIRE(r.w == 30);
        REQUIRE(r.h == 40);

        r.set_size(msq::Size2i(50, 60));
        REQUIRE(r.w == 50);
        REQUIRE(r.h == 60);

        r.reset();
        REQUIRE(r.x == 0);
        REQUIRE(r.y == 0);
        REQUIRE(r.w == 0);
        REQUIRE(r.h == 0);

        // extremes
        msq::Rect2i r2(2, 4, 10, 20);
        REQUIRE(r2.min_x() == 2);
        REQUIRE(r2.max_x() == 12);
        REQUIRE(r2.min_y() == 4);
        REQUIRE(r2.max_y() == 24);
        REQUIRE(r2.min().x == 2);
        REQUIRE(r2.min().y == 4);
        REQUIRE(r2.max().x == 12);
        REQUIRE(r2.max().y == 24);
    }

    SECTION("equality operators") {
        msq::Rect2i r1(1, 2, 10, 20);
        msq::Rect2i r2(1, 2, 10, 20);
        msq::Rect2i r3(1, 2, 99, 20);

        REQUIRE(r1 == r2);
        REQUIRE(r1 != r3);
    }

    SECTION("arithmetic operators") {
        msq::Rect2i r(1, 2, 10, 20);
        msq::Vector2i v(3, 4);

        auto r2 = r + v;
        REQUIRE(r2.x == 4);
        REQUIRE(r2.y == 6);
        REQUIRE(r2.w == 10);
        REQUIRE(r2.h == 20);

        auto r3 = r - v;
        REQUIRE(r3.x == -2);
        REQUIRE(r3.y == -2);
        REQUIRE(r3.w == 10);
        REQUIRE(r3.h == 20);
    }

    SECTION("compound assignment operators") {
        msq::Rect2i r(1, 2, 10, 20);
        msq::Vector2i v(3, 4);

        r += v;
        REQUIRE(r.x == 4);
        REQUIRE(r.y == 6);

        r -= v;
        REQUIRE(r.x == 1);
        REQUIRE(r.y == 2);
    }

    SECTION("contains") {
        msq::Rect2i r(0, 0, 10, 10);

        REQUIRE(msq::contains(r, 0, 0));
        REQUIRE(msq::contains(r, 5, 5));
        REQUIRE_FALSE(msq::contains(r, 10, 5)); // max_x is exclusive
        REQUIRE_FALSE(msq::contains(r, 5, 10)); // max_y is exclusive
        REQUIRE_FALSE(msq::contains(r, -1, 5));

        REQUIRE(msq::contains(r, msq::Point2i(3, 4)));
        REQUIRE_FALSE(msq::contains(r, msq::Point2i(10, 10)));
    }

    SECTION("intersection") {
        msq::Rect2i r1(0, 0, 10, 10);
        msq::Rect2i r2(5, 5, 10, 10);
        msq::Rect2i r3(20, 20, 10, 10);

        auto i = msq::intersection(r1, r2);
        REQUIRE(i.has_value());
        REQUIRE(i->x == 5);
        REQUIRE(i->y == 5);
        REQUIRE(i->w == 5);
        REQUIRE(i->h == 5);

        REQUIRE_FALSE(msq::intersection(r1, r3).has_value());

        REQUIRE(intersects(r1, r2));
        REQUIRE_FALSE(intersects(r1, r3));
    }
}
