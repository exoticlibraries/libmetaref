/*!gcc {0} -I../../../libcester/include/ -I. -I../reflection/structs -I../../include/ -o out.exe; ./out.exe --cester-verbose --cester-minimal */

#include <exotic/cester.h>
#include <exotic/metaref.h>
#ifndef INCLUDE_STRUCTS
#define INCLUDE_STRUCTS
#include "../reflection/structs/friend_struct.h"
#endif

CESTER_TEST(METAREF_GENERIC_TYPE_STR_short, _,
	short short_1 = 1;
	short int short_int_1 = -1;
	unsigned short unsigned_short_1 = 1;
	unsigned short int unsigned_short_int_1 = 1;
	unsigned int unsigned_int_1 = 1;

	cester_assert_str_equal("short", METAREF_GENERIC_TYPE_STR(short_1));
	cester_assert_str_equal("short", METAREF_GENERIC_TYPE_STR(short_int_1));
	cester_assert_str_equal("unsigned short", METAREF_GENERIC_TYPE_STR(unsigned_short_1));
	cester_assert_str_equal("unsigned short", METAREF_GENERIC_TYPE_STR(unsigned_short_int_1));
)

CESTER_TEST(METAREF_GENERIC_TYPE_STR_int, _,
	int int_1 = 1;
	unsigned int unsigned_int_1 = 1;

	cester_assert_str_equal("int", METAREF_GENERIC_TYPE_STR(int_1));
	cester_assert_str_equal("unsigned int", METAREF_GENERIC_TYPE_STR(unsigned_int_1));
)

CESTER_TEST(METAREF_GENERIC_TYPE_STR_long_int, _,
	long int long_int_1 = 1;
	signed long int signed_long_int_1 = 1;
	unsigned long int unsigned_long_int_1 = 1;

	cester_assert_str_equal("long int", METAREF_GENERIC_TYPE_STR(long_int_1));
	cester_assert_str_equal("long int", METAREF_GENERIC_TYPE_STR(signed_long_int_1));
	cester_assert_str_equal("unsigned long int", METAREF_GENERIC_TYPE_STR(unsigned_long_int_1));
)

CESTER_TEST(METAREF_GENERIC_TYPE_STR_long_long_int, _,
	long long int long_long_int_1 = 1;
	signed long long int signed_long_long_int_1 = 1;
	unsigned long long int unsigned_long_long_int_1 = 1;

	cester_assert_str_equal("long long int", METAREF_GENERIC_TYPE_STR(long_long_int_1));
	cester_assert_str_equal("long long int", METAREF_GENERIC_TYPE_STR(signed_long_long_int_1));
	cester_assert_str_equal("unsigned long long int", METAREF_GENERIC_TYPE_STR(unsigned_long_long_int_1));
)

CESTER_TEST(METAREF_GENERIC_TYPE_STR_char, _,
	char char_1 = 'a';
	signed char signed_char_1 = 'a';
	unsigned char unsigned_char_1 = 'a';

	cester_assert_str_equal("char", METAREF_GENERIC_TYPE_STR(char_1));
	cester_assert_str_equal("signed char", METAREF_GENERIC_TYPE_STR(signed_char_1));
	cester_assert_str_equal("unsigned char", METAREF_GENERIC_TYPE_STR(unsigned_char_1));
)

CESTER_TEST(METAREF_GENERIC_TYPE_STR_float_double_long_double, _,
	float float_1 = 0.4F;
	double double_1 = 0.1;
	long double long_double_1 = 432142345.367263767;

	cester_assert_str_equal("float", METAREF_GENERIC_TYPE_STR(float_1));
	cester_assert_str_equal("double", METAREF_GENERIC_TYPE_STR(double_1));
	cester_assert_str_equal("long double", METAREF_GENERIC_TYPE_STR(long_double_1));
)

CESTER_TEST(METAREF_GENERIC_TYPE_STR_char_ptr, _,
	char *greet = "Hello World";

	cester_assert_str_equal("char *", METAREF_GENERIC_TYPE_STR(greet));
)

CESTER_TEST(METAREF_GENERIC_TYPE_STR_void_ptr, _,
	Friend *friend = (Friend *) calloc(1, sizeof(Friend));

	cester_assert_str_equal("void *", METAREF_GENERIC_TYPE_STR(friend));
	free(friend);
)

CESTER_OPTIONS(
    CESTER_MINIMAL();
    CESTER_VERBOSE_LEVEL(3);
)


