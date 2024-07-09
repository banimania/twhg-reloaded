#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <raylib.h>
#include <string>

inline Texture keyTexture;
inline Texture arrowLeftTexture;
inline Texture arrowRightTexture;
inline Texture configurationTexture;
inline Texture playTexture;
inline Texture rightArrowTexture;
inline Texture downArrowTexture;
inline Texture leftArrowTexture;
inline Texture upArrowTexture;
inline Texture trashTexture;
inline Texture duplicateTexture;

void loadTextures();
Texture GetTextureFromName(std::string textureName);

#endif
