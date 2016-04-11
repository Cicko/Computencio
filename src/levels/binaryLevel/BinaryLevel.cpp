#include "BinaryLevel.h"
#include <cmath>

BinaryLevel::BinaryLevel(int level) {
  actualLevel = level;
  setNumContainers();
}

BinaryLevel::~BinaryLevel() { }

const int BinaryLevel::getNumContainers() {
  return numContainers;
}


void BinaryLevel::setNumContainers () {
  numContainers = pow(2, actualLevel);
}

void BinaryLevel::incrementLevel() {
  actualLevel++;
  setNumContainers();
}
