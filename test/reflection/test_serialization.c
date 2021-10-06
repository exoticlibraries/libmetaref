/*!gcc {0} -I../../libcester/include/ -I. -I./structs -I../../include/ -o out.exe; ./out.exe */

#include <exotic/cester.h>
#include <ctype.h>
#ifndef INCLUDE_STRUCTS
#define INCLUDE_STRUCTS
#include "structs/types_struct.h"
#endif

#define MEM_MAX_LEN 2000

CESTER_BODY(

int is_valid_json_string(char* char_buffer)
{
    if (char_buffer[0] == '\0') {
        return 0;
    }
    int length = 0;
    while (char_buffer[length] != '\0') {
        ++length;
    }

    if (length == 0) {
        return 0;
    }

    for (int i = 0; i < length; ++i) {
        if (!isprint((unsigned char)char_buffer[i])) {
            return 0;
        }
    }
    return 1;
}

char *struct_to_json_string_metaref(Struct *the_struct) 
{
    char *ret = (char *) "";
    cester_concat_char(&ret, '{');
    FOREACH_FIELD_INDEX(the_struct, index, field, {
        // name
        cester_concat_char(&ret, '"');
        cester_concat_str(&ret, field.name);
        cester_concat_str(&ret, "\":");
        
        // value
        if (METAREF_FIELD_VALUE_IS_NULL(field)) {
            cester_concat_str(&ret, "null");
        } else {
            if (METAREF_FIELD_IS_CHAR_ARRAY(field)) {
                cester_concat_char(&ret, '"');
                if (ret != METAREF_FIELD_VALUE_PTR(field) && is_valid_json_string((char *)METAREF_FIELD_VALUE_PTR(field)) == 1) {
                    cester_concat_str(&ret, (char *)METAREF_FIELD_VALUE_PTR(field));
                }
                cester_concat_char(&ret, '"');
                
            } else if (METAREF_FIELD_IS_INT(field)) {
                int value = *(METAREF_FIELD_VALUE_PTR_AS(int, field));
                cester_concat_int(&ret, value);
                
            } else if (METAREF_FIELD_IS_DOUBLE(field)) {
                double value = *(METAREF_FIELD_VALUE_PTR_AS(double, field));
                char tmp[30];
                cester_sprintf1(tmp, 30, "%lf", value);
                cester_concat_str(&ret, tmp);
                
            } else {
                cester_concat_str(&ret, "null");
            }
        }
        if (index != METAREF_STRUCT_FIELD_COUNT(Friend)-1) {
            cester_concat_char(&ret, ',');
        }
    })
    cester_concat_char(&ret, '}');
    return ret;
}

)

CESTER_TEST(serialize_uninitialized_fields, inst, {
    Friend *friend = calloc(1, sizeof(Friend));
    Struct *the_struct = METAREF_GET_STRUCT(Friend, friend);
    cester_assert_str_equal(struct_to_json_string_metaref(the_struct), "{\"name\":null,\"picture\":null}");
    
    METAREF_FREE_STRUCT(Friend);
    free(friend);
})

CESTER_TEST(serialize_empty_fields, inst, {
    Friend *friend = calloc(1, sizeof(Friend));
    Struct *the_struct = METAREF_GET_STRUCT(Friend, friend);
    friend->name = "";
    friend->picture = "";
    cester_assert_str_equal(struct_to_json_string_metaref(the_struct), "{\"name\":\"\",\"picture\":\"\"}");
    
    METAREF_FREE_STRUCT(Friend);
    free(friend);
})

CESTER_TEST(serialize_null_fields, inst, {
    Friend *friend = calloc(1, sizeof(Friend));
    Struct *the_struct = METAREF_GET_STRUCT(Friend, friend);
    friend->name = NULL;
    friend->picture = NULL;
    cester_assert_str_equal(struct_to_json_string_metaref(the_struct), "{\"name\":null,\"picture\":null}");
    
    METAREF_FREE_STRUCT(Friend);
    free(friend);
})

CESTER_TEST(serialize_str_fields, inst, {
    Friend *friend = calloc(1, sizeof(Friend));
    Struct *the_struct = METAREF_GET_STRUCT(Friend, friend);
    friend->name = "Bayek";
    friend->picture = "/beach/eagle.png";
    cester_assert_str_not_equal(struct_to_json_string_metaref(the_struct), "{\"name\":null,\"picture\":null}");
    
    METAREF_FREE_STRUCT(Friend);
    free(friend);
})

CESTER_TEST(serialize_null_fields_types, inst, {
    Types *types = calloc(1, sizeof(Types));
    Struct *types_struct = METAREF_GET_STRUCT(Types, types);
    types->field2 = 1;
    types->field21 = 0.3;
    cester_assert_str_not_equal(struct_to_json_string_metaref(types_struct), "{\"name\":null,\"picture\":null}");
    
    METAREF_FREE_STRUCT(Types);
    free(types);
})

CESTER_OPTIONS(
    CESTER_VERBOSE();
    CESTER_MINIMAL();
)




















