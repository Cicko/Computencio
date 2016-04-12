#ifndef _SWITCH_H_
#define _SWITCH_H_

#include "cocos2d.h"

USING_NS_CC;


class Switch : public Checkbox {
  int id;
public:
  Switch();
  ~Switch();
  static Switch* create (int);
  
};


#endif
