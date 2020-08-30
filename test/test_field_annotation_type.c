/*!g++ {0} -I../../libcester/include/ -I. -I./structs -I../include/ -o out.exe; ./out.exe --cester-verbose */

#include <exotic/cester.h>
#ifndef INCLUDE_STRUCTS
#define INCLUDE_STRUCTS
#include "structs/preference_struct.h"
#endif

CESTER_TEST(check_field_string_annotation, _,
    Field field = METAREF_GET_STRUCT_FIELD(Preference, "ip_address");
    cester_assert_true(METAREF_FIELD_HAS_ANNOTATION(field, "KONFIGER_value"));
    cester_assert_ptr_not_equal((void*)METAREF_FIELD_GET_ANNOTATION(field, "KONFIGER_value").name, NULL);
    cester_assert_true(METAREF_FIELD_ANNOTATION_IS_STRING(field, "KONFIGER_value"));
    cester_assert_str_equal(METAREF_FIELD_ANNOTATION_STR_VALUE(field, "KONFIGER_value"), "IpAddress");
)

CESTER_TEST(check_field_string_annotation_2, _,
    Field field = METAREF_GET_STRUCT_FIELD(Preference, "google_map_link");
    cester_assert_false(METAREF_FIELD_HAS_ANNOTATION(field, "KONFIGER_value"));
    cester_assert_ptr_equal((void*)METAREF_FIELD_GET_ANNOTATION(field, "KONFIGER_value").name, NULL);
    cester_assert_false(METAREF_FIELD_ANNOTATION_IS_STRING(field, "KONFIGER_value"));
    cester_assert_str_not_equal(METAREF_FIELD_ANNOTATION_STR_VALUE(field, "KONFIGER_value"), "IpAddress");
)

CESTER_TEST(check_field_string_annotation_3, _,
    Field field = METAREF_GET_STRUCT_FIELD(Preference, "fullname");
    cester_assert_true(METAREF_FIELD_HAS_ANNOTATION(field, "KONFIGER_value"));
    cester_assert_ptr_not_equal((void*)METAREF_FIELD_GET_ANNOTATION(field, "KONFIGER_value").name, NULL);
    cester_assert_true(METAREF_FIELD_ANNOTATION_IS_STRING(field, "KONFIGER_value"));
    cester_assert_str_equal(METAREF_FIELD_ANNOTATION_STR_VALUE(field, "KONFIGER_value"), "FullName");
    
    cester_assert_true(METAREF_FIELD_HAS_ANNOTATION(field, "SIZE_msg"));
    cester_assert_ptr_not_equal((void*)METAREF_FIELD_GET_ANNOTATION(field, "SIZE_msg").name, NULL);
    cester_assert_true(METAREF_FIELD_ANNOTATION_IS_STRING(field, "SIZE_msg"));
    cester_assert_str_equal(METAREF_FIELD_ANNOTATION_STR_VALUE(field, "SIZE_msg"), "The length of the name must be between 10 and 50");
)

CESTER_TEST(check_field_int_annotation, _,
    Field field = METAREF_GET_STRUCT_FIELD(Preference, "fullname");
    cester_assert_true(METAREF_FIELD_HAS_ANNOTATION(field, "SIZE_max"));
    cester_assert_ptr_not_equal((void*)METAREF_FIELD_GET_ANNOTATION(field, "SIZE_max").name, NULL);
    cester_assert_false(METAREF_FIELD_ANNOTATION_IS_STRING(field, "SIZE_max"));
    cester_assert_true(METAREF_FIELD_ANNOTATION_IS_INT(field, "SIZE_max"));
    cester_assert_int_eq(METAREF_FIELD_ANNOTATION_INT_VALUE(field, "SIZE_max"), 150);
)

CESTER_TEST(check_field_int_annotation_2, _,
    Field field = METAREF_GET_STRUCT_FIELD(Preference, "fullname");
    cester_assert_true(METAREF_FIELD_HAS_ANNOTATION(field, "SIZE_min"));
    cester_assert_ptr_not_equal((void*)METAREF_FIELD_GET_ANNOTATION(field, "SIZE_min").name, NULL);
    cester_assert_false(METAREF_FIELD_ANNOTATION_IS_STRING(field, "SIZE_min"));
    cester_assert_true(METAREF_FIELD_ANNOTATION_IS_INT(field, "SIZE_min"));
    cester_assert_int_eq(METAREF_FIELD_ANNOTATION_INT_VALUE(field, "SIZE_min"), 10);
)

CESTER_TEST(check_field_int_annotation_cmp, _,
    Field field = METAREF_GET_STRUCT_FIELD(Preference, "fullname");
    cester_assert_true(METAREF_FIELD_HAS_ANNOTATION(field, "SIZE_max"));
    cester_assert_true(METAREF_FIELD_HAS_ANNOTATION(field, "SIZE_min"));
    int min = METAREF_FIELD_ANNOTATION_INT_VALUE(field, "SIZE_min");
    int max = METAREF_FIELD_ANNOTATION_INT_VALUE(field, "SIZE_max");
    cester_assert_int_gt(max, min);
)

CESTER_TEST(check_field_long_annotation, _,
    Field field = METAREF_GET_STRUCT_FIELD(Preference, "always_reconnect");
    cester_assert_true(METAREF_FIELD_HAS_ANNOTATION(field, "NUMBER_long"));
    cester_assert_ptr_not_equal((void*)METAREF_FIELD_GET_ANNOTATION(field, "NUMBER_long").name, NULL);
    cester_assert_false(METAREF_FIELD_ANNOTATION_IS_STRING(field, "NUMBER_long"));
    cester_assert_false(METAREF_FIELD_ANNOTATION_IS_INT(field, "NUMBER_long"));
    cester_assert_true(METAREF_FIELD_ANNOTATION_IS_LONG(field, "NUMBER_long"));
    cester_assert_llong_eq(METAREF_FIELD_ANNOTATION_LONG_VALUE(field, "NUMBER_long"), 7652653625635265);
    cester_assert_llong_gt(METAREF_FIELD_ANNOTATION_LONG_VALUE(field, "NUMBER_long"), 10);
)

CESTER_TEST(check_field_function_annotation, _,
    Field field = METAREF_GET_STRUCT_FIELD(Preference, "google_map_link");
    cester_assert_true(METAREF_FIELD_HAS_ANNOTATION(field, "URL_prefix"));
    cester_assert_ptr_not_equal((void*)METAREF_FIELD_GET_ANNOTATION(field, "URL_prefix").name, NULL);
    cester_assert_false(METAREF_FIELD_ANNOTATION_IS_STRING(field, "URL_prefix"));
    cester_assert_true(METAREF_FIELD_ANNOTATION_IS_FUNCTION(field, "URL_prefix"));
    cester_assert_str_not_equal((char *) METAREF_FIELD_ANNOTATION_FUNC_VALUE(field, "URL_prefix")(NULL), NULL);
    cester_assert_str_equal((char *) METAREF_FIELD_ANNOTATION_FUNC_VALUE(field, "URL_prefix")(NULL), "https://www.google.ng/maps/place/");
)

CESTER_OPTIONS(
    CESTER_MINIMAL();
    CESTER_VERBOSE();
)


