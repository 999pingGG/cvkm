#pragma once
#ifndef _CVKM_H_
#define _CVKM_H_

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#if defined(__GNUC__)
#define IGNORE_WARNINGS_BEGIN\
_Pragma("GCC diagnostic push")\
_Pragma("GCC diagnostic ignored \"-Wunused-function\"")
#define IGNORE_WARNINGS_END\
_Pragma("GCC diagnostic pop")
#else
#define IGNORE_WARNINGS_BEGIN
#define IGNORE_WARNINGS_END
#endif

IGNORE_WARNINGS_BEGIN

#define VKM_DEFINE_VEC3(prefix, type) typedef union vkm_##prefix##vec3 {\
  struct {\
    type x, y, z;\
  };\
  struct {\
    type r, g, b;\
  };\
  type raw[3];\
} vkm_##prefix##vec3

VKM_DEFINE_VEC3(b, int8_t);
VKM_DEFINE_VEC3(ub, uint8_t);
VKM_DEFINE_VEC3(s, int16_t);
VKM_DEFINE_VEC3(us, uint16_t);
VKM_DEFINE_VEC3(i, int32_t);
VKM_DEFINE_VEC3(u, uint32_t);
VKM_DEFINE_VEC3(l, int64_t);
VKM_DEFINE_VEC3(ul, uint64_t);
VKM_DEFINE_VEC3(, float);
VKM_DEFINE_VEC3(d, double);

#define VKM_VEC3_OPERATION(type, operation, operator) static void vkm_##type##_##operation(\
  const vkm_##type* a,\
  const vkm_##type* b,\
  vkm_##type* result\
) {\
  *result = (vkm_##type){ { a->x operator b->x, a->y operator b->y, a->z operator b->z } };\
}

#define VKM_VEC3_SCALAR_OPERATION(vec_type, scalar_type, operation, operator)\
static void vkm_##vec_type##_##operation##_scalar(\
  const vkm_##vec_type* vec,\
  const scalar_type scalar,\
  vkm_##vec_type* result\
) {\
  *result = (vkm_##vec_type){ { vec->x operator scalar, vec->y operator scalar, vec->z operator scalar } };\
}

#define VKM_VEC3_ALL_OPERATIONS(vec_type, scalar_type) VKM_VEC3_OPERATION(vec_type, add, +)\
VKM_VEC3_OPERATION(vec_type, sub, -)\
VKM_VEC3_OPERATION(vec_type, mul, *)\
VKM_VEC3_OPERATION(vec_type, div, /)\
VKM_VEC3_SCALAR_OPERATION(vec_type, scalar_type, mul, *)\
VKM_VEC3_SCALAR_OPERATION(vec_type, scalar_type, div, /)

VKM_VEC3_ALL_OPERATIONS(bvec3, int8_t)
VKM_VEC3_ALL_OPERATIONS(ubvec3, uint8_t)
VKM_VEC3_ALL_OPERATIONS(svec3, int16_t)
VKM_VEC3_ALL_OPERATIONS(usvec3, uint16_t)
VKM_VEC3_ALL_OPERATIONS(ivec3, int32_t)
VKM_VEC3_ALL_OPERATIONS(uvec3, uint32_t)
VKM_VEC3_ALL_OPERATIONS(lvec3, int64_t)
VKM_VEC3_ALL_OPERATIONS(ulvec3, uint64_t)
VKM_VEC3_ALL_OPERATIONS(vec3, float)
VKM_VEC3_ALL_OPERATIONS(dvec3, double)

#define vkm_add(a, b, result) _Generic((a),\
  vkm_bvec3*: vkm_bvec3_add,\
  vkm_ubvec3*: vkm_ubvec3_add,\
  vkm_svec3*: vkm_svec3_add,\
  vkm_usvec3*: vkm_usvec3_add,\
  vkm_ivec3*: vkm_ivec3_add,\
  vkm_uvec3*: vkm_uvec3_add,\
  vkm_lvec3*: vkm_lvec3_add,\
  vkm_ulvec3*: vkm_ulvec3_add,\
  vkm_vec3*: vkm_vec3_add,\
  vkm_dvec3*: vkm_dvec3_add\
)(a, b, result)

#define vkm_sub(a, b, result) _Generic((a),\
  vkm_bvec3*: vkm_bvec3_sub,\
  vkm_ubvec3*: vkm_ubvec3_sub,\
  vkm_svec3*: vkm_svec3_sub,\
  vkm_usvec3*: vkm_usvec3_sub,\
  vkm_ivec3*: vkm_ivec3_sub,\
  vkm_uvec3*: vkm_uvec3_sub,\
  vkm_lvec3*: vkm_lvec3_sub,\
  vkm_ulvec3*: vkm_ulvec3_sub,\
  vkm_vec3*: vkm_vec3_sub,\
  vkm_dvec3*: vkm_dvec3_sub\
)(a, b, result)

#define VKM_MUL_DIV_OPERATIONS(vec_type, scalar_type, operation, b) vkm_##vec_type*: _Generic((b),\
  vkm_##vec_type*: vkm_##vec_type##_##operation,\
  scalar_type: vkm_##vec_type##_##operation##_scalar,\
  default: ((void)0)\
)\

#define vkm_mul(a, b, result) _Generic((a),\
  VKM_MUL_DIV_OPERATIONS(bvec3, int8_t, mul, b),\
  VKM_MUL_DIV_OPERATIONS(ubvec3, uint8_t, mul, b),\
  VKM_MUL_DIV_OPERATIONS(svec3, int16_t, mul, b),\
  VKM_MUL_DIV_OPERATIONS(usvec3, uint16_t, mul, b),\
  VKM_MUL_DIV_OPERATIONS(ivec3, int32_t, mul, b),\
  VKM_MUL_DIV_OPERATIONS(uvec3, uint32_t, mul, b),\
  VKM_MUL_DIV_OPERATIONS(lvec3, int64_t, mul, b),\
  VKM_MUL_DIV_OPERATIONS(ulvec3, uint64_t, mul, b),\
  VKM_MUL_DIV_OPERATIONS(vec3, float, mul, b),\
  VKM_MUL_DIV_OPERATIONS(dvec3, double, mul, b)\
)(a, b, result)

#define vkm_div(a, b, result) _Generic((a),\
  VKM_MUL_DIV_OPERATIONS(bvec3, int8_t, div, b),\
  VKM_MUL_DIV_OPERATIONS(ubvec3, uint8_t, div, b),\
  VKM_MUL_DIV_OPERATIONS(svec3, int16_t, div, b),\
  VKM_MUL_DIV_OPERATIONS(usvec3, uint16_t, div, b),\
  VKM_MUL_DIV_OPERATIONS(ivec3, int32_t, div, b),\
  VKM_MUL_DIV_OPERATIONS(uvec3, uint32_t, div, b),\
  VKM_MUL_DIV_OPERATIONS(lvec3, int64_t, div, b),\
  VKM_MUL_DIV_OPERATIONS(ulvec3, uint64_t, div, b),\
  VKM_MUL_DIV_OPERATIONS(vec3, float, div, b),\
  VKM_MUL_DIV_OPERATIONS(dvec3, double, div, b)\
)(a, b, result)

#define VKM_SQRT(type, suffix) static type vkm_sqrt##suffix(const type x) {\
  return (type)sqrt((double)x);\
}

VKM_SQRT(int8_t, b)
VKM_SQRT(uint8_t, ub)
VKM_SQRT(int16_t, s)
VKM_SQRT(uint16_t, us)
VKM_SQRT(int32_t, i)
VKM_SQRT(uint32_t, ui)
VKM_SQRT(int64_t, l)
VKM_SQRT(uint64_t, ul)

#define vkm_sqrt(x) _Generic((x),\
  int8_t: vkm_sqrtb,\
  uint8_t: vkm_sqrtub,\
  int16_t: vkm_sqrts,\
  uint16_t: vkm_sqrtus,\
  int32_t: vkm_sqrti,\
  uint32_t: vkm_sqrtui,\
  int64_t: vkm_sqrtl,\
  uint64_t: vkm_sqrtul,\
  float: sqrtf,\
  double: sqrt\
)(x)

#define VKM_VEC3_MISC_OPERATIONS_FOR_UNSIGNED_INTS(vec_type, scalar_type) static scalar_type vkm_##vec_type##_dot(\
  const vkm_##vec_type* a,\
  const vkm_##vec_type* b\
) {\
  return a->x * b->x + a->y * b->y + a->z * b->z;\
}\
\
static void vkm_##vec_type##_cross(const vkm_##vec_type* a, const vkm_##vec_type* b, vkm_##vec_type* result){\
  *result = (vkm_##vec_type){ {\
    a->y * b->z - a->z * b->y,\
    a->z * b->x - a->x * b->z,\
    a->x * b->y - a->y * b->x,\
  } };\
}\
\
static scalar_type vkm_##vec_type##_sqr_magnitude(const vkm_##vec_type* vec) {\
  return vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;\
}\
\
static scalar_type vkm_##vec_type##_magnitude(const vkm_##vec_type* vec) {\
  return vkm_sqrt(vkm_##vec_type##_sqr_magnitude(vec));\
}\
\
static void vkm_##vec_type##_clear(vkm_##vec_type* vec) {\
  *vec = (vkm_##vec_type){ { (scalar_type)0, (scalar_type)0, (scalar_type)0 } };\
}

#define VKM_VEC3_INVERT(vec_type) static void vkm_##vec_type##_invert(const vkm_##vec_type* vec, vkm_##vec_type* result) {\
  *result = (vkm_##vec_type){ { -vec->x, -vec->y, -vec->z } };\
}

#define VKM_VEC3_NORMALIZE(vec_type, scalar_type) static void vkm_##vec_type##_normalize(\
  const vkm_##vec_type* vec,\
  vkm_##vec_type* result\
) {\
  const scalar_type magnitude = vkm_##vec_type##_magnitude(vec);\
  if (magnitude > (scalar_type)0) {\
    vkm_##vec_type##_div_scalar(vec, magnitude, result);\
  }\
}

#define VKM_VEC3_MISC_OPERATIONS_FOR_INTS(vec_type, scalar_type)\
  VKM_VEC3_MISC_OPERATIONS_FOR_UNSIGNED_INTS(vec_type, scalar_type)\
  VKM_VEC3_INVERT(vec_type)

#define VKM_VEC3_MISC_OPERATIONS(vec_type, scalar_type)\
  VKM_VEC3_MISC_OPERATIONS_FOR_INTS(vec_type, scalar_type)\
  VKM_VEC3_NORMALIZE(vec_type, scalar_type)

VKM_VEC3_MISC_OPERATIONS_FOR_INTS(bvec3, int8_t)
VKM_VEC3_MISC_OPERATIONS_FOR_UNSIGNED_INTS(ubvec3, uint8_t)
VKM_VEC3_MISC_OPERATIONS_FOR_INTS(svec3, int16_t)
VKM_VEC3_MISC_OPERATIONS_FOR_UNSIGNED_INTS(usvec3, uint16_t)
VKM_VEC3_MISC_OPERATIONS_FOR_INTS(ivec3, int32_t)
VKM_VEC3_MISC_OPERATIONS_FOR_UNSIGNED_INTS(uvec3, uint32_t)
VKM_VEC3_MISC_OPERATIONS_FOR_INTS(lvec3, int64_t)
VKM_VEC3_MISC_OPERATIONS_FOR_UNSIGNED_INTS(ulvec3, uint64_t)
VKM_VEC3_MISC_OPERATIONS(vec3, float)
VKM_VEC3_MISC_OPERATIONS(dvec3, double)

#define vkm_dot(a, b) _Generic((a),\
  vkm_bvec3*: vkm_bvec3_dot,\
  vkm_ubvec3*: vkm_ubvec3_dot,\
  vkm_svec3*: vkm_svec3_dot,\
  vkm_usvec3*: vkm_usvec3_dot,\
  vkm_ivec3*: vkm_ivec3_dot,\
  vkm_uvec3*: vkm_uvec3_dot,\
  vkm_lvec3*: vkm_lvec3_dot,\
  vkm_ulvec3*: vkm_ulvec3_dot,\
  vkm_vec3*: vkm_vec3_dot,\
  vkm_dvec3*: vkm_dvec3_dot\
)(a, b)

#define vkm_cross(a, b, result) _Generic((a),\
  vkm_bvec3*: vkm_bvec3_cross,\
  vkm_ubvec3*: vkm_ubvec3_cross,\
  vkm_svec3*: vkm_svec3_cross,\
  vkm_usvec3*: vkm_usvec3_cross,\
  vkm_ivec3*: vkm_ivec3_cross,\
  vkm_uvec3*: vkm_uvec3_cross,\
  vkm_lvec3*: vkm_lvec3_cross,\
  vkm_ulvec3*: vkm_ulvec3_cross,\
  vkm_vec3*: vkm_vec3_cross,\
  vkm_dvec3*: vkm_dvec3_cross\
)(a, b, result)

#define vkm_sqr_magnitude(vec) _Generic((vec),\
  vkm_bvec3*: vkm_bvec3_sqr_magnitude,\
  vkm_ubvec3*: vkm_ubvec3_sqr_magnitude,\
  vkm_svec3*: vkm_svec3_sqr_magnitude,\
  vkm_usvec3*: vkm_usvec3_sqr_magnitude,\
  vkm_ivec3*: vkm_ivec3_sqr_magnitude,\
  vkm_uvec3*: vkm_uvec3_sqr_magnitude,\
  vkm_lvec3*: vkm_lvec3_sqr_magnitude,\
  vkm_ulvec3*: vkm_ulvec3_sqr_magnitude,\
  vkm_vec3*: vkm_vec3_sqr_magnitude,\
  vkm_dvec3*: vkm_dvec3_sqr_magnitude\
)(vec)

#define vkm_magnitude(vec) _Generic((vec),\
  vkm_bvec3*: vkm_bvec3_magnitude,\
  vkm_ubvec3*: vkm_ubvec3_magnitude,\
  vkm_svec3*: vkm_svec3_magnitude,\
  vkm_usvec3*: vkm_usvec3_magnitude,\
  vkm_ivec3*: vkm_ivec3_magnitude,\
  vkm_uvec3*: vkm_uvec3_magnitude,\
  vkm_lvec3*: vkm_lvec3_magnitude,\
  vkm_ulvec3*: vkm_ulvec3_magnitude,\
  vkm_vec3*: vkm_vec3_magnitude,\
  vkm_dvec3*: vkm_dvec3_magnitude\
)(vec)

#define vkm_normalize(vec, result) _Generic((vec),\
  vkm_vec3*: vkm_vec3_normalize,\
  vkm_dvec3*: vkm_dvec3_normalize\
)(vec, result)

#define vkm_clear(vec) _Generic((vec),\
  vkm_bvec3*: vkm_bvec3_clear,\
  vkm_ubvec3*: vkm_ubvec3_clear,\
  vkm_svec3*: vkm_svec3_clear,\
  vkm_usvec3*: vkm_usvec3_clear,\
  vkm_ivec3*: vkm_ivec3_clear,\
  vkm_uvec3*: vkm_uvec3_clear,\
  vkm_lvec3*: vkm_lvec3_clear,\
  vkm_ulvec3*: vkm_ulvec3_clear,\
  vkm_vec3*: vkm_vec3_clear,\
  vkm_dvec3*: vkm_dvec3_clear\
)(vec)

#define vkm_invert(vec, result) _Generic((vec),\
  vkm_bvec3*: vkm_bvec3_invert,\
  vkm_svec3*: vkm_svec3_invert,\
  vkm_ivec3*: vkm_ivec3_invert,\
  vkm_lvec3*: vkm_lvec3_invert,\
  vkm_vec3*: vkm_vec3_invert,\
  vkm_dvec3*: vkm_dvec3_invert\
)(vec, result)

#define VKM_VEC3_LOGICAL_OPERATION(type, operation, operator) static bool vkm_##type##_##operation(\
  const vkm_##type* a,\
  const vkm_##type* b\
) {\
  return a->x operator b->x && a->y operator b->y && a->z operator b->z;\
}

#define VKM_VEC3_LOGICAL_OPERATIONS(type) VKM_VEC3_LOGICAL_OPERATION(type, eq, ==)\
  VKM_VEC3_LOGICAL_OPERATION(type, lt, <)\
  VKM_VEC3_LOGICAL_OPERATION(type, gt, >)\
  VKM_VEC3_LOGICAL_OPERATION(type, le, <=)\
  VKM_VEC3_LOGICAL_OPERATION(type, ge, >=)

VKM_VEC3_LOGICAL_OPERATIONS(bvec3)
VKM_VEC3_LOGICAL_OPERATIONS(ubvec3)
VKM_VEC3_LOGICAL_OPERATIONS(svec3)
VKM_VEC3_LOGICAL_OPERATIONS(usvec3)
VKM_VEC3_LOGICAL_OPERATIONS(ivec3)
VKM_VEC3_LOGICAL_OPERATIONS(uvec3)
VKM_VEC3_LOGICAL_OPERATIONS(lvec3)
VKM_VEC3_LOGICAL_OPERATIONS(ulvec3)
VKM_VEC3_LOGICAL_OPERATIONS(vec3)
VKM_VEC3_LOGICAL_OPERATIONS(dvec3)

#define vkm_eq(a, b) _Generic((a),\
  vkm_bvec3*: vkm_bvec3_eq,\
  vkm_ubvec3*: vkm_ubvec3_eq,\
  vkm_svec3*: vkm_svec3_eq,\
  vkm_usvec3*: vkm_usvec3_eq,\
  vkm_ivec3*: vkm_ivec3_eq,\
  vkm_uvec3*: vkm_uvec3_eq,\
  vkm_lvec3*: vkm_lvec3_eq,\
  vkm_ulvec3*: vkm_ulvec3_eq,\
  vkm_vec3*: vkm_vec3_eq,\
  vkm_dvec3*: vkm_dvec3_eq\
)(a, b)

#define vkm_lt(a, b) _Generic((a),\
  vkm_bvec3*: vkm_bvec3_lt,\
  vkm_ubvec3*: vkm_ubvec3_lt,\
  vkm_svec3*: vkm_svec3_lt,\
  vkm_usvec3*: vkm_usvec3_lt,\
  vkm_ivec3*: vkm_ivec3_lt,\
  vkm_uvec3*: vkm_uvec3_lt,\
  vkm_lvec3*: vkm_lvec3_lt,\
  vkm_ulvec3*: vkm_ulvec3_lt,\
  vkm_vec3*: vkm_vec3_lt,\
  vkm_dvec3*: vkm_dvec3_lt\
)(a, b)

#define vkm_gt(a, b) _Generic((a),\
  vkm_bvec3*: vkm_bvec3_gt,\
  vkm_ubvec3*: vkm_ubvec3_gt,\
  vkm_svec3*: vkm_svec3_gt,\
  vkm_usvec3*: vkm_usvec3_gt,\
  vkm_ivec3*: vkm_ivec3_gt,\
  vkm_uvec3*: vkm_uvec3_gt,\
  vkm_lvec3*: vkm_lvec3_gt,\
  vkm_ulvec3*: vkm_ulvec3_gt,\
  vkm_vec3*: vkm_vec3_gt,\
  vkm_dvec3*: vkm_dvec3_gt\
)(a, b)

#define vkm_le(a, b) _Generic((a),\
  vkm_bvec3*: vkm_bvec3_le,\
  vkm_ubvec3*: vkm_ubvec3_le,\
  vkm_svec3*: vkm_svec3_le,\
  vkm_usvec3*: vkm_usvec3_le,\
  vkm_ivec3*: vkm_ivec3_le,\
  vkm_uvec3*: vkm_uvec3_le,\
  vkm_lvec3*: vkm_lvec3_le,\
  vkm_ulvec3*: vkm_ulvec3_le,\
  vkm_vec3*: vkm_vec3_le,\
  vkm_dvec3*: vkm_dvec3_le\
)(a, b)

#define vkm_ge(a, b) _Generic((a),\
  vkm_bvec3*: vkm_bvec3_ge,\
  vkm_ubvec3*: vkm_ubvec3_ge,\
  vkm_svec3*: vkm_svec3_ge,\
  vkm_usvec3*: vkm_usvec3_ge,\
  vkm_ivec3*: vkm_ivec3_ge,\
  vkm_uvec3*: vkm_uvec3_ge,\
  vkm_lvec3*: vkm_lvec3_ge,\
  vkm_ulvec3*: vkm_ulvec3_ge,\
  vkm_vec3*: vkm_vec3_ge,\
  vkm_dvec3*: vkm_dvec3_ge\
)(a, b)

IGNORE_WARNINGS_END
#endif
