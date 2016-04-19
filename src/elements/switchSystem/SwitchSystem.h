#ifndef _SWITCH_SYSTEM_HPP_
#define _SWITCH_SYSTEM_HPP_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <vector>

using namespace std;
using namespace cocos2d::ui;
using namespace cocos2d;

USING_NS_CC;

class SwitchSystem : public Node {
public:
  static vector<vector <Sprite*> > platforms; // Rotative platforms directed by the switches.
  static vector<CheckBox*> switches;
  SwitchSystem();
  bool init();
  static SwitchSystem* create (int numSwitches);
  void onStateChanged (cocos2d::Ref*, CheckBox::EventType);
};


#endif
