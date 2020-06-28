
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 27 June 2020
    \file metaref.h
*/

#ifndef EXOTIC_METAREF_STRUCT
#ifdef __STRUCT_FILE__
#define EXOTIC_METAREF_STRUCT

#ifdef METAREF_PREPROCESSING_DONE
#undef METAREF_PREPROCESSING_DONE
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef METAREF_STRUCTS_DECLARED
#define METAREF_STRUCTS_DECLARED
/**

*/
typedef struct struct_struct {
    char *name;
    char *file_name;
    size_t line_num;
    char **annotations;
    Field **fields;
} Struct;

/**
    This structure for the Struct field. Each field has a 
    name, type, ptr_address and annotations. 
    
    The name and type is stored as char array (c string), 
    ptr_address is the pointer to the field location in memory 
    dereferencing it will return the field as (void*) then it can 
    be casted to it actrual type to read it value or change it 
    value. 
    
    The example below shows how ho to change the value of an 
    int field in a struct using the field name:
    
    davit_struct.h
    
    \code
    #define __STRUCT_FILE__ "davit_struct.h"
    #include <exotic/metaref.h>
    
    STRUCT(Davit, 
        FIELD(int, num)
        FIELD(char *, str)
    )
    \endcode
    
    \code
    #include "davit_struct.h"
    #include <stdlib.h>
    
    int main() {
        Davit *davit = malloc(sizeof(Davit));
        
        Struct *the_struct = METAREF_GET_STRUCT(Davit, davit);
        if (the_struct == NULL) {
            return 1;
        }
        Field *num = METAREF_GET_FIELD(the_struct, "num");
        METAREF_SET_FIELD_CAST();
        return 0;
    }
    \endcode
*/
typedef struct field_struct {
    char *name;                /**< The identifier of of the field */
    char *type;                /**< The type of of the field in `char *` */
    void **ptr_address;        /**< The field location in memory, dereferenced value of ptr_address can be used to set the field value */
    void **annotations;        /**< The array of annotations for the field. */
} Field;
#endif

// first exapnsion

/* Undef the macros for another reimport */
#ifdef STRUCT
    #undef STRUCT
    #undef FIELD
    #undef ANNOTATED_FIELD
    #undef ANNOTATION
#endif

#define STRUCT(struct_name, ...) \
    typedef struct METAREF_##struct_name { \
        __VA_ARGS__ \
    } struct_name;
    
#define FIELD(type_v, identifier) \
    type_v identifier;

// second exapnsion
#include __STRUCT_FILE__

#undef STRUCT
#undef FIELD

#define STRUCT(struct_name, ...) \
    static char *METAREF_##struct_name##_fields[] = { \
        __VA_ARGS__ \
        NULL  \
    };
    
#define FIELD(type_v, identifier) \
    #identifier,

// third exapnsion
#ifdef __STRUCT_FILE__
#include __STRUCT_FILE__
#undef __STRUCT_FILE__
#endif

#undef STRUCT
#undef FIELD

#define STRUCT(struct_name, ...) \
    Field METAREF_##struct_name##_get_field(struct_name *the_meta_struct, char *name) \
    {  \
        Field field;\
        field.name = ""; \
        field.type = "void"; \
        __VA_ARGS__ \
        return field; \
    }
    
#define FIELD(type_v, identifier) \
        if (name == #identifier) { \
            field.ptr_address = (void*)&the_meta_struct->identifier; \
            field.name = name; \
            field.type = #type_v; \
        }
 
#ifndef METAREF_HELPER_MACROS
#define METAREF_HELPER_MACROS 
// inspection helper macros

#define METAREF_CONCAT(x, y) x y

#define METAREF_GET_NAME(struct_name) METAREF_##struct_name

#define METAREF_STRUCT_FIELD_EXISTS(struct_name, obj, meta_name) (METAREF_##struct_name##_get_field(obj, meta_name).name != "")

#define METAREF_GET_STRUCT_FIELD(struct_name, obj, name) METAREF_##struct_name##_get_field(obj, name)

#define METAREF_GET_FIELD(struct, name) METAREF_get_field(struct, name)

#define METAREF_GET_FIELDS(struct_name) METAREF_##struct_name##_fields

#define FOREACH_STRUCT_FIELD(struct_name, obj, field, body) \
    for(size_t i = 0; METAREF_GET_FIELDS(struct_name)[i] != NULL; ++i) {\
        Field field = METAREF_GET_STRUCT_FIELD(struct_name, obj, METAREF_GET_FIELDS(struct_name)[i]);    \
        body   \
    }          \

#define METAREF_SET_STRUCT_FIELD(struct_name, obj, name, value)\
    *(METAREF_##struct_name##_get_field(obj, name)).ptr_address = value;

#define METAREF_SAFELY_SET_STRUCT_FIELD(struct_name, obj, name, value) \
    if (METAREF_STRUCT_FIELD_EXISTS(struct_name, obj, name)) { \
        *(METAREF_##struct_name##_get_field(obj, name)).ptr_address = value; \
    }

#define METAREF_SET_STRUCT_FIELD_CAST(struct_name, obj, name, type, value)\
    *((type*)(METAREF_##struct_name##_get_field(obj, name)).ptr_address) = value;

#define METAREF_SAFELY_SET_STRUCT_FIELD_CAST(field, type, value)\
    *((type*)field.ptr_address) = value;

#define METAREF_SET_FIELD(field, value)\
    *field.ptr_address = value;

#define METAREF_SAFELY_SET_FIELD(field, value) \
    if (field.name != NULL && field.name != "") { \
        *field.ptr_address = value; \
    }

#define METAREF_SET_FIELD_CAST(field, type, value)\
    *((type*)field.ptr_address) = value;

#define METAREF_SAFELY_SET_FIELD_CAST(field, type, value)\
    *((type*)field.ptr_address) = value;
    
#endif

#define METAREF_PREPROCESSING_DONE
#undef EXOTIC_METAREF_STRUCT

#ifdef __cplusplus
}
#endif

#endif
#endif
