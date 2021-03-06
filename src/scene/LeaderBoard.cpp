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

#include <helpers.hpp>
#include <scene/LeaderBoard.hpp>

using namespace nongravitar;
using namespace nongravitar::scene;
using namespace nongravitar::assets;

LeaderBoard &LeaderBoard::initialize(Assets &assets) noexcept {
    pubsub::subscribe(*this);

    mGameOverTitle.setFont(assets.getFontsManager().get(FontId::Mechanical));
    mGameOverTitle.setCharacterSize(64);

    mSpaceLabel.setFont(assets.getFontsManager().get(FontId::Mechanical));
    mSpaceLabel.setCharacterSize(32);
    mSpaceLabel.setString("[ESC]");
    helpers::centerOrigin(mSpaceLabel, mSpaceLabel.getLocalBounds());

    return *this;
}

SceneId LeaderBoard::update(const sf::RenderWindow &window, SceneManager &sceneManager, Assets &assets, sf::Time elapsed) noexcept {
    const auto[windowWidth, windowHeight] = window.getSize();

    if (auto &audioManager = assets.getAudioManager(); SoundTrackId::AmbientStarfield != audioManager.getPlaying()) {
        audioManager.play(SoundTrackId::AmbientStarfield);
    }

    mGameOverTitle.setPosition(windowWidth / 2.0f, windowHeight / 3.14f);
    mSpaceLabel.setPosition(windowWidth / 2.0f, windowHeight / 1.12f);

    return Scene::update(window, sceneManager, assets, elapsed);
}

void LeaderBoard::render(sf::RenderTarget &window) const noexcept {
    window.draw(mGameOverTitle);
    window.draw(mSpaceLabel);
}

void LeaderBoard::operator()(const messages::GameOver &message) noexcept {
    char buffer[64];
    snprintf(buffer, std::size(buffer), "  Game Over\n\n\nScore: %05u", message.score);
    mGameOverTitle.setString(buffer);
    helpers::centerOrigin(mGameOverTitle, mGameOverTitle.getLocalBounds());
}
