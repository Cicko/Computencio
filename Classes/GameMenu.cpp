#include "GameMenu.h"
#include "StartScene.h"
#include <iostream>

using namespace std;

USING_NS_CC;

Scene* GameMenu::createScene()
{
    auto scene = Scene::create();

    auto layer = GameMenu::create();

    scene->addChild(layer);

    return scene;
}

bool GameMenu::init()
{

    cout << "GameMenu init" << endl;
    if ( !LayerColor::initWithColor(Color4B(234,89,58,255)) )
    {
        return false;
    }

    // setFontName es un método estático por lo tanto desde que establezcamos un tipo de fuente
    // todos los objetos menuItemFont que vayamos creando se dibujaran con esa fuente.
    MenuItemFont::setFontName("fonts/Amatic-Bold.ttf");
    auto play     = MenuItemFont::create("Comenzar", CC_CALLBACK_0(GameMenu::play,this));


    MenuItemFont::setFontName("fonts/AmaticSC-Regular.ttf");
    auto settings = MenuItemFont::create("Opciones", CC_CALLBACK_0(GameMenu::settings,this));
    auto quit     = MenuItemFont::create("Salir", CC_CALLBACK_0(GameMenu::quit,this));





    auto *menu = Menu::create(play, settings, quit, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);



    return true;
}

void GameMenu::play(void) {
  CCLOG("PLAY");
  cout << "Play yeah" << endl;

  auto scene = StartScene::createScene();
  auto director = Director::getInstance();

  director->replaceScene(TransitionFade::create(2, scene, Color3B(255,255,255)));

}

void GameMenu::settings(void) {
  CCLOG("SETTINGS");
}

void GameMenu::quit(void) {
  CCLOG("QUIT");
}

void GameMenu::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
