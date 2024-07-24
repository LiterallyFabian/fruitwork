# fruitwork

fruitwork is a simple component-based game engine written in C++ and the SDL2 library.

## Technical Details
### Naming Conventions
fruitwork is using a slightly modified version of the LLDB naming conventions (taken from & modified in [CLion](https://www.jetbrains.com/clion/)). The differences are as follows:
- Camel case is used for global/local variables and parameters.
- Namespace members are indented by 4 spaces.
- Switch cases are always on a new line (`Keep simple cases in one line = false`)

### Building
fruitwork uses Makefiles to build the project, which can be found at its root. The Makefile uses the following project structure:
```
.
├── build/
├── fruitwork/
│   ├── include/
│   ├── resources/
│   ├── src/
│   └── Makefile
└── project/
    ├── include/
    ├── resources/
    └── src/
```

## Acknowledgements

- [SDL2](https://www.libsdl.org/)
- [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
- [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)
- [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)

The scene system is based on [Unity Scenes](https://docs.unity3d.com/Manual/CreatingScenes.html) and [Finite state machines](https://en.wikipedia.org/wiki/Finite-state_machine), the latter explained by [Lazy Foo' Productions](http://lazyfoo.net/articles/article06/index.php). Various StackOverflow answers are attributed in the code.