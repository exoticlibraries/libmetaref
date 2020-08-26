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

CESTER_TEST(iterate_annotations_raw, _,
    size_t i;
    Field ip_address_field = METAREF_GET_FIELD(Preference, "ip_address");
    cester_assert_int_ne(ip_address_field.line_num, 0);
    for(i = 0; ip_address_field.annotations[i].line_num != 0; ++i) {
        cester_assert_str_not_equal(ip_address_field.annotations[i].name, "");
    }
    
    
    Field google_map_link_field = METAREF_GET_FIELD(Preference, "google_map_link");
    cester_assert_int_ne(google_map_link_field.line_num, 0);
    for(i = 0; google_map_link_field.annotations[i].line_num != 0; ++i) {
        if (google_map_link_field.annotations[i].type == METAREF_ANNOTATION_FUNCTION) {
            cester_assert_str_not_equal(google_map_link_field.annotations[i].name, 
                                        (char *)google_map_link_field.annotations[i].func_ptr(NULL));
        }
    }
    
    Field fullname_field = METAREF_GET_FIELD(Preference, "fullname");
    cester_assert_int_ne(fullname_field.line_num, 0);
    for(i = 0; fullname_field.annotations[i].line_num != 0; ++i) {
        if (fullname_field.annotations[i].type == METAREF_ANNOTATION_STRING) {
            cester_assert_str_not_equal(fullname_field.annotations[i].name, fullname_field.annotations[i].str_value);
        } else if (fullname_field.annotations[i].type == METAREF_ANNOTATION_LONG) {
            cester_assert_long_ne(-219291, fullname_field.annotations[i].long_value);
        }
    }
)

CESTER_TEST(iterate_annotations_macro_helper, _,
    Field field1 = METAREF_GET_FIELD(Preference, "ip_address");
    FOREACH_FIELD_ANNOTATION(field1, annotation, {
        cester_assert_str_not_equal(annotation.name, "");
    })
    
    Field field2 = METAREF_GET_FIELD(Preference, "google_map_link");
    FOREACH_FIELD_ANNOTATION(field2, annotation, {
        cester_assert_str_not_equal(annotation.name, "");
    })
    
    Field field3 = METAREF_GET_FIELD(Preference, "fullname");
    FOREACH_FIELD_ANNOTATION(field3, annotation, {
        cester_assert_str_not_equal(annotation.name, "");
    })
)




