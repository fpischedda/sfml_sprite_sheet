////////////////////////////////////////////////////////////
//
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

#include <cmath>
#include "sprite_sheet.hpp"

template <typename T>
const T vector_length(const sf::Vector2<T>& v){

  return static_cast<T>(std::fabs(sqrt(v.x*v.x + v.y*v.y)));
}

SpriteSheet::SpriteSheet(const sf::Texture* tex) : m_texture(tex)
{

}

template <typename T>
void SpriteSheet::add_frame_rect(sf::Rect<T> rect)
{
  auto right = rect.left + rect.width;
  auto bottom = rect.top + rect.height;
  
  FrameInfo frame = {
    {
      sf::Vector2f(0, 0),
      sf::Vector2f(0, rect.height),
      sf::Vector2f(rect.width, rect.height),
      sf::Vector2f(rect.width, 0),
    },
    {
      sf::Vector2f(rect.left, rect.top),
      sf::Vector2f(rect.left, bottom),
      sf::Vector2f(right, bottom),
      sf::Vector2f(right, rect.top),
    },
    {0, 0, static_cast<float>(rect.width), static_cast<float>(rect.height) }
  };
  
  m_frames.push_back(frame);
}

void SpriteSheet::add_frame(const std::vector<sf::Vector2f>& points){

  auto width = vector_length(points[0] - points[1]);
  auto height = vector_length(points[0] - points[2]);
  
  FrameInfo frame = {
    {
      sf::Vector2f(0, 0),
      sf::Vector2f(0, height),
      sf::Vector2f(width, height),
      sf::Vector2f(width, 0),
    },
    {
      points[0],
      points[1],
      points[2],
      points[3],
    },
    {0, 0, width, height }
  };
  
  m_frames.push_back(frame);
}

void SpriteSheet::set_texture(sf::Texture& texture)
{
    m_texture = &texture;
}
