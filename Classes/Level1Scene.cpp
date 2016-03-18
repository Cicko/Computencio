#include "Level1Scene.h"
#include <iostream>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include "Door.h"
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//  #include "Door.cpp"
//#endif

using namespace std;
using namespace cocos2d::ui;

USING_NS_CC;

Scene* Level1Scene::createScene()
{

    auto scene = Scene::createWithPhysics();

    // With this line you can see all physics bodies
    //scene->getPhysicsWorld()->setDebugDrawMask (PhysicsWorld::DEBUGDRAW_ALL);

    auto layer = Level1Scene::create();

    if (layer == nullptr)
        cerr << "layer is nullptr" << endl;

    scene->addChild(layer);

    return scene;
}



bool Level1Scene::init() {    // R: 187   G: 173  B : 160
  if ( !LayerGradient::initWithColor(Color4B(0,150,255,255), Color4B(255,255,255,255))) {
    return false;
  }
  visibleSize_ = Director::getInstance()->getVisibleSize();
  origin_ = Director::getInstance()->getVisibleOrigin();
  auto edgeBody = PhysicsBody::createEdgeBox (visibleSize_, PhysicsMaterial(0.1f,0.5f,0.5f), 3);

  auto edgeNode = Node::create();
  edgeNode->setPosition(Point(visibleSize_.width / 2 + origin_.x, visibleSize_.height / 2 + origin_.y));
  edgeNode->setPhysicsBody(edgeBody);
  this->addChild(edgeNode);
  numApples_ = 0;
  createMap();
  createSwitches();
  schedule(schedule_selector(Level1Scene::createCircle), 0.2 );
  return true;
}

void Level1Scene::createMap () {

  auto floorSprite = Sprite::create("floor.png");
  int numFloors = visibleSize_.width / floorSprite->getBoundingBox().size.width;
  int separation = visibleSize_.width / numFloors;

  for (int i = 0; i <= numFloors; i++) {
      auto physicsBody = PhysicsBody::createBox(floorSprite->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
      physicsBody->setDynamic(false);
      auto floorSprite = Sprite::create("floor.png");
      floorSprite->setScale(3);
      floorSprite->setAnchorPoint(Vec2(0,0));
      floorSprite->setPosition(Vec2(separation * i , 0));
      floorSprite->setPhysicsBody(physicsBody);
      addChild(floorSprite);
  }

  paloSprite_ = Sprite::create("palo.png");
  auto physicsBody = PhysicsBody::createBox(paloSprite_->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
  physicsBody->setDynamic(false);
  paloSprite_->setPosition(Vec2(visibleSize_.width / 2, visibleSize_.height / 2));
  paloSprite_->setPhysicsBody(physicsBody);
  paloSprite_->setRotation(45);
  on_ = false;

  addChild(paloSprite_);

}

// El parámetro es obligatorio para que funcione el schedule_selector
void Level1Scene::createCircle (float dt) {
  // Generate polygon info automatically.
  numApples_++;
  cout << numApples_ << endl;
//  auto pinfo = AutoPolygon::generatePolygon("apple.png");

  // Create a sprite with polygon info.
  srand(time(0));
  int randomval = rand() % 5;

  Sprite* sprite;

  switch (randomval) {
    case 0:
      sprite = Sprite::create("greenCircle.png");
      break;
    case 1:
      sprite = Sprite::create("blueCircle.png");
      break;
    case 2:
      sprite = Sprite::create("redCircle.png");
      break;
    case 3:
      sprite = Sprite::create("yellowCircle.png");
      break;
    case 4:
      sprite = Sprite::create("brownCircle.png");
    default:
      sprite = Sprite::create("purpleCircle.png");
  }


  sprite->setPosition(Vec2(visibleSize_.width / 2, visibleSize_.height / 1.5));
  addChild(sprite);

  auto physicsBody = PhysicsBody::createCircle(sprite->getBoundingBox().size.height / 2, PhysicsMaterial(0.01f, 0.0f, 1.0f));
  physicsBody->setDynamic(true);
  sprite->setPhysicsBody(physicsBody);
}

void Level1Scene::createSwitches() {
    auto switch1 = CheckBox::create("off_switch.png","on_switch.png");
    switch1->setPosition(Vec2(visibleSize_.width / 4, visibleSize_.height / 4));
    switch1->setScale(1);
    switch1->addEventListener(CC_CALLBACK_2(Level1Scene::onStateChanged, this));
    switches_.push_back(switch1);
    this->addChild(switch1,0);
}




// This method takes care of closing and opening doors. Not efficient.
void Level1Scene::onStateChanged(cocos2d::Ref* sender, CheckBox::EventType type) {
  on_ = !on_;
  cout << on_ << endl;
  if (on_)
    paloSprite_->setRotation(-45);
  else
    paloSprite_->setRotation(45);
}
