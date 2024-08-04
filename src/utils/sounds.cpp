#include "sounds.hpp"
#include <raylib.h>
#include "needed.hpp"

void loadSounds() {
  deathSound = LoadSound("./res/sounds/death.wav");
  coinPickupSound = LoadSound("./res/sounds/coinpickup.wav");;
  keyPickupSound = LoadSound("./res/sounds/keypickup.wav");;
  
  music = LoadMusicStream("./res/sounds/music.mp3");
}

void updateVolumes() {
  SetMasterVolume(TWHGReloaded::master / 100.0f);
  SetSoundVolume(deathSound, TWHGReloaded::effects / 100.0f);
  SetSoundVolume(keyPickupSound, TWHGReloaded::effects / 100.0f);
  SetSoundVolume(coinPickupSound, TWHGReloaded::effects / 100.0f);
  SetMusicVolume(music, TWHGReloaded::music / 100.0f);
}
