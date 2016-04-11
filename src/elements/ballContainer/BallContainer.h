#ifndef _BALL_CONTAINER_
#define _BALL_CONTAINER_


#include "cocos2d.h"
#include <iostream>

USING_NS_CC;

class BallContainer : public Node {
public:
  bool init();
  static BallContainer* create (Color3B, int, int);
  BallContainer();
  ~BallContainer();
};





#endif
