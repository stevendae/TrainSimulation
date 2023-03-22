# Train Simulation

![C++](https://img.shields.io/badge/C%2B%2B-14-blue)

## Structure

``` text
├── CMakeLists.txt
├── app
│   ├── CMakesLists.txt
│   └── main.cc
├── cmake
│   └── cmake modules
├── src
│   ├── CMakesLists.txt
│   ├── my_lib.h
│   └── my_lib.cc
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

- Unit testing

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug --target unit_tests
cd tests
./unit_tests
```


