#include "StartScene.h"
#include <iostream>
#include <math.h>
#include "Door.h"
#include "Door.cpp"

using namespace std;
using namespace cocos2d::ui;

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


  visibleSize_ = Director::getInstance()->getVisibleSize();

  createDoors(4);
  createSwitches();


  return true;
}

void StartScene::createDoors(short num_doors)
{
  num_doors_ = num_doors;
  for(int i = 0;i < num_doors;i++)
  {
    auto door = Door::createDoor();
    door->setPosition(Vec2( (i * 80) + 120, visibleSize_.height/2));
    door->setScale(1);
    doors_.push_back(door);
    this->addChild(door,0);
  }

}

void StartScene::createSwitches()
{
<<<<<<< 1623874047a36c2b0493a950d4d2a3180f43d39a
  int num_switches = log(num_doors_) / log(2);  // Android doesn't have support to log2
=======
  int num_switches = log(num_doors_) / log(2);
>>>>>>> Funcionando para Android.
  for(int i = 0; i < num_switches; i++)
  {
    auto switch1 = CheckBox::create("off_switch.png","on_switch.png");
    switch1->setPosition(Vec2(visibleSize_.width * (i+2)/7, visibleSize_.height /4));
    switch1->setScale(0.6);
    //switch1->addEventListener(CC_CALLBACK_2(StartScene::onStateChanged),this);
    switch1->addEventListener(CC_CALLBACK_2(StartScene::onStateChanged, this));
    switches_.push_back(switch1);
    this->addChild(switch1,0);
  }
}



// This method takes care of closing and opening doors. Not efficient.
void StartScene::onStateChanged(cocos2d::Ref* sender, CheckBox::EventType type)
{
  cout << "Id del checkbox" << sender->_ID << endl;
  //cout << "----- Su evento es : " << type << endl;
  unsigned short inx = 0;
  int w = 0;
  for(int i = switches_.size()-1;i >= 0;i--)
  {
    if(switches_[i]->isSelected()) // method CheckBox::getSelectedState() is deprecated on Android
        inx += pow(2,w);
    w++;
  }

  for(int i = 0;i < doors_.size(); i++)
  {
    if(i == inx)
        doors_[i]->open();
    else
        doors_[i]->close();
  }
}
