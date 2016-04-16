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

Vec2 BinaryLevel::getContainerPos (int index) {
  Size visibleSize = Director::getInstance()->getVisibleSize();
  int yPos = visibleSize.height * 1 / 4;
  int xPos = visibleSize.width * (index) / getNumContainers();
  return Vec2 (xPos, yPos);
}
