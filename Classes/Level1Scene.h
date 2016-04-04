#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Door.h"
#include <vector>

using namespace std;
using namespace cocos2d::ui;

class Level1Scene : public cocos2d::LayerColor
{
public:
   static cocos2d::Scene* createScene();

   virtual bool init();

   CREATE_FUNC(Level1Scene);
   void createMap();
   void createCircle(float);
   void createSwitches();
   void onStateChanged(cocos2d::Ref* ,CheckBox::EventType);

   void createGUIText();
   bool onContactBegin (cocos2d::PhysicsContact &contact);
private:
    int                     score;
    string                  scoreString;
    CCLabelTTF*             scoreLabel;
    vector<ui::CheckBox*>   switches_;
    bool                    on_;
    Size                    visibleSize_;
    Point                   origin_;
    vector<Sprite* >        bases;
    Node*                 rotateMap;
    RotateTo*             rotater = NULL;
    int rotation;
};

#endif // __START_SCENE_H__
