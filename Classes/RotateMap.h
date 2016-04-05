#ifndef _ROTATE_MAP_
#define _ROTATE_MAP_


#include "cocos2d.h"
#include <iostream>
#include <vector>

using namespace std;

USING_NS_CC;

class RotateMap : public cocos2d::Node
{
public:

  bool init();
  static RotateMap* create(int value);
  RotateMap();
  ~RotateMap();
};


#endif
