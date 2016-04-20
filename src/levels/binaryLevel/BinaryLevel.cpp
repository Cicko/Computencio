#include "BinaryLevel.h"
#include <cmath>


BinaryLevel::BinaryLevel(int level) {
  actualLevel = level;
  updateNumContainers();
  containerSize = 50;
}

BinaryLevel::~BinaryLevel() { }

const int BinaryLevel::getNumContainers() {
  return numContainers;
}

void BinaryLevel::updateNumContainers () {
  numContainers = pow(2, actualLevel);
}

void BinaryLevel::incrementLevel() {
  actualLevel++;
  updateNumContainers ();
  setContainerSize (50 / getActualLevel());
}

Vec2 BinaryLevel::getContainerPos (int index) {

  Size visibleSize = Director::getInstance()->getVisibleSize();
  int xSeparation = visibleSize.width / (getNumContainers() + 1);
  int yPos = visibleSize.height * 1 / 4;
  int xPos = xSeparation * (index + 1) - getContainerSize() / 2;
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

Size BinaryLevel::getPlatformSize() {

}
