#ifndef SOUNDS_HPP
#define SOUNDS_HPP

#include <raylib.h>

inline Sound deathSound;
inline Sound coinPickupSound;
inline Sound keyPickupSound;

inline Music music;

void loadSounds();
void updateVolumes();

#endif
