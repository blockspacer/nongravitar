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

#include <SFML/Graphics.hpp>
#include <Scene.hpp>
#include <Assets.hpp>
#include <SceneManager.hpp>

namespace nongravitar {
    class Game final {
    public:
        Game() = default; // no default-constructible

        Game(const Game &) = delete; // no copy-constructible
        Game &operator=(const Game &) = delete; // no copy-assignable

        Game(Game &&) = delete; // no move-constructible
        Game &operator=(Game &&) = delete; // no move-assignable

        /**
         * Initialize assets loading them into memory.
         *
         * @warning
         *  This method should be called exactly once in the life-cycle of this object, any usage of this object
         *  without proper initialization will result in a error.
         */
        Game &initialize();

        int run();

    private:
        void initializeWindow();
        void initializeScenes();

        void handleEvents();

        sf::RenderWindow mWindow;
        SceneManager mSceneManager;
        Assets mAssets;
        sf::Clock mClock;
        SceneId mCurrentSceneId = nullSceneId;
    };
}
