#ifndef _ROTATE_MAP_
#define _ROTATE_MAP_


#include "cocos2d.h"
#include <iostream>

using namespace std;

USING_NS_CC;


class RotateMap : public cocos2d::Node
{
public:

  //CREATE_FUNC(RotateMap);
  bool init();
  static RotateMap* create(int value);
  RotateMap();
  ~RotateMap();

};


#endif
