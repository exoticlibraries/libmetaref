/*!g++ {0} -I../../libcester/include/ -I. -I./structs -I../include/ -o out.exe; ./out.exe --cester-verbose */

#include <exotic/cester.h>
#ifndef INCLUDE_STRUCTS
#define INCLUDE_STRUCTS
#include "structs/friend_struct.h"
#include "structs/date_struct.h"
#endif

CESTER_TEST(test_struct_direct, _,
    Struct *friend_struct = METAREF_Friend_Struct_init();
    
    cester_assert_not_null(friend_struct);
    cester_assert_str_equal(friend_struct->name, "Friend");
    cester_assert_str_not_equal(friend_struct->file_name, "");
    cester_assert_int_ne(friend_struct->line_num, 0);
    
    if (METAREF_Friend_Struct != NULL) {
        free(METAREF_Friend_Struct);
        METAREF_Friend_Struct = NULL;
    }
)

CESTER_TEST(test_struct_macro_helper, _,
    Struct *date_struct = METAREF_GET_STRUCT(Date);
    
    cester_assert_not_null(date_struct);
    cester_assert_str_equal(date_struct->name, "Date");
    cester_assert_str_not_equal(date_struct->file_name, "");
    cester_assert_int_ne(date_struct->line_num, 0);
    
    METAREF_FREE_STRUCT(Date);
)

CESTER_TEST(compare_direct_and_macro_helper, _,
    Struct *friend_struct1 = METAREF_GET_STRUCT(Friend);
    Struct *friend_struct2 = METAREF_Friend_Struct_init();
    
    cester_assert_not_null(friend_struct1);
    cester_assert_not_null(friend_struct2);
    cester_assert_ptr_equal(friend_struct1, friend_struct2);
    
    METAREF_FREE_STRUCT(Friend);
    if (METAREF_Friend_Struct != NULL) {
        free(METAREF_Friend_Struct);
        METAREF_Friend_Struct = NULL;
    }
)

CESTER_OPTIONS(
    CESTER_MINIMAL();
    CESTER_VERBOSE();
)

