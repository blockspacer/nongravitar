/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Davide Di Carlo
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <variant>
#include "wrapper.hpp"
#include "helpers.hpp"

namespace gravitar::components {
    struct Position final : public Wrapper<sf::Vector2f> {
        template<typename ...Args>
        explicit Position(Args &&... args) : Wrapper(std::forward<Args>(args)...) {}
    };

    struct Velocity final : public Wrapper<sf::Vector2f> {
        template<typename ...Args>
        explicit Velocity(Args &&... args) : Wrapper(std::forward<Args>(args)...) {}
    };

    struct Rotation final : public Wrapper<float> {
        template<typename ...Args>
        explicit Rotation(Args &&... args) : Wrapper(std::forward<Args>(args)...) {}
    };

    struct Renderable final : public Wrapper<std::variant<sf::Sprite>> {
        Renderable() = delete;

        explicit Renderable(sf::Sprite &&instance);
    };
}
