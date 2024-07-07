#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <raylib.h>
#include <string>

inline Texture enemyTexture;
inline Texture coinTexture;
inline Texture keyTexture;
inline Texture arrowLeftTexture;
inline Texture arrowRightTexture;
inline Texture configurationTexture;
inline Texture playTexture;

void loadTextures();
Texture GetTextureFromName(std::string textureName);

#endif
