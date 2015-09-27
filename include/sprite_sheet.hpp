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
#include <memory>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

struct FrameInfo {
  enum Rotation {

    None=0,
    CW,
    CCW
  };

  sf::Vector2f tex_coords[4];
  sf::Vector2f frame_size[4];
  sf::FloatRect local_bounds;
  Rotation rotation;

  template <typename T>
  static FrameInfo from_rect(const sf::Rect<T> rect,
			      FrameInfo::Rotation rotation=FrameInfo::Rotation::None);
};

class SpriteSheet
{
public:
  typedef std::unique_ptr<SpriteSheet> SpriteSheetPtr;
  typedef std::unique_ptr<sf::Texture> TexturePtr;
  
  SpriteSheet(sf::Texture* texture=nullptr);

  static SpriteSheetPtr from_json(const char* sprite_sheet_filename,
						 const char* texture_filename);
  template <typename T>
  SpriteSheet& add_frame_rect(const sf::Rect<T> rect,
			      FrameInfo::Rotation rotation=FrameInfo::Rotation::None);
  SpriteSheet& add_frame(const std::vector<sf::Vector2f>& points);
  SpriteSheet& set_texture(TexturePtr& texture);

  inline const sf::Texture* get_texture() const {
    return m_texture.get();
  }

  inline std::size_t get_size() const {
    return m_frames.size();
  }

  inline const FrameInfo& get_frame(std::size_t n) const {
    return m_frames[n];
  }

private:
  std::vector<FrameInfo> m_frames;
  TexturePtr m_texture;
};

#endif // SPRITE_SHEET_HPP
