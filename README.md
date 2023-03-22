# Train Simulation

![C++](https://img.shields.io/badge/C%2B%2B-14-blue)

## Structure

``` text
├── CMakeLists.txt
├── app
│   ├── CMakesLists.txt
│   └── main.cpp
├── cmake
│   └── cmake modules
├── src
│   ├── simulation
        ├── Track.h
        ├── Node.h
        ├── Train.h
        ├── InputHandler.h
        ├── Files.h
        ├── Simulation.h
        ├── Track.cpp
        ├── Train.cpp
        ├── InputHandler.cpp
        ├── Files.cpp
        └── Simulation.cpp
```

Library code goes into [src/](src/), main program code in [app/](app) and tests go in [tests/](tests/).

## Software Requirements

- CMake 3.16+
- GNU Makefile
- Conan or VCPKGG++9 (or higher), Clang++9 (or higher)

## Building

First, clone this repo and do the preliminary work:

```shell
git clone --recursive https://github.com/stevendae/TrainSimulation
make prepare
```

- App Executable

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --target main
cd app
./main
```


