#ifndef _LEVEL_MENU_H_
#define _LEVEL_MENU_H_

#include "cocos2d.h"
#include <iostream>

using namespace std;

class LevelMenu : public cocos2d::LayerColor {
public:
   static cocos2d::Scene* createLevelMenu();

   virtual bool init();

   CREATE_FUNC(LevelMenu);
};

#endif
