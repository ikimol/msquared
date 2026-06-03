// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include <msquared/core/event_queue.hpp>
#include <msquared/ecs/world.hpp>

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <vector>

namespace ecs = msq::ecs;

struct Foo {
    Foo() = default;

    explicit Foo(int value)
    : value(value) {}

    int value = 0;
};

struct Bar {
    Bar() = default;

    explicit Bar(const char* value)
    : value(value) {}

    std::string_view value;
};

struct Baz {};

TEST_CASE("ecs_query", "[ecs]") {
    msq::EventQueue event_queue(4096);
    ecs::World world(event_queue);

    world.register_component<Foo>();
    world.register_component<Bar>();
    world.register_component<Baz>();

    SECTION("matching entities") {
        world.create_entity_with([](auto& b) { b.template add_component<Foo>(1); });
        world.create_entity_with([](auto& b) { b.template add_component<Foo>(2); });
        world.create_entity_with([](auto& b) { b.template add_component<Foo>(3); });
        world.apply_changes();

        std::vector<int> values;
        for (auto [foo] : world.query<Foo>()) {
            values.push_back(foo.value);
        }
        std::sort(values.begin(), values.end());
        REQUIRE(values == std::vector {1, 2, 3});
    }

    SECTION("filters all required components") {
        world.create_entity_with([](auto& b) {
            b.template add_component<Foo>(1);
            b.template add_component<Bar>("bar");
        });
        world.create_entity_with([](auto& b) { b.template add_component<Foo>(); });
        world.apply_changes();

        auto count = 0;
        for (auto [foo, bar] : world.query<Foo, Bar>()) {
            ++count;
            REQUIRE(foo.value == 1.f);
            REQUIRE(bar.value == "bar");
        }
        REQUIRE(count == 1);
    }

    SECTION("empty world yields nothing") {
        auto count = 0;
        for (auto [_] : world.query<Foo>()) {
            ++count;
        }
        REQUIRE(count == 0);
    }

    SECTION("spans multiple archetypes") {
        for (int i = 0; i < 3; ++i) {
            world.create_entity_with([](auto& b) {
                b.template add_component<Foo>();
                b.template add_component<Bar>();
            });
        }
        for (int i = 0; i < 2; ++i) {
            world.create_entity_with([](auto& b) {
                b.template add_component<Foo>();
                b.template add_component<Bar>();
                b.template add_component<Baz>();
            });
        }
        world.apply_changes();

        auto count = 0;
        for (auto [foo, bar] : world.query<Foo, Bar>()) {
            ++count;
        }
        REQUIRE(count == 5);
    }

    SECTION("skips empty archetypes") {
        auto e1 = world.create_entity_with([](auto& b) {
            b.template add_component<Foo>();
            b.template add_component<Bar>();
        });
        world.create_entity_with([](auto& b) {
            b.template add_component<Foo>();
            b.template add_component<Bar>();
            b.template add_component<Baz>();
        });
        world.apply_changes();

        // prime the query cache so both archetypes are registered for the query
        auto initial = 0;
        for (auto [foo, bar] : world.query<Foo, Bar>()) {
            ++initial;
        }
        REQUIRE(initial == 2);

        // deplete the (Foo, Bar) archetype
        e1.destroy();
        world.apply_changes();

        auto count = 0;
        for (auto [foo, bar] : world.query<Foo, Bar>()) {
            ++count;
        }
        REQUIRE(count == 1);
    }

    SECTION("yields correct entities") {
        auto e = world.create_entity_with([](auto& b) { b.template add_component<Foo>(100); });
        world.apply_changes();

        for (auto [id, h] : world.query_with_entity<Foo>()) {
            REQUIRE(id == e.id());
            REQUIRE(h.value == 100);
        }
    }

    SECTION("entities stay consistent with their components") {
        std::vector<ecs::Entity> entities;
        entities.reserve(5);
        for (int i = 0; i < 5; ++i) {
            entities.push_back(world.create_entity_with([i](auto& b) { b.template add_component<Foo>(i); }));
        }
        world.apply_changes();

        for (auto [id, foo] : world.query_with_entity<Foo>()) {
            auto matcher = [id = id](const ecs::Entity& e) { return e.id() == id; };
            auto it = std::find_if(entities.begin(), entities.end(), matcher);
            REQUIRE(it != entities.end());

            auto expected_value = std::distance(entities.begin(), it);
            REQUIRE(foo.value == expected_value);
        }
    }

    SECTION("components can be mutated during iteration") {
        world.create_entities_with(3, [](auto& b) { b.template add_component<Foo>(); });
        world.apply_changes();

        auto i = 0;
        for (auto [foo] : world.query<Foo>()) {
            foo.value = ++i;
        }

        std::vector<int> values;
        for (auto [foo] : world.query<Foo>()) {
            values.push_back(foo.value);
        }
        std::sort(values.begin(), values.end());
        REQUIRE(values == std::vector {1, 2, 3});
    }

    SECTION("swap-remove preserves component values of remaining entities") {
        std::vector<ecs::Entity> entities;
        entities.reserve(5);
        for (int i = 0; i < 5; ++i) {
            entities.push_back(world.create_entity_with([i](auto& b) { b.template add_component<Foo>(i); }));
        }
        world.apply_changes();

        entities[2].destroy();
        world.apply_changes();

        std::vector<int> values;
        for (auto [foo] : world.query<Foo>()) {
            values.push_back(foo.value);
        }
        std::sort(values.begin(), values.end());
        REQUIRE(values == std::vector {0, 1, 3, 4});
    }

    SECTION("swap-remove preserves entity IDs") {
        std::vector<ecs::Entity> entities;
        entities.reserve(5);
        for (int i = 0; i < 5; ++i) {
            entities.push_back(world.create_entity_with([i](auto& b) { b.template add_component<Foo>(i); }));
        }
        world.apply_changes();

        entities[2].destroy();
        world.apply_changes();

        std::vector<ecs::EntityID> ids;
        for (auto [id, _] : world.query_with_entity<Foo>()) {
            ids.push_back(id);
        }

        REQUIRE(ids.size() == 4);
        REQUIRE(std::find(ids.begin(), ids.end(), entities[2].id()) == ids.end());

        for (int i : {0, 1, 3, 4}) {
            REQUIRE(std::find(ids.begin(), ids.end(), entities[i].id()) != ids.end());
        }
    }

    SECTION("destroying entity during iteration does not affect the current loop") {
        world.create_entity_with([](auto& b) { b.template add_component<Foo>(1); });
        auto e2 = world.create_entity_with([](auto& b) { b.template add_component<Foo>(2); });
        world.apply_changes();

        REQUIRE(e2.is_alive());

        // queue destruction while iterating – both entities must still be visited
        auto count = 0;
        for (auto [id, _] : world.query_with_entity<Foo>()) {
            if (id == e2.id()) {
                e2.destroy();
            }
            ++count;
        }
        REQUIRE(count == 2);

        // only after this call is the entity removed
        world.apply_changes();

        count = 0;
        for (auto [foo] : world.query<Foo>()) {
            ++count;
            REQUIRE(foo.value == 1.f);
        }
        REQUIRE(count == 1);
    }

    SECTION("adding a component during iteration does not affect the current loop") {
        auto e = world.create_entity_with([](auto& b) { b.template add_component<Foo>(1); });
        world.apply_changes();

        for (auto [foo] : world.query<Foo>()) {
            e.add_component<Bar>("add"); // queued, not yet applied
        }

        // before apply, the entity is not yet in the archetype
        auto before = 0;
        for (auto [foo, bar] : world.query<Foo, Bar>()) {
            ++before;
        }
        REQUIRE(before == 0);

        world.apply_changes();

        // after apply, the entity is in the archetype
        auto after = 0;
        for (auto [foo, bar] : world.query<Foo, Bar>()) {
            ++after;
            REQUIRE(bar.value == "add");
        }
        REQUIRE(after == 1);
    }

    SECTION("removing a component during iteration does not affect the current loop") {
        auto e = world.create_entity_with([](auto& b) {
            b.template add_component<Foo>(1);
            b.template add_component<Bar>("remove");
        });
        world.apply_changes();

        for (auto [foo, bar] : world.query<Foo, Bar>()) {
            e.remove_component<Bar>(); // queued, not applied yet
        }

        // before apply, the entity is still in the archetype
        auto before = 0;
        for (auto [foo, bar] : world.query<Foo, Bar>()) {
            ++before;
        }
        REQUIRE(before == 1);

        world.apply_changes();

        // after apply, the entity is no longer in the archetype
        auto after_foo_bar = 0;
        for (auto [foo, bar] : world.query<Foo, Bar>()) {
            ++after_foo_bar;
        }
        REQUIRE(after_foo_bar == 0);

        // entity moved to different archetype
        auto after_foo = 0;
        for (auto [foo] : world.query<Foo>()) {
            ++after_foo;
        }
        REQUIRE(after_foo == 1);
    }
}
