#include <rapidjson/document.h>
#include "utils.hpp"
#include "animation_loader.hpp"

AnimationList& AnimationLoader::load_json_from_file(const char* filename) {

  return load_json(load_text_file_content(filename));
}

AnimationList& AnimationLoader::load_json(std::string& json_data) {

  Document d;
  d.Parse(json_data);

  SpriteSheet& ss = SpriteSheet::from_json(d["sprite_sheet_filename"],
					   d["texture_filename"]);

  AnimationList* anim_list = new AnimationList(ss);
  
  for(auto f : d["animations"]){
    auto fi = FrameInfo::create_from_json_dom(f);
    frames.push_back(fi);
  }
}
