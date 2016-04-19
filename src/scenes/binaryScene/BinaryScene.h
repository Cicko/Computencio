#ifndef __BINARY_SCENE_H__
#define __BINARY_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../../levels/binaryLevel/BinaryLevel.h"

#include <vector>

using namespace std;
using namespace cocos2d::ui;
using namespace cocos2d;

class BinaryScene : public cocos2d::LayerColor {
public:
   static cocos2d::Scene* createScene ();

   virtual bool init ();

   CREATE_FUNC (BinaryScene);
   void activateCollisionEvents ();
   void addContainer (int,int);
   void addContainers ();
   void addMapBounds ();
   void addSwitches ();
   void createCircle (float);
   void createGUIText ();
   void createMap ();
   void initializeAttributes ();
   void onStateChanged (cocos2d::Ref*, CheckBox::EventType);
   bool onContactBegin (cocos2d::PhysicsContact &contact);
   void shakeScreen ();
   void prepareScheduler ();
   void updateBallRespawnInterval ();
private:
    // Objects
    BinaryLevel* binaryLevel;
    vector<CheckBox*> switches_;
    LabelTTF* scoreLabel;
    vector<Sprite* > bases;

    int actualLevel;
    int numSwitches;
    int score;
    int lives;
    float ballRespawnInterval;
    Size visibleSize;
    Point origin;
};

#endif // __START_SCENE_H__
