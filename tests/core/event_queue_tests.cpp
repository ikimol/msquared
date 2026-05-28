// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include <msquared/core/event_queue.hpp>

#include <catch2/catch_test_macros.hpp>

#include <string_view>

namespace {

struct FooEvent {
    FooEvent() = default;

    explicit FooEvent(int value)
    : value(value) {}

    int value = 0;
};

struct BarEvent {
    BarEvent() = default;

    explicit BarEvent(const char* value)
    : value(value) {}

    std::string_view value;
};

} // namespace

TEST_CASE("core_event_queue", "[core]") {
    msq::EventQueue queue(64);

    SECTION("dispatch") {
        SECTION("typed subscriber") {
            auto received = -1;

            auto s = queue.subscribe<FooEvent>([&](const FooEvent& e) { received = e.value; });

            queue.send<FooEvent>(3);
            REQUIRE(received == -1); // not yet dispatched

            queue.dispatch();
            REQUIRE(received == 3);
        }

        SECTION("raw-type subscriber") {
            auto called = false;

            auto s = queue.subscribe(msq::event_type<FooEvent>(), [&](const void* ptr) {
                auto& e = *static_cast<const FooEvent*>(ptr);
                called = e.value == 5;
            });

            queue.send<FooEvent>(5);
            queue.dispatch();
            REQUIRE(called);
        }
    }

    SECTION("multiple event types are dispatched independently") {
        auto foo_count = 0;
        auto bar_count = 0;

        auto s1 = queue.subscribe<FooEvent>([&](const FooEvent&) { ++foo_count; });
        auto s2 = queue.subscribe<BarEvent>([&](const BarEvent&) { ++bar_count; });

        queue.send<FooEvent>();
        queue.send<BarEvent>();
        queue.send<FooEvent>();
        queue.dispatch();

        REQUIRE(foo_count == 2);
        REQUIRE(bar_count == 1);
    }

    SECTION("no subscribers") {
        queue.send<FooEvent>();
        REQUIRE_NOTHROW(queue.dispatch());
    }

    SECTION("multiple subscribers") {
        auto count = 0;

        auto s1 = queue.subscribe<FooEvent>([&](const FooEvent&) { ++count; });
        auto s2 = queue.subscribe<FooEvent>([&](const FooEvent&) { ++count; });

        queue.send<FooEvent>();
        queue.dispatch();
        REQUIRE(count == 2);
    }

    SECTION("destroying subscription") {
        auto count = 0;

        {
            auto s = queue.subscribe<FooEvent>([&](const FooEvent&) { ++count; });
            queue.send<FooEvent>();
            queue.dispatch();
            REQUIRE(count == 1);
        }

        queue.send<FooEvent>();
        queue.dispatch();
        REQUIRE(count == 1);
    }

    SECTION("enabled state") {
        auto s = queue.subscribe<FooEvent>([](const FooEvent&) {});
        REQUIRE(s.is_enabled());

        s.set_enabled(false);
        REQUIRE_FALSE(s.is_enabled());

        s.set_enabled(true);
        REQUIRE(s.is_enabled());
    }

    SECTION("disabled subscription") {
        auto count = 0;

        auto s = queue.subscribe<FooEvent>([&](const FooEvent&) { ++count; });
        s.set_enabled(false);

        queue.send<FooEvent>();
        queue.dispatch();
        REQUIRE(count == 0);
    }

    SECTION("re-enabled subscription") {
        int count = 0;

        auto s = queue.subscribe<FooEvent>([&](const FooEvent&) { ++count; });
        s.set_enabled(false);

        queue.send<FooEvent>();
        queue.dispatch();
        REQUIRE(count == 0);

        s.set_enabled(true);
        queue.send<FooEvent>();
        queue.dispatch();
        REQUIRE(count == 1);
    }

    SECTION("deferring") {
        auto count = 0;

        auto s = queue.subscribe<FooEvent>([&](const FooEvent&) {
            ++count;
            // send another event during dispatch
            queue.send<FooEvent>();
        });

        queue.send<FooEvent>();
        queue.dispatch(); // processes 1 event, enqueues 1 more
        REQUIRE(count == 1);

        queue.dispatch(); // processes the deferred event
        REQUIRE(count == 2);
    }
}
