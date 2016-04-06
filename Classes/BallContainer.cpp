#include "basicIncludes.h"
#include "BallContainer.h"

using namespace std;
using namespace cocos2d;


BallContainer* BallContainer::create(Color3B) {

  BallContainer* ballContainer = new BallContainer();
  if (ballContainer && ballContainer->init()) {
    auto rectWithBorder = DrawNode::create();
    Vec2 vertices[] =
    {
      Vec2(0,100),
      Vec2(100,100),
      Vec2(100,0),
      Vec2(0,0)
    };
  rectWithBorder->drawPolygon(vertices, 4, Color4F(1.0f,0.3f,0.3f,1), 3, Color4F(0.2f,0.2f,0.2f,1));
  ballContainer->addChild(rectWithBorder);

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
