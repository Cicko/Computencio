#ifndef _BINARY_LEVEL_H_
#define _BINARY_LEVEL_H_

#include "../Level.h"
#include "cocos2d.h"

using namespace cocos2d;

class BinaryLevel : public Level {
public:
  BinaryLevel(int level);
  ~BinaryLevel();
  const int getNumContainers();
  void setNumContainers();
  void incrementLevel();
  Vec2 getContainerPos(int);
private:
  int actualLevel;
  int numContainers;
};

#endif
