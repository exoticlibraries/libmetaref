/*!gcc {0} -I../../libcester/include/ -I. -I./structs -I../include/ -o out.exe; ./out.exe --cester-verbose --cester-minimal */

#include <exotic/cester.h>
#ifndef INCLUDE_STRUCTS
#define INCLUDE_STRUCTS
#include "structs/user_table_struct.h"
#endif

CESTER_TEST(iterate_all_struct_annotation, _,
    FOREACH_STRUCT_ANNOTATION(User, annotation, {
        cester_assert_ptr_not_equal(NULL, (void*)annotation.name);
        cester_assert_str_not_equal(annotation.name, NULL);
    })
)

CESTER_TEST(check_struct_string_annotation, _,        
    cester_assert_true(STRUCT_HAS_ANNOTATION(User, "DATABASE_table"));
    cester_assert_ptr_not_equal((void*)STRUCT_GET_ANNOTATION(User, "DATABASE_table").name, NULL);
    cester_assert_true(STRUCT_ANNOTATION_IS_STRING(User, "DATABASE_table"));
    cester_assert_str_equal(STRUCT_ANNOTATION_STR_VALUE(User, "DATABASE_table"), "user");
    cester_assert_str_equal(STRUCT_ANNOTATION_STR_VALUE(User, "KONFIGER_file"), "#{rsc}/user.conf");
)

CESTER_TEST(check_struct_long_annotation, _,        
    cester_assert_true(STRUCT_HAS_ANNOTATION(User, "SIZE_max"));
    cester_assert_ptr_not_equal((void*)STRUCT_GET_ANNOTATION(User, "SIZE_max").name, NULL);
    cester_assert_false(STRUCT_ANNOTATION_IS_STRING(User, "SIZE_max"));
    cester_assert_true(STRUCT_ANNOTATION_IS_LONG(User, "SIZE_max"));
    cester_assert_long_eq(STRUCT_ANNOTATION_LONG_VALUE(User, "SIZE_max"), 2000);
)

CESTER_TEST(check_struct_function_annotation, _,        
    cester_assert_true(STRUCT_HAS_ANNOTATION(User, "TO_STRING"));
    cester_assert_ptr_not_equal((void*)STRUCT_GET_ANNOTATION(User, "TO_STRING").name, NULL);
    cester_assert_false(STRUCT_ANNOTATION_IS_STRING(User, "TO_STRING"));
    cester_assert_true(STRUCT_ANNOTATION_IS_FUNCTION(User, "TO_STRING"));
    char *user_str = (char *) STRUCT_ANNOTATION_FUNC_VALUE(User, "TO_STRING")(NULL);
    cester_assert_str_not_equal(user_str, "user");
    cester_assert_str_equal(user_str, "Name=libmetaref");
)


