// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include <msquared/ecs/component_mask.hpp>

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <vector>

namespace {

struct Position {};

struct Velocity {};

struct Health {};

struct Render {};

} // namespace

namespace ecs = msq::ecs;

TEST_CASE("ecs_component_mask", "[ecs]") {
    SECTION("construction") {
        ecs::ComponentMask mask;
        REQUIRE_FALSE(mask.test(ecs::component_type<Position>()));
    }

    SECTION("set") {
        ecs::ComponentMask mask;

        SECTION("set bit is reported present") {
            mask.set(ecs::component_type<Position>());
            REQUIRE(mask.test(ecs::component_type<Position>()));
        }

        SECTION("unset bit is reported absent") {
            mask.set(ecs::component_type<Position>());
            REQUIRE_FALSE(mask.test(ecs::component_type<Velocity>()));
        }

        SECTION("returns self for chaining") {
            mask.set(ecs::component_type<Position>())
                .set(ecs::component_type<Velocity>())
                .set(ecs::component_type<Health>());
            REQUIRE(mask.test(ecs::component_type<Position>()));
            REQUIRE(mask.test(ecs::component_type<Velocity>()));
            REQUIRE(mask.test(ecs::component_type<Health>()));
        }
    }

    SECTION("unset") {
        ecs::ComponentMask mask;
        mask.set(ecs::component_type<Position>());
        mask.set(ecs::component_type<Velocity>());

        SECTION("clears the bit") {
            mask.unset(ecs::component_type<Position>());
            REQUIRE_FALSE(mask.test(ecs::component_type<Position>()));
        }

        SECTION("does not affect other bits") {
            mask.unset(ecs::component_type<Position>());
            REQUIRE(mask.test(ecs::component_type<Velocity>()));
        }

        SECTION("no-op on an absent bit") {
            mask.unset(ecs::component_type<Render>());
            REQUIRE(mask.test(ecs::component_type<Position>()));
            REQUIRE(mask.test(ecs::component_type<Velocity>()));
        }
    }

    SECTION("equality") {
        ecs::ComponentMask a;
        a.set(ecs::component_type<Position>());
        a.set(ecs::component_type<Velocity>());

        SECTION("equal to identical mask") {
            ecs::ComponentMask b;
            b.set(ecs::component_type<Position>());
            b.set(ecs::component_type<Velocity>());
            REQUIRE(a == b);
            REQUIRE_FALSE(a != b);
        }

        SECTION("not equal to different mask") {
            ecs::ComponentMask c;
            c.set(ecs::component_type<Position>());
            REQUIRE(a != c);
            REQUIRE_FALSE(a == c);
        }

        SECTION("two empty masks are equal") {
            ecs::ComponentMask e1;
            ecs::ComponentMask e2;
            REQUIRE(e1 == e2);
        }
    }

    SECTION("iteration") {
        SECTION("empty mask yields no components") {
            ecs::ComponentMask mask;
            std::size_t count = 0;
            for ([[maybe_unused]] auto type : mask) {
                ++count;
            }
            REQUIRE(count == 0);
        }

        SECTION("iterates all set components") {
            auto p = ecs::component_type<Position>();
            auto v = ecs::component_type<Velocity>();
            auto h = ecs::component_type<Health>();

            ecs::ComponentMask mask;
            mask.set(p).set(v).set(h);

            std::vector<ecs::ComponentType> types;
            for (auto type : mask) {
                types.push_back(type);
            }

            REQUIRE(types.size() == 3);
            REQUIRE(std::find(types.begin(), types.end(), p) != types.end());
            REQUIRE(std::find(types.begin(), types.end(), v) != types.end());
            REQUIRE(std::find(types.begin(), types.end(), h) != types.end());
        }
    }

    SECTION("make_component_mask") {
        auto mask = ecs::make_component_mask<Position, Velocity>();
        REQUIRE(mask.test(ecs::component_type<Position>()));
        REQUIRE(mask.test(ecs::component_type<Velocity>()));
        REQUIRE_FALSE(mask.test(ecs::component_type<Health>()));
    }

    SECTION("is_empty") {
        SECTION("default mask is empty") {
            ecs::ComponentMask mask;
            REQUIRE(mask.is_empty());
        }

        SECTION("not empty after set") {
            ecs::ComponentMask mask;
            mask.set(ecs::component_type<Position>());
            REQUIRE_FALSE(mask.is_empty());
        }

        SECTION("empty after set then unset") {
            ecs::ComponentMask mask;
            mask.set(ecs::component_type<Position>());
            mask.unset(ecs::component_type<Position>());
            REQUIRE(mask.is_empty());
        }
    }

    SECTION("count") {
        SECTION("empty mask has count zero") {
            ecs::ComponentMask mask;
            REQUIRE(mask.count() == 0);
        }

        SECTION("count reflects number of set bits") {
            ecs::ComponentMask mask;
            mask.set(ecs::component_type<Position>());
            REQUIRE(mask.count() == 1);
            mask.set(ecs::component_type<Velocity>());
            REQUIRE(mask.count() == 2);
            mask.set(ecs::component_type<Health>());
            REQUIRE(mask.count() == 3);
        }

        SECTION("count decreases on unset") {
            ecs::ComponentMask mask;
            mask.set(ecs::component_type<Position>());
            mask.set(ecs::component_type<Velocity>());
            mask.unset(ecs::component_type<Position>());
            REQUIRE(mask.count() == 1);
        }
    }

    SECTION("contains") {
        auto pv = ecs::make_component_mask<Position, Velocity>();

        SECTION("contains a strict subset") {
            auto p = ecs::make_component_mask<Position>();
            REQUIRE(pv.contains(p));
        }

        SECTION("contains itself") {
            REQUIRE(pv.contains(pv));
        }

        SECTION("does not contain a superset") {
            auto pvh = ecs::make_component_mask<Position, Velocity, Health>();
            REQUIRE_FALSE(pv.contains(pvh));
        }

        SECTION("does not contain a disjoint mask") {
            auto h = ecs::make_component_mask<Health>();
            REQUIRE_FALSE(pv.contains(h));
        }

        SECTION("any mask contains an empty mask") {
            ecs::ComponentMask empty;
            REQUIRE(pv.contains(empty));
        }
    }

    SECTION("operators") {
        SECTION("operator&=") {
            ecs::ComponentMask a;
            a.set(ecs::component_type<Position>());
            a.set(ecs::component_type<Velocity>());

            ecs::ComponentMask b;
            b.set(ecs::component_type<Velocity>());
            b.set(ecs::component_type<Health>());

            a &= b;

            SECTION("keeps only common bits") {
                REQUIRE(a.test(ecs::component_type<Velocity>()));
            }

            SECTION("clears bits not in both") {
                REQUIRE_FALSE(a.test(ecs::component_type<Position>()));
                REQUIRE_FALSE(a.test(ecs::component_type<Health>()));
            }
        }

        SECTION("operator|=") {
            ecs::ComponentMask a;
            a.set(ecs::component_type<Position>());

            ecs::ComponentMask b;
            b.set(ecs::component_type<Velocity>());

            a |= b;

            SECTION("contains bits from both operands") {
                REQUIRE(a.test(ecs::component_type<Position>()));
                REQUIRE(a.test(ecs::component_type<Velocity>()));
            }

            SECTION("does not set unrelated bits") {
                REQUIRE_FALSE(a.test(ecs::component_type<Health>()));
            }
        }

        SECTION("operator^=") {
            ecs::ComponentMask a;
            a.set(ecs::component_type<Position>());
            a.set(ecs::component_type<Velocity>());

            ecs::ComponentMask b;
            b.set(ecs::component_type<Velocity>());
            b.set(ecs::component_type<Health>());

            a ^= b;

            SECTION("sets bits present in exactly one operand") {
                REQUIRE(a.test(ecs::component_type<Position>()));
                REQUIRE(a.test(ecs::component_type<Health>()));
            }

            SECTION("clears bits present in both operands") {
                REQUIRE_FALSE(a.test(ecs::component_type<Velocity>()));
            }
        }

        SECTION("operator~") {
            ecs::ComponentMask mask;
            mask.set(ecs::component_type<Position>());
            mask.set(ecs::component_type<Velocity>());

            auto complement = ~mask;

            SECTION("flips set bits to unset") {
                REQUIRE_FALSE(complement.test(ecs::component_type<Position>()));
                REQUIRE_FALSE(complement.test(ecs::component_type<Velocity>()));
            }

            SECTION("flips unset bits to set") {
                REQUIRE(complement.test(ecs::component_type<Health>()));
                REQUIRE(complement.test(ecs::component_type<Render>()));
            }

            SECTION("count is max_components minus original count") {
                REQUIRE(complement.count() == ecs::max_components - mask.count());
            }

            SECTION("does not modify the original") {
                REQUIRE(mask.test(ecs::component_type<Position>()));
                REQUIRE(mask.test(ecs::component_type<Velocity>()));
            }
        }

        SECTION("operator&") {
            auto pv = ecs::make_component_mask<Position, Velocity>();
            auto vh = ecs::make_component_mask<Velocity, Health>();

            auto result = pv & vh;

            REQUIRE(result.test(ecs::component_type<Velocity>()));
            REQUIRE_FALSE(result.test(ecs::component_type<Position>()));
            REQUIRE_FALSE(result.test(ecs::component_type<Health>()));
        }

        SECTION("operator|") {
            auto pv = ecs::make_component_mask<Position, Velocity>();
            auto vh = ecs::make_component_mask<Velocity, Health>();

            auto result = pv | vh;

            REQUIRE(result.test(ecs::component_type<Position>()));
            REQUIRE(result.test(ecs::component_type<Velocity>()));
            REQUIRE(result.test(ecs::component_type<Health>()));
            REQUIRE_FALSE(result.test(ecs::component_type<Render>()));
        }

        SECTION("operator^") {
            auto pv = ecs::make_component_mask<Position, Velocity>();
            auto vh = ecs::make_component_mask<Velocity, Health>();

            auto result = pv ^ vh;

            REQUIRE(result.test(ecs::component_type<Position>()));
            REQUIRE(result.test(ecs::component_type<Health>()));
            REQUIRE_FALSE(result.test(ecs::component_type<Velocity>()));
        }
    }
}
