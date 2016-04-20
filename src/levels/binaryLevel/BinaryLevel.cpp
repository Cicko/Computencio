#include "BinaryLevel.h"
#include <cmath>

#define INITIAL_CONTAINER_SIZE 80
#define INITIAL_PLATFORM_SIZE 80
#define PLATFORM_WIDTH_FACTOR 10

BinaryLevel::BinaryLevel() {
  actualLevel = 1;
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
  containerSeparation = Director::getInstance()->getVisibleSize().width / (numContainers + 1);
}

void BinaryLevel::incrementLevel() {
  actualLevel++;
  platformSize = Vec2 (platformSize.width / 1.3, platformSize.height / 1.5);
  updateNumContainers ();
  setContainerSize (INITIAL_CONTAINER_SIZE / getActualLevel());
}

Vec2 BinaryLevel::getContainerPos (int index) {

  Size visibleSize = Director::getInstance()->getVisibleSize();

  int yPos = visibleSize.height * 1 / 4;
  int xPos = containerSeparation * (index + 1) - getContainerSize() / 2;

  return Vec2 (xPos, yPos);

}

int BinaryLevel::getContainerSeparation() {
  return containerSeparation;
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
