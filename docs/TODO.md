# CKA_TODO

- Debug / release configurations
    - Different #defs based off configuration
- Debug
    - [ ] Debug UI
    - [ ] Debug rendering
        - [ ] Axis draw
        - [ ] Debug shapes
            - 2D (Triangle, Rect, custom polygons [from set of points])
            - 3D (~~Cube~~, Pyramid, Sphere, Line, Grid)
- [ ] Error handling / reporting
- [ ] Background / skybox rendering 
- GLSL / Shaders
    - [ ] Reduce reliance on sokol-shdc
        - [ ] Implement "clean" glsl shader files
    - [ ] Implement uniform vxcolor.glsl
- Refactoring
    - Clean up graphics initialization / termination
    - Clean up thepit Graphics API (as an interface for sokol)
