// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/engine/input/input_map.hpp"

#include <algorithm>

namespace msq {

void InputMap::bind(ActionID action_id, Binding binding) {
    m_bindings[action_id].push_back(binding);
}

void InputMap::unbind(ActionID action_id) {
    m_bindings.erase(action_id);
}

void InputMap::unbind(ActionID action_id, Binding binding) {
    if (auto it = m_bindings.find(action_id); it != m_bindings.end()) {
        auto& bindings = it->second;
        bindings.erase(std::remove(bindings.begin(), bindings.end(), binding), bindings.end());
    }
}

const std::vector<Binding>& InputMap::bindings_for(ActionID action_id) const {
    static const std::vector<Binding> empty;
    auto it = m_bindings.find(action_id);
    return it != m_bindings.end() ? it->second : empty;
}

} // namespace msq
