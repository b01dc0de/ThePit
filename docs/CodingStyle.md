# CodingStyle

- Enforce spaces
- Unless completely unavoidable, changes should not be breaking to existing supported dev platforms (Windows, Linux, MacOS)
- All header files should begin and end with a header define of the format: 
    - ``
    #ifndef THEPIT_FILENAME_H
    #define THEPIT_FILENAME_H
        // ...
    #endif // THEPIT_FILENAME_H
    ``
- Source Files should be organized as follows:
    - GLSL source and 'sokolified' files (.glsl.h) should be in src/GLSL
    - cpp/h files should be in src/
    - __Subject to change__ once a clear system architecture has taken shape

- Casing:
    - PascalCase
        - Type names
        - Function/Method names
    - snake_case
        - Variables

- Namespace: All engine/game code relating to ThePit should be within thepit namespace

