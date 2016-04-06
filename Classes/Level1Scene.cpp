#include "Level1Scene.h"
#include "Door.h"
#include "RotateMap.h"
#include "Utils.h"


/// BALL MANAGER
#define BALL_RESPAWN_INTERVAL 2
#define BALL_RESPAWN_ACCELERATION 0.1   // Increment speed per invocation

#define NUM_DIFF_CIRCLES 2
#define ROTATION_INTERVAL 0.2f

// PHYSICS BITMASK MANAGER
#define RED_BALL_BITMASK 0x00000A
#define YELLOW_BALL_BITMASK 0x00000B

#define RED_BASE_BITMASK 0x0000AA
#define YELLOW_BASE_BITMASK 0x0000BB

// COLOR MANAGER
#define BACKGROUND_COLOR4B Color4B(135, 211, 124, 255)
#define BACKGROUND_COLOR3B Color3B(135, 211, 124)  // SHOULD BE EQUAL to BACKGROUND_COLOR4B
#define SHAKE_COLOR3B Color3B(207,0,15)

// SCREEN MANAGER
#define SHAKE_SCREEN_DURATION 0.3f
#define SHAKE_SCREEN_SPEED 2.0f


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


bool Level1Scene::init() {    // R: 187   G: 173  B : 160 Alpha
  if ( !LayerColor::initWithColor(BACKGROUND_COLOR4B)) {
    return false;
  }

  ballRespawnInterval = BALL_RESPAWN_INTERVAL;

  visibleSize_ = Director::getInstance()->getVisibleSize();
  origin_ = Director::getInstance()->getVisibleOrigin();

  auto edgeBody = PhysicsBody::createEdgeBox (visibleSize_, PhysicsMaterial(0.1f,0.5f,0.5f), 3);
  auto edgeNode = Node::create();

  edgeNode->setPosition(Point(visibleSize_.width / 2 + origin_.x, visibleSize_.height / 2 + origin_.y));
  edgeNode->setPhysicsBody(edgeBody);
  this->addChild(edgeNode);
  createMap();
  createSwitches();
  schedule(schedule_selector(Level1Scene::createCircle), ballRespawnInterval);
  createGUIText();

  return true;
}


void Level1Scene::createGUIText() {

  score = 0;
  lives = 3;
  scoreLabel = CCLabelTTF::create(intToString(score), "Helvetica", 24,
                                      CCSizeMake(245, 32), kCCTextAlignmentCenter);

  scoreLabel->setPosition(Vec2(visibleSize_.width * 0.8, visibleSize_.height * 0.9));
  addChild(scoreLabel);

}

void Level1Scene::createMap() {
  int xMiddle = visibleSize_.width / 2;
  int yMiddle = visibleSize_.height / 2;

  rotateMap = RotateMap::create(1);
/*
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

  rotateMap->setPosition (Point(xMiddle, yMiddle * 1.5));

  rotateMap->addChild (redBase);
  rotateMap->addChild (yellowBase);
*/

  rotateMap->setPosition (Point(xMiddle, yMiddle * 1.5));


  addChild(rotateMap);

  // Drawing part
  //auto drawNode = DrawNode::create();

//  Color4F color(0.5, 0.5, 0.5, 1);
//  drawNode->drawSegment(Vec2(0- redBase->getContentSize().width / 2, 100), Vec2(0 - redBase->getContentSize().width / 2, -100), 1, color);

//  drawNode->setAnchorPoint(Vec2(0,0));

  //rotateMap->addChild(drawNode);

  // Detect Collision manager
  auto contactListener = EventListenerPhysicsContact::create();
  contactListener->onContactBegin = CC_CALLBACK_1(Level1Scene::onContactBegin, this);
  Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}


bool Level1Scene::onContactBegin(cocos2d::PhysicsContact &contact) {
  PhysicsBody *a = contact.getShapeA()->getBody();
  PhysicsBody *b = contact.getShapeB()->getBody();

  auto aMask = a->getCollisionBitmask();
  auto bMask = b->getCollisionBitmask();

  // check if th e bodies have collided
  if ((RED_BALL_BITMASK == aMask && RED_BASE_BITMASK == bMask) ||
      (RED_BALL_BITMASK == bMask && RED_BASE_BITMASK == aMask)) {
        score++;
    if (aMask == RED_BALL_BITMASK)
      this->removeChild(a->getOwner());
    else
      this->removeChild(b->getOwner());
  }
  else if ((YELLOW_BALL_BITMASK == aMask && YELLOW_BASE_BITMASK == bMask) ||
        (YELLOW_BALL_BITMASK == bMask && YELLOW_BASE_BITMASK == aMask)) {
          score++;
    if (aMask == YELLOW_BALL_BITMASK)
      this->removeChild(a->getOwner());
    else
      this->removeChild(b->getOwner());
  }
  else {
    lives--;
    cout << "MAL" << endl;
    shakeScreen();
    if (aMask == YELLOW_BALL_BITMASK || aMask == RED_BALL_BITMASK)
      this->removeChild(a->getOwner());
    else if(bMask == YELLOW_BALL_BITMASK || bMask == RED_BALL_BITMASK)
      this->removeChild(b->getOwner());
  }
  scoreLabel->setString("Score " + intToString(score));
  return true;
}

// El parámetro es obligatorio para que funcione el schedule_selector
void Level1Scene::createCircle (float dt) {
  srand(time(0));
  int randomval = rand() % NUM_DIFF_CIRCLES;
  ballRespawnInterval -= 0.3;
  Sprite* sprite;
  int mask;

  switch (randomval) {
    case 0:
      sprite = Sprite::create("redCircle.png");
      mask = RED_BALL_BITMASK;
      break;
    case 1:
      sprite = Sprite::create("yellowCircle.png");
      mask = YELLOW_BALL_BITMASK;
      break;
  }

  sprite->setPosition(Vec2(visibleSize_.width / 2, visibleSize_.height / 1.2));
  auto physicsBody = PhysicsBody::createCircle (sprite->getBoundingBox().size.height / 2, PhysicsMaterial(0.01f, 0.0f, 1.0f));
  physicsBody->setDynamic(true);
  physicsBody->setCollisionBitmask(mask);
  physicsBody->setContactTestBitmask(true);
  sprite->setPhysicsBody(physicsBody);

  this->addChild(sprite);
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
    short rotation = 0;
    if (on_)
      rotation = 180;
    else
      rotation = -360;

    rotater = RotateTo::create(ROTATION_INTERVAL, rotation);
    rotater->retain();
    rotateMap->runAction(rotater);
}





void Level1Scene::shakeScreen() {

//experiment more with these four values to get a rough or smooth effect!
    float interval = 0.f;
    float duration = SHAKE_SCREEN_DURATION;
    float speed = SHAKE_SCREEN_SPEED;
    float magnitude = 1.0f;

    static float elapsed = 0.f;

    this->schedule([=](float dt) {
        float randomStart = random(-1000.0f, 1000.0f);
        elapsed += dt;

        float percentComplete = elapsed / duration;

// We want to reduce the shake from full power to 0 starting half way through
        float damper = 1.0f - clampf(2.0f * percentComplete - 1.0f, 0.0f, 1.0f);

// Calculate the noise parameter starting randomly and going as fast as speed allows
        float alpha = randomStart + speed * percentComplete;
        // map noise to [-1, 1]
        float x = noise(alpha, 0.0f) * 2.0f - 1.0f;
        float y = noise(0.0f, alpha) * 2.0f - 1.0f;

        x *= magnitude * damper;
        y *= magnitude * damper;
        this->setPosition(x, y);
        cout << "(" << x << ", " << y << ")" << endl;

        this->setColor(SHAKE_COLOR3B);


        if (elapsed >= duration)
        {
            elapsed = 0;
            this->unschedule("Shake");
            this->setPosition(Vec2::ZERO);
            this->setColor(BACKGROUND_COLOR3B);
        }

    }, interval, CC_REPEAT_FOREVER, 0.f, "Shake");  // CC_REPEAT_FOREVER es MAX_UINT
}
