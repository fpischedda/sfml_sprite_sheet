#include <iostream>
#include <fstream>


std::string load_text_file_content(const char* filename) {
  ifstream source;
  std::stringstream buffer;

  source.open(filename, ios::in);

  if(source.is_open()){
    buffer << source.rdbuf();
  }

  source.close();

  return buffer.str();
}
