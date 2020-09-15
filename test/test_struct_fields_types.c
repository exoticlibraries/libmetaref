/*!g++ {0} -I../../libcester/include/ -I. -I./structs -I../include/ -o out.exe; ./out.exe --cester-verbose */

#include <exotic/cester.h>
#ifndef INCLUDE_STRUCTS
#define INCLUDE_STRUCTS
#include "structs/types_struct.h"
#endif

CESTER_TEST(check_struct_field_char_array, _,
    cester_assert_true(METAREF_STRUCT_FIELD_IS_CHAR_ARRAY(Types, "field1"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_CHAR_ARRAY(Types, "field00"));
    cester_assert_false(METAREF_STRUCT_FIELD_IS_CHAR_ARRAY(Types, "field2"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_CHAR_ARRAY(Types, "field1"));
)

CESTER_TEST(check_struct_field_int, _,
    cester_assert_false(METAREF_STRUCT_FIELD_IS_INT(Types, "field1"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_INT(Types, "field2"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_INT(Types, "field3"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_UINT(Types, "field4"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_UINT(Types, "field5"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_UINT(Types, "field6"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_UINT(Types, "field7"));
)

CESTER_TEST(check_struct_field_short, _,
    cester_assert_true(METAREF_STRUCT_FIELD_IS_SHORT(Types, "field8"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_SHORT(Types, "field9"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_SHORT(Types, "field11"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_SHORT(Types, "field12"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_USHORT(Types, "field13"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_USHORT(Types, "field10"));
)

CESTER_TEST(check_struct_field_long, _,
    cester_assert_true(METAREF_STRUCT_FIELD_IS_LONG(Types, "field14"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_LONG(Types, "field15"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_LONG(Types, "field17"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_LONG(Types, "field18"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_ULONG(Types, "field16"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_ULONG(Types, "field19"));
)

CESTER_TEST(check_struct_field_floating_points, _,
    cester_assert_true(METAREF_STRUCT_FIELD_IS_FLOAT(Types, "field20"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_DOUBLE(Types, "field21"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_LONG_DOUBLE(Types, "field22"));
)

CESTER_TEST(check_struct_field_char, _,
    cester_assert_true(METAREF_STRUCT_FIELD_IS_CHAR(Types, "field23"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_CHAR(Types, "field24"));
    cester_assert_true(METAREF_STRUCT_FIELD_IS_UCHAR(Types, "field25"));
)

CESTER_OPTIONS(
    CESTER_MINIMAL();
    CESTER_VERBOSE();
)

