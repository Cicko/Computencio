#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Door.h"
#include <vector>

using namespace std;
using namespace cocos2d::ui;

class Level1Scene : public cocos2d::LayerGradient
{
public:
   static cocos2d::Scene* createScene();

   virtual bool init();

   CREATE_FUNC(Level1Scene);
   void createMap();
   void createFruit(float);
   void createSwitches();
   void onStateChanged(cocos2d::Ref* ,CheckBox::EventType);

private:
    vector<ui::CheckBox*>   switches_;
    bool                    on_;
    Size                    visibleSize_;
    unsigned                numApples_;
    Sprite*                    paloSprite_;
};

#endif // __START_SCENE_H__
