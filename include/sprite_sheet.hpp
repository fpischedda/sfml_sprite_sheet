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

#ifndef SPRITE_SHEET_HPP
#define SPRITE_SHEET_HPP

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

struct FrameInfo {

  sf::Vector2f tex_coords[4];
  sf::Vector2f frame_size[4];
  sf::FloatRect local_bounds;
};

class SpriteSheet
{
public:
  SpriteSheet(const sf::Texture* tex=NULL);

  template <typename T>
  SpriteSheet& add_frame_rect(const sf::Rect<T> rect);
  SpriteSheet& add_frame(const std::vector<sf::Vector2f>& points);
  SpriteSheet& set_texture(const sf::Texture& texture);

  inline const sf::Texture* get_texture() const {
    return m_texture;
  }

  inline std::size_t get_size() const {
    return m_frames.size();
  }

  inline const FrameInfo& get_frame(std::size_t n) const {
    return m_frames[n];
  }

private:
  std::vector<FrameInfo> m_frames;
  const sf::Texture* m_texture;
};

#endif // SPRITE_SHEET_HPP
