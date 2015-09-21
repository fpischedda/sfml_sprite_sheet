#include "animation_player.hpp"

AnimationPlayer::AnimationPlayer(const Animation* animation) :
  m_animation(animation), m_current_frame(NULL),
  m_current_frame_index(0), m_is_paused(false), m_is_looped(false)
{

}

void AnimationPlayer::set_animation(const Animation& animation)
{
  m_animation = &animation;
  set_frame_index(0);
}

void AnimationPlayer::set_frame_time(sf::Time time)
{
  m_frame_time = time;
}

void AnimationPlayer::play()
{
  m_is_paused = false;
}

void AnimationPlayer::play(const Animation& animation)
{
  if (get_animation() != &animation)
    set_animation(animation);
  play();
}

void AnimationPlayer::pause()
{
  m_is_paused = true;
}

void AnimationPlayer::stop()
{
  m_is_paused = true;
  set_frame_index(0);
}

void AnimationPlayer::set_looped(bool looped)
{
  m_is_looped = looped;
}

void AnimationPlayer::set_frame_index(std::size_t new_frame_index,
				      bool reset_time)
{
  m_current_frame_index = new_frame_index;
  m_current_frame = & m_animation->get_frame(m_current_frame_index);

  if (reset_time)
    m_current_time = sf::Time::Zero;
}

const FrameInfo* AnimationPlayer::update(sf::Time dt) {

  if (!m_is_paused) return m_current_frame;
  
  // if not paused and we have a valid animation
  if (m_animation) {
    // add delta time
    m_current_time += dt;

    // if current time is bigger then the frame time advance one frame
    while (m_current_time >= m_frame_time) {
      // reset time, but keep the remainder
      m_current_time -= m_frame_time;

      // get next Frame index
      if (m_current_frame_index + 1 < m_animation->get_frame_count()) {
	m_current_frame_index++;
      }
      else {
	// animation has ended
	m_current_frame_index = 0; // reset to start

	if (!m_is_looped) {
	  m_is_paused = true;
	  return NULL;
	}
      }
    }

    m_current_frame = & m_animation->get_frame(m_current_frame_index);
    return m_current_frame;
  }

  return NULL;
}
