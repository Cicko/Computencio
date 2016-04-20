#include "BinaryLevel.h"
#include <cmath>

#define INITIAL_CONTAINER_SIZE 80
#define INITIAL_PLATFORM_SIZE 65
#define PLATFORM_WIDTH_FACTOR 20

BinaryLevel::BinaryLevel(int level) {
  actualLevel = level;
  platformSize = Vec2(INITIAL_PLATFORM_SIZE, INITIAL_PLATFORM_SIZE / PLATFORM_WIDTH_FACTOR);
  updateNumContainers();
  containerSize = INITIAL_CONTAINER_SIZE;
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
  platformSize = Vec2 (platformSize.width / 2, platformSize.height / 2);
  updateNumContainers ();
  setContainerSize (50 / getActualLevel());
}

Vec2 BinaryLevel::getContainerPos (int index) {

  Size visibleSize = Director::getInstance()->getVisibleSize();
  int xSeparation = visibleSize.width / (getNumContainers() + 1);

/*
  int yPos = visibleSize.height * 1 / 4;
  int xPos = xSeparation * (index + 1) - getContainerSize() / 2;
  return Vec2 (xPos, yPos);
*/

  if (getActualLevel() == 1) {
    int yPos = visibleSize.height * 1 / 4;
    int xPos = xSeparation * (index + 1) - getContainerSize() / 2;
    return Vec2 (xPos, yPos);
  }

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
  return platformSize;
}
