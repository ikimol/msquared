// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/engine/input/binding.hpp"

namespace msq {

bool operator==(Binding lhs, Binding rhs) {
    return lhs.input == rhs.input && lhs.modifiers == rhs.modifiers;
}

bool operator!=(Binding lhs, Binding rhs) {
    return !(lhs == rhs);
}

} // namespace msq
