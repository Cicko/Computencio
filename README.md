
#Computencio

Computencio is a funny educational game which purpose is to provide a slight idea about
computer programming layers:

![](layers.jpg)

Each layer is known by different game levels.


### About this repo

#### Folders

- In the __Classes__ folder are all source codes of this game (cpp and h files).
- Files like __proj.android__ or __proj.linux__ are folders containing basic configuration of its
platform. Also there are __proj.android-studio__ folder so you can use this project easily with Android Studio IDE. Moreover you can
-

Basic configuration to develop in it:

```bash
git clone https://github.com/Computencio/computencio.git
cd computencio
ln path-to-cocos-lib cocos2d
```

To build the project, you need use `cocos2d` command, to get more documentation
about it [[http://www.cocos2d-x.org/wiki/Cocos2d-console]]

```bash
cocos run -p android

cocos run -p linux
```

If you want add new source code files to project ensure that you add the
respective path to following files: *CMakeList.txt* and
*proj.android/jni/Android.mk*
