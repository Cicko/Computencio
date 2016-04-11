#ifndef __BINARY_SCENE_H__
#define __BINARY_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include <vector>

using namespace std;
using namespace cocos2d::ui;
using namespace cocos2d;

class BinaryScene : public cocos2d::LayerColor {
public:
   static cocos2d::Scene* createScene();

   virtual bool init();

   CREATE_FUNC(BinaryScene);
   void createMap();
   void createCircle(float);
   void createSwitches();
   void onStateChanged(cocos2d::Ref* ,CheckBox::EventType);
   void shakeScreen();
   void createGUIText();
   void activateCollisionEvents ();
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
    int rotation;
};

#endif // __START_SCENE_H__
