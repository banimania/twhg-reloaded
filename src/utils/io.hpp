#ifndef IO_HPP
#define IO_HPP

#include <string>
#include "../level/level.hpp"

std::string readFile(std::string path);
void writeFile(std::string path, std::string contents);

Level* loadLevel(std::string path);
std::string writeLevel(Level* level);

#endif
