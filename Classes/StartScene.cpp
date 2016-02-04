#include "StartScene.h"
#include <iostream>

using namespace std;

USING_NS_CC;

Scene* StartScene::createScene()
{
    auto scene = Scene::create();
    auto layer = StartScene::create();

    if (layer == nullptr)
        cerr << "layer is nullptr" << endl;

    scene->addChild(layer);

    return scene;
}



bool StartScene::init()
{    // R: 187   G: 173  B : 160
    if ( !LayerColor::initWithColor(Color4B(187,173,160,255)) )
    {
        return false;
    }


  cout << "StartScene init" << endl;
  Size visibleSize = Director::getInstance()->getVisibleSize();


  // Constructor de CheckBox puedes mandarle hasta 5 imágenes.
  //auto switch1 = ui::CheckBox::create("closedDoor.png","openDoor.jpg");

  auto door = Door::createDoor();

  door->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
  //door->addTouchEventListener( CC_CALLBACK_0(StartScene::onMouseDown,this ));
  door->setScale(0.5);
  this->addChild(door,0);


  return true;
}


void StartScene::onMouseDown(void)
{
    cout << "Mouse down" << endl;
}
