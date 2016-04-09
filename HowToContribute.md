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
