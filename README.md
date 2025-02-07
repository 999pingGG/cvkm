# cvkm
Yet another (WIP) header-only math library for C. Just like cglm means "C GL math", cvkm means "C Vulkan math".
I hope it will be useful for graphics and physics programming. Documentation coming soon.

## Requirements
A C11 compiler, since the library makes heavy use of `_Generic` to simplify code and kind of achieve function
overloading. The tests are trivial to compile, but I'm using CMake here.

## Installation
This library is all-inline so far, just grab `cvkm.h` and you're good to go.

## Testing
Do a standard CMake build to build the tests.

## Motivation
Because cglm doesn't support doubles and I thought it would be cool to use generics in C!

## Roadmap
- [Flecs](https://www.flecs.dev/flecs/) components.
- SIMD, anyone?
