#include <check.h>
#include <unistd.h>

#include "studium/macros.h"
#include "studium/stmath.h"

/* ===========================================================================*/
/*                           Matrix and Vector Test                           */
/* ===========================================================================*/

// Helper function
static int
compare_array(const float* array, const float* expected, size_t size)
{
    size_t i;
    for(i = 0; i < size; i++)
	if(array[i] != expected[i])
	    return 1;
    return 0;
}

// Helper macro
#define assert_array_ok(arr1, expect, sz)		\
    ck_assert_int_eq(compare_array((float*)&arr1,	\
				   expect,		\
				   sz),			\
		     0)

START_TEST(test_st_2dvectors)
{
    st_vec2 v2d_1 = st_vec2_zero();
    st_vec2 v2d_2 = st_vec2_one();
    st_vec2 v2d_3 = st_vec2_new((float[2]) {8.0f, 6.0f});

    // Test 2D vector creation
    {
	const float* expect_1 = (float[2]){0.0f, 0.0f};
	const float* expect_2 = (float[2]){1.0f, 1.0f};
	const float* expect_3 = (float[2]){8.0f, 6.0f};
    
	assert_array_ok(v2d_1, expect_1, 2);
	assert_array_ok(v2d_2, expect_2, 2);
	assert_array_ok(v2d_3, expect_3, 2);
    }

    // Test 2D vector arithmetic

    // Sum
    {
	st_vec2 sum = st_vec2_sum(v2d_2, v2d_3);
	const float* expect = (float[2]){9.0f, 7.0f};
	assert_array_ok(sum, expect, 2);
    }

    // Subtract
    {
	st_vec2 sub = st_vec2_sub(v2d_2, v2d_3);
	const float* expect = (float[2]){-7.0f, -5.0f};
	assert_array_ok(sub, expect, 2);
    }

    // Negate
    {
	st_vec3 v = st_vec3_new((float[3]){5.0f, 4.0f, 7.0f});
	st_vec3 neg = st_vec3_neg(v);
	const float* expect = (float[3]){-5.0f, -4.0f, -7.0f};
	assert_array_ok(neg, expect, 3);
    }

    // Scalar multiplication
    {
	st_mat4 mat = st_mat4_identity();
	st_mat4 mult = st_mat4_scalar_mult(3.0f, &mat);
	const float* expect = (float[16]){3.0f, 0.0f, 0.0f, 0.0f,
					 0.0f, 3.0f, 0.0f, 0.0f,
					 0.0f, 0.0f, 3.0f, 0.0f,
					 0.0f, 0.0f, 0.0f, 3.0f};
	assert_array_ok(mult, expect, 16);
    }

    // Cross multiplication
    // Algorithm applies to all kinds of matrices
    {
	st_mat2 mat1, mat2;
	
	// Copy these values to the matrices
	{
	    const float* buf = (float[4]){ 1.0f, 4.0f,
					   3.0f, 3.0f  };
	    size_t i;
	    for(i = 0; i < 4; i++) {
		mat1.A[i] = mat2.A[i] = buf[i];
	    }
	}

	const float* expect = (float[4]){ 13.0f, 16.0f,
					  12.0f, 21.0f  };
	st_mat2 result = st_mat2_mult(&mat1, &mat2);
	assert_array_ok(result.A, expect, 4);
    }

    // Determinants of 4x4 matrices
    {
	st_mat4 mat;
	const float* buf = (float[16]){  1.0f, 4.0f, 2.0f, 3.0f,
					 0.0f, 1.0f, 4.0f, 4.0f,
					-1.0f, 0.0f, 1.0f, 0.0f,
					 2.0f, 0.0f, 4.0f, 1.0f };
	memcpy(mat.A, buf, sizeof(float) * 16);
	float det = st_mat4_det(&mat);
	ck_assert_float_eq(det, 65.0f);
    }

    // Invert matrix
    // TODO

    // Transpose matrix
    {
	st_mat3 mat = st_mat3_identity();
	mat.a12 = 5.0f;
	mat.a13 = 8.0f;
	st_mat3 transp = st_mat3_transpose(&mat);
	const float* expect = (float[9]){1.0f, 0.0f, 0.0f,
					 5.0f, 1.0f, 0.0f,
					 8.0f, 0.0f, 1.0f};
	assert_array_ok(transp, expect, 9);
    }

    // Sum two matrices

    // TODO: more tests
    
}
END_TEST

Suite*
vector_matrix_suite(void)
{
    Suite* s = suite_create("Vectors and Matrices");

    TCase* tc_vectors = tcase_create("Vector Operations");
    tcase_add_test(tc_vectors, test_st_2dvectors);

    suite_add_tcase(s, tc_vectors);
    return s;
}

/* ===========================================================================*/
/*                                  Test Runner                               */
/* ===========================================================================*/

int
main(void)
{
    int failed;
    SRunner* sr;
    
    sr = srunner_create(vector_matrix_suite());
    
    srunner_run_all(sr, CK_VERBOSE);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return failed;
}
