#ifndef _SWITCH_SYSTEM_HPP_
#define _SWITCH_SYSTEM_HPP_

#include "cocos2d.h"

USING_NS_CC;

class SwitchSystem : public Node {
private:
  int actualLevel;
public:
  bool init();
  static SwitchSystem* create (int level, Size visibleSize);
  SwitchSystem();
  ~SwitchSystem();
};


#endif
