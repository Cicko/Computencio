#ifndef __DOOR_CPP_
#define __DOOR_CPP_

#include "Door.h"
#include <iostream>

using namespace std;
using namespace cocos2d;



Door::Door() {}

Door::~Door() {}

Door* Door::createDoor()
{
  Door* door = new Door();

  if(door->initWithFile("closedDoor.png"))
  {
    door->_openedTex = new cocos2d::Texture2D;
    door->_closedTex = new cocos2d::Texture2D;
    door->_aduTex = new cocos2d::Texture2D;

    Image * openImage = new Image;
    Image * closedImage = new Image;
    Image * aduImage = new Image;

    if(!openImage->initWithImageFile("openDoor.png")) return NULL;
    if(!closedImage->initWithImageFile("closedDoor.png")) return NULL;
    if(!aduImage->initWithImageFile("adu.png")) return NULL;

    bool ok = door->_openedTex->initWithImage(openImage);
    ok &= door->_closedTex->initWithImage(closedImage);
    ok &= door->_aduTex->initWithImage(aduImage);

    if(!ok) return NULL;

    door->autorelease();

    door->_isOpened = false;
    door->setTexture(door->_closedTex);

    cout << "Todo bien" << endl;
    return door;
  }
  else{
    cout << "No se pudo crear" << endl;
    CC_SAFE_DELETE(door);
    return NULL;
  }

}

void Door::switchState()
{
  if(_isOpened)
  {
    _isOpened = false;
    setTexture(_closedTex);
  }
  else
  {
    _isOpened = true;
    setTexture(_openedTex);
  }
}

void Door::open()
{
  _isOpened = true;
  setTexture(_openedTex);
}

void Door::close()
{
  _isOpened = false;
  setTexture(_closedTex);
}

void Door::adu()
{
  setTexture(_aduTex);
}

Size Door::getSize()
{
  return _openedTex->getContentSize();
}


#endif
