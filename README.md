# The adapted adapted Vulkan Tutorial

The Adapted Vulkan Toturial shows how to draw an object using the Vulkan API. It is based on the origin Vulkan Tutorial, but has been adapted to include the following features:

* SDL2 instead of GLFW.
* Vulkan Memory Allocator (VMA).
* Volk function loader.
* Imgui.
* Slang instead of GLSL.

Note that this repository is a fork of the adapted Vulkan Tutorial and is additionally adapted to be used on Linux.

All features except Imgui are already part of the Vulkan SDK or contained in this repository, and thus make sense to be used.

## Prerequisites

* [the vulkan SDK](https://vulkan.lunarg.com/doc/view/latest/linux/getting_started_ubuntu.html).

## Build and run
Just build it with CMake and run it from the commandline:
```
cmake -B build
cmake --build build --config Debug
./build/28_model_loading
```
