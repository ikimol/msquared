// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include <shard/source_location.hpp>

#include <cstdlib>

#if defined(MSQ_DEBUG)
#define MSQ_INTERNAL_ABORT() std::abort()
#define MSQ_INTERNAL_DEBUG_ASSERT(c, m)                                                                                \
    do {                                                                                                               \
        if (!(c)) {                                                                                                    \
            msq::detail::log_assertion(SHARD_CURRENT_SOURCE_LOCATION, (m));                                            \
            std::abort();                                                                                              \
        }                                                                                                              \
    } while (false)
#else
#define MSQ_INTERNAL_ABORT() ((void) (0))
#define MSQ_INTERNAL_DEBUG_ASSERT(c, m) ((void) (0))
#endif

#define MSQ_INTERNAL_ASSERT_1(c) MSQ_INTERNAL_DEBUG_ASSERT(c, #c)
#define MSQ_INTERNAL_ASSERT_2(c, m) MSQ_INTERNAL_DEBUG_ASSERT(c, m)
#define MSQ_INTERNAL_PICK_ASSERT(_1, _2, M, ...) M

/// Raise an assertion in debug builds with an optional message
#define MSQ_ASSERT(...)                                                                                                \
    MSQ_INTERNAL_PICK_ASSERT(__VA_ARGS__, MSQ_INTERNAL_ASSERT_2, MSQ_INTERNAL_ASSERT_1, )(__VA_ARGS__)

/// Raises an assertion in debug builds and returns the value in release builds
#define MSQ_ASSERT_RETURN(c, r)                                                                                        \
    do {                                                                                                               \
        if (!(c)) {                                                                                                    \
            msq::detail::log_assertion(SHARD_CURRENT_SOURCE_LOCATION, #c);                                             \
            MSQ_INTERNAL_ABORT();                                                                                      \
            return (r);                                                                                                \
        }                                                                                                              \
    } while (false)

/// Raises an assertion in debug builds and returns early
#define MSQ_ASSERT_RETURN_VOID(c)                                                                                      \
    do {                                                                                                               \
        if (!(c)) {                                                                                                    \
            msq::detail::log_assertion(SHARD_CURRENT_SOURCE_LOCATION, #c);                                             \
            MSQ_INTERNAL_ABORT();                                                                                      \
            return;                                                                                                    \
        }                                                                                                              \
    } while (false)

namespace msq {

/// The type of function called to log an assertion
using assertion_log_fn = void (*)(const shard::source_location&, const char*);

/// Set the active assertion logger function
void set_assertion_logger(assertion_log_fn log_fn);

namespace detail {

// invoke the active assertion handler
void log_assertion(const shard::source_location& location, const char* message);

} // namespace detail
} // namespace msq
