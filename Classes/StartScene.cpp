#include "StartScene.h"
#include <iostream>
#include <cmath>

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
  int num_switches = log(num_doors_) / log(2);  // Android doesn't have support to log2
  for(int i = 0; i < num_switches; i++)
  {
    auto switch1 = ui::CheckBox::create("off_switch.png","on_switch.png");
    switch1->setPosition(Vec2(visibleSize_.width * (i+2)/7, visibleSize_.height /4));
    switch1->setScale(0.6);
    switch1->addEventListener(CC_CALLBACK_0(StartScene::onStateChanged,this));
    switches_.push_back(switch1);
    this->addChild(switch1,0);
  }
}




void StartScene::onStateChanged()
{
  unsigned short inx = 0;
  int w = 0;
  for(int i = switches_.size()-1;i >= 0;i--)
  {
    if(switches_[i]->getSelectedState())
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
