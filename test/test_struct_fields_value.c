/*!g++ {0} -I../../libcester/include/ -I. -I./structs -I../include/ -o out.exe; ./out.exe --cester-verbose */

#include <exotic/cester.h>
#ifndef INCLUDE_STRUCTS
#define INCLUDE_STRUCTS
#include "structs/friend_struct.h"
#include "structs/date_struct.h"
#endif

CESTER_TEST(test_struct_iterate_field, _,
    FOREACH_STRUCT_FIELD(Friend, name, {
        cester_assert_str_not_equal(name, NULL);
    })
    
    FOREACH_STRUCT_FIELD(Date, name, {
        cester_assert_str_not_equal(NULL, name);
    })
)

CESTER_TEST(test_struct_has_field, _,
    cester_assert_true(METAREF_HAS_FIELD(Friend, "name"));
    cester_assert_true(METAREF_HAS_FIELD(Friend, "picture"));
    cester_assert_false(METAREF_HAS_FIELD(Friend, "location"));
    cester_assert_true(METAREF_HAS_FIELD(Date, "day"));
    cester_assert_true(METAREF_HAS_FIELD(Date, "time"));
)

CESTER_TEST(test_struct_fields_value, _,
    Friend *padi = (Friend *) malloc(sizeof(Friend));
    
    free(padi);
)


