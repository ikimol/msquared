// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include <msquared/ecs.hpp>

#include <array>

namespace ecs = msq::ecs;

int main(int /*argc*/, char* /*argv*/[]) {
    msq::EventQueue event_queue(1024);

    std::array subscriptions = {
        event_queue.subscribe<ecs::EntityWillBeDestroyedEvent>(
            [](auto e) { std::printf("%d will be destroyed\n", e.entity.id().index()); }),
        event_queue.subscribe<ecs::ComponentWasAddedEvent<int>>(
            [](auto e) { std::printf("<int> was added to %d\n", e.entity.id().index()); }),
        event_queue.subscribe<ecs::ComponentWasRemovedEvent<int>>(
            [](auto e) { std::printf("<int> was removed from %d\n", e.entity.id().index()); }),
        event_queue.subscribe<ecs::ComponentWasAddedEvent<float>>(
            [](auto e) { std::printf("<float> was added to %d\n", e.entity.id().index()); }),
        event_queue.subscribe<ecs::ComponentWasRemovedEvent<float>>(
            [](auto e) { std::printf("<float> was removed from %d\n", e.entity.id().index()); }),
    };

    ecs::World world(event_queue);
    world.register_component<int>();
    world.register_component<float>();

    world.create_entity().add_component<int>(10);
    world.create_entity().add_component<int>(20);
    world.create_entity().add_component<int>(30);
    world.create_entity().add_component<int>(40);
    world.apply_changes();
    event_queue.dispatch();

    {
        auto e = world.create_entity();
        e.add_component<int>(50);
        e.add_component<float>(1.1f);
        world.apply_changes();
        event_queue.dispatch();
    }

    {
        auto e = world.create_entity();
        e.add_component<int>();
        e.remove_component<int>();
        world.apply_changes();
        event_queue.dispatch();
    }

    {
        world.create_entity().destroy();
        world.apply_changes();
        event_queue.dispatch();
    }

    world.create_entity_with([](auto& builder) {
        builder.template add_component<int>(60);
        builder.template add_component<float>(3.3f);
    });
    world.apply_changes();
    event_queue.dispatch();

    world.create_entities_with(4, [](auto& builder) {
        builder.template add_component<int>(70);
        builder.template add_component<float>(4.4f);
    });
    world.apply_changes();
    event_queue.dispatch();

    for (auto [f] : world.query<float>()) {
        f /= 2.f;
    }

    for (auto [i] : world.query<int>()) {
        std::printf("i = %d\n", i);
    }

    for (auto [f] : world.query<float>()) {
        std::printf("f = %.2f\n", f);
    }

    for (auto [i, f] : world.query<int, float>()) {
        std::printf("i = %d, f = %.2f\n", i, f);
    }

    for (auto [id, i] : world.query_with_entity<int>()) {
        auto has_float = world.has_component<float>(id);
        std::printf("entity %u: i = %d (has_float = %s)\n", id.index(), i, has_float ? "true" : "false");
    }

    return 0;
}
