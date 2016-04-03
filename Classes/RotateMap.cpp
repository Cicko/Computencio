

#include "RotateMap.h"
#include <iostream>

using namespace std;
using namespace cocos2d;



RotateMap::RotateMap() {

  auto redBase = Sprite::create("redCircleFloor.png");
  auto yellowBase = Sprite::create("yellowCircleFloor.png");

  auto redBasePhysicsBody = PhysicsBody::createBox(redBase->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
  auto yellowBasePhysicsBody = PhysicsBody::createBox(yellowBase->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));

  redBasePhysicsBody->setDynamic (false);
  yellowBasePhysicsBody->setDynamic (false);

  redBase->setPhysicsBody (redBasePhysicsBody);
  yellowBase->setPhysicsBody (yellowBasePhysicsBody);

  redBase->setPosition (Vec2(0, 0));
  yellowBase->setPosition (Vec2(1, 1));


  addChild (redBase);
  addChild (yellowBase);

}

RotateMap::~RotateMap() {}

RotateMap* RotateMap::createRotateMap()
{
  return NULL;
}
