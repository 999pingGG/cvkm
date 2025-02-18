#include <stdint.h>

#include <cvkm.h>
#include <munit.h>

#define MAX_FLOAT_TO_TEST 1000000.0

#define RANDOM_VEC3(vec_type, scalar_type, n)\
  const scalar_type x##n = (scalar_type)(munit_rand_double() * MAX_FLOAT_TO_TEST);\
  const scalar_type y##n = (scalar_type)(munit_rand_double() * MAX_FLOAT_TO_TEST);\
  const scalar_type z##n = (scalar_type)(munit_rand_double() * MAX_FLOAT_TO_TEST);\
  vec_type vec##n = { { x##n, y##n, z##n } }

#define INITIALIZE_TWO_VEC3(vec_type, scalar_type)\
  RANDOM_VEC3(vec_type, scalar_type, 1);\
  RANDOM_VEC3(vec_type, scalar_type, 2);\
\
  vec_type result

#define VKM_VEC3_TEST(vec_type, scalar_type, assertion, operation, operator) static MunitResult vec_type##_##operation(\
  const MunitParameter* params,\
  void* userdata\
) {\
  (void)params;\
  (void)userdata;\
  INITIALIZE_TWO_VEC3(vkm_##vec_type, scalar_type);\
\
  vkm_##operation(&vec1, &vec2, &result);\
\
  munit_assert_##assertion(result.x, ==, x1 operator x2);\
  munit_assert_##assertion(result.y, ==, y1 operator y2);\
  munit_assert_##assertion(result.z, ==, z1 operator z2);\
\
  return MUNIT_OK;\
}

#define VKM_VEC3_SCALAR_TEST(vec_type, scalar_type, assertion, operation, operator)\
static MunitResult vec_type##_##operation##_scalar(\
  const MunitParameter* params,\
  void* userdata\
) {\
  (void)params;\
  (void)userdata;\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 1);\
  const scalar_type scalar = (scalar_type)(munit_rand_double() * MAX_FLOAT_TO_TEST);\
\
  vkm_##operation(&vec1, scalar, &vec1);\
\
  munit_assert_##assertion(vec1.x, ==, x1 operator scalar);\
  munit_assert_##assertion(vec1.y, ==, y1 operator scalar);\
  munit_assert_##assertion(vec1.z, ==, z1 operator scalar);\
\
  return MUNIT_OK;\
}

#define VKM_VEC3_ALL_TESTS(vec_type, scalar_type, assertion) VKM_VEC3_TEST(vec_type, scalar_type, assertion, add, +)\
  VKM_VEC3_TEST(vec_type, scalar_type, assertion, sub, -)\
  VKM_VEC3_TEST(vec_type, scalar_type, assertion, mul, *)\
  VKM_VEC3_TEST(vec_type, scalar_type, assertion, div, /)\
  VKM_VEC3_SCALAR_TEST(vec_type, scalar_type, assertion, mul, *)\
  VKM_VEC3_SCALAR_TEST(vec_type, scalar_type, assertion, div, /)

VKM_VEC3_ALL_TESTS(bvec3, int8_t, int8)
VKM_VEC3_ALL_TESTS(ubvec3, uint8_t, uint8)
VKM_VEC3_ALL_TESTS(svec3, int16_t, int16)
VKM_VEC3_ALL_TESTS(usvec3, uint16_t, uint16)
VKM_VEC3_ALL_TESTS(ivec3, int32_t, int32)
VKM_VEC3_ALL_TESTS(uvec3, uint32_t, uint32)
VKM_VEC3_ALL_TESTS(lvec3, int64_t, int64)
VKM_VEC3_ALL_TESTS(ulvec3, uint64_t, uint64)
VKM_VEC3_ALL_TESTS(vec3, float, float)
VKM_VEC3_ALL_TESTS(dvec3, double, double)

#define VKM_VEC3_MISC_OPERATIONS_TEST_FOR_INTS(vec_type, scalar_type, assertion) static MunitResult vec_type##_dot(\
  const MunitParameter* params,\
  void* userdata\
) {\
  (void)params;\
  (void)userdata;\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 1);\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 2);\
\
  munit_assert_##assertion(vkm_dot(&vec1, &vec2), ==, vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);\
\
  return MUNIT_OK;\
}\
\
static MunitResult vec_type##_cross(\
  const MunitParameter* params,\
  void* userdata\
) {\
  (void)params;\
  (void)userdata;\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 1);\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 2);\
\
  vkm_##vec_type result;\
  vkm_cross(&vec1, &vec2, &result);\
\
  munit_assert_##assertion(result.x, ==, vec1.y * vec2.z - vec1.z * vec2.y);\
  munit_assert_##assertion(result.y, ==, vec1.z * vec2.x - vec1.x * vec2.z);\
  munit_assert_##assertion(result.z, ==, vec1.x * vec2.y - vec1.y * vec2.x);\
\
  return MUNIT_OK;\
}\
\
static MunitResult vec_type##_sqr_magnitude(\
  const MunitParameter* params,\
  void* userdata\
) {\
  (void)params;\
  (void)userdata;\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 1);\
\
  const scalar_type sqr_magnitude = vkm_sqr_magnitude(&vec1);\
  munit_assert_##assertion(sqr_magnitude, ==, x1 * x1 + y1 * y1 + z1 * z1);\
\
  return MUNIT_OK;\
}\
\
static MunitResult vec_type##_magnitude(const MunitParameter* params, void* userdata) {\
  (void)params;\
  (void)userdata;\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 1);\
\
  const scalar_type sqr_magnitude = vkm_sqr_magnitude(&vec1);\
  const scalar_type magnitude = vkm_magnitude(&vec1);\
  munit_assert_##assertion(sqr_magnitude, ==, x1 * x1 + y1 * y1 + z1 * z1);\
  munit_assert_##assertion(magnitude, ==, vkm_sqrt((scalar_type)(x1 * x1 + y1 * y1 + z1 * z1)));\
  munit_assert_##assertion(vkm_sqrt(sqr_magnitude), ==, magnitude);\
\
  return MUNIT_OK;\
}\
\
static MunitResult vec_type##_clear(const MunitParameter* params, void* userdata) {\
  (void)params;\
  (void)userdata;\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 1);\
\
  vkm_clear(&vec1);\
  munit_assert_##assertion(vec1.x, ==, (scalar_type)0);\
  munit_assert_##assertion(vec1.y, ==, (scalar_type)0);\
  munit_assert_##assertion(vec1.z, ==, (scalar_type)0);\
\
  return MUNIT_OK;\
}\
\
static MunitResult vec_type##_invert(const MunitParameter* params, void* userdata) {\
  (void)params;\
  (void)userdata;\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 1);\
  vkm_##vec_type result;\
\
  vkm_invert(&vec1, &result);\
  munit_assert_##assertion(result.x, ==, -vec1.x);\
  munit_assert_##assertion(result.y, ==, -vec1.y);\
  munit_assert_##assertion(result.z, ==, -vec1.z);\
\
  return MUNIT_OK;\
}

#define VKM_VEC3_NORMALIZE_TEST(vec_type, scalar_type) static MunitResult vec_type##_normalize(\
  const MunitParameter* params,\
  void* userdata\
) {\
  (void)params;\
  (void)userdata;\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 1);\
\
  const scalar_type magnitude = vkm_magnitude(&vec1);\
  vkm_normalize(&vec1, &vec1);\
  munit_assert_##scalar_type(vec1.x, ==, x1 / magnitude);\
  munit_assert_##scalar_type(vec1.y, ==, y1 / magnitude);\
  munit_assert_##scalar_type(vec1.z, ==, z1 / magnitude);\
\
  return MUNIT_OK;\
}

#define VKM_VEC3_MISC_OPERATIONS_TEST(vec_type, scalar_type, assertion)\
  VKM_VEC3_MISC_OPERATIONS_TEST_FOR_INTS(vec_type, scalar_type, assertion)\
  VKM_VEC3_NORMALIZE_TEST(vec_type, scalar_type)

VKM_VEC3_MISC_OPERATIONS_TEST_FOR_INTS(bvec3, int8_t, int8)
VKM_VEC3_MISC_OPERATIONS_TEST_FOR_INTS(ubvec3, uint8_t, uint8)
VKM_VEC3_MISC_OPERATIONS_TEST_FOR_INTS(svec3, int16_t, int16)
VKM_VEC3_MISC_OPERATIONS_TEST_FOR_INTS(usvec3, uint16_t, uint16)
VKM_VEC3_MISC_OPERATIONS_TEST_FOR_INTS(ivec3, int32_t, int32)
VKM_VEC3_MISC_OPERATIONS_TEST_FOR_INTS(uvec3, uint32_t, uint32)
VKM_VEC3_MISC_OPERATIONS_TEST_FOR_INTS(lvec3, int64_t, int64)
VKM_VEC3_MISC_OPERATIONS_TEST_FOR_INTS(ulvec3, uint64_t, uint64)
VKM_VEC3_MISC_OPERATIONS_TEST(vec3, float, float)
VKM_VEC3_MISC_OPERATIONS_TEST(dvec3, double, double)

#define VKM_VEC3_LOGICAL_OPERATION_TEST(vec_type, scalar_type, operation, operator)\
static MunitResult vec_type##_##operation(\
  const MunitParameter* params,\
  void* userdata\
) {\
  (void)params;\
  (void)userdata;\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 1);\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 2);\
\
  munit_assert(\
    vkm_##operation(&vec1, &vec2) == (vec1.x operator vec2.x && vec1.y operator vec2.y && vec1.z operator vec2.z)\
  );\
\
  return MUNIT_OK;\
}

#define VKM_VEC3_LOGICAL_OPERATION_TEST_ALL(vec_type, scalar_type) \
  VKM_VEC3_LOGICAL_OPERATION_TEST(vec_type, scalar_type, eq, ==)\
  VKM_VEC3_LOGICAL_OPERATION_TEST(vec_type, scalar_type, lt, <)\
  VKM_VEC3_LOGICAL_OPERATION_TEST(vec_type, scalar_type, gt, >)\
  VKM_VEC3_LOGICAL_OPERATION_TEST(vec_type, scalar_type, le, <=)\
  VKM_VEC3_LOGICAL_OPERATION_TEST(vec_type, scalar_type, ge, >=)

VKM_VEC3_LOGICAL_OPERATION_TEST_ALL(bvec3, int8_t)
VKM_VEC3_LOGICAL_OPERATION_TEST_ALL(ubvec3, uint8_t)
VKM_VEC3_LOGICAL_OPERATION_TEST_ALL(svec3, int16_t)
VKM_VEC3_LOGICAL_OPERATION_TEST_ALL(usvec3, uint16_t)
VKM_VEC3_LOGICAL_OPERATION_TEST_ALL(ivec3, int32_t)
VKM_VEC3_LOGICAL_OPERATION_TEST_ALL(uvec3, uint32_t)
VKM_VEC3_LOGICAL_OPERATION_TEST_ALL(lvec3, int64_t)
VKM_VEC3_LOGICAL_OPERATION_TEST_ALL(ulvec3, uint64_t)
VKM_VEC3_LOGICAL_OPERATION_TEST_ALL(vec3, int32_t)
VKM_VEC3_LOGICAL_OPERATION_TEST_ALL(dvec3, int32_t)

#define DEFINE_TEST(test_name, func) {\
  .name = test_name,\
  .test = func,\
}

int main(const int argc, char* const* argv) {
#define VKM_VEC_TEST_SUITE_DECL_FOR_INTS(type) MunitTest type##_tests[] = {\
  DEFINE_TEST("/add", type##_add),\
  DEFINE_TEST("/sub", type##_sub),\
  DEFINE_TEST("/mul", type##_mul),\
  DEFINE_TEST("/div", type##_div),\
  DEFINE_TEST("/mul_scalar", type##_mul_scalar),\
  DEFINE_TEST("/div_scalar", type##_div_scalar),\
  DEFINE_TEST("/dot", type##_dot),\
  DEFINE_TEST("/cross", type##_cross),\
  DEFINE_TEST("/sqr_magnitude", type##_sqr_magnitude),\
  DEFINE_TEST("/magnitude", type##_magnitude),\
  { 0 },\
  DEFINE_TEST("/clear", type##_clear),\
  DEFINE_TEST("/invert", type##_invert),\
  DEFINE_TEST("/eq", type##_eq),\
  DEFINE_TEST("/lt", type##_lt),\
  DEFINE_TEST("/gt", type##_gt),\
  DEFINE_TEST("/le", type##_le),\
  DEFINE_TEST("/ge", type##_ge),\
  { 0 },\
}

#define VKM_VEC_TEST_SUITE_DECL(type) VKM_VEC_TEST_SUITE_DECL_FOR_INTS(type);\
  type##_tests[10] = (MunitTest)DEFINE_TEST("/normalize", type##_normalize)

  VKM_VEC_TEST_SUITE_DECL_FOR_INTS(bvec3);
  VKM_VEC_TEST_SUITE_DECL_FOR_INTS(ubvec3);
  VKM_VEC_TEST_SUITE_DECL_FOR_INTS(svec3);
  VKM_VEC_TEST_SUITE_DECL_FOR_INTS(usvec3);
  VKM_VEC_TEST_SUITE_DECL_FOR_INTS(ivec3);
  VKM_VEC_TEST_SUITE_DECL_FOR_INTS(uvec3);
  VKM_VEC_TEST_SUITE_DECL_FOR_INTS(lvec3);
  VKM_VEC_TEST_SUITE_DECL_FOR_INTS(ulvec3);
  VKM_VEC_TEST_SUITE_DECL(vec3);
  VKM_VEC_TEST_SUITE_DECL(dvec3);

#define VKM_VEC_TEST_SUITE(type) {\
  .prefix = "/"#type,\
  .tests = type##_tests,\
  .iterations = 1000000,\
}

  MunitSuite suites[] = {
    VKM_VEC_TEST_SUITE(bvec3),
    VKM_VEC_TEST_SUITE(ubvec3),
    VKM_VEC_TEST_SUITE(svec3),
    VKM_VEC_TEST_SUITE(usvec3),
    VKM_VEC_TEST_SUITE(ivec3),
    VKM_VEC_TEST_SUITE(uvec3),
    VKM_VEC_TEST_SUITE(lvec3),
    VKM_VEC_TEST_SUITE(ulvec3),
    VKM_VEC_TEST_SUITE(vec3),
    VKM_VEC_TEST_SUITE(dvec3),
    { 0 },
  };

  const MunitSuite main_suite = {
    .prefix = "/cvkm",
    .suites = suites,
    .iterations = 1,
  };

  return munit_suite_main(&main_suite, NULL, argc, argv);
}
