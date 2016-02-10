#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Door.h"
#include <vector>

using namespace std;
using namespace cocos2d::ui;

class StartScene : public cocos2d::LayerColor
{
public:
   static cocos2d::Scene* createScene();

   virtual bool init();

   CREATE_FUNC(StartScene);
   void createDoors(short);
   void createSwitches();
   void onStateChanged(cocos2d::Ref* ,CheckBox::EventType);

private:
    vector<Door*>           doors_;
    vector<ui::CheckBox*>   switches_;
    Size                    visibleSize_;
    unsigned short          num_doors_;  // Don't delete unsigned
    float                   doorScale_;
    unsigned short          openedDoor_;
};

#endif // __START_SCENE_H__
