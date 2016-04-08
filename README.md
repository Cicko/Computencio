#Computencio

Computencio is a funny educational game which purpose is to provide a slight idea about
computer abstract layers:

![](layers.jpg)

Each layer is known by different game levels in ascending order of difficulty. 

## Binaries
Soon!

## Development

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
