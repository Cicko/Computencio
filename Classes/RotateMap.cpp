
// PHYSICS BITMASK MANAGER
#define RED_BALL_BITMASK 0x00000A
#define YELLOW_BALL_BITMASK 0x00000B

#define RED_BASE_BITMASK 0x0000AA
#define YELLOW_BASE_BITMASK 0x0000BB


#include "basicIncludes.h"
#include <iostream>
#include "cocos2d.h"
#include "RotateMap.h"

using namespace std;
using namespace cocos2d;


RotateMap* RotateMap::create(int i) {

  RotateMap* rotateMap = new RotateMap();
  if(rotateMap && rotateMap->init()) {

    auto redBase = Sprite::create("redCircleFloor.png");
    auto yellowBase = Sprite::create ("yellowCircleFloor.png");

    auto redBasePhysicsBody = PhysicsBody::createBox(redBase->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
    redBasePhysicsBody->setCollisionBitmask(RED_BASE_BITMASK);
    redBasePhysicsBody->setContactTestBitmask(true);

    auto yellowBasePhysicsBody = PhysicsBody::createBox(yellowBase->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
    yellowBasePhysicsBody->setCollisionBitmask(YELLOW_BASE_BITMASK);
    yellowBasePhysicsBody->setContactTestBitmask(true);

    redBasePhysicsBody->setDynamic (false);
    yellowBasePhysicsBody->setDynamic (false);

    redBase->setPhysicsBody (redBasePhysicsBody);
    yellowBase->setPhysicsBody (yellowBasePhysicsBody);

    redBase->setPosition (Point(0,-100));
    yellowBase->setPosition (Point(0, 100));

    rotateMap->addChild (redBase);
    rotateMap->addChild (yellowBase);

    return rotateMap;
  }
  CC_SAFE_DELETE(rotateMap);
  return NULL;
}

RotateMap::RotateMap() {}
RotateMap::~RotateMap() {}

bool RotateMap::init()
{
  if(!Node::init())
    return false;

  return true;
}
