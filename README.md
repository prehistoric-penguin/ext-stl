## ext-stl

Encapsulation for STL container, to be cache friendly for small objects

### Build

build for debug:

```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

build for benchmark:

```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
```

Only tested on G++ 4.8, higher version of g++ will be also ok to compile.

### Reference

[EASTL](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2271.html)

[Chromium Base StackContainer](http://code.woboq.org/qt5/qtwebengine/src/3rdparty/chromium/base/containers/)

[CppCon 2014: Chandler Carruth "Efficiency with Algorithms, Performance with Data Structures"](https://www.youtube.com/watch?v=fHNmRkzxHWs)
