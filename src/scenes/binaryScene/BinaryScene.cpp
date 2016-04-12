#include "BinaryScene.h"
#include "../../elements/ballContainer/BallContainer.h"
#include "../../elements/ball/Ball.h"
#include "../../utils/Utils.h"
#include "../../levels/binaryLevel/BinaryLevel.h"


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
#define SHAKE_COLOR3B Color3B(145, 211, 124)

#define CONTAINERS_COLOR3B Color3B(108, 122, 137)
#define BALL_COLOR3B Color3B(30, 130, 76)

// SCREEN MANAGER
#define SHAKE_SCREEN_DURATION 0.3f
#define SHAKE_SCREEN_SPEED 2.0f


//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//  #include "Door.cpp"
//#endif

using namespace std;
using namespace cocos2d::ui;

USING_NS_CC;


Scene* BinaryScene::createScene() {
    auto scene = Scene::createWithPhysics();
    // With this line you can see all physics bodies
    //scene->getPhysicsWorld()->setDebugDrawMask (PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = BinaryScene::create();
    if (layer == nullptr)
        cerr << "layer is nullptr" << endl;
    scene->addChild(layer);
    return scene;
}


bool BinaryScene::init() {    // R: 187   G: 173  B : 160 Alpha


  if ( !LayerColor::initWithColor(BACKGROUND_COLOR4B)) {
    return false;
  }

  ballRespawnInterval = BALL_RESPAWN_INTERVAL;

  visibleSize = Director::getInstance()->getVisibleSize();
  origin_ = Director::getInstance()->getVisibleOrigin();

  auto edgeBody = PhysicsBody::createEdgeBox (visibleSize, PhysicsMaterial(0.1f,0.5f,0.5f), 3);
  auto edgeNode = Node::create();
  edgeNode->setPosition(Point(visibleSize.width / 2 + origin_.x, visibleSize.height / 2 + origin_.y));
  edgeNode->setPhysicsBody(edgeBody);
  this->addChild(edgeNode);

  //createMap();
  createSwitches();
  schedule(schedule_selector(BinaryScene::createCircle), ballRespawnInterval);
  createGUIText();

  BallContainer * ballContainer = BallContainer::create(CONTAINERS_COLOR3B, 30, RED_BALL_BITMASK);

  ballContainer->setPosition(visibleSize.width / 2 - 50, 100);
  addChild(ballContainer);

  BinaryLevel* binaryLevel = new BinaryLevel(4);

  cout << binaryLevel->getNumContainers() << " is the number of containers" << endl;


  return true;
}


void BinaryScene::createGUIText() {

  score = 0;
  lives = 3;
  scoreLabel = LabelTTF::create(intToString(score), "Helvetica", 24,
                                      CCSizeMake(245, 32), kCCTextAlignmentCenter);

  scoreLabel->setPosition(Vec2(visibleSize.width * 0.8, visibleSize.height * 0.9));
  addChild(scoreLabel);

}

void BinaryScene::createMap() {
  int xMiddle = visibleSize.width / 2;
  int yMiddle = visibleSize.height / 2;


}

void BinaryScene::activateCollisionEvents () {

    // Detect Collision manager
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(BinaryScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}


bool BinaryScene::onContactBegin(cocos2d::PhysicsContact &contact) {
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
void BinaryScene::createCircle (float dt) {


  /**  VIEJO
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
  **/

  Ball * ball = Ball::create(BALL_COLOR3B, 1);
  ball->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.2));

  addChild(ball);
}

void BinaryScene::createSwitches() {
    auto switch1 = CheckBox::create("off_switch.png", "on_switch.png");
    switch1->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 4));
    switch1->setScale(0.3);
    rotation = 0;
    switch1->addEventListener(CC_CALLBACK_2(BinaryScene::onStateChanged, this));
    switches_.push_back(switch1);
    addChild(switch1,0);
}


void BinaryScene::onStateChanged(cocos2d::Ref* sender, CheckBox::EventType type) {
    on_ = !on_;
}

void BinaryScene::shakeScreen() {
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


        if (elapsed >= duration) {
            elapsed = 0;
            this->unschedule("Shake");
            this->setPosition(Vec2::ZERO);
            this->setColor(BACKGROUND_COLOR3B);
        }

    }, interval, CC_REPEAT_FOREVER, 0.f, "Shake");  // CC_REPEAT_FOREVER es MAX_UINT
}
