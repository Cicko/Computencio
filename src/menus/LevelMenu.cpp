#include "LevelMenu.h"
#include "../levels/binaryLevel/BinaryLevel.h"
#include "../levels/assemblyLevel/AssemblyLevel.h"
#include "../levels/opcodeLevel/OpcodeLevel.h"

#include "../scenes/binaryScene/BinaryScene.h"

// SCENE
#define BACKGROUND_COLOR4B Color4B(135, 211, 124, 255)

// TRANSITION
#define TRANSITION_COLOR3B Color3B(255,255,255)
#define TRANSITION_DELAY 1

using namespace std;
using namespace cocos2d::ui;

USING_NS_CC;


Scene* LevelMenu::createLevelMenu() {
    //auto scene = Scene::createWithPhysics();
    auto scene = Scene::create();
    // With this line you can see all physics bodies
    //scene->getPhysicsWorld()->setDebugDrawMask (PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = LevelMenu::create();
    if (layer == nullptr)
        cerr << "layer is nullptr" << endl;
    scene->addChild(layer);
    return scene;
}


bool LevelMenu::init() {
  if ( !LayerColor::initWithColor(BACKGROUND_COLOR4B)) {
    return false;
  }
  auto binary = MenuItemImage::create("binary.png", "binary.png", CC_CALLBACK_1(LevelMenu::binary,this));

  auto *menu = Menu::create(binary, NULL);
  menu->alignItemsVertically();
  addChild(menu);

  return true;
}


void LevelMenu::binary (cocos2d::Ref * sender) {
  auto scene = BinaryScene::createScene();
  auto director = Director::getInstance();
  director->replaceScene(TransitionFade::create(TRANSITION_DELAY, scene, TRANSITION_COLOR3B));
}
