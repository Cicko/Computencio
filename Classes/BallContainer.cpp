#include "basicIncludes.h"
#include "BallContainer.h"

using namespace std;
using namespace cocos2d;

#define LINE_WIDTH 3

BallContainer* BallContainer::create(Color3B color, int size, int physicsMask) {

  BallContainer* ballContainer = new BallContainer();
  if (ballContainer && ballContainer->init()) {
    auto bottomRect = Sprite::create();
    auto leftRect = Sprite::create();
    auto rightRect = Sprite::create();

    bottomRect->setTextureRect(Rect(0, 0, size , LINE_WIDTH));
    leftRect->setTextureRect(Rect(0, 0, LINE_WIDTH, size));
    rightRect->setTextureRect(Rect(0, 0, LINE_WIDTH, size));

    bottomRect->setColor(color);
    leftRect->setColor(color);
    rightRect->setColor(color);

    // Create Physics Bodies
    auto bottomRectPhysicsBody = PhysicsBody::createBox(bottomRect->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
    auto leftRectPhysicsBody = PhysicsBody::createBox(leftRect->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
    auto rightRectPhysicsBody = PhysicsBody::createBox(rightRect->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));

    bottomRectPhysicsBody->setCollisionBitmask(physicsMask);
    leftRectPhysicsBody->setCollisionBitmask(physicsMask);
    rightRectPhysicsBody->setCollisionBitmask(physicsMask);

    bottomRectPhysicsBody->setContactTestBitmask(true);
    leftRectPhysicsBody->setContactTestBitmask(true);
    rightRectPhysicsBody->setContactTestBitmask(true);

    bottomRectPhysicsBody->setDynamic (false);
    leftRectPhysicsBody->setDynamic (false);
    rightRectPhysicsBody->setDynamic (false);

    bottomRect->setPhysicsBody(bottomRectPhysicsBody);
    leftRect->setPhysicsBody(leftRectPhysicsBody);
    rightRect->setPhysicsBody(rightRectPhysicsBody);

    bottomRect->setAnchorPoint(Vec2(0, 0));
    leftRect->setAnchorPoint(Vec2(0, 0));
    rightRect->setAnchorPoint(Vec2(0, 0));

    bottomRect->setPosition(Vec2(0, 0));
    leftRect->setPosition(Vec2(0, 0));
    rightRect->setPosition(Vec2(size, 0));

    ballContainer->addChild(bottomRect);
    ballContainer->addChild(leftRect);
    ballContainer->addChild(rightRect);

    return ballContainer;
  }
  CC_SAFE_DELETE(ballContainer);
  return NULL;
}

BallContainer::BallContainer()  {}
BallContainer::~BallContainer() {}

bool BallContainer::init() {
  if(!Node::init())
    return false;

  return true;
}
