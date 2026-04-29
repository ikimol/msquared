// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/core/assert.hpp"

#include <filesystem>
#include <iostream>

namespace msq {
namespace {

assertion_log_fn g_assertion_log_fn;

void default_assertion_log_fn(const shard::source_location& location, const char* message) {
    const auto filename = std::filesystem::path(location.file_name).filename().string();
    std::cerr << '[' << filename << ':' << location.line << "] Assertion failed: " << message << std::endl;
}

} // namespace

void set_assertion_logger(assertion_log_fn log_fn) {
    g_assertion_log_fn = log_fn;
}

namespace detail {

void log_assertion(const shard::source_location& location, const char* message) {
    (g_assertion_log_fn ? g_assertion_log_fn : default_assertion_log_fn)(location, message);
}

} // namespace detail
} // namespace msq
