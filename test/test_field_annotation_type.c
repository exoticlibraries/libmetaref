/*!g++ {0} -I../../libcester/include/ -I. -I./structs -I../include/ -o out.exe; ./out.exe --cester-verbose */

#include <exotic/cester.h>
#ifndef INCLUDE_STRUCTS
#define INCLUDE_STRUCTS
#include "structs/preference_struct.h"
#endif

CESTER_TEST(check_field_string_annotation, _,
    Field field = METAREF_GET_FIELD(Preference, "ip_address");
    cester_assert_true(METAREF_FIELD_HAS_ANNOTATION(field, "KONFIGER_value"));
    cester_assert_ptr_not_equal((void*)METAREF_FIELD_GET_ANNOTATION(field, "KONFIGER_value").name, NULL);
    cester_assert_true(METAREF_FIELD_ANNOTATION_IS_STRING(field, "KONFIGER_value"));
    cester_assert_str_equal(METAREF_FIELD_ANNOTATION_STR_VALUE(field, "KONFIGER_value"), "IpAddress");
)




