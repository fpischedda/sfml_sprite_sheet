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

#include "animated_sprite.hpp"

AnimatedSprite::AnimatedSprite(Animation *animation) :
    m_animation_player(animation)
{
  update(sf::Time::Zero);
}

void AnimatedSprite::set_color(const sf::Color& color)
{
  // Update the vertices' color
  m_vertices[0].color = color;
  m_vertices[1].color = color;
  m_vertices[2].color = color;
  m_vertices[3].color = color;
}

sf::FloatRect AnimatedSprite::getLocalBounds() const
{
  return m_current_frame->local_bounds;
}

sf::FloatRect AnimatedSprite::getGlobalBounds() const
{
  return getTransform().transformRect(getLocalBounds());
}

void AnimatedSprite::update(const sf::Time dt)
{
  auto frame = m_animation_player.update(dt);
  
  if (frame) {

    if( frame != m_current_frame){
      m_vertices[0].position = frame->frame_size[0];
      m_vertices[1].position = frame->frame_size[1];
      m_vertices[2].position = frame->frame_size[2];
      m_vertices[3].position = frame->frame_size[3];
	
      m_vertices[0].texCoords = frame->tex_coords[0];
      m_vertices[1].texCoords = frame->tex_coords[1];
      m_vertices[2].texCoords = frame->tex_coords[2];
      m_vertices[3].texCoords = frame->tex_coords[3];

      m_current_frame = frame;
    }
  }
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if (m_texture) {
    states.transform *= getTransform();
    states.texture = m_texture;
    target.draw(m_vertices, 4, sf::Quads, states);
  }
}
