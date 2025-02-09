#pragma once
#ifndef _CVKM_H_
#define _CVKM_H_

#include <math.h>
#include <stdbool.h>

typedef union vkm_vec3 {
  struct {
    float x, y, z;
  };

  struct {
    float r, g, b;
  };

  float raw[3];
} vkm_vec3;

typedef union vkm_dvec3 {
  struct {
    double x, y, z;
  };

  struct {
    double r, g, b;
  };

  double raw[3];
} vkm_dvec3;

#define VKM_VEC3_OPERATION(type, operation, operator) static void vkm_##type##_##operation(\
  const vkm_##type* a,\
  const vkm_##type* b,\
  vkm_##type* result\
) {\
  *result = (vkm_##type){ a->x operator b->x, a->y operator b->y, a->z operator b->z };\
}

#define VKM_VEC3_SCALAR_OPERATION(vec_type, scalar_type, operation, operator)\
static void vkm_##vec_type##_##operation##_scalar(\
  const vkm_##vec_type* vec,\
  const scalar_type scalar,\
  vkm_##vec_type* result\
) {\
  *result = (vkm_##vec_type){ vec->x operator scalar, vec->y operator scalar, vec->z operator scalar };\
}

VKM_VEC3_OPERATION(vec3, add, +)
VKM_VEC3_OPERATION(vec3, sub, -)
VKM_VEC3_OPERATION(vec3, mul, *)
VKM_VEC3_OPERATION(vec3, div, /)

VKM_VEC3_OPERATION(dvec3, add, +)
VKM_VEC3_OPERATION(dvec3, sub, -)
VKM_VEC3_OPERATION(dvec3, mul, *)
VKM_VEC3_OPERATION(dvec3, div, /)

#define vkm_add(a, b, result) _Generic((a),\
  vkm_vec3*: vkm_vec3_add,\
  vkm_dvec3*: vkm_dvec3_add\
)(a, b, result)

#define vkm_sub(a, b, result) _Generic((a),\
  vkm_vec3*: vkm_vec3_sub,\
  vkm_dvec3*: vkm_dvec3_sub\
)(a, b, result)

#define vkm_mul(a, b, result) _Generic((a),\
  vkm_vec3*: _Generic((b),\
    vkm_vec3*: vkm_vec3_mul,\
    float: vkm_vec3_mul_scalar,\
    default: ((void)0)\
  ),\
  vkm_dvec3*: _Generic((b),\
    vkm_dvec3*: vkm_dvec3_mul,\
    double: vkm_dvec3_mul_scalar,\
    default: ((void)0)\
  )\
)(a, b, result)

#define vkm_div(a, b, result) _Generic((a),\
  vkm_vec3*: _Generic((b),\
    vkm_vec3*: vkm_vec3_div,\
    float: vkm_vec3_div_scalar,\
    default: ((void)0)\
  ),\
  vkm_dvec3*: _Generic((b),\
    vkm_dvec3*: vkm_dvec3_div,\
    double: vkm_dvec3_div_scalar,\
    default: ((void)0)\
  )\
)(a, b, result)

VKM_VEC3_SCALAR_OPERATION(vec3, float, mul, *)
VKM_VEC3_SCALAR_OPERATION(vec3, float, div, /)

VKM_VEC3_SCALAR_OPERATION(dvec3, double, mul, *)
VKM_VEC3_SCALAR_OPERATION(dvec3, double, div, /)

#define vkm_sqrt(x) _Generic((x),\
  float: sqrtf,\
  double: sqrt\
)(x)

#define VKM_VEC3_MISC_OPERATIONS(vec_type, scalar_type) static scalar_type vkm_##vec_type##_sqr_magnitude(\
  const vkm_##vec_type* vec\
) {\
  return vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;\
}\
\
static scalar_type vkm_##vec_type##_magnitude(const vkm_##vec_type* vec) {\
  return vkm_sqrt(vkm_##vec_type##_sqr_magnitude(vec));\
}\
\
static void vkm_##vec_type##_normalize(const vkm_##vec_type* vec, vkm_##vec_type* result) {\
  const scalar_type magnitude = vkm_##vec_type##_magnitude(vec);\
  if (magnitude > (scalar_type)0) {\
    vkm_##vec_type##_div_scalar(vec, magnitude, result);\
  }\
}\
\
static void vkm_##vec_type##_clear(vkm_##vec_type* vec) {\
  *vec = (vkm_##vec_type){ (scalar_type)0, (scalar_type)0, (scalar_type)0 };\
}\
\
static void vkm_##vec_type##_invert(vkm_##vec_type* vec) {\
  *vec = (vkm_##vec_type){ -vec->x, -vec->y, -vec->z };\
}

VKM_VEC3_MISC_OPERATIONS(vec3, float)
VKM_VEC3_MISC_OPERATIONS(dvec3, double)

#define VKM_VEC3_LOGICAL_OPERATION(type, operation, operator) static bool vkm_##type##_##operation(\
  const vkm_##type* a,\
  const vkm_##type* b\
) {\
  return a->x operator b->x && a->y operator b->y && a->z operator b->z;\
}

VKM_VEC3_LOGICAL_OPERATION(vec3, eq, ==)
VKM_VEC3_LOGICAL_OPERATION(vec3, lt, <)
VKM_VEC3_LOGICAL_OPERATION(vec3, gt, >)
VKM_VEC3_LOGICAL_OPERATION(vec3, le, <=)
VKM_VEC3_LOGICAL_OPERATION(vec3, ge, >=)

VKM_VEC3_LOGICAL_OPERATION(dvec3, eq, ==)
VKM_VEC3_LOGICAL_OPERATION(dvec3, lt, <)
VKM_VEC3_LOGICAL_OPERATION(dvec3, gt, >)
VKM_VEC3_LOGICAL_OPERATION(dvec3, le, <=)
VKM_VEC3_LOGICAL_OPERATION(dvec3, ge, >=)
#endif
