# FinalProjectPLP

## Prerequisites:

- __Compiler__: c++/g++
- C++ version: 17
- g++ version: 13.0.0

## Knowledge Summary:
- **_header files_** - pre-existing and user-defined header files
- _#define_ - declare an identifier with token string (constant/enum val) substituted whenever identifier forms a token: ```#define CONSTVAR 3```
- __vector__ - dynamic arrays with changeable size, continuous storage (accessed and traversed by _iterator_), several built-in features (iterator, capacity, element accesss)
- _pair_ - ```pair(dataType1, dataType2) Pair_name``` - store 2 variables into 1
- *pass_by_pointer* - point to the first element of the array
- __Static scoping__ - definition of variables is searched in its containing block and outer containing block

### How to check C++ version:

1. Create a .cpp file with content as below:

```
#include<iostream>

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
}
```

<br/>2. Compile and run the file then you will see your c++ version (_e.g: c++98, c++17_)

## How to set up Raylib

1. Download file "Source code (zip)" from [here](https://github.com/raysan5/raylib/releases/tag/4.0.0) then unzip it
2. Open terminal running on folder "src" inside the folder downloaded. Then type command `make`. Now we have file 'librarylib.a' in "src" folder

## How to run

### _Automatically_
I expect to run the _makefile_ file only to auto-generate the build_osx file and run the window. However, it does not run as expectation. Please not feel inconvenient to run my project manually.

### _Manually_

1. `cd Template-4.0.0/src`
2. `clang++ src/*.cpp -Ilib/ -o "bin/build_osx" -std=c++17 -Llib/ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a`
3. `make build_osx` (You now see a build_osx file in "bin" folder)
4. Run the main.cpp file
