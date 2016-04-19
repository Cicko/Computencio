#include "SwitchSystem.h"

#define SWITCH_SEPARATION 20   // Separation between switches in pixels

SwitchSystem::SwitchSystem() {}

SwitchSystem* SwitchSystem::create(int numSwitches) {

  SwitchSystem* switchSystem = new SwitchSystem();
  if (switchSystem && switchSystem->init()) {

    Size visibleSize = Director::getInstance()->getVisibleSize();

    for (int i = 0; i < numSwitches; i++) {

      auto aSwitch = CheckBox::create("off_switch.png", "on_switch.png");
      aSwitch->setPosition(Vec2(visibleSize.width * 3 / 4 + SWITCH_SEPARATION * i,
                                visibleSize.height / 4));
      aSwitch->setScale(0.3);
      //aSwitch->addEventListener(CC_CALLBACK_2(SwitchSystem::onStateChanged, this));
      //switches.push_back(aSwitch);
      switchSystem->addChild(aSwitch, 0);;
    }

/*
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
*/
  //  switchSystem->addChild(bottomRect);
  //  switchSystem->addChild(leftRect);
  //  switchSystem->addChild(rightRect);

    return switchSystem;
  }
  CC_SAFE_DELETE(switchSystem);
  return NULL;
}

bool SwitchSystem::init() {
  if(!Node::init())
    return false;

  return true;
}





/*
void SwitchSystem::onStateChanged (cocos2d::Ref* ref, CheckBox::EventType e) {


  //for(int i = switches.size()-1 ; i >= 0; i--) {
  //  if(switches[i]->isSelected()) ; // method CheckBox::getSelectedState() is deprecated on Android
  //}
}
/*
  short rotation = 0;
  if (on_)
    rotation = 180;
  else
    rotation = -360;

rotater = RotateTo::create(ROTATION_INTERVAL, rotation);
rotater->retain();
rotateMap->runAction(rotater);
*/
