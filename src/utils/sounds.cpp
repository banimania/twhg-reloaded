#include "sounds.hpp"

void loadSounds() {
  deathSound = LoadSound("./res/sounds/death.wav");
  coinPickupSound = LoadSound("./res/sounds/coinpickup.wav");;
  keyPickupSound = LoadSound("./res/sounds/keypickup.wav");;
}
