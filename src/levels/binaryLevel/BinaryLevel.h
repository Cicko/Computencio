#ifndef _BINARY_LEVEL_H_
#define _BINARY_LEVEL_H_

#include "../Level.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;


// Logic class that contains all information about specific binary level
class BinaryLevel : public Level {
public:
  BinaryLevel(int level);
  ~BinaryLevel();
  const int getNumContainers();
  const int getContainerSize();
  const int getActualLevel();
  const int getNumSwitches();
  Size getPlatformSize ();
  void updateNumContainers ();
  void setContainerSize(int size); // Just one value
  void incrementLevel();
  Vec2 getContainerPos(int index);
private:
  int actualLevel;
  int numContainers;
  int containerSize;
  Size platformSize;
  int platformSeparation;
};

#endif
