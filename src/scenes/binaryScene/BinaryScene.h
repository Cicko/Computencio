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
   void addContainer (int x, int y);  // it positionate a new container at given position
   void addContainers ();             // this method will positionate containers automatically
   void addMapBounds ();
   void addSwitches ();
   void addPlatforms ();
   void createBall (float);
   void createGUIText ();
   const int getActualLevel ();
   void initializeAttributes ();
   void onStateChanged (cocos2d::Ref*, CheckBox::EventType);
   bool onContactBegin (cocos2d::PhysicsContact &contact);
   void shakeScreen ();
   void prepareScheduler ();
   void rotatePlatforms(int index, bool right);
   void updateBallRespawnInterval (int);
private:
    // Objects
    BinaryLevel* binaryLevel;
    vector<CheckBox*> switches;
    LabelTTF* scoreLabel;
    vector<Sprite* > platforms;

    int actualLevel;
    int numSwitches;
    int score;
    int lives;
    float ballRespawnInterval;
    Size visibleSize;
    Point origin;
};

#endif // __START_SCENE_H__
