
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 27 June 2020
    \file metaref.h
*/

#ifndef EXOTIC_METAREF_STRUCT
#ifdef __STRUCT_FILE__
#define EXOTIC_METAREF_STRUCT

#ifndef __cplusplus
#ifndef __STDC_VERSION__
    #error This library is not supported in C version less than C99.
    #include <metaref_not_supported_in_standard_less_than_C99>
#endif
#endif

#ifdef __cplusplus
#if __cplusplus <= 199711L
    #error This library is not supported in C++ version less than C++11.
    #include <metaref_not_supported_in_standard_less_than_C++11>
#endif
#endif

#ifdef METAREF_PREPROCESSING_DONE
#undef METAREF_PREPROCESSING_DONE
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef METAREF_STRUCTS_DECLARED
#define METAREF_STRUCTS_DECLARED
/**

**/
typedef struct annotation_struct_ {
    char **params;
} Annotation;

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
typedef struct field_struct_ {
    const char *name;                /**< The identifier of of the field */
    const char *type;                /**< The type of of the field in `char *` */
    void **ptr_address;        /**< The field location in memory, dereferenced value of ptr_address can be used to set the field value */
    Annotation **annotations;        /**< The array of annotations for the field. */
} Field;

/**
    
*/
typedef struct struct_struct_ {
    const char *name;
    const char *file_name;
    size_t line_num;
    Annotation **annotations;
    Field **fields;
} Struct;
#endif

// first exapnsion

/* Undef the macros for another reimport */
#ifdef STRUCT
    #undef STRUCT
    #undef FIELD
    #undef ANNOTATED_FIELD
    #undef ANNOTATION
    #undef _A
#endif

/**
    Generate the structure on first macro expansion. 
    The Struct value is created, the function is also 
    implemented in a way such that the value is only 
    set once throughout the program lifetime.
*/
#define STRUCT(struct_name, ...) \
    typedef struct METAREF_##struct_name { \
        __VA_ARGS__ \
    } struct_name;\
    \
    Struct *METAREF_##struct_name##_Struct; \
    Struct *METAREF_##struct_name##_Struct_init() { \
        if (METAREF_##struct_name##_Struct == NULL) {\
            METAREF_##struct_name##_Struct = (Struct *) malloc(sizeof(Struct));\
            METAREF_##struct_name##_Struct->name = #struct_name;\
            METAREF_##struct_name##_Struct->file_name = __FILE__;\
            METAREF_##struct_name##_Struct->line_num = __LINE__;\
        }\
        return METAREF_##struct_name##_Struct;\
    }
    
/**

*/
#define FIELD(type_v, identifier) \
    type_v identifier;
    
/**

*/
#define 

// second exapnsion
#include __STRUCT_FILE__

#undef STRUCT
#undef FIELD

#define STRUCT(struct_name, ...) \
    static const char *METAREF_##struct_name##_fields[] = { \
        __VA_ARGS__ \
        NULL  \
    };\
    
    
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
            field.ptr_address = (void**)&the_meta_struct->identifier; \
            field.name = name; \
            field.type = #type_v; \
        }
 
#ifndef METAREF_HELPER_MACROS
#define METAREF_HELPER_MACROS 
// inspection helper macros

/**
    Concatenate two objects
*/
#define METAREF_CONCAT(x, y) x y

/**
    Build the name of any value for Metaref by 
    appending `METAREF_` before the value
*/
#define METAREF_GET_NAME(struct_name) METAREF_##struct_name

/**
    Initialize the `Struct *` object of the struct, calling 
    this more than once will only return the same value as 
    the object holds the structure and not value of the 
    struct. 
    
    This is equivalent to calling the method directly 
    \code
    STRUCT(Location,
        FIELD(long, longitude)
        FIELD(long, latitude)
    )
    \endcode
    
    \code
    Struct my_struct = METAREF_Location_Struct_init();
    \endcode
    
    After using the object in the a code block it should be 
    freed to avoid dangling in memory. Free the object with 
    the macro `METAREF_FREE_STRUCT`.
*/
#define METAREF_GET_STRUCT(struct_name)\
    METAREF_##struct_name##_Struct_init();
    
/**
    Destroy the `Struct *` object that is initialized 
    using the `METAREF_GET_STRUCT` macro. To get the struct 
    again use the METAREF_GET_STRUCT macro.
    
    Beyound this point try to use the object **WILL** result 
    in undefined behaviours.
*/
#define METAREF_FREE_STRUCT(struct_name)\
    if (METAREF_##struct_name##_Struct != NULL) {\
        free(METAREF_##struct_name##_Struct);\
        METAREF_##struct_name##_Struct = NULL;\
    }


// ========================


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
