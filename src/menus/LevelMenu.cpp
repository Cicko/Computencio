#include "LevelMenu.h"
#include "../levels/binaryLevel/BinaryLevel.h"
#include "../levels/assemblyLevel/AssemblyLevel.h"
#include "../levels/opcodeLevel/OpcodeLevel.h"



using namespace std;
using namespace cocos2d::ui;

USING_NS_CC;


Scene* LevelMenu::createLevelMenu() {
    auto scene = Scene::createWithPhysics();
    // With this line you can see all physics bodies
    //scene->getPhysicsWorld()->setDebugDrawMask (PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = LevelMenu::create();
    if (layer == nullptr)
        cerr << "layer is nullptr" << endl;
    scene->addChild(layer);
    return scene;
}


bool LevelMenu::init() {    // R: 187   G: 173  B : 160 Alpha

}
