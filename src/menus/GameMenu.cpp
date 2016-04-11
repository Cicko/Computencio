#include "GameMenu.h"
#include "../scenes/binaryScene/BinaryScene.h"
#include <iostream>

using namespace std;

// SCENE
#define BACKGROUND_COLOR4B Color4B(135, 211, 124, 255)

// MENU ITEMS FONT
#define MENU_ITEMS_FONT_COLOR Color3B(30, 130, 76)
#define MENU_ITEM_FONT_SIZE 50

// TRANSITION
#define TRANSITION_COLOR3B Color3B(255,255,255)
#define TRANSITION_DELAY 1

USING_NS_CC;

Scene* GameMenu::createScene() {
    auto scene = Scene::create();
    auto layer = GameMenu::create();
    scene->addChild(layer);
    return scene;
}

bool GameMenu::init() {
    cout << "GameMenu init" << endl;
    if (!LayerColor::initWithColor(BACKGROUND_COLOR4B)) {
        return false;
    }

    // setFontName es un método estático por lo tanto desde que establezcamos un tipo de fuente
    // todos los objetos menuItemFont que vayamos creando se dibujaran con esa fuente.
    //    MenuItemFont::setFontName("fonts/AmaticSC-Regular.ttf");
    MenuItemFont::setFontName("fonts/Amatic-Bold.ttf");
    MenuItemFont::setFontSize(MENU_ITEM_FONT_SIZE);

    auto play    = MenuItemFont::create("Comenzar", CC_CALLBACK_0(GameMenu::play,this));
    auto settings = MenuItemFont::create("Opciones", CC_CALLBACK_0(GameMenu::settings,this));
    auto quit     = MenuItemFont::create("Salir", CC_CALLBACK_0(GameMenu::quit,this));

    play->setColor(MENU_ITEMS_FONT_COLOR);
    settings->setColor(MENU_ITEMS_FONT_COLOR);
    quit->setColor(MENU_ITEMS_FONT_COLOR);

    auto *menu = Menu::create(play, settings, quit, NULL);
    menu->alignItemsVertically();
    addChild(menu);

    return true;
}

void GameMenu::play(void) {
  CCLOG("PLAY");

  auto scene = BinaryScene::createScene();
  auto director = Director::getInstance();

  director->replaceScene(TransitionFade::create(TRANSITION_DELAY, scene, TRANSITION_COLOR3B));
}

void GameMenu::settings(void) {
  CCLOG("SETTINGS");
}

void GameMenu::quit(void) {
  CCLOG("QUIT");
}

void GameMenu::menuCloseCallback(Ref* pSender) {
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
