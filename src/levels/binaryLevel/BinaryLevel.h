#ifndef _BINARY_LEVEL_H_
#define _BINARY_LEVEL_H_

#include "../Level.h"

class BinaryLevel : public Level {
public:
  BinaryLevel(int level);
  ~BinaryLevel();
  const int getNumContainers();
  void setNumContainers();
  void incrementLevel();
private:
  int actualLevel;
  int numContainers;
};

#endif
