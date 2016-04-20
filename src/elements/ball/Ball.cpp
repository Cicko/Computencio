#include "Ball.h"
#include <string>
#include <cstdlib>

using namespace std;

#define BALL_SIZE 0.5
#define BALL_MATERIAL  PhysicsMaterial(0.1f,0.3f,0.5f)

Ball::Ball() {}
Ball::~Ball() {}

Ball* Ball::create(Color3B color, int mask) {
  Ball* ball = new Ball();
  if (ball && ball->initWithFile("redCircle.png")) {
    ball->setColor (color);
    ball->setScale (BALL_SIZE);

    auto ballPhysics = PhysicsBody::createCircle(ball->getContentSize().height / 2, BALL_MATERIAL);
    ballPhysics->setCollisionBitmask(mask);
    ballPhysics->setContactTestBitmask(true);
    ballPhysics->setDynamic(true);
    ball->setPhysicsBody(ballPhysics);

    string maskString(static_cast<ostringstream*>( &(ostringstream() << mask) )->str());

    LabelTTF * scoreLabel = LabelTTF::create (maskString,
                  "Helvetica", 24, CCSizeMake(245, 32), kCCTextAlignmentCenter);

    //ball->setAnchorPoint(Vec2(0.5, 0.5));
    scoreLabel->setAnchorPoint(Vec2(0.5, 0.5));
    ball->addChild(scoreLabel);

    return ball;
  }
  CC_SAFE_DELETE(ball);
  return NULL;
}
