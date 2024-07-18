#include "io.hpp"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

std::string readFile(std::string path) {
  return "";
};

void writeFile(std::string path, std::string contents) {

};

Level* loadLevel(std::string levelJSON) {
  Level* level = new Level();
  
  std::vector<std::string> tokens;
  std::istringstream f(levelJSON);
  std::string s;
  while(getline(f, s, ',')) {
    tokens.push_back(s);
  }

  level->name = tokens.at(0);
  level->startX = std::stoi(tokens.at(1));
  level->startY = std::stoi(tokens.at(2));

  return level;
};

std::string writeLevel(Level* level) {
  std::string result = "";

  result += level->name;
  result += ",";
  result += std::to_string(level->startX);
  result += ",";
  result += std::to_string(level->startY);

  return result;
};
