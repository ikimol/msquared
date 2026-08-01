// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/engine/input/input_map.hpp"

#include <string>

namespace msq {

/// A named context for the active bindings at a given time
class InputContext {
public:
    explicit InputContext(std::string name)
    : m_name(std::move(name)) {}

    /// Get the name of this context
    const std::string& name() const { return m_name; }

    /// Get the inputs of this context
    InputMap& input_map() { return m_input_map; }

    /// Get the inputs of this context
    const InputMap& input_map() const { return m_input_map; }

private:
    std::string m_name;
    InputMap m_input_map;
};

} // namespace msq
