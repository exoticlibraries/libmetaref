/*!gcc {0} -I../../../libcester/include/ -I. -I../reflection/structs -I../../include/ -o out.exe; ./out.exe --cester-verbose --cester-minimal */

#include <exotic/cester.h>
#include <exotic/metaref.h>
#ifndef INCLUDE_STRUCTS
#define INCLUDE_STRUCTS
#include "../reflection/structs/friend_struct.h"
#endif

CESTER_TEST(METAREF_GENERIC_FORMAT_SPECIFIER_short, _,
	short short_1 = 1;
	short int short_int_1 = -1;
	unsigned short unsigned_short_1 = 1;
	unsigned short int unsigned_short_int_1 = 1;
	unsigned int unsigned_int_1 = 1;

	cester_assert_str_equal("\%hd", METAREF_GENERIC_FORMAT_SPECIFIER(short_1));
	cester_assert_str_equal("\%hd", METAREF_GENERIC_FORMAT_SPECIFIER(short_int_1));
	cester_assert_str_equal("\%hu", METAREF_GENERIC_FORMAT_SPECIFIER(unsigned_short_1));
	cester_assert_str_equal("\%hu", METAREF_GENERIC_FORMAT_SPECIFIER(unsigned_short_int_1));
)

CESTER_TEST(METAREF_GENERIC_FORMAT_SPECIFIER_int, _,
	int int_1 = 1;
	unsigned int unsigned_int_1 = 1;

	cester_assert_str_equal("\%d", METAREF_GENERIC_FORMAT_SPECIFIER(int_1));
	cester_assert_str_equal("\%u", METAREF_GENERIC_FORMAT_SPECIFIER(unsigned_int_1));
)

CESTER_TEST(METAREF_GENERIC_FORMAT_SPECIFIER_long_int, _,
	long int long_int_1 = 1;
	signed long int signed_long_int_1 = 1;
	unsigned long int unsigned_long_int_1 = 1;

	cester_assert_str_equal("\%ld", METAREF_GENERIC_FORMAT_SPECIFIER(long_int_1));
	cester_assert_str_equal("\%ld", METAREF_GENERIC_FORMAT_SPECIFIER(signed_long_int_1));
	cester_assert_str_equal("\%lu", METAREF_GENERIC_FORMAT_SPECIFIER(unsigned_long_int_1));
)

CESTER_TEST(METAREF_GENERIC_FORMAT_SPECIFIER_long_long_int, _,
	long long int long_long_int_1 = 1;
	signed long long int signed_long_long_int_1 = 1;
	unsigned long long int unsigned_long_long_int_1 = 1;

	cester_assert_str_equal("\%lld", METAREF_GENERIC_FORMAT_SPECIFIER(long_long_int_1));
	cester_assert_str_equal("\%lld", METAREF_GENERIC_FORMAT_SPECIFIER(signed_long_long_int_1));
	cester_assert_str_equal("\%llu", METAREF_GENERIC_FORMAT_SPECIFIER(unsigned_long_long_int_1));
)

CESTER_TEST(METAREF_GENERIC_FORMAT_SPECIFIER_char, _,
	char char_1 = 'a';
	signed char signed_char_1 = 'a';
	unsigned char unsigned_char_1 = 'a';

	cester_assert_str_equal("\%c", METAREF_GENERIC_FORMAT_SPECIFIER(char_1));
	cester_assert_str_equal("\%c", METAREF_GENERIC_FORMAT_SPECIFIER(signed_char_1));
	cester_assert_str_equal("\%c", METAREF_GENERIC_FORMAT_SPECIFIER(unsigned_char_1));
)

CESTER_TEST(METAREF_GENERIC_FORMAT_SPECIFIER_float_double_long_double, _,
	float float_1 = 0.4F;
	double double_1 = 0.1;
	long double long_double_1 = 432142345.367263767;

	cester_assert_str_equal("\%f", METAREF_GENERIC_FORMAT_SPECIFIER(float_1));
	cester_assert_str_equal("\%lf", METAREF_GENERIC_FORMAT_SPECIFIER(double_1));
	cester_assert_str_equal("\%Lf", METAREF_GENERIC_FORMAT_SPECIFIER(long_double_1));
)

CESTER_TEST(METAREF_GENERIC_FORMAT_SPECIFIER_char_ptr, _,
	char *greet = "Hello World";

	cester_assert_str_equal("\%s", METAREF_GENERIC_FORMAT_SPECIFIER(greet));
)

CESTER_TEST(METAREF_GENERIC_FORMAT_SPECIFIER_void_ptr, _,
	Friend *friend = (Friend *) calloc(1, sizeof(Friend));

	cester_assert_str_equal("\%p", METAREF_GENERIC_FORMAT_SPECIFIER(friend));
	free(friend);
)

CESTER_OPTIONS(
    CESTER_MINIMAL();
    CESTER_VERBOSE_LEVEL(3);
)


