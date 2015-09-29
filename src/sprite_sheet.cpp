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
#include <rapidjson/document.h>
#include "utils.hpp"
#include "sprite_sheet.hpp"

template <typename T>
const T vector_length(const sf::Vector2<T>& v){

  return static_cast<T>(std::fabs(sqrt(v.x*v.x + v.y*v.y)));
}

template <typename T>
FrameInfo from_rect(const sf::Rect<T> rect,
			    FrameInfo::Rotation rotation)
{
  auto right = rect.left + rect.width;
  auto bottom = rect.top + rect.height;
  
  switch(rotation){
    
  case FrameInfo::Rotation::CW:
    return {
      {
	sf::Vector2f(right, rect.top),
	sf::Vector2f(rect.left, rect.top),
	sf::Vector2f(rect.left, bottom),
	sf::Vector2f(right, bottom),
      },
      {
	sf::Vector2f(0, 0),
	sf::Vector2f(0, rect.width),
	sf::Vector2f(rect.height, rect.width),
	sf::Vector2f(rect.height, 0),
      },
      {0, 0, static_cast<float>(rect.height), static_cast<float>(rect.width) }
    };
    
  case FrameInfo::Rotation::CCW:
    return {
      {
	sf::Vector2f(rect.left, bottom),
	sf::Vector2f(right, bottom),
	sf::Vector2f(right, rect.top),
	sf::Vector2f(rect.left, rect.top),
      },
      {
	sf::Vector2f(0, 0),
	sf::Vector2f(0, rect.height),
	sf::Vector2f(rect.width, rect.height),
	sf::Vector2f(rect.width, 0),
      },
      {0, 0, static_cast<float>(rect.height), static_cast<float>(rect.width) }
    };

  default:
    return {
      {
	sf::Vector2f(rect.left, rect.top),
	sf::Vector2f(rect.left, bottom),
	sf::Vector2f(right, bottom),
	sf::Vector2f(right, rect.top),
      },
      {
	sf::Vector2f(0, 0),
	sf::Vector2f(0, rect.height),
	sf::Vector2f(rect.width, rect.height),
	sf::Vector2f(rect.width, 0),
      },
      {0, 0, static_cast<float>(rect.width), static_cast<float>(rect.height) }
    };
  }
}

SpriteSheet::SpriteSheet(TexturePtr& texture) : m_texture(std::move(texture))
{

}

SpriteSheet::SpriteSheetPtr SpriteSheet::from_json(const char* sprite_sheet_filename,
						   const char* texture_filename) {

  TexturePtr tex(new sf::Texture());

  if( !tex->loadFromFile(texture_filename) ) {
    return nullptr;
  }

  rapidjson::Document d;
  d.Parse(load_text_file_content(sprite_sheet_filename).c_str());

  SpriteSheetPtr ss(new SpriteSheet(tex));

  const rapidjson::Value& frames = d["frames"];
  for(auto f=frames.Begin(); f != frames.End(); ++f) {
    auto rotation = (*f)["rotated"].GetBool() ?
      FrameInfo::Rotation::CW : FrameInfo::Rotation::None;
    const rapidjson::Value& frame = (*f)["frame"];
    auto x = frame["x"].GetInt();
    auto y = frame["y"].GetInt();
    auto width = frame["w"].GetInt();
    auto height = frame["h"].GetInt();
    ss->add_frame_rect(sf::IntRect(x, y, width, height), rotation);
  }

  return ss;
}

template <typename T>
SpriteSheet& SpriteSheet::add_frame_rect(const sf::Rect<T> rect,
					 FrameInfo::Rotation rotation){

  m_frames.push_back(FrameInfo::from_rect(rect, rotation));
  return *this;
}

SpriteSheet& SpriteSheet::add_frame(const std::vector<sf::Vector2f>& points){

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

  return *this;
}

SpriteSheet& SpriteSheet::set_texture(TexturePtr& texture)
{
  m_texture = std::move(texture);

  return *this;
}
