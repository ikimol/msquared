// Copyright (c) 2026 Miklos Molnar. All rights reserved.

#include "msquared/sdl/iostream.hpp"

namespace msq::sdl {

bool read_byte(SDL_IOStream* stream, Uint8& byte) {
    return SDL_ReadU8(stream, &byte);
}

std::size_t read_bytes(SDL_IOStream* stream, void* ptr, std::size_t size, std::size_t count) {
    return SDL_ReadIO(stream, ptr, count * size);
}

bool write_byte(SDL_IOStream* stream, Uint8 byte) {
    return SDL_WriteU8(stream, byte);
}

std::size_t write_bytes(SDL_IOStream* stream, const void* ptr, std::size_t size, std::size_t count) {
    return SDL_WriteIO(stream, ptr, count * size);
}

} // namespace msq::sdl
