/*!gcc {0} -I../../../libcester/include/ -I. -I./structs -I../../include/ -o out.exe; ./out.exe --cester-verbose --cester-minimal */

#include <exotic/cester.h>
#include <exotic/metaref.h>

CESTER_TEST(METAREF_CONCAT, _,
	const char *hello_world = "Hello World";

    cester_assert_int_eq(20, METAREF_CONCAT(2, 0));
    cester_assert_float_eq(2.0, METAREF_CONCAT(2., 0));
    cester_assert_float_eq(2.0, METAREF_CONCAT(2, .0));
    cester_assert_long_eq(20L, METAREF_CONCAT(2, 0L));
    cester_assert_long_eq(20L, METAREF_CONCAT(20, L));
    cester_assert_str_equal(hello_world, METAREF_CONCAT(hello_, world));
    cester_assert_str_equal(hello_world, METAREF_CONCAT(hello, _world));
    cester_assert_str_equal("Hello World", METAREF_CONCAT(he, llo_world));
)

CESTER_TEST(METAREF_DOUBLE_TOKEN, _,
	const char *hellohello = "Hello World";

    cester_assert_int_eq(22, METAREF_DOUBLE_TOKEN(2));
    cester_assert_str_equal(hellohello, METAREF_DOUBLE_TOKEN(hello));
    cester_assert_str_equal("Hello World", METAREF_DOUBLE_TOKEN(hello));
)

CESTER_TEST(METAREF_DUPLICATE_VALUE, _,
    cester_assert_nothing();
)

CESTER_TEST(METAREF_DUPLICATE_VALUE_WITH_DELIMITER, _,
    cester_assert_nothing();
)

CESTER_OPTIONS(
    CESTER_MINIMAL();
    CESTER_VERBOSE_LEVEL(3);
)

