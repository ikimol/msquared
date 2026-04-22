// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include <msquared/core/math.hpp>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

namespace Matchers = Catch::Matchers;

TEST_CASE("math") {
    SECTION("angle") {
        SECTION("construction") {
            msq::Angle a1;
            REQUIRE(a1.as_degrees() == 0.f);

            auto a2 = msq::degrees(90.f);
            REQUIRE(a2.as_degrees() == 90.f);

            auto a3 = msq::radians(msq::pi);
            REQUIRE_THAT(a3.as_degrees(), Matchers::WithinRel(180.f));
        }

        SECTION("conversion") {
            auto a1 = msq::degrees(180.f);
            REQUIRE_THAT(a1.as_radians(), Matchers::WithinRel(msq::pi));

            auto a2 = msq::radians(msq::pi / 2.f);
            REQUIRE_THAT(a2.as_degrees(), Matchers::WithinRel(90.f));
        }

        SECTION("equality operators") {
            auto a1 = msq::degrees(45.f);
            auto a2 = msq::degrees(45.f);
            auto a3 = msq::degrees(90.f);

            REQUIRE(a1 == a2);
            REQUIRE(a1 != a3);
        }

        SECTION("comparison operators") {
            auto a1 = msq::degrees(45.f);
            auto a2 = msq::degrees(90.f);

            REQUIRE(a1 < a2);
            REQUIRE(a1 <= a2);
            REQUIRE(a2 > a1);
            REQUIRE(a2 >= a1);
            REQUIRE(a1 <= msq::degrees(45.f));
            REQUIRE(a1 >= msq::degrees(45.f));
        }

        SECTION("arithmetic operators") {
            auto a1 = msq::degrees(90.f);
            auto a2 = msq::degrees(45.f);

            auto neg = -a1;
            REQUIRE(neg.as_degrees() == -90.f);

            auto sum = a1 + a2;
            REQUIRE(sum.as_degrees() == 135.f);

            auto diff = a1 - a2;
            REQUIRE(diff.as_degrees() == 45.f);

            auto scaled = a1 * 2.f;
            REQUIRE(scaled.as_degrees() == 180.f);

            auto scaled2 = 3.f * a2;
            REQUIRE(scaled2.as_degrees() == 135.f);

            auto divided = a1 / 3.f;
            REQUIRE(divided.as_degrees() == 30.f);
        }

        SECTION("compound assignment operators") {
            auto a = msq::degrees(90.f);

            a += msq::degrees(45.f);
            REQUIRE(a.as_degrees() == 135.f);

            a -= msq::degrees(45.f);
            REQUIRE(a.as_degrees() == 90.f);

            a *= 2.f;
            REQUIRE(a.as_degrees() == 180.f);

            a /= 4.f;
            REQUIRE(a.as_degrees() == 45.f);
        }
    }

    SECTION("vector2") {
        SECTION("construction") {
            msq::Vector2i v1;
            REQUIRE(v1.x == 0);
            REQUIRE(v1.y == 0);

            msq::Vector2i v2(3, 4);
            REQUIRE(v2.x == 3);
            REQUIRE(v2.y == 4);

            msq::Vector2f v3(5.5f, 6.5f);
            msq::Vector2i v4(v3);
            REQUIRE(v4.x == 5);
            REQUIRE(v4.y == 6);
        }

        SECTION("member functions") {
            msq::Vector2i v(3, 4);
            REQUIRE_FALSE(v.is_zero());

            msq::Vector2i v2(0, 5);
            REQUIRE(v2.is_zero());

            v.reset();
            REQUIRE(v.x == 0);
            REQUIRE(v.y == 0);

            v.set(5, 6);
            REQUIRE(v.x == 5);
            REQUIRE(v.y == 6);

            REQUIRE(v[0] == 5);
            REQUIRE(v[1] == 6);

            msq::Vector2i v3(3, 4);
            REQUIRE(v3.length_sq() == 25);
            REQUIRE_THAT(v3.length(), Matchers::WithinRel(5.f));
        }

        SECTION("equality operators") {
            msq::Vector2i v1(3, 4);
            msq::Vector2i v2(3, 4);
            msq::Vector2i v3(5, 6);

            REQUIRE(v1 == v2);
            REQUIRE(v1 != v3);
        }

        SECTION("arithmetic operators") {
            msq::Vector2i v1(3, 4);
            msq::Vector2i v2(1, 2);

            auto neg = -v1;
            REQUIRE(neg.x == -3);
            REQUIRE(neg.y == -4);

            auto sum = v1 + v2;
            REQUIRE(sum.x == 4);
            REQUIRE(sum.y == 6);

            auto diff = v1 - v2;
            REQUIRE(diff.x == 2);
            REQUIRE(diff.y == 2);

            auto scaled = v1 * 2;
            REQUIRE(scaled.x == 6);
            REQUIRE(scaled.y == 8);

            auto scaled2 = 3 * v1;
            REQUIRE(scaled2.x == 9);
            REQUIRE(scaled2.y == 12);

            auto divided = v1 / 2;
            REQUIRE(divided.x == 1);
            REQUIRE(divided.y == 2);
        }

        SECTION("compound assignment operators") {
            msq::Vector2i v(3, 4);

            v += msq::Vector2i(1, 2);
            REQUIRE(v.x == 4);
            REQUIRE(v.y == 6);

            v -= msq::Vector2i(1, 1);
            REQUIRE(v.x == 3);
            REQUIRE(v.y == 5);

            v *= 2;
            REQUIRE(v.x == 6);
            REQUIRE(v.y == 10);

            v /= 2;
            REQUIRE(v.x == 3);
            REQUIRE(v.y == 5);
        }

        SECTION("dot product") {
            msq::Vector2i v1(3, 4);
            msq::Vector2i v2(2, 1);

            auto result = msq::dot(v1, v2);
            REQUIRE(result == 10); // (3 * 2) + (4 * 1) = 10
        }
    }

    SECTION("vector3") {
        SECTION("construction") {
            msq::Vector3i v1;
            REQUIRE(v1.x == 0);
            REQUIRE(v1.y == 0);
            REQUIRE(v1.z == 0);

            msq::Vector3i v2(1, 2, 3);
            REQUIRE(v2.x == 1);
            REQUIRE(v2.y == 2);
            REQUIRE(v2.z == 3);

            msq::Vector3f v3(4.5f, 5.5f, 6.5f);
            msq::Vector3i v4(v3);
            REQUIRE(v4.x == 4);
            REQUIRE(v4.y == 5);
            REQUIRE(v4.z == 6);
        }

        SECTION("member functions") {
            msq::Vector3i v(3, 4, 0);
            REQUIRE(v.is_zero());

            msq::Vector3i v2(3, 4, 5);
            REQUIRE_FALSE(v2.is_zero());

            v2.reset();
            REQUIRE(v2.x == 0);
            REQUIRE(v2.y == 0);
            REQUIRE(v2.z == 0);

            v2.set(5, 6, 7);
            REQUIRE(v2.x == 5);
            REQUIRE(v2.y == 6);
            REQUIRE(v2.z == 7);

            REQUIRE(v2[0] == 5);
            REQUIRE(v2[1] == 6);
            REQUIRE(v2[2] == 7);

            msq::Vector3i v3(2, 3, 6);
            REQUIRE(v3.length_sq() == 49);
            REQUIRE_THAT(v3.length(), Matchers::WithinRel(7.f));
        }

        SECTION("equality operators") {
            msq::Vector3i v1(1, 2, 3);
            msq::Vector3i v2(1, 2, 3);
            msq::Vector3i v3(4, 5, 6);

            REQUIRE(v1 == v2);
            REQUIRE(v1 != v3);
        }

        SECTION("arithmetic operators") {
            msq::Vector3i v1(1, 2, 3);
            msq::Vector3i v2(4, 5, 6);

            auto neg = -v1;
            REQUIRE(neg.x == -1);
            REQUIRE(neg.y == -2);
            REQUIRE(neg.z == -3);

            auto sum = v1 + v2;
            REQUIRE(sum.x == 5);
            REQUIRE(sum.y == 7);
            REQUIRE(sum.z == 9);

            auto diff = v2 - v1;
            REQUIRE(diff.x == 3);
            REQUIRE(diff.y == 3);
            REQUIRE(diff.z == 3);

            auto scaled = v1 * 2;
            REQUIRE(scaled.x == 2);
            REQUIRE(scaled.y == 4);
            REQUIRE(scaled.z == 6);

            auto scaled2 = 3 * v1;
            REQUIRE(scaled2.x == 3);
            REQUIRE(scaled2.y == 6);
            REQUIRE(scaled2.z == 9);

            auto divided = v2 / 2;
            REQUIRE(divided.x == 2);
            REQUIRE(divided.y == 2);
            REQUIRE(divided.z == 3);
        }

        SECTION("compound assignment operators") {
            msq::Vector3i v(1, 2, 3);

            v += msq::Vector3i(4, 5, 6);
            REQUIRE(v.x == 5);
            REQUIRE(v.y == 7);
            REQUIRE(v.z == 9);

            v -= msq::Vector3i(1, 2, 3);
            REQUIRE(v.x == 4);
            REQUIRE(v.y == 5);
            REQUIRE(v.z == 6);

            v *= 2;
            REQUIRE(v.x == 8);
            REQUIRE(v.y == 10);
            REQUIRE(v.z == 12);

            v /= 2;
            REQUIRE(v.x == 4);
            REQUIRE(v.y == 5);
            REQUIRE(v.z == 6);
        }

        SECTION("dot product") {
            msq::Vector3i v1(1, 2, 3);
            msq::Vector3i v2(4, 5, 6);

            auto result = msq::dot(v1, v2);
            REQUIRE(result == 32); // 1*4 + 2*5 + 3*6 = 32
        }

        SECTION("cross product") {
            msq::Vector3i v1(1, 0, 0);
            msq::Vector3i v2(0, 1, 0);

            auto result = msq::cross(v1, v2);
            REQUIRE(result.x == 0);
            REQUIRE(result.y == 0);
            REQUIRE(result.z == 1);

            msq::Vector3i v3(1, 2, 3);
            msq::Vector3i v4(4, 5, 6);
            auto result2 = msq::cross(v3, v4);
            REQUIRE(result2.x == -3);
            REQUIRE(result2.y == 6);
            REQUIRE(result2.z == -3);
        }
    }

    SECTION("matrix3") {
        SECTION("construction") {
            msq::Matrix3i m1;
            REQUIRE(m1 == msq::Matrix3i::zero());

            msq::Matrix3i m2(1, 2, 3, 4, 5, 6, 7, 8, 9);

            // clang-format off
            REQUIRE(m2(0, 0) == 1); REQUIRE(m2(0, 1) == 2); REQUIRE(m2(0, 2) == 3);
            REQUIRE(m2(1, 0) == 4); REQUIRE(m2(1, 1) == 5); REQUIRE(m2(1, 2) == 6);
            REQUIRE(m2(2, 0) == 7); REQUIRE(m2(2, 1) == 8); REQUIRE(m2(2, 2) == 9);
            // clang-format on

            msq::Vector3i a(1, 4, 7);
            msq::Vector3i b(2, 5, 8);
            msq::Vector3i c(3, 6, 9);
            msq::Matrix3i m3(a, b, c);

            // clang-format off
            REQUIRE(m3(0, 0) == 1); REQUIRE(m3(0, 1) == 2); REQUIRE(m3(0, 2) == 3);
            REQUIRE(m3(1, 0) == 4); REQUIRE(m3(1, 1) == 5); REQUIRE(m3(1, 2) == 6);
            REQUIRE(m3(2, 0) == 7); REQUIRE(m3(2, 1) == 8); REQUIRE(m3(2, 2) == 9);
            // clang-format on
        }

        SECTION("member functions") {
            msq::Matrix3i m(1, 2, 3, 4, 5, 6, 7, 8, 9);

            // element access

            REQUIRE(m(0, 0) == 1);
            REQUIRE(m(0, 2) == 3);
            REQUIRE(m(1, 0) == 4);
            REQUIRE(m(2, 2) == 9);

            // column access

            REQUIRE(m[0].x == 1);
            REQUIRE(m[0].y == 4);
            REQUIRE(m[0].z == 7);

            REQUIRE(m[1].x == 2);
            REQUIRE(m[1].y == 5);
            REQUIRE(m[1].z == 8);

            REQUIRE(m[2].x == 3);
            REQUIRE(m[2].y == 6);
            REQUIRE(m[2].z == 9);

            // determinant
            msq::Matrix3i identity(1, 0, 0, 0, 1, 0, 0, 0, 1);
            REQUIRE(identity.determinant() == 1);

            // singular matrix (rows are linearly dependent) -> det = 0
            msq::Matrix3i singular(1, 2, 3, 4, 5, 6, 7, 8, 9);
            REQUIRE(singular.determinant() == 0);

            // diagonal matrix -> det = product of diagonal
            msq::Matrix3i diagonal(2, 0, 0, 0, 3, 0, 0, 0, 1);
            REQUIRE(diagonal.determinant() == 6);

            // inverse
            msq::Matrix3f f_identity(1, 0, 0, 0, 1, 0, 0, 0, 1);
            auto inv_identity = f_identity.inverse();
            REQUIRE_THAT(inv_identity(0, 0), Matchers::WithinAbs(1.f, 1e-6f));
            REQUIRE_THAT(inv_identity(0, 1), Matchers::WithinAbs(0.f, 1e-6f));
            REQUIRE_THAT(inv_identity(0, 2), Matchers::WithinAbs(0.f, 1e-6f));

            REQUIRE_THAT(inv_identity(1, 0), Matchers::WithinAbs(0.f, 1e-6f));
            REQUIRE_THAT(inv_identity(1, 1), Matchers::WithinAbs(1.f, 1e-6f));
            REQUIRE_THAT(inv_identity(1, 2), Matchers::WithinAbs(0.f, 1e-6f));

            REQUIRE_THAT(inv_identity(2, 0), Matchers::WithinAbs(0.f, 1e-6f));
            REQUIRE_THAT(inv_identity(2, 1), Matchers::WithinAbs(0.f, 1e-6f));
            REQUIRE_THAT(inv_identity(2, 2), Matchers::WithinAbs(1.f, 1e-6f));

            // M * inverse(M) = I
            msq::Matrix3f n(2.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f);
            auto inv_n = n.inverse();
            auto product = n * inv_n;
            REQUIRE_THAT(product(0, 0), Matchers::WithinAbs(1.f, 1e-6f));
            REQUIRE_THAT(product(0, 1), Matchers::WithinAbs(0.f, 1e-6f));
            REQUIRE_THAT(product(0, 2), Matchers::WithinAbs(0.f, 1e-6f));

            REQUIRE_THAT(product(1, 0), Matchers::WithinAbs(0.f, 1e-6f));
            REQUIRE_THAT(product(1, 1), Matchers::WithinAbs(1.f, 1e-6f));
            REQUIRE_THAT(product(1, 2), Matchers::WithinAbs(0.f, 1e-6f));

            REQUIRE_THAT(product(2, 0), Matchers::WithinAbs(0.f, 1e-6f));
            REQUIRE_THAT(product(2, 1), Matchers::WithinAbs(0.f, 1e-6f));
            REQUIRE_THAT(product(2, 2), Matchers::WithinAbs(1.f, 1e-6f));
        }

        SECTION("equality operators") {
            msq::Matrix3i m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
            msq::Matrix3i m2(1, 2, 3, 4, 5, 6, 7, 8, 9);
            msq::Matrix3i m3(9, 8, 7, 6, 5, 4, 3, 2, 1);

            REQUIRE(m1 == m2);
            REQUIRE(m1 != m3);
        }

        SECTION("arithmetic operators") {
            msq::Matrix3i identity(1, 0, 0, 0, 1, 0, 0, 0, 1);

            msq::Matrix3i m(1, 2, 3, 4, 5, 6, 7, 8, 9);
            auto result = identity * m;
            // clang-format off
            REQUIRE(result(0, 0) == 1); REQUIRE(result(0, 1) == 2); REQUIRE(result(0, 2) == 3);
            REQUIRE(result(1, 0) == 4); REQUIRE(result(1, 1) == 5); REQUIRE(result(1, 2) == 6);
            REQUIRE(result(2, 0) == 7); REQUIRE(result(2, 1) == 8); REQUIRE(result(2, 2) == 9);
            // clang-format on

            msq::Matrix3i scale_rows(1, 0, 0, 0, 2, 0, 0, 0, 3);
            auto ab = scale_rows * m;
            // clang-format off
            REQUIRE(ab(0, 0) == 1); REQUIRE(ab(0, 1) == 2); REQUIRE(ab(0, 2) == 3);
            REQUIRE(ab(1, 0) == 8); REQUIRE(ab(1, 1) == 10); REQUIRE(ab(1, 2) == 12);
            REQUIRE(ab(2, 0) == 21); REQUIRE(ab(2, 1) == 24); REQUIRE(ab(2, 2) == 27);
            // clang-format on

            // matrix * vector

            msq::Vector3i v(1, 2, 3);
            auto w = identity * v;
            REQUIRE(w.x == 1);
            REQUIRE(w.y == 2);
            REQUIRE(w.z == 3);

            msq::Matrix3i scale(2, 0, 0, 0, 3, 0, 0, 0, 4);
            auto w2 = scale * v;
            REQUIRE(w2.x == 2);
            REQUIRE(w2.y == 6);
            REQUIRE(w2.z == 12);
        }
    }

    SECTION("point2") {
        SECTION("construction") {
            msq::Point2i p1;
            REQUIRE(p1.x == 0);
            REQUIRE(p1.y == 0);

            msq::Point2i p2(3, 4);
            REQUIRE(p2.x == 3);
            REQUIRE(p2.y == 4);

            msq::Point2f p3(5.5f, 6.5f);
            msq::Point2i p4(p3);
            REQUIRE(p4.x == 5);
            REQUIRE(p4.y == 6);

            msq::Vector2i v(3, 4);
            msq::Point2i p5(v);
            REQUIRE(p5.x == 3);
            REQUIRE(p5.y == 4);
        }

        SECTION("member functions") {
            msq::Point2i p(3, 4);

            p.reset();
            REQUIRE(p.x == 0);
            REQUIRE(p.y == 0);

            p.set(5, 6);
            REQUIRE(p.x == 5);
            REQUIRE(p.y == 6);

            REQUIRE(p[0] == 5);
            REQUIRE(p[1] == 6);
        }

        SECTION("conversion") {
            msq::Point2i p(3, 4);
            msq::Vector2i v = p;
            REQUIRE(v.x == 3);
            REQUIRE(v.y == 4);
        }

        SECTION("equality operators") {
            msq::Point2i p1(3, 4);
            msq::Point2i p2(3, 4);
            msq::Point2i p3(5, 6);

            REQUIRE(p1 == p2);
            REQUIRE(p1 != p3);
        }

        SECTION("arithmetic operators") {
            msq::Point2i p1(3, 4);
            msq::Point2i p2(1, 2);
            msq::Vector2i v(1, 2);

            auto sum = p1 + v;
            REQUIRE(sum.x == 4);
            REQUIRE(sum.y == 6);

            auto p_diff = p1 - p2;
            REQUIRE(p_diff.x == 2);
            REQUIRE(p_diff.y == 2);

            auto v_diff = p1 - v;
            REQUIRE(v_diff.x == 2);
            REQUIRE(v_diff.y == 2);
        }

        SECTION("compound assignment operators") {
            msq::Point2i p(3, 4);

            p += msq::Vector2i(1, 2);
            REQUIRE(p.x == 4);
            REQUIRE(p.y == 6);

            p -= msq::Vector2i(1, 1);
            REQUIRE(p.x == 3);
            REQUIRE(p.y == 5);
        }
    }
}
