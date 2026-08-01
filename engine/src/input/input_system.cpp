// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/engine/input/input_system.hpp"

#include <msquared/core/assert.hpp>

#include <shard/algorithm/variant_switch.hpp>

#include <algorithm>

#define MATCH_ACTION(bindings, state)                                                                                  \
    std::any_of(bindings.begin(), bindings.end(), [this](const auto& binding) {                                        \
        auto state = shard::variant_switch(                                                                            \
            binding.input,                                                                                             \
            [this](const SDL_Scancode& c) { return m_keyboard.state(c); },                                             \
            [this](const MouseButton& b) { return m_mouse.state(b); });                                                \
        return state && binding.modifiers == current_modifiers();                                                      \
    })

namespace msq {
namespace {

Modifiers current_modifiers() {
    auto keymod = SDL_GetModState();
    Modifiers modifiers;
    modifiers.set(Modifier::Shift, keymod & SDL_KMOD_SHIFT);
    modifiers.set(Modifier::Ctrl, keymod & SDL_KMOD_CTRL);
    modifiers.set(Modifier::Alt, keymod & SDL_KMOD_ALT);
    modifiers.set(Modifier::System, keymod & SDL_KMOD_GUI);
    return modifiers;
}

} // namespace

ContextID InputSystem::register_context(std::string name) {
    MSQ_ASSERT(m_contexts.size() < invalid_context);
    auto context_id = m_contexts.size();
    m_contexts.emplace_back(std::move(name));
    return context_id;
}

void InputSystem::set_active_context(ContextID context_id) {
    MSQ_ASSERT(context_id < m_contexts.size() && context_id != invalid_context, "invalid context");
    m_active_context_id = context_id;
}

InputMap& InputSystem::input_map_for(ContextID context_id) {
    MSQ_ASSERT(context_id < m_contexts.size() && context_id != invalid_context, "invalid context");
    return m_contexts[context_id].input_map();
}

bool InputSystem::is_pressed(ActionID action_id) const {
    MSQ_ASSERT(m_active_context_id != invalid_context, "invalid context");
    return MATCH_ACTION(m_contexts[m_active_context_id].input_map().bindings_for(action_id), is_pressed);
}

bool InputSystem::is_held(ActionID action_id) const {
    MSQ_ASSERT(m_active_context_id != invalid_context, "invalid context");
    return MATCH_ACTION(m_contexts[m_active_context_id].input_map().bindings_for(action_id), is_held);
}

bool InputSystem::was_just_pressed(ActionID action_id) const {
    MSQ_ASSERT(m_active_context_id != invalid_context, "invalid context");
    return MATCH_ACTION(m_contexts[m_active_context_id].input_map().bindings_for(action_id), was_just_pressed);
}

bool InputSystem::was_just_released(ActionID action_id) const {
    MSQ_ASSERT(m_active_context_id != invalid_context, "invalid context");
    return MATCH_ACTION(m_contexts[m_active_context_id].input_map().bindings_for(action_id), was_just_released);
}

void InputSystem::begin_frame() {
    m_mouse.begin_frame();
    m_keyboard.begin_frame();
}

void InputSystem::handle_event(const SDL_Event& event) {
    switch (event.type) {
    case SDL_EVENT_KEY_DOWN:
    case SDL_EVENT_KEY_UP:
        m_keyboard.update(event.key.scancode, event.key.down);
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP:
        m_mouse.update(static_cast<MouseButton>(event.button.button), event.button.down);
        break;
    default:
        break;
    }
}

void InputSystem::reset() {
    m_mouse.reset();
    m_keyboard.reset();
}

} // namespace msq
