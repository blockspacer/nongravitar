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

#include <Assets.hpp>

using namespace nongravitar;
using namespace nongravitar::assets;

void Assets::initialize() {
    mFontsManager.initialize();
    mAudioManager.initialize();
    mTexturesManager.initialize();
    mSpriteSheetsManager.initialize(mTexturesManager);
}

const SpriteSheetsManager &Assets::getSpriteSheetsManager() const noexcept {
    return mSpriteSheetsManager;
}

const TexturesManager &Assets::getTexturesManager() const noexcept {
    return mTexturesManager;
}

const FontsManager &Assets::getFontsManager() const noexcept {
    return mFontsManager;
}

AudioManager &Assets::getAudioManager() noexcept {
    return mAudioManager;
}
