#ifndef _ROTATE_MAP_
#define _ROTATE_MAP_


#include "cocos2d.h"
#include <iostream>
#include <vector>

using namespace std;

USING_NS_CC;


class RotateMap : public cocos2d::Sprite
{
public:

  RotateMap();
  ~RotateMap();
  static RotateMap* createRotateMap();

private:
  vector <cocos2d::Sprite> parts;
};


#endif
