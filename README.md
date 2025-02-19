# cvkm
Yet another (WIP) header-only math library for C. Just like cglm means "C GL math", cvkm means "C Vulkan math". The
functions are generic, meaning that you can use a single function which can operate on several different types! I hope
it will be useful for graphics and physics programming. Compiles absolutely warning-free.

## Requirements
A C11 compiler, since the library makes heavy use of `_Generic` to simplify code and kind of achieve function
overloading. The tests are trivial to compile, but I'm using CMake here.

## Installation
This library is all-inline so far, just grab `cvkm.h` and you're good to go.

## Available types

| Type         | Description                      |
|--------------|----------------------------------|
| `vkm_bvec2`  | 2-component vector of `int8_t`   |
| `vkm_ubvec2` | 2-component vector of `uint8_t`  |
| `vkm_svec2`  | 2-component vector of `int16_t`  |
| `vkm_usvec2` | 2-component vector of `uint16_t` |
| `vkm_ivec2`  | 2-component vector of `int32_t`  |
| `vkm_uvec2`  | 2-component vector of `uint32_t` |
| `vkm_lvec2`  | 2-component vector of `int64_t`  |
| `vkm_ulvec2` | 2-component vector of `uint64_t` |
| `vkm_vec2`   | 2-component vector of `float`    |
| `vkm_dvec2`  | 2-component vector of `double`   |
| `vkm_bvec3`  | 3-component vector of `int8_t`   |
| `vkm_ubvec3` | 3-component vector of `uint8_t`  |
| `vkm_svec3`  | 3-component vector of `int16_t`  |
| `vkm_usvec3` | 3-component vector of `uint16_t` |
| `vkm_ivec3`  | 3-component vector of `int32_t`  |
| `vkm_uvec3`  | 3-component vector of `uint32_t` |
| `vkm_lvec3`  | 3-component vector of `int64_t`  |
| `vkm_ulvec3` | 3-component vector of `uint64_t` |
| `vkm_vec3`   | 3-component vector of `float`    |
| `vkm_dvec3`  | 3-component vector of `double`   |

## Available functions
All of those are generic! Use them with any types that are valid for the operation. All parameters are pointers to
vectors and/or scalars, the `const` ones are inputs while the non-const ones are input/outputs, except when the name is
`result`; then it's only written, not read.

| Function                | Description                                                                                                              | Formula(e)                                       |
|-------------------------|--------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------|
| `vkm_add(a, b, result)` | Addition.                                                                                                                | $\vec{a} + \vec{b}$                              |
| `vkm_sub(a, b, result)` | Subtraction.                                                                                                             | $\vec{a} - \vec{b}$                              |
| `vkm_mul(a, b, result)` | Multiplication. For a pair of vectors, it's the component-wise multiplication.                                           | $\vec{a} \bullet \vec{b}$<br>$\vec{v}x$          |
| `vkm_div(a, b, result)` | Multiplication. For a pair of vectors, it's the component-wise division.                                                 | $\vec{a} \oslash \vec{b}$<br>$\frac{\vec{v}}{x}$ |
| `vkm_sqrt(x)`           | Square root of a scalar.                                                                                                 | $\sqrt{x}$                                       |
| `vkm_dot(a, b)`         | Scalar product AKA dot product.                                                                                          | $\vec{a} \cdot \vec{b}$                          |
| `vkm_cross(a, b)`       | Vector product AKA cross product.                                                                                        | $\vec{a} \times \vec{b}$                         |
| `vkm_sqr_magnitude(v)`  | Squared magnitude of a vector. Avoids a potentially expensive square root to save performance when it's fine to do this. | $\|\vec{v}\|^2$                                  |
| `vkm_magnitude(v)`      | Magnitude of a vector.                                                                                                   | $\|\vec{v}\|$                                    |
| `vkm_normalize(v)`      | Normalizes the given vector.                                                                                             | $\frac{\vec{v}}{\|\vec{v}\|}$                    |
| `vkm_clear(v)`          | Set all of the vector's components to 0.                                                                                 | $\vec{0}$                                        |
| `vkm_invert(v)`         | Negate all of a vector's components.                                                                                     | $-\vec{a}$                                       |
| `vkm_eq(a, b)`          | Returns `true` when all of the corresponding components of the vectors are equal.                                        | $\vec{a} = \vec{b}$                              |
| `vkm_lt(a, b)`          | Returns `true` when all of the corresponding first vector's components are less than the second's.                       | $\vec{a} < \vec{b}$                              |
| `vkm_gt(a, b)`          | Returns `true` when all of the corresponding first vector's components are greater than the second's.                    | $\vec{a} > \vec{b}$                              |
| `vkm_le(a, b)`          | Returns `true` when all of the corresponding first vector's components are less than or equal to the second's.           | $\vec{a} \leq \vec{b}$                           |
| `vkm_ge(a, b)`          | Returns `true` when all of the corresponding first vector's components are greater than or equal to the second's.        | $\vec{a} \geq \vec{b}$                           | 

## Testing
Do a standard CMake build to build the tests.

## Motivation
Because cglm doesn't support doubles or vecs of all int types and I thought it would be cool to use generics in C!

## Roadmap
- [Flecs](https://www.flecs.dev/flecs/) components.
- SIMD, anyone?
