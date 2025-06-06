The Adapted Vulkan Toturial shows how to draw an object using the Vulkan API. It is based on the origin Vulkan Tutorial, but has been adapted to include the following features:

* SDL2 instead of GLFW.
* Vulkan Memory Allocator (VMA).
* Volk function loader.
* Imgui.
* Slang instead of GLSL.

For Windows and MacOS, all features except Imgui are already part of the Vulkan SDK, and thus make sense to be used.
For Linux, SDL2 and glm have to be installed in addition to the Vulkan SDK.

On Windows compile using MSVC and the compile.cmd file, or use CMake from VS Code or run (using MSVC generator)
```
cmake -B build
cmake --build build --config Debug
build\Debug\28_model_loading.exe
```

On Linux compile using CMake:
```
cmake -B build
cmake --build build --config Debug
./build/28_model_loading
```
Note: Use GCC instead of Clang.

You need two prerequisites:

* The Vulkan SDK needs to be installed, and the environment variable VULKAN_SDK needs to point to it.
* You need to clone the IMGUI repo (https://github.com/ocornut/imgui) into some directory. In the file *compile.cmd* or *CMakeLists.txt*, set the IMGUI variable to this directory. 
* When using CMake, Imgui is automatically fetched from the Git repo (usually to build/_deps/imgui-src), no need to clone it.

Only the CPP files are needed, no need to compile it.

