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

#include <scene/TitleScreen.hpp>
#include <scene/SolarSystem.hpp>
#include <scene/LeaderBoard.hpp>
#include <constants.hpp>
#include <helpers.hpp>
#include <Game.hpp>

using namespace nongravitar;
using namespace nongravitar::scene;
using namespace nongravitar::constants;

Game &Game::initialize() {
    mAssets.initialize();
    initializeWindow();
    initializeScenes();
    return *this;
}

int Game::run() {
    mClock.restart();

    for (handleEvents(); nullSceneId != mCurrentSceneId; handleEvents()) {
        mCurrentSceneId = mSceneManager.get(mCurrentSceneId).update(mWindow, mSceneManager, mAssets, mClock.restart());
        mWindow.clear();
        mSceneManager.get(mCurrentSceneId).render(mWindow);
        mWindow.display();
    }

    mWindow.close();
    return 0;
}

void Game::initializeWindow() {
    mWindow.create({800, 600}, "NonGravitar", sf::Style::Fullscreen);
    mWindow.setVerticalSyncEnabled(true);
    mWindow.setMouseCursorVisible(false);
    mWindow.setKeyRepeatEnabled(false);
    mWindow.setFramerateLimit(FPS);
    mWindow.setActive(true);
}

void Game::initializeScenes() {
    auto &leaderBoard = mSceneManager.emplace<LeaderBoard>().initialize(mAssets);
    auto &solarSystem = mSceneManager
            .emplace<SolarSystem>(leaderBoard.getSceneId())
            .initialize(mWindow, mSceneManager, mAssets);

    mCurrentSceneId = mSceneManager.emplace<TitleScreen>(solarSystem.getSceneId(), mAssets).getSceneId();
}

void Game::handleEvents() {
    auto event = sf::Event{};

    while (nullSceneId != mCurrentSceneId and mWindow.pollEvent(event)) {
        if (sf::Event::KeyPressed == event.type) {
            switch (event.key.code) {
                case sf::Keyboard::Escape:
                    mCurrentSceneId = nullSceneId;
                    break;

                case sf::Keyboard::F6:
                    mAssets.getAudioManager().toggle();
                    break;

                case sf::Keyboard::Delete:
                    helpers::debug([&]() { mWindow.create({800, 600}, "NonGravitar", sf::Style::None); });
                    break;

                case sf::Keyboard::F4:
                    helpers::debug([&]() { mWindow.create({800, 600}, "NonGravitar", sf::Style::Fullscreen); });
                    break;

                default:
                    mCurrentSceneId = mSceneManager.get(mCurrentSceneId).onEvent(event);
                    break;
            }
        }
    }
}
