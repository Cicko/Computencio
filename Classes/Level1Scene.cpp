#include "Level1Scene.h"
#include "Door.h"
#include "RotateMap.h"


#define BALL_RESPAWN_INTERVAL 1
#define NUM_DIFF_CIRCLES 2
#define ROTATION_INTERVAL 0.2f
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
//    scene->getPhysicsWorld()->setDebugDrawMask (PhysicsWorld::DEBUGDRAW_ALL);

    auto layer = Level1Scene::create();

    if (layer == nullptr)
        cerr << "layer is nullptr" << endl;

    scene->addChild(layer);

    return scene;
}



bool Level1Scene::init() {    // R: 187   G: 173  B : 160
  if ( !LayerColor::initWithColor(Color4B(234,89,58,255))) {
    return false;
  }

  visibleSize_ = Director::getInstance()->getVisibleSize();
  origin_ = Director::getInstance()->getVisibleOrigin();

  auto edgeBody = PhysicsBody::createEdgeBox (visibleSize_, PhysicsMaterial(0.1f,0.5f,0.5f), 3);
  auto edgeNode = Node::create();

  edgeNode->setPosition(Point(visibleSize_.width / 2 + origin_.x, visibleSize_.height / 2 + origin_.y));
  edgeNode->setPhysicsBody(edgeBody);
  this->addChild(edgeNode);
  createMap();
  createSwitches();
  schedule(schedule_selector(Level1Scene::createCircle), BALL_RESPAWN_INTERVAL );

  return true;
}

/*
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
*/

void Level1Scene::createMap() {
  int xMiddle = visibleSize_.width / 2;
  int yMiddle = visibleSize_.height / 2;

  rotateMap = new Node();

  auto redBase = Sprite::create("redCircleFloor.png");
  auto yellowBase = Sprite::create ("yellowCircleFloor.png");

  auto redBasePhysicsBody = PhysicsBody::createBox(redBase->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
  auto yellowBasePhysicsBody = PhysicsBody::createBox(yellowBase->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));

  redBasePhysicsBody->setDynamic (false);
  yellowBasePhysicsBody->setDynamic (false);

  redBase->setPhysicsBody (redBasePhysicsBody);
  yellowBase->setPhysicsBody (yellowBasePhysicsBody);

  redBase->setPosition (Point(0,-100));
  yellowBase->setPosition (Point(0, 100));

  rotateMap->setPosition (Point(xMiddle, yMiddle * 1.5));

  rotateMap->addChild (redBase);
  rotateMap->addChild (yellowBase);

  addChild(rotateMap);
}

// El parámetro es obligatorio para que funcione el schedule_selector
void Level1Scene::createCircle (float dt) {

//  auto rotateTo = RotateTo::create(1.0f, 40.0f);
  //rotateMap->runAction(rotateTo);


  srand(time(0));
  int randomval = rand() % NUM_DIFF_CIRCLES;

  Sprite* sprite;

  switch (randomval) {
    case 0:
      sprite = Sprite::create("redCircle.png");
      break;
    case 1:
      sprite = Sprite::create("yellowCircle.png");
      break;
  }


  sprite->setPosition(Vec2(visibleSize_.width / 2, visibleSize_.height / 1.5));
  addChild(sprite);

  auto physicsBody = PhysicsBody::createCircle (sprite->getBoundingBox().size.height / 2, PhysicsMaterial(0.01f, 0.0f, 1.0f));
  physicsBody->setDynamic(true);
  sprite->setPhysicsBody(physicsBody);
}

void Level1Scene::createSwitches() {
    auto switch1 = CheckBox::create("off_switch.png","on_switch.png");
    switch1->setPosition(Vec2(visibleSize_.width / 4, visibleSize_.height / 4));
    switch1->setScale(0.3);
    rotation = 0;
    switch1->addEventListener(CC_CALLBACK_2(Level1Scene::onStateChanged, this));
    switches_.push_back(switch1);
    this->addChild(switch1,0);
}



void Level1Scene::onStateChanged(cocos2d::Ref* sender, CheckBox::EventType type) {
    on_ = !on_;

    //if(rotater == NULL || rotater->isDone()) {
        if (on_)
          rotater = RotateTo::create(ROTATION_INTERVAL, 180);
        else
          rotater = RotateTo::create(ROTATION_INTERVAL, -360);

        rotater->retain();
        rotateMap->runAction(rotater);
    //}
}
