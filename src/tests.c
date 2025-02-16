#include <cvkm.h>

#include <munit.h>

#define MAX_FLOAT_TO_TEST 1000000.0

#define RANDOM_VEC3(vec_type, scalar_type, n) \
  const scalar_type x##n = (scalar_type)(munit_rand_double() * MAX_FLOAT_TO_TEST);\
  const scalar_type y##n = (scalar_type)(munit_rand_double() * MAX_FLOAT_TO_TEST);\
  const scalar_type z##n = (scalar_type)(munit_rand_double() * MAX_FLOAT_TO_TEST);\
  vec_type vec##n = { x##n, y##n, z##n }

#define INITIALIZE_TWO_VEC3(vec_type, scalar_type) \
  RANDOM_VEC3(vec_type, scalar_type, 1);\
  RANDOM_VEC3(vec_type, scalar_type, 2);\
\
  vec_type result

#define VKM_VEC3_TEST(vec_type, scalar_type, operation, operator) static MunitResult vec_type##_##operation(\
  const MunitParameter* params,\
  void* userdata\
) {\
  INITIALIZE_TWO_VEC3(vkm_##vec_type, scalar_type);\
\
  vkm_##operation(&vec1, &vec2, &result);\
\
  munit_assert_##scalar_type(result.x, ==, x1 operator x2);\
  munit_assert_##scalar_type(result.y, ==, y1 operator y2);\
  munit_assert_##scalar_type(result.z, ==, z1 operator z2);\
\
  return MUNIT_OK;\
}

#define VKM_VEC3_SCALAR_TEST(vec_type, scalar_type, operation, operator)\
static MunitResult vec_type##_##operation##_scalar(\
  const MunitParameter* params,\
  void* userdata\
) {\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 1);\
  const scalar_type scalar = (scalar_type)(munit_rand_double() * MAX_FLOAT_TO_TEST);\
\
  vkm_##operation(&vec1, scalar, &vec1);\
\
  munit_assert_##scalar_type(vec1.x, ==, x1 operator scalar);\
  munit_assert_##scalar_type(vec1.y, ==, y1 operator scalar);\
  munit_assert_##scalar_type(vec1.z, ==, z1 operator scalar);\
\
  return MUNIT_OK;\
}

VKM_VEC3_TEST(vec3, float, add, +)
VKM_VEC3_TEST(vec3, float, sub, -)
VKM_VEC3_TEST(vec3, float, mul, *)
VKM_VEC3_TEST(vec3, float, div, /)

VKM_VEC3_SCALAR_TEST(vec3, float, mul, *)
VKM_VEC3_SCALAR_TEST(vec3, float, div, /)

VKM_VEC3_TEST(dvec3, double, add, +)
VKM_VEC3_TEST(dvec3, double, sub, -)
VKM_VEC3_TEST(dvec3, double, mul, *)
VKM_VEC3_TEST(dvec3, double, div, /)

VKM_VEC3_SCALAR_TEST(dvec3, double, mul, *)
VKM_VEC3_SCALAR_TEST(dvec3, double, div, /)

#define VKM_VEC3_MISC_OPERATIONS_TEST(vec_type, scalar_type) static MunitResult vec_type##_dot(\
  const MunitParameter* params,\
  void* userdata\
) {\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 1);\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 2);\
  \
  munit_assert_##scalar_type(vkm_dot(&vec1, &vec2), ==, vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);\
  \
  return MUNIT_OK;\
}\
\
static MunitResult vec_type##_cross(\
  const MunitParameter* params,\
  void* userdata\
) {\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 1);\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 2);\
\
  vkm_##vec_type result;\
  vkm_cross(&vec1, &vec2, &result);\
  \
  munit_assert_##scalar_type(result.x, ==, vec1.y * vec2.z - vec1.z * vec2.y);\
  munit_assert_##scalar_type(result.y, ==, vec1.z * vec2.x - vec1.x * vec2.z);\
  munit_assert_##scalar_type(result.z, ==, vec1.x * vec2.y - vec1.y * vec2.x);\
\
  return MUNIT_OK;\
}\
\
static MunitResult vec_type##_sqr_magnitude(\
  const MunitParameter* params,\
  void* userdata\
) {\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 1);\
\
  const scalar_type sqr_magnitude = vkm_##vec_type##_sqr_magnitude(&vec1);\
  munit_assert_##scalar_type(sqr_magnitude, ==, x1 * x1 + y1 * y1 + z1 * z1);\
\
  return MUNIT_OK;\
}\
\
static MunitResult vec_type##_magnitude(const MunitParameter* params, void* userdata) {\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 1);\
\
  const scalar_type sqr_magnitude = vkm_##vec_type##_sqr_magnitude(&vec1);\
  const scalar_type magnitude = vkm_##vec_type##_magnitude(&vec1);\
  munit_assert_##scalar_type(sqr_magnitude, ==, x1 * x1 + y1 * y1 + z1 * z1);\
  munit_assert_##scalar_type(magnitude, ==, vkm_sqrt(x1 * x1 + y1 * y1 + z1 * z1));\
  munit_assert_##scalar_type(vkm_sqrt(sqr_magnitude), ==, magnitude);\
\
  return MUNIT_OK;\
}\
\
static MunitResult vec_type##_normalize(const MunitParameter* params, void* userdata) {\
  RANDOM_VEC3(vkm_##vec_type, scalar_type, 1);\
\
  const scalar_type magnitude = vkm_##vec_type##_magnitude(&vec1);\
  vkm_##vec_type##_normalize(&vec1, &vec1);\
  munit_assert_##scalar_type(vec1.x, ==, x1 / magnitude);\
  munit_assert_##scalar_type(vec1.y, ==, y1 / magnitude);\
  munit_assert_##scalar_type(vec1.z, ==, z1 / magnitude);\
\
  return MUNIT_OK;\
}

VKM_VEC3_MISC_OPERATIONS_TEST(vec3, float)
VKM_VEC3_MISC_OPERATIONS_TEST(dvec3, double)

#define DEFINE_TEST(test_name, func) {\
  .name = test_name,\
  .test = func,\
}

int main(const int argc, char* const* argv) {
#define VKM_VEC_TEST_SUITE(type) MunitTest type##_tests[] = {\
  DEFINE_TEST("/add", type##_add),\
  DEFINE_TEST("/sub", type##_sub),\
  DEFINE_TEST("/mul", type##_mul),\
  DEFINE_TEST("/div", type##_div),\
  DEFINE_TEST("/mul_scalar", type##_mul_scalar),\
  DEFINE_TEST("/dot", type##_dot),\
  DEFINE_TEST("/cross", type##_cross),\
  DEFINE_TEST("/sqr_magnitude", type##_sqr_magnitude),\
  DEFINE_TEST("/magnitude", type##_magnitude),\
  DEFINE_TEST("/normalize", type##_normalize),\
  { 0 },\
}

  VKM_VEC_TEST_SUITE(vec3);
  VKM_VEC_TEST_SUITE(dvec3);

  MunitSuite suites[] = {
    {
      .prefix = "/vec3",
      .tests = vec3_tests,
      .iterations = 1000000,
    },
    {
      .prefix = "/dvec3",
      .tests = dvec3_tests,
      .iterations = 1000000,
    },
    { 0 },
  };

  const MunitSuite main_suite = {
    .prefix = "/cvkm",
    .suites = suites,
    .iterations = 1,
  };

  return munit_suite_main(&main_suite, NULL, argc, argv);
}
