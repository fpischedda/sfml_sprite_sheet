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

#ifndef ANIMATION_PLAYER_HPP
#define ANIMATION_PLAYER_HPP

#include <SFML/System.hpp>
#include "animation.hpp"

class AnimationPlayer{
  
public:
  AnimationPlayer(const Animation* animation=NULL);

  const FrameInfo* get_current_frame() const;
  const FrameInfo* update(sf::Time dt);

  void set_frame_time(sf::Time time);
  void play();
  void play(const Animation& animation);
  void pause();
  void stop();
  void set_looped(bool looped);

  inline const Animation* get_animation() const {
    return m_animation;
  }
  void set_animation(const Animation& animation);
  
  inline bool is_looped() const {
    return m_is_looped;
  }
  inline bool is_playing() const {
    return !m_is_paused;
  }
  inline sf::Time get_frame_time() const {
    return m_frame_time;
  }
  void set_frame_index(std::size_t new_frame_index,
				   bool resetTime = true);
  
private:
  const FrameInfo* m_current_frame;
  const Animation* m_animation;
  
  sf::Time m_frame_time;
  sf::Time m_current_time;
  std::size_t m_current_frame_index;
  bool m_is_paused;
  bool m_is_looped;
};

#endif // ANIMATION_INCLUDE
