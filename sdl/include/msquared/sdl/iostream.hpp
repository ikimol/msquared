// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#pragma once

#include "msquared/sdl/detail/pointer.hpp"

#include <SDL3/SDL_iostream.h>

namespace msq::sdl {
namespace detail {

template <>
struct Deleter<SDL_IOStream> {
    void operator()(SDL_IOStream* ptr) const noexcept { SDL_CloseIO(ptr); }
};

} // namespace detail

/// Alias for managed SDL_IOStream
using IOStream = detail::Pointer<SDL_IOStream>;

// operations

/// Read a single byte into memory
bool read_byte(SDL_IOStream* stream, Uint8& byte);

/// Read bytes into memory
std::size_t read_bytes(SDL_IOStream* stream, void* ptr, std::size_t size, std::size_t count);

/// Read an array of objects
template <typename T>
std::size_t read_array_raw(SDL_IOStream* stream, T* ptr, std::size_t count) {
    return read_bytes(stream, ptr, sizeof(T), count);
}

/// Read an array of objects
template <typename T, std::size_t N>
std::size_t read_array(SDL_IOStream* stream, T (&array)[N]) {
    return read_array_raw(stream, array, N);
}

/// Read a single object
template <typename T>
std::size_t read_object(SDL_IOStream* stream, T& obj) {
    return read_array_raw(stream, &obj, 1);
}

/// Write a single byte from memory
bool write_byte(SDL_IOStream* stream, Uint8 byte);

/// Write bytes from memory
std::size_t write_bytes(SDL_IOStream* stream, const void* ptr, std::size_t size, std::size_t count);

/// Write an array of objects
template <typename T>
std::size_t write_array_raw(SDL_IOStream* stream, const T* ptr, std::size_t count) {
    return WriteToStream(stream, ptr, sizeof(T), count);
}

/// Write an array of objects
template <typename T, std::size_t N>
std::size_t write_array(SDL_IOStream* stream, const T (&array)[N]) {
    return write_array_raw(stream, array, N);
}

/// Write a single object
template <typename T>
std::size_t write_object(SDL_IOStream* stream, const T& obj) {
    return write_array_raw(stream, &obj, 1);
}

} // namespace msq::sdl
