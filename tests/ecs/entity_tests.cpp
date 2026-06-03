// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include <msquared/core/event_queue.hpp>
#include <msquared/ecs/world.hpp>

#include <catch2/catch_test_macros.hpp>

namespace ecs = msq::ecs;

TEST_CASE("ecs_entities", "[ecs]") {
    msq::EventQueue event_queue(4096);
    ecs::World world(event_queue);

    SECTION("basics") {
        auto e = world.create_entity();
        REQUIRE(e.is_alive());

        SECTION("destroy") {
            e.destroy();
            world.apply_changes();
            REQUIRE_FALSE(e.is_alive());
        }

        SECTION("reuse") {
            REQUIRE(e.id().index() == 0);
            REQUIRE(e.id().generation() == 1);

            e.destroy();
            world.apply_changes();

            auto e2 = world.create_entity();
            REQUIRE(e2.id().index() == 0);
            REQUIRE(e2.id().generation() == 2);
        }

        SECTION("copy") {
            auto copy = e;
            REQUIRE(copy == e);

            copy.destroy();
            world.apply_changes();
            REQUIRE_FALSE(e.is_alive());
            REQUIRE_FALSE(copy.is_alive());
        }

        SECTION("clone") {
            auto clone = e.clone();
            REQUIRE(clone != e);

            clone.destroy();
            world.apply_changes();
            REQUIRE(e.is_alive());
            REQUIRE_FALSE(clone.is_alive());
        }
    }

    SECTION("multiple") {
        std::vector<ecs::Entity> entities;
        entities.reserve(100);

        for (auto i = 0; i < 100; ++i) {
            entities.push_back(world.create_entity());
        }

        SECTION("destroy") {
            for (auto e : entities) {
                e.destroy();
            }
            world.apply_changes();
        }
    }
}
