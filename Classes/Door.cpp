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

    Image * openImage = new Image;
    Image * closedImage = new Image;
    cout << "Todo bien 1" << endl;
    if(!openImage->initWithImageFile("openDoor.png")) return NULL;
    if(!closedImage->initWithImageFile("closedDoor.png")) return NULL;
    cout << "Todo bien 2" << endl;
    bool ok = door->_openedTex->initWithImage(openImage);
    ok &= door->_closedTex->initWithImage(closedImage);

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
