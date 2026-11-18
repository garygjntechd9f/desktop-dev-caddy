# DevCaddy
A lightweight, extensible C++ desktop toolbox for everyday development tasks, built with CMake and Dear ImGui

## windows-debug build
### 1. build
```
cmake -S . -B "../build-debug" -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="../install-debug"
```
### 2. compile
```
cmake --build "../build-debug" --parallel %NUMBER_OF_PROCESSORS%
``` 
### 3. install
```
cmake --install "../build-debug"
```
### 4. install
```
cd ../build-debug/bin
.\DevCaddy.exe
```