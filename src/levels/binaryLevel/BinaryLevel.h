#ifndef _BINARY_LEVEL_H_
#define _BINARY_LEVEL_H_

#include "../Level.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class BinaryLevel : public Level {
public:
  BinaryLevel(int level);
  ~BinaryLevel();
  const int getNumContainers();
  const int getContainerSize();
  const int getActualLevel();
  const int getNumSwitches();
  void setNumContainers();
  void setContainerSize(int);
  void incrementLevel();
  Vec2 getContainerPos(int);
private:
  int actualLevel;
  int numContainers;
  int containerSize;
};

#endif
