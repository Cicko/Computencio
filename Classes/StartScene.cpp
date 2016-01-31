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
{
    if ( !Layer::init() )
    {
        cout << "Fallo en el Layer.init" << endl;
        return false;
    }


  cout << "StartScene init" << endl;
  Size visibleSize = Director::getInstance()->getVisibleSize();


  auto background = Sprite::create("Yo.jpg");
  background->setPosition(visibleSize.width/2, visibleSize.height/2);
  this->addChild(background,0);

  return true;
}
