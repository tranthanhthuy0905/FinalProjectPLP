# FinalProjectPLP

## Prerequisites:

- C++ version: 17
- g++ version: 13.0.0

## How to check C++ version:

1. Create a .cpp file with content as below:

`````#include<iostream>

int main() {
    if (__cplusplus == 201703L)
        std::cout << "C++17" << endl;
    else if (__cplusplus == 201402L)
        std::cout << "C++14" << endl;
    else if (__cplusplus == 201103L)
        std::cout << "C++11" << endl;
    else if (__cplusplus == 199711L)
        std::cout << "C++98" << endl;
    else
        std::cout << "pre-standard C++" << endl;
}````
2. Compile and run the file then you will see your c++ version (*e.g: c++98, c++17*)

# How to set up Raylib

1. Download file "Source code (zip)" from [here](https://github.com/raysan5/raylib/releases/tag/4.0.0) then unzip it
2. Open terminal running on folder "src" inside the folder downloaded. Then type command `make`. Now we have file 'librarylib.a' in "src" folder

# How to run

* Automatically

* Manually
1. ```cd Template-4.0.0/src```
2. ```clang++ src/*.cpp -Ilib/ -o "bin/build_osx" -std=c++17 -Llib/ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a```
3. ```make build_osx``` (You now see a build_osx file in "bin" folder)
4. Run the main.cpp file
`````
