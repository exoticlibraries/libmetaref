/*!g++ {0} -I../../libcester/include/ -I. -I./structs -I../include/ -o out.exe; ./out.exe --cester-verbose */

#include <exotic/cester.h>
#ifndef INCLUDE_STRUCTS
#define INCLUDE_STRUCTS
#include "structs/preference_struct.h"
#endif

CESTER_TEST(iterate_all_struct_annotation, _,
    FOREACH_STRUCT_ANNOTATION(Preference, annotation, {
        cester_assert_ptr_not_equal(NULL, (void*)annotation.name);
        cester_assert_str_not_equal(annotation.name, NULL);
    })
)

