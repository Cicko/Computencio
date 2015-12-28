#include "GameMenu.h"

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
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("MenuBackground.png");
    background->setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(background,0);

    auto play     = MenuItemFont::create("Jugar", CC_CALLBACK_0(GameMenu::play,this));
    auto settings = MenuItemFont::create("Opciones", CC_CALLBACK_0(GameMenu::settings,this));
    auto quit     = MenuItemFont::create("Salir", CC_CALLBACK_0(GameMenu::quit,this));

    auto *menu = Menu::create(play, settings, quit, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);
    return true;
}

void GameMenu::play(void) {
  CCLOG("PLAY");
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
