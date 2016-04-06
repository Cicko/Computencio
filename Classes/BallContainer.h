#ifndef _BALL_CONTAINER_
#define _BALL_CONTAINER_


#include "cocos2d.h"
#include <iostream>

using namespace std;

USING_NS_CC;

class BallContainer : public Node {
public:
  bool init();
  static BallContainer* create (Color3B);
  BallContainer();
  ~BallContainer();
};





#endif
