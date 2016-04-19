#include "BinaryLevel.h"
#include <cmath>


BinaryLevel::BinaryLevel(int level) {
  actualLevel = level;
  setNumContainers();
  containerSize = 50;
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
  setNumContainers ();
  setContainerSize (50 / getActualLevel());
}

Vec2 BinaryLevel::getContainerPos (int index) {
  Size visibleSize = Director::getInstance()->getVisibleSize();
  int yPos = visibleSize.height * 1 / 4;
  int xPos = visibleSize.width * (index) * 2 / (getNumContainers() * 3) + visibleSize.width / 6;
  return Vec2 (xPos, yPos);
}

const int BinaryLevel::getContainerSize () {
  return containerSize;
}

void BinaryLevel::setContainerSize(int newSize) {
  containerSize = newSize;
}

const int BinaryLevel::getActualLevel () {
  return actualLevel;
}

const int BinaryLevel::getNumSwitches () {
  return actualLevel;
}
