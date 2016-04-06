#ifdef _BALL_H_
#define _BALL_H_

#include "cocos2d.h"
#include <iostream>

using namespace std;
USING_NS_CC;


class Ball : public Sprite {
private:
  const size;
public:
  bool init();
  static Ball* create (Color3B, int);
  BallContainer();
  ~BallContainer();
};


#endif
