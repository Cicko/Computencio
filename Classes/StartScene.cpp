#include "StartScene.h"
#include <iostream>
#include <math.h>
#include "Door.h"
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//  #include "Door.cpp"
//#endif

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
  if ( !LayerColor::initWithColor(Color4B(187,173,160,255))) {
    return false;
  }
  visibleSize_ = Director::getInstance()->getVisibleSize();

  createDoors(4);
  createSwitches();

  return true;

}

void StartScene::createDoors(short num_doors)
{
  doorScale_ = 1.5;
  num_doors_ = num_doors;

  auto pos = visibleSize_.width / num_doors; // space for each door
  auto alpha = visibleSize_.width / (num_doors*2); // Space between left limit and first door


  for(int i = 0;i < num_doors;i++)
  {
    auto door = Door::createDoor();

    door->setPosition(alpha + pos*i, visibleSize_.height/2);
    door->setScale(doorScale_);
    doors_.push_back(door);
    this->addChild(door,0);
  }

  doors_[0]->open();
  openedDoor_ = 0;
  cout << "Door size : " << doors_[0]->getSize().width * doorScale_ << " , " << doors_[0]->getSize().height * doorScale_ << endl;

}

void StartScene::createSwitches()
{

  int num_switches = log(num_doors_) / log(2);  // Android doesn't have support to log2
  for(int i = 0; i < num_switches; i++)
  {
    auto switch1 = CheckBox::create("off_switch.png","on_switch.png");
    switch1->setPosition(Vec2(visibleSize_.width * (i+2)/7, visibleSize_.height /4));
    switch1->setScale(1);
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
  unsigned short inx = 0; // index of the door in the doors_ array to open
  int w = 0; // binary index weight

  for(int i = switches_.size()-1;i >= 0;i--)
  {
    if(switches_[i]->isSelected()) // method CheckBox::getSelectedState() is deprecated on Android
      inx += pow(2,w);
    w++;
  }

  doors_[openedDoor_]->close();
  doors_[inx]->open();
  openedDoor_ = inx;

}
