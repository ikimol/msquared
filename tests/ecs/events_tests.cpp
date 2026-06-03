// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include <msquared/core/event_queue.hpp>
#include <msquared/ecs/world.hpp>

#include <catch2/catch_test_macros.hpp>

namespace ecs = msq::ecs;

TEST_CASE("ecs_events", "[ecs]") {
    msq::EventQueue event_queue(32);
    ecs::World world(event_queue);

    SECTION("entities") {
        SECTION("destroy") {
            auto e = world.create_entity();

            std::optional<ecs::Entity> entity;
            auto callback = [&](const ecs::EntityWillBeDestroyedEvent& event) { entity = event.entity; };
            auto subscription = event_queue.subscribe<ecs::EntityWillBeDestroyedEvent>(callback);

            e.destroy();
            world.apply_changes();
            event_queue.dispatch();
            REQUIRE(entity == e);
        }
    }

    SECTION("components") {
        world.register_component<int>();

        SECTION("add") {
            auto e = world.create_entity();

            std::optional<ecs::Entity> entity;
            auto callback = [&](const ecs::ComponentWasAddedEvent<int>& event) {
                entity = event.entity;
                REQUIRE(event.entity.has_component<int>());
            };
            auto subscription = event_queue.subscribe<ecs::ComponentWasAddedEvent<int>>(callback);

            e.add_component<int>(42);
            world.apply_changes();
            event_queue.dispatch();
            REQUIRE(entity == e);
        }

        SECTION("remove") {
            auto e = world.create_entity();

            std::optional<ecs::Entity> entity;

            auto callback_1 = [&](const ecs::ComponentWasRemovedEvent<int>& event) { entity = event.entity; };
            auto subscription = event_queue.subscribe<ecs::ComponentWasRemovedEvent<int>>(callback_1);

            e.add_component<int>(42);
            world.apply_changes();
            event_queue.dispatch();
            REQUIRE(e.has_component<int>());

            e.remove_component<int>();
            world.apply_changes();
            event_queue.dispatch();
            REQUIRE_FALSE(e.has_component<int>());

            REQUIRE(entity == e);
        }
    }
}
