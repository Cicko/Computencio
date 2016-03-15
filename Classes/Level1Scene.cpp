#include "Level1Scene.h"
#include <iostream>
#include <math.h>
#include "Door.h"
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//  #include "Door.cpp"
//#endif

using namespace std;
using namespace cocos2d::ui;

USING_NS_CC;

Scene* Level1Scene::createScene()
{
    //auto scene = Scene::create();
    auto scene = Scene::createWithPhysics();
    auto layer = Level1Scene::create();

    if (layer == nullptr)
        cerr << "layer is nullptr" << endl;

    scene->addChild(layer);

    return scene;
}



bool Level1Scene::init() {    // R: 187   G: 173  B : 160
  if ( !LayerColor::initWithColor(Color4B(187,173,160,255))) {
    return false;
  }
  visibleSize_ = Director::getInstance()->getVisibleSize();

  createMap();
  createFruit();
  createFruit();
//  createSwitches();

  return true;
}

void Level1Scene::createMap () {


  auto floorSprite = Sprite::create("floor.png");
  floorSprite->setPosition(Vec2(visibleSize_.width / 2, 120));
  floorSprite->setScale(4);
  addChild(floorSprite);

  auto physicsBody = PhysicsBody::createBox(floorSprite->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
  physicsBody->setDynamic(false);

  floorSprite->setPhysicsBody(physicsBody);
}

void Level1Scene::createFruit () {
  // Generate polygon info automatically.
  auto pinfo = AutoPolygon::generatePolygon("apple.png");

  // Create a sprite with polygon info.
  auto sprite = Sprite::create("apple.png");

  sprite->setPosition(Vec2(visibleSize_.width / 2, visibleSize_.height / 2));
  addChild(sprite);

  auto physicsBody = PhysicsBody::createBox(sprite->getContentSize() / 4, PhysicsMaterial(0.0f, 0.0f, 0.0f));
  physicsBody->setDynamic(true);
  sprite->setPhysicsBody(physicsBody);
}

void Level1Scene::createSwitches() {

  const int NUM_SWITCHES = 1;
  for(int i = 0; i < NUM_SWITCHES; i++)
  {
    auto switch1 = CheckBox::create("off_switch.png","on_switch.png");
    switch1->setPosition(Vec2(visibleSize_.width * (i+2)/7, visibleSize_.height /4));
    switch1->setScale(1);
    switch1->addEventListener(CC_CALLBACK_2(Level1Scene::onStateChanged, this));
    switches_.push_back(switch1);
    this->addChild(switch1,0);
  }
}



// This method takes care of closing and opening doors. Not efficient.
void Level1Scene::onStateChanged(cocos2d::Ref* sender, CheckBox::EventType type)
{
  cout << "Id del checkbox" << sender->_ID << endl;
  //cout << "----- Su evento es : " << type << endl;
  unsigned short inx = 0; // index of the door in the doors_ array to open
  int w = 0; // binary index weight

  for(int i = switches_.size()-1;i >= 0;i--)
  {
    if(switches_[i]->isSelected()) // method CheckBox::getSelectedState() is deprecated on Android
      inx += pow(2,w);
    w++;
  }

}
