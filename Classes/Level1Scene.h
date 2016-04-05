#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "RotateMap.h"
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
   void createCircle(float);
   void createSwitches();
   void onStateChanged(cocos2d::Ref* ,CheckBox::EventType);
   void shakeScreen();
   void createGUIText();
   bool onContactBegin (cocos2d::PhysicsContact &contact);
private:
    int score;
    int lives;
    float ballRespawnInterval;
    LabelTTF* scoreLabel;
    vector<ui::CheckBox*> switches_;
    bool on_;
    Size visibleSize_;
    Point origin_;
    vector<Sprite* > bases;
    RotateMap* rotateMap;
    RotateTo* rotater = NULL;
    int rotation;
};

#endif // __START_SCENE_H__
