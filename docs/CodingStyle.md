# CodingStyle

## General Project

- Unless _completely_ unavoidable, changes should not be breaking to existing supported dev platforms (Windows, Linux, MacOS)

- Source Files should be organized as follows:
    - GLSL source and 'sokolified' files (*.glsl.h) should be in src/GLSL
    - cpp/h files should be in src/
    - __Subject to change__ once a clear system architecture has taken shape

## C++ Style

- Namespace: All engine code relating to ThePit should be within `namespace thepit {}`

- Enforce spaces, not tabs

- All header files should begin and end with a header define of the format: 
    - ``
    #ifndef THEPIT_FILENAME_H
    #define THEPIT_FILENAME_H
        // ...
    #endif // THEPIT_FILENAME_H
    ``
- Header includes
    - Prefer `#include "OtherFile.h"` in `Example.cpp` over `Example.h` when possible
    - If symbol declarations in `Example.h` need type definitions from `OtherFile.h`, then include header file there
    - Include external library and standard library files with angle brackets `#include <LibFile.h>`

- Casing:
    - PascalCase
        - Source file names: `ExampleFile.cpp` `ExampleFile.h`
        - Type names: `struct ExampleType`
        - Function/Method names: `void ExampleType::DoTheThing()`
    - snake_case
        - Variables: `int example_var1, example_var2`


