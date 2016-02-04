#ifndef __DOOR_H__
#define __DOOR_H__

#include "cocos2d.h"
#include <iostream>

using namespace std;

USING_NS_CC;


class Door : public cocos2d::Sprite
{
public:

  Door();
  ~Door();
  static Door* createDoor();


  void SwitchState();

  void Close();
  void Open();

  bool IsOpened();

  cocos2d::Texture2D * _openedTex;
  cocos2d::Texture2D * _closedTex;

  bool _isOpened;

};


#endif
