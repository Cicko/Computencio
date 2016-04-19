#ifndef _BALL_H_
#define _BALL_H_

#include "cocos2d.h"
#include <iostream>

using namespace std;
USING_NS_CC;


class Ball : public Sprite {
public:
  Ball();
  ~Ball();
  static Ball* create (Color3B, int mask);
};

#endif
