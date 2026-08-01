// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/engine/input/action_id.hpp"
#include "msquared/engine/input/binding.hpp"

#include <vector>
#include <unordered_map>

namespace msq {

/// A mapping of actions to their set of bindings
class InputMap {
public:
    /// Add a binding for an action
    void bind(ActionID action_id, Binding binding);

    /// Remove every binding of an action
    void unbind(ActionID action_id);

    /// Remove a single binding of an action
    void unbind(ActionID action_id, Binding binding);

    /// Get the bindings for an action
    const std::vector<Binding>& bindings_for(ActionID action_id) const;

private:
    std::unordered_map<ActionID, std::vector<Binding>> m_bindings;
};

} // namespace msq
