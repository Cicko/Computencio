#include "BinaryScene.h"
#include "../../elements/ballContainer/BallContainer.h"
#include "../../elements/ball/Ball.h"
#include "../../utils/Utils.h"

// Switchs
#define SWITCH_SEPARATION 40

// PLATFORMS
#define PLATFORM_COLOR Color3B (0, 0, 0)
#define Y_PLATFORMS_OFFSET 150
#define PLATFORM_CENTER_FACTOR 6

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


/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "Door.cpp"
#endif
*/

using namespace std;
using namespace cocos2d::ui;

USING_NS_CC;

Scene* BinaryScene::createScene() {
    auto scene = Scene::createWithPhysics();
    // With this line you can see all physics bodies contours
    //scene->getPhysicsWorld()->setDebugDrawMask (PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = BinaryScene::create();
    if (layer == nullptr)
        cerr << "layer is nullptr" << endl;
    scene->addChild(layer);
    return scene;
}


bool BinaryScene::init() {
  if ( !LayerColor::initWithColor(BACKGROUND_COLOR4B)) {
    return false;
  }

  initializeAttributes ();
  addMapBounds ();
  addSwitches ();
  addPlatforms ();
  addContainers ();
  createGUIText ();
  prepareScheduler ();  // Scheduler will invoke createBall() every ballRespawnInterval in seconds.

  return true;
}

void BinaryScene::initializeAttributes () {
  ballRespawnInterval = BALL_RESPAWN_INTERVAL;
  actualLevel = 1;
  score = 0;
  lives = 3;

  binaryLevel = new BinaryLevel();
  incrementLevel();

  visibleSize = Director::getInstance()->getVisibleSize();
  origin = Director::getInstance()->getVisibleOrigin();
}

void BinaryScene::addContainers () {
  for (int i = 0; i < binaryLevel->getNumContainers(); i++) {
    Vec2 position = binaryLevel->getContainerPos (i);
    addContainer (position.x, position.y);
  }
}

void BinaryScene::prepareScheduler () {
  schedule(schedule_selector(BinaryScene::createBall), ballRespawnInterval);
}

void BinaryScene::incrementLevel () {
  binaryLevel->incrementLevel();
  actualLevel++;
}

void BinaryScene::addMapBounds () {
    auto edgeBody = PhysicsBody::createEdgeBox (visibleSize, PhysicsMaterial(0.1f,0.5f,0.5f), 3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    addChild(edgeNode);
}

void BinaryScene::addContainer (int x, int y) {
  BallContainer * ballContainer = BallContainer::create(CONTAINERS_COLOR3B, binaryLevel->getContainerSize(), RED_BALL_BITMASK);
  ballContainer->setPosition(x, y);
  addChild(ballContainer);
}


void BinaryScene::createGUIText() {
  scoreLabel = LabelTTF::create(intToString(score),
                                "Helvetica", 24,
                                CCSizeMake(245, 32), kCCTextAlignmentCenter);
  scoreLabel->setPosition(Vec2(visibleSize.width * 0.8, visibleSize.height * 0.9));
  addChild(scoreLabel);
}

void BinaryScene::addSwitches() {

  for (int i = 0; i < binaryLevel->getNumSwitches(); i++) {
    auto aSwitch = CheckBox::create("off_switch.png", "on_switch.png");

    aSwitch->setPosition(Vec2(visibleSize.width * 1 / 4 + SWITCH_SEPARATION * i,
                              visibleSize.height / 5));
    aSwitch->setScale(0.3);
    aSwitch->addEventListener(CC_CALLBACK_2(BinaryScene::onStateChanged, this));
    switches.push_back(aSwitch);
    addChild(aSwitch, 0);
  }
}

void BinaryScene::addPlatforms () {
  Size platformSize = binaryLevel->getPlatformSize();
  int yPlatformSeparation = binaryLevel->getNumContainers() * 2;
  int numFloors = getActualLevel();

  for (int i = 0; i < numFloors; i++) {
    for (int j = 0; j < pow(2,i); j++) {
      auto platform = Sprite::create();

      int xPlatformSeparation = visibleSize.width / pow(2, i+1);

      platform->setTextureRect(Rect(0, 0, platformSize.width, platformSize.height));
      platform->setColor(PLATFORM_COLOR);

      // Create Physics Bodies
      auto platformPhysicsBody = PhysicsBody::createBox (platform->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));

      platformPhysicsBody->setDynamic (false);
      platform->setPhysicsBody (platformPhysicsBody);
      platform->setAnchorPoint (Vec2(0.5, 0.5));

      //int xPos = (visibleSize.width) * (j*2+1) / pow(2,i+1) + 3;
      int index;
      if (i == 0)
        index = binaryLevel->getNumContainers() / 2;
      //else if (i == 1) index = (binaryLevel->getNumContainers() / 4) * (j*2+1);
      //else if (i == 2) index = (binaryLevel->getNumContainers() / 8) * (j*2+1);
      else
        index = (binaryLevel->getNumContainers() / pow(2,i+1)) * (j*2+1);

      int xContainerPos = binaryLevel->getContainerPos(index).x;
      int xContainerSize = binaryLevel->getContainerSize();

      int xPos = xContainerPos - binaryLevel->getContainerSeparation() / PLATFORM_CENTER_FACTOR;
      int yPos = visibleSize.height * numFloors * (numFloors - i + 1) / yPlatformSeparation;

      cout << "XPOS : " << xPos << " , YPOS = " << yPos << endl;

      platform->setPosition (Vec2(xPos, yPos));


      platforms.push_back(platform);

      addChild (platform);
    }
  }
}


void BinaryScene::activateCollisionEvents () {
    // Detect Collision manager
    auto contactListener = EventListenerPhysicsContact::create ();
    contactListener->onContactBegin = CC_CALLBACK_1 (BinaryScene::onContactBegin, this);
    Director::getInstance ()->getEventDispatcher ()->addEventListenerWithSceneGraphPriority(contactListener, this);
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
void BinaryScene::createBall (float dt) {

  srand(time(0));
  int randomval = rand() % binaryLevel->getNumContainers() + 1;

  Ball * ball = Ball::create(BALL_COLOR3B, randomval);
  ball->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.2));

  addChild(ball);
}



void BinaryScene::onStateChanged(cocos2d::Ref* sender, CheckBox::EventType type) {


  cout << "YEAH" << endl;
  for(int i = switches.size()-1 ; i >= 0; i--) {
    if(switches[i]->isSelected())         // method CheckBox::getSelectedState() is deprecated on Android
      rotatePlatforms(i, false);
    else
      rotatePlatforms(i, true);

  }

}

void BinaryScene::rotatePlatforms(int index, bool right) {
      int firstPlatformIndex = pow (2, index) - 1;
      int numPlatforms = pow (2, index);

      int rotation;
      if (right)
        rotation = 45;
      else
        rotation = -45;

      for (int i = 0; i < numPlatforms; i++) {
        auto rotater = RotateTo::create(ROTATION_INTERVAL, rotation);
        platforms.at(firstPlatformIndex + i)->runAction(rotater);
      }
}


/// This method will update the ball respawn interval in function on ballRespawnInterval
/// attribute value
void BinaryScene::updateBallRespawnInterval (int value) {
  ballRespawnInterval = value;
  unschedule (schedule_selector(BinaryScene::createBall));
  schedule (schedule_selector(BinaryScene::createBall), ballRespawnInterval);
}

const int BinaryScene::getActualLevel () {
  return actualLevel;
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
