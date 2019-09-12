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

#include <map>
#include <memory>
#include <typeindex>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "animation.hpp"
#include "cycle.hpp"
#include "spritesheet.hpp"

namespace gravitar {
    /*
     * SoundTracks
     */

    enum class SoundTrackId {
        MainTheme,
    };

    class SoundTracksManager final {
    public:
        friend class Game;

        SoundTracksManager(const SoundTracksManager &) = delete; // no copy-constructible
        SoundTracksManager &operator=(const SoundTracksManager &) = delete; // no copy-assignable

        SoundTracksManager(SoundTracksManager &&) = delete; // no move-constructible
        SoundTracksManager &operator=(SoundTracksManager &&) = delete; // no move-assignable

        void togglePlaying() noexcept;

        void play(SoundTrackId id) noexcept;

    private:
        SoundTracksManager() = default; // private default constructor, only Game can construct this class

        void initialize();

        void load(const char *filename, SoundTrackId id);

        std::map<SoundTrackId, sf::Music> mSoundtracks;
        sf::Music *mCurrentlyPlaying{nullptr};
    };

    /*
     * Fonts
     */

    enum class FontId {
        Mechanical
    };

    class FontsManager final {
    public:
        friend class Game;

        FontsManager(const FontsManager &) = delete; // no copy-constructible
        FontsManager &operator=(const FontsManager &) = delete; // no copy-assignable

        FontsManager(FontsManager &&) = delete; // no move-constructible
        FontsManager &operator=(FontsManager &&) = delete; // no move-assignable

        [[nodiscard]] const sf::Font &get(FontId id) const noexcept;

    private:
        FontsManager() = default; // private default constructor, only Game can construct this class

        void initialize();

        void load(const char *filename, FontId id);

        std::map<FontId, sf::Font> mFonts;
    };

    /*
     * Textures
     */

    enum class TextureId {
        GravitarTitle,
        SpaceShip,
        Bullet,
    };

    class TexturesManager final {
    public:
        friend class Game;

        TexturesManager(const TexturesManager &) = delete; // no copy-constructible
        TexturesManager &operator=(const TexturesManager &) = delete; // no copy-assignable

        TexturesManager(TexturesManager &&) = delete; // no move-constructible
        TexturesManager &operator=(TexturesManager &&) = delete; // no move-assignable

        [[nodiscard]] const sf::Texture &get(TextureId id) const noexcept;

    private:
        TexturesManager() = default; // private default constructor, only Game can construct this class

        void initialize();

        void load(const char *filename, TextureId id);

        std::map<TextureId, sf::Texture> mTextures;
    };

    /*
     * GravitarTitle
     */

    class GravitarTitle final : public sf::Drawable {
    public:
        friend class Game;

        GravitarTitle(const GravitarTitle &) = delete; // no copy-constructible
        GravitarTitle &operator=(const GravitarTitle &) = delete; // no copy-assignable

        GravitarTitle(GravitarTitle &&) = delete; // no move-constructible
        GravitarTitle &operator=(GravitarTitle &&) = delete; // no move-assignable

        void setPosition(float x, float y);

    private:
        GravitarTitle() = default; // private default constructor, only Game can construct this class

        void initialize(const TexturesManager &textureManager);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const final;

        sf::Sprite mSprite;
    };

    /*
     * SpaceLabel
     */

    class SpaceLabel final : public sf::Drawable {
    public:
        friend class Game;

        SpaceLabel(const SpaceLabel &) = delete; // no copy-constructible
        SpaceLabel &operator=(const SpaceLabel &) = delete; // no copy-assignable

        SpaceLabel(SpaceLabel &&) = delete; // no move-constructible
        SpaceLabel &operator=(SpaceLabel &&) = delete; // no move-assignable

        void update(const sf::Time &time);

        void setPosition(float x, float y);

    private:
        SpaceLabel(); // private default constructor, only Game can construct this class

        void initialize(const FontsManager &fontsManager);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const final;

        using Transition = std::array<sf::Uint8, 8>;
        Animation<sf::Text, Cycle<const Transition, Transition::const_iterator>> mInstance;
    };

    /*
     * SpriteSheets
     */

    enum class SpriteSheetId {
        SpaceShip,
        Bullet,
    };

    class SpriteSheetsManager final {
    public:
        friend class Game;

        SpriteSheetsManager(const SpriteSheetsManager &) = delete; // no copy-constructible
        SpriteSheetsManager &operator=(const SpriteSheetsManager &) = delete; // no copy-assignable

        SpriteSheetsManager(SpriteSheetsManager &&) = delete; // no move-constructible
        SpriteSheetsManager &operator=(SpriteSheetsManager &&) = delete; // no move-assignable

        [[nodiscard]] const SpriteSheet &get(SpriteSheetId id) const noexcept;

    private:
        SpriteSheetsManager() = default; // private default constructor, only Game can construct this class

        void initialize(const TexturesManager &texturesManager);

        std::map<SpriteSheetId, SpriteSheet> mSpriteSheets;
    };
}
