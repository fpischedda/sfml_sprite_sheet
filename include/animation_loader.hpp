#ifndef ANIMATION_LOADER_HPP
#define ANIMATION_LOADER_HPP

#include "animation.hpp"


class AnimationLoader {

public:
  static Animation* load_json(const char* filename);
};
#endif
