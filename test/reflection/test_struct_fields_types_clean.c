/*!g++ {0} -I../../libcester/include/ -I. -I./structs -I../../include/ -o out.exe; ./out.exe --cester-verbose */

#include <exotic/cester.h>
#ifndef INCLUDE_STRUCTS
#define INCLUDE_STRUCTS
#include "structs/types_struct.h"
#endif

CESTER_TEST(check_struct_field_char_array, _,
    Field field1 = METAREF_GET_STRUCT_FIELD(Types, "field1");
    cester_assert_true(METAREF_FIELD_IS_CHAR_ARRAY(field1));
    
    Field field2 = METAREF_GET_STRUCT_FIELD(Types, "field00");
    cester_assert_true(METAREF_FIELD_IS_CHAR_ARRAY(field2));
    
    Field field3 = METAREF_GET_STRUCT_FIELD(Types, "field2");
    cester_assert_false(METAREF_FIELD_IS_CHAR_ARRAY(field3));
    
    Field field4 = METAREF_GET_STRUCT_FIELD(Types, "field1");
    cester_assert_true(METAREF_FIELD_IS_CHAR_ARRAY(field4));
)

CESTER_TEST(check_struct_field_int, _,
    Field field1 = METAREF_GET_STRUCT_FIELD(Types, "field1");
    cester_assert_false(METAREF_FIELD_IS_INT(field1));
    
    Field field2 = METAREF_GET_STRUCT_FIELD(Types, "field2");
    cester_assert_true(METAREF_FIELD_IS_INT(field2));
    
    Field field3 = METAREF_GET_STRUCT_FIELD(Types, "field3");
    cester_assert_true(METAREF_FIELD_IS_INT(field3));
    
    Field field4 = METAREF_GET_STRUCT_FIELD(Types, "field4");
    cester_assert_true(METAREF_FIELD_IS_UINT(field4));
    
    Field field5 = METAREF_GET_STRUCT_FIELD(Types, "field5");
    cester_assert_true(METAREF_FIELD_IS_UINT(field5));
    
    Field field6 = METAREF_GET_STRUCT_FIELD(Types, "field6");
    cester_assert_true(METAREF_FIELD_IS_UINT(field6));
    
    Field field7 = METAREF_GET_STRUCT_FIELD(Types, "field7");
    cester_assert_true(METAREF_FIELD_IS_UINT(field7));
)

CESTER_TEST(check_struct_field_short, _,
    Field field8 = METAREF_GET_STRUCT_FIELD(Types, "field8");
    cester_assert_true(METAREF_FIELD_IS_SHORT(field8));
    
    Field field9 = METAREF_GET_STRUCT_FIELD(Types, "field9");
    cester_assert_true(METAREF_FIELD_IS_SHORT(field9));
    
    Field field11 = METAREF_GET_STRUCT_FIELD(Types, "field11");
    cester_assert_true(METAREF_FIELD_IS_SHORT(field11));
    
    Field field12 = METAREF_GET_STRUCT_FIELD(Types, "field12");
    cester_assert_true(METAREF_FIELD_IS_SHORT(field12));
    
    Field field13 = METAREF_GET_STRUCT_FIELD(Types, "field13");
    cester_assert_true(METAREF_FIELD_IS_USHORT(field13));
    
    Field field10 = METAREF_GET_STRUCT_FIELD(Types, "field10");
    cester_assert_true(METAREF_FIELD_IS_USHORT(field10));
)

CESTER_TEST(check_struct_field_long, _,
    Field field14 = METAREF_GET_STRUCT_FIELD(Types, "field14");
    cester_assert_true(METAREF_FIELD_IS_LONG(field14));
    
    Field field15 = METAREF_GET_STRUCT_FIELD(Types, "field15");
    cester_assert_true(METAREF_FIELD_IS_LONG(field15));
    
    Field field17 = METAREF_GET_STRUCT_FIELD(Types, "field17");
    cester_assert_true(METAREF_FIELD_IS_LONG(field17));
    
    Field field18 = METAREF_GET_STRUCT_FIELD(Types, "field18");
    cester_assert_true(METAREF_FIELD_IS_LONG(field18));
    
    Field field16 = METAREF_GET_STRUCT_FIELD(Types, "field16");
    cester_assert_true(METAREF_FIELD_IS_ULONG(field16));
    
    Field field19 = METAREF_GET_STRUCT_FIELD(Types, "field19");
    cester_assert_true(METAREF_FIELD_IS_ULONG(field19));
)

CESTER_TEST(check_struct_field_floating_points, _,
    Field field20 = METAREF_GET_STRUCT_FIELD(Types, "field20");
    cester_assert_true(METAREF_FIELD_IS_FLOAT(field20));
    
    Field field21 = METAREF_GET_STRUCT_FIELD(Types, "field21");
    cester_assert_true(METAREF_FIELD_IS_DOUBLE(field21));
    
    Field field22 = METAREF_GET_STRUCT_FIELD(Types, "field22");
    cester_assert_true(METAREF_FIELD_IS_LONG_DOUBLE(field22));
)

CESTER_TEST(check_struct_field_char, _,
    Field field23 = METAREF_GET_STRUCT_FIELD(Types, "field23");
    cester_assert_true(METAREF_FIELD_IS_CHAR(field23));
    
    Field field24 = METAREF_GET_STRUCT_FIELD(Types, "field24");
    cester_assert_true(METAREF_FIELD_IS_CHAR(field24));
    
    Field field25 = METAREF_GET_STRUCT_FIELD(Types, "field25");
    cester_assert_true(METAREF_FIELD_IS_UCHAR(field25));
)

CESTER_OPTIONS(
    CESTER_MINIMAL();
    CESTER_VERBOSE();
)

