#include "basicIncludes.h"
#include "Ball.h"

using namespace std;

#define BALL_SIZE 0.5

Ball::Ball() {}
Ball::~Ball() {}

Ball* Ball::create(Color3B color, int mask) {
  Ball* ball = new Ball();
  if (ball && ball->initWithFile("redCircle.png")) {
    ball->setColor(color);

    ball->setScale (BALL_SIZE);
    ball->setPosition(0, 0);
    return ball;
  }
  CC_SAFE_DELETE(ball);
  return NULL;
}
