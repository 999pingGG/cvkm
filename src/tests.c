#include <stdint.h>

#define CVKM_FLECS_IMPLEMENTATION
#include <cvkm.h>
#include <flecs.h>
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

#define CVKM_VEC3_TEST(vec_type, scalar_type, assertion, operation, operator) static MunitResult vec_type##_##operation(\
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

#define CVKM_VEC3_SCALAR_TEST(vec_type, scalar_type, assertion, operation, operator)\
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

#define CVKM_VEC3_ALL_TESTS(vec_type, scalar_type, assertion) CVKM_VEC3_TEST(vec_type, scalar_type, assertion, add, +)\
  CVKM_VEC3_TEST(vec_type, scalar_type, assertion, sub, -)\
  CVKM_VEC3_TEST(vec_type, scalar_type, assertion, mul, *)\
  CVKM_VEC3_TEST(vec_type, scalar_type, assertion, div, /)\
  CVKM_VEC3_SCALAR_TEST(vec_type, scalar_type, assertion, mul, *)\
  CVKM_VEC3_SCALAR_TEST(vec_type, scalar_type, assertion, div, /)

CVKM_VEC3_ALL_TESTS(bvec3, int8_t, int8)
CVKM_VEC3_ALL_TESTS(ubvec3, uint8_t, uint8)
CVKM_VEC3_ALL_TESTS(svec3, int16_t, int16)
CVKM_VEC3_ALL_TESTS(usvec3, uint16_t, uint16)
CVKM_VEC3_ALL_TESTS(ivec3, int32_t, int32)
CVKM_VEC3_ALL_TESTS(uvec3, uint32_t, uint32)
CVKM_VEC3_ALL_TESTS(lvec3, int64_t, int64)
CVKM_VEC3_ALL_TESTS(ulvec3, uint64_t, uint64)
CVKM_VEC3_ALL_TESTS(vec3, float, float)
CVKM_VEC3_ALL_TESTS(dvec3, double, double)

#define CVKM_VEC3_MISC_OPERATIONS_TEST_FOR_UNSIGNED_INTS(vec_type, scalar_type, assertion) static MunitResult vec_type##_dot(\
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
}

#define CVKM_VEC3_INVERT_TEST(vec_type, scalar_type, assertion) static MunitResult vec_type##_invert(\
  const MunitParameter* params,\
  void* userdata\
) {\
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

#define CVKM_VEC3_NORMALIZE_TEST(vec_type, scalar_type) static MunitResult vec_type##_normalize(\
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

#define CVKM_VEC3_MISC_OPERATIONS_TEST_FOR_INTS(vec_type, scalar_type, assertion)\
  CVKM_VEC3_MISC_OPERATIONS_TEST_FOR_UNSIGNED_INTS(vec_type, scalar_type, assertion)\
  CVKM_VEC3_INVERT_TEST(vec_type, scalar_type, assertion)

#define CVKM_VEC3_MISC_OPERATIONS_TEST(vec_type, scalar_type, assertion)\
  CVKM_VEC3_MISC_OPERATIONS_TEST_FOR_INTS(vec_type, scalar_type, assertion)\
  CVKM_VEC3_NORMALIZE_TEST(vec_type, scalar_type)

CVKM_VEC3_MISC_OPERATIONS_TEST_FOR_INTS(bvec3, int8_t, int8)
CVKM_VEC3_MISC_OPERATIONS_TEST_FOR_UNSIGNED_INTS(ubvec3, uint8_t, uint8)
CVKM_VEC3_MISC_OPERATIONS_TEST_FOR_INTS(svec3, int16_t, int16)
CVKM_VEC3_MISC_OPERATIONS_TEST_FOR_UNSIGNED_INTS(usvec3, uint16_t, uint16)
CVKM_VEC3_MISC_OPERATIONS_TEST_FOR_INTS(ivec3, int32_t, int32)
CVKM_VEC3_MISC_OPERATIONS_TEST_FOR_UNSIGNED_INTS(uvec3, uint32_t, uint32)
CVKM_VEC3_MISC_OPERATIONS_TEST_FOR_INTS(lvec3, int64_t, int64)
CVKM_VEC3_MISC_OPERATIONS_TEST_FOR_UNSIGNED_INTS(ulvec3, uint64_t, uint64)
CVKM_VEC3_MISC_OPERATIONS_TEST(vec3, float, float)
CVKM_VEC3_MISC_OPERATIONS_TEST(dvec3, double, double)

#define CVKM_VEC3_LOGICAL_OPERATION_TEST(vec_type, scalar_type, operation, operator)\
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

#define CVKM_VEC3_LOGICAL_OPERATION_TEST_ALL(vec_type, scalar_type) \
  CVKM_VEC3_LOGICAL_OPERATION_TEST(vec_type, scalar_type, eq, ==)\
  CVKM_VEC3_LOGICAL_OPERATION_TEST(vec_type, scalar_type, lt, <)\
  CVKM_VEC3_LOGICAL_OPERATION_TEST(vec_type, scalar_type, gt, >)\
  CVKM_VEC3_LOGICAL_OPERATION_TEST(vec_type, scalar_type, le, <=)\
  CVKM_VEC3_LOGICAL_OPERATION_TEST(vec_type, scalar_type, ge, >=)

CVKM_VEC3_LOGICAL_OPERATION_TEST_ALL(bvec3, int8_t)
CVKM_VEC3_LOGICAL_OPERATION_TEST_ALL(ubvec3, uint8_t)
CVKM_VEC3_LOGICAL_OPERATION_TEST_ALL(svec3, int16_t)
CVKM_VEC3_LOGICAL_OPERATION_TEST_ALL(usvec3, uint16_t)
CVKM_VEC3_LOGICAL_OPERATION_TEST_ALL(ivec3, int32_t)
CVKM_VEC3_LOGICAL_OPERATION_TEST_ALL(uvec3, uint32_t)
CVKM_VEC3_LOGICAL_OPERATION_TEST_ALL(lvec3, int64_t)
CVKM_VEC3_LOGICAL_OPERATION_TEST_ALL(ulvec3, uint64_t)
CVKM_VEC3_LOGICAL_OPERATION_TEST_ALL(vec3, float)
CVKM_VEC3_LOGICAL_OPERATION_TEST_ALL(dvec3, double)

static void Simulate(ecs_iter_t* it) {
  Position* positions = ecs_field(it, Position, 0);
  Velocity* velocities = ecs_field(it, Velocity, 1);
  //const Mass* masses = ecs_field(it, Mass, 2);
  const Damping* dampings = ecs_field(it, Damping, 3);

  for (int i = 0; i < it->count; i++) {
    Position* position = positions + i;
    Velocity* velocity = velocities + i;
    const Damping* damping = dampings ? dampings + i : NULL;

    vkm_vec2 delta;
    vkm_mul(velocity, it->delta_time, &delta);
    vkm_add(position, &delta, position);

    vkm_add(velocity, (&(vkm_vec2){ { 0.0f, -9.81f * it->delta_time } }), velocity);

    if (damping) {
      vkm_mul(velocity, *damping, velocity);
    }
  }
}

static MunitResult flecs(const MunitParameter* params, void* userdata) {
  (void)params;
  ecs_world_t* world = userdata;

  for (int i = 0; i < 100; i++) {
    const ecs_entity_t entity = ecs_new(world);

    ecs_set(world, entity, Position, {
      .x = (float)munit_rand_double() * 100.0f,
      .y = (float)munit_rand_double() * 100.0f,
    });
    ecs_set(world, entity, Velocity, {
      .x = (float)munit_rand_double() * 10.0f,
      .y = (float)munit_rand_double() * 10.0f,
    });
    ecs_set(world, entity, Mass, { (float)munit_rand_double() * 9.0f + 1.0f });
    if (munit_rand_double() < 0.5) {
      ecs_set(world, entity, Damping, { (float)munit_rand_double() * 0.01f + 0.99f });
    }
  }

  ecs_app_run(world, &(ecs_app_desc_t){
    .target_fps = 10,
    .delta_time = 0.1f,
    .frames = 30,
    .enable_rest = true,
    .enable_stats = true,
  });

  return MUNIT_OK;
}

static void* flecs_setup(const MunitParameter params[], void* user_data) {
  (void)params;
  (void)user_data;

  ecs_world_t* world = ecs_init();

  ECS_IMPORT(world, cvkm);

  ECS_SYSTEM(world, Simulate, EcsOnUpdate,
    [inout] cvkm.Position,
    [inout] cvkm.Velocity,
    [in] cvkm.Mass,
    [in] ?cvkm.Damping
  );
  
  return world;
}

static void flecs_tear_down(void* fixture) {
  ecs_fini(fixture);
}

#define DEFINE_TEST(test_name, func) {\
  .name = test_name,\
  .test = func,\
}

int main(const int argc, char* const* argv) {
#define CVKM_VEC_TEST_SUITE_DECL_FOR_UNSIGNED_INTS(type) MunitTest type##_tests[] = {\
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
  DEFINE_TEST("/clear", type##_clear),\
  DEFINE_TEST("/eq", type##_eq),\
  DEFINE_TEST("/lt", type##_lt),\
  DEFINE_TEST("/gt", type##_gt),\
  DEFINE_TEST("/le", type##_le),\
  DEFINE_TEST("/ge", type##_ge),\
  { 0 },\
}

#define CVKM_VEC_TEST_SUITE_DECL_FOR_INTS(type) MunitTest type##_tests[] = {\
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
  DEFINE_TEST("/clear", type##_clear),\
  DEFINE_TEST("/invert", type##_invert),\
  DEFINE_TEST("/eq", type##_eq),\
  DEFINE_TEST("/lt", type##_lt),\
  DEFINE_TEST("/gt", type##_gt),\
  DEFINE_TEST("/le", type##_le),\
  DEFINE_TEST("/ge", type##_ge),\
  { 0 },\
}

#define CVKM_VEC_TEST_SUITE_DECL(type) MunitTest type##_tests[] = {\
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
  DEFINE_TEST("/normalize", type##_normalize),\
  DEFINE_TEST("/clear", type##_clear),\
  DEFINE_TEST("/invert", type##_invert),\
  DEFINE_TEST("/eq", type##_eq),\
  DEFINE_TEST("/lt", type##_lt),\
  DEFINE_TEST("/gt", type##_gt),\
  DEFINE_TEST("/le", type##_le),\
  DEFINE_TEST("/ge", type##_ge),\
  { 0 },\
}

  CVKM_VEC_TEST_SUITE_DECL_FOR_INTS(bvec3);
  CVKM_VEC_TEST_SUITE_DECL_FOR_UNSIGNED_INTS(ubvec3);
  CVKM_VEC_TEST_SUITE_DECL_FOR_INTS(svec3);
  CVKM_VEC_TEST_SUITE_DECL_FOR_UNSIGNED_INTS(usvec3);
  CVKM_VEC_TEST_SUITE_DECL_FOR_INTS(ivec3);
  CVKM_VEC_TEST_SUITE_DECL_FOR_UNSIGNED_INTS(uvec3);
  CVKM_VEC_TEST_SUITE_DECL_FOR_INTS(lvec3);
  CVKM_VEC_TEST_SUITE_DECL_FOR_UNSIGNED_INTS(ulvec3);
  CVKM_VEC_TEST_SUITE_DECL(vec3);
  CVKM_VEC_TEST_SUITE_DECL(dvec3);

  MunitTest flecs_tests[] = {
    {
      .name = "/basic-system",
      .test = flecs,
      .setup = flecs_setup,
      .tear_down = flecs_tear_down,
    },
    { 0 },
  };

#define CVKM_VEC_TEST_SUITE(type) {\
  .prefix = "/"#type,\
  .tests = type##_tests,\
  .iterations = 1000000,\
}

  MunitSuite suites[] = {
    CVKM_VEC_TEST_SUITE(bvec3),
    CVKM_VEC_TEST_SUITE(ubvec3),
    CVKM_VEC_TEST_SUITE(svec3),
    CVKM_VEC_TEST_SUITE(usvec3),
    CVKM_VEC_TEST_SUITE(ivec3),
    CVKM_VEC_TEST_SUITE(uvec3),
    CVKM_VEC_TEST_SUITE(lvec3),
    CVKM_VEC_TEST_SUITE(ulvec3),
    CVKM_VEC_TEST_SUITE(vec3),
    CVKM_VEC_TEST_SUITE(dvec3),
    CVKM_VEC_TEST_SUITE(flecs),
    { 0 },
  };

  const MunitSuite main_suite = {
    .prefix = "/cvkm",
    .suites = suites,
    .iterations = 1,
  };

  return munit_suite_main(&main_suite, NULL, argc, argv);
}
