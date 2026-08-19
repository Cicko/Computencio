# How to Contribute

if you don't have worked collaboratively with multiple projects I think this writing can be very useful for you, even if you have done it it will help you to understand faster how this game is coded.

This first thing to know about this game it was appeared thinking on extensibility so most probably you almost don't have to touch any source code. Let see it with more details.

## Adding new code

Before anything you should have cloned this project. If you have not, see [README.md](README.md) the paragraph __How To Contribute --> Cloning__.

###### How to publicize your contribution

When you have finished your new functionality or fixed some bug you should make a [pull request](https://help.github.com/articles/using-pull-requests/) and wait until your request is accepted.


##### Adding new levels

If you have any idea of any new type of levels that can show how some part of computer or computational algorithm works. This section will explain you what steps you should make to perform this task comfortably

#### 1. Make a subclass of [Level.h](Classes/Levels/Level.h)

For example:

```c++
class MyCustomLevel : public Level {
private:
  int actualDifficulty;
  int anyAttribute;
public:
  MyCustomLevel(int difficulty);
  void incrementDifficulty();
  void anyMethodThatYouWantToHave(int anyParameter);
};
```

This class should be only logical. Should only have information like number of balls, size of containers, etc.. The class that draw all things on screen should be a custom __scene class__ so when you create new type of levels you MUST create a respective scene class.

#### 2. Make a subclass of [Scene.h](Classes/Scenes/Scene.h)

For example:

```c++
class MyCustomScene : public Scene {
private:
  int anySceneAttribute;
public:
  MyCustomScene(MyCustomLevel level);
  void anySceneMethodThatYouWantToUse(int param);
};
```

#### 3. Making know the new scene

Once you have created your custom scene class with respective custom levels you must indicate to the game the presence of that new scene so you just have to go to the [LevelMenu.h](LevelMenu.h) and push back the new scene in the constructor:

For example:

```c++
scenes.push_back(MyCustomScene::createScene());
```

where `scenes` is a container of the scenes available in the level menu. If your menu is built with buttons instead of a list, create a new button and a new callback function as `LevelMenu::binary` does:

```c++
void LevelMenu::myCustom(cocos2d::Ref* sender) {
  auto scene = MyCustomScene::createScene();
  auto director = Director::getInstance();
  director->replaceScene(TransitionFade::create(TRANSITION_DELAY, scene, TRANSITION_COLOR3B));
}
```

#### 4. Add your new files to the build system

As explained in [README.md](README.md), every new source file must be added to:

- __CMakeLists.txt__
- __proj.android/jni/Android.mk__

#### 5. Add all required resources

If your new level needs images, fonts or sounds, put them in the __Resources__ folder and reference them by their file names inside your scene class.

##### Adding new functionalities

Adding a new functionality (a new game element, a new interaction, a new UI component, etc.) follows the same open/close principle:

1. Create a new class in the most appropriate folder (`src/elements`, `src/menus`, `src/scenes`, ...). Preferably create a header/source pair following the existing naming pattern, e.g. `src/elements/myElement/MyElement.h` and `MyElement.cpp`.
2. Keep the class as small and self-contained as possible. If it needs physics, sprites or GUI, inherit from the appropriate cocos2d-x base class (`Node`, `Sprite`, `LayerColor`, ...).
3. Add the new scene or menu that uses the functionality, and register it in [LevelMenu](src/menus/LevelMenu.cpp) / [GameMenu](src/menus/GameMenu.cpp) as described in the previous section.
4. Add the new files to the build system (`CMakeLists.txt`, `proj.android/jni/Android.mk`).
5. Add all required resources to the __Resources__ folder.
6. Make sure the new functionality compiles on every platform you support and that it does not break existing levels. Then open a [pull request](https://help.github.com/articles/using-pull-requests/).
