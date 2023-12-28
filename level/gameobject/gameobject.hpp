#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

class GameObject {
public:
  float x, y, width, height;

  virtual void tick() {};

  GameObject(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {};
};

#endif
