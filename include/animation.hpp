////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Francesco Pischedda (francesco.pischedda@google.com)
// Based on the previous work of
// Copyright (C) 2014 Maximilian Wagenbach (aka. Foaly) (foaly.f@web.de)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>
#include "sprite_sheet.hpp"

typedef std::vector<FrameInfo&> AnimationFrames;

class Animation
{
public:
  Animation(const SpriteSheet& sprite_sheet, const AnimationFrames& frames);

  void set_sprite_sheet(const SpriteSheet& sprite_sheet);

  inline const sf::Texture* get_texture() const {
    return m_sprite_sheet->get_texture();
  }

  inline const SpriteSheet& get_sprite_sheet() const {
    return m_sprite_sheet;
  }

  inline std::size_t get_frame_count() const {
    return m_animation_frames.size();
  }

  inline const FrameInfo& get_frame(std::size_t n) const {
    return m_animation_frames[n];
  }

private:
  const SpriteSheet& m_sprite_sheet;
  const AnimationFrames& m_animation_frames;
};

#endif // ANIMATION_INCLUDE
