
#Computencio

Computencio is a funny educational game which purpose is to provide a slight idea about
computer programming layers:

![](layers.jpg)

Each layer is known by different game levels. Also this game is very extensible thanks to the __open / close__ principle. In the __HowToContribute.md__ file is explained very well how to contribute to this game.


### About this repo


- In the __Classes__ folder are all source codes of this game (cpp and h files).
- Files like __proj.android__ or __proj.linux__ are folders containing basic configuration of its
platform. Also there are __proj.android-studio__ folder so you can use this project easily with Android Studio IDE.
- The __Resources__ folder contain just that, resources such images and fonts.

### How to contribute

First thing you have to do to contribute is to clone this project and create a link to [cocos2d-x library](http://www.cocos2d-x.org/filedown/cocos2d-x-3.10.zip).

```bash
git clone https://github.com/Computencio/computencio.git
cd computencio
ln path-to-cocos-lib cocos2d
```
Now you have to create _platform-build_ folder like __linux-build__, go inside and construct it with cmake (CMakeLists.txt file at root of this repo). Finally execute make to create configuration files for all platforms (this will delay few minutes). In case to have some errors you can visit the [forum](http://discuss.cocos2d-x.org/)

```bash
mkdir linux-build
cd linux-build
cmake ..
make
```

 [cocos2d console ](http://www.cocos2d-x.org/wiki/Cocos2d-console)

```bash
cocos run -p android

cocos run -p linux
```

If you want add new source code files to project ensure that you add the
respective path to following files: *CMakeList.txt* and
*proj.android/jni/Android.mk*
