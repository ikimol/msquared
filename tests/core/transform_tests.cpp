// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include <msquared/core/math.hpp>
#include <msquared/core/transform.hpp>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

namespace Matchers = Catch::Matchers;

TEST_CASE("core_transform", "[core]") {
    SECTION("construction") {
        msq::Transform t;
        REQUIRE(t == msq::Transform::identity);
    }

    SECTION("equality operators") {
        msq::Transform t1;
        msq::Transform t2;
        REQUIRE(t1 == t2);

        msq::Transform t3;
        t3.translate(1.f, 0.f);
        REQUIRE(t1 != t3);
    }

    SECTION("translate") {
        msq::Transform t;
        t.translate(3.f, 4.f);

        // translation moves a point
        auto p = t.apply_to(msq::Point2f(1.f, 2.f));
        REQUIRE_THAT(p.x, Matchers::WithinAbs(4.f, 1e-6f));
        REQUIRE_THAT(p.y, Matchers::WithinAbs(6.f, 1e-6f));

        // translation does not affect direction vectors
        auto v = t.apply_to(msq::Vector2f(1.f, 2.f));
        REQUIRE_THAT(v.x, Matchers::WithinAbs(1.f, 1e-6f));
        REQUIRE_THAT(v.y, Matchers::WithinAbs(2.f, 1e-6f));
    }

    SECTION("rotate") {
        msq::Transform t;
        t.rotate(msq::degrees(90.f));

        auto p = t.apply_to(msq::Point2f(1.f, 0.f));
        REQUIRE_THAT(p.x, Matchers::WithinAbs(0.f, 1e-6f));
        REQUIRE_THAT(p.y, Matchers::WithinAbs(1.f, 1e-6f));

        auto v = t.apply_to(msq::Vector2f(1.f, 0.f));
        REQUIRE_THAT(v.x, Matchers::WithinAbs(0.f, 1e-6f));
        REQUIRE_THAT(v.y, Matchers::WithinAbs(1.f, 1e-6f));
    }

    SECTION("rotate around center") {
        msq::Transform t;
        t.rotate(msq::degrees(90.f), {1.f, 0.f});

        // (2, 0) rotated 90° around (1, 0) -> (1, 1)
        auto p = t.apply_to(msq::Point2f(2.f, 0.f));
        REQUIRE_THAT(p.x, Matchers::WithinAbs(1.f, 1e-6f));
        REQUIRE_THAT(p.y, Matchers::WithinAbs(1.f, 1e-6f));
    }

    SECTION("scale") {
        msq::Transform t;
        t.scale(2.f, 3.f);

        auto p = t.apply_to(msq::Point2f(2.f, 3.f));
        REQUIRE_THAT(p.x, Matchers::WithinAbs(4.f, 1e-6f));
        REQUIRE_THAT(p.y, Matchers::WithinAbs(9.f, 1e-6f));

        auto v = t.apply_to(msq::Vector2f(2.f, 3.f));
        REQUIRE_THAT(v.x, Matchers::WithinAbs(4.f, 1e-6f));
        REQUIRE_THAT(v.y, Matchers::WithinAbs(9.f, 1e-6f));
    }

    SECTION("scale around center") {
        msq::Transform t;
        t.scale(2.f, 1.f, {1.f, 0.f});

        // (2, 0) scaled by (2, 1) around (1, 0) -> (3, 0)
        auto p = t.apply_to(msq::Point2f(2.f, 0.f));
        REQUIRE_THAT(p.x, Matchers::WithinAbs(3.f, 1e-6f));
        REQUIRE_THAT(p.y, Matchers::WithinAbs(0.f, 1e-6f));
    }

    SECTION("inverse") {
        msq::Transform t;
        t.translate(3.f, 4.f).rotate(msq::degrees(45.f)).scale(2.f);

        auto p = msq::Point2f(5.f, 6.f);
        auto restored = t.inverse().apply_to(t.apply_to(p));
        REQUIRE_THAT(restored.x, Matchers::WithinAbs(p.x, 1e-5f));
        REQUIRE_THAT(restored.y, Matchers::WithinAbs(p.y, 1e-5f));
    }

    SECTION("combine") {
        msq::Transform t1, t2;
        t1.translate(1.f, 0.f);
        t2.translate(0.f, 1.f);

        t1.combine(t2);
        auto p = t1.apply_to(msq::Point2f(0.f, 0.f));
        REQUIRE_THAT(p.x, Matchers::WithinAbs(1.f, 1e-6f));
        REQUIRE_THAT(p.y, Matchers::WithinAbs(1.f, 1e-6f));
    }

    SECTION("apply rect") {
        msq::Transform t;
        t.scale(2.f);

        // rect at (1, 2) with size (3, 4) scaled by 2 -> (2, 4) with size (6, 8)
        auto r = t.apply_to(msq::Rect2f(1.f, 2.f, 3.f, 4.f));
        REQUIRE_THAT(r.x, Matchers::WithinAbs(2.f, 1e-6f));
        REQUIRE_THAT(r.y, Matchers::WithinAbs(4.f, 1e-6f));
        REQUIRE_THAT(r.w, Matchers::WithinAbs(6.f, 1e-6f));
        REQUIRE_THAT(r.h, Matchers::WithinAbs(8.f, 1e-6f));
    }
}
