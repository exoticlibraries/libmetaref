
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 27 June 2020
    \file metaref.h
*/

/**
    The counter that manages the index 
    of a struct in the annotation array.
*/
#ifndef __COUNTER__
    #error This library is not supported with this compiler. Use any compiler with __COUNTER__ macro declared
    #include <metaref_not_supported_with_no___COUNTER__>
#endif

#ifndef EXOTIC_METAREF_STRUCT
#ifdef __STRUCT_FILE__
#ifndef __STRUCT_NAME__
    #error You need to declare the struct name value before including metaref.h
#endif
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
    Concatenate two objects implicitly
*/
#define METAREF_CONCAT_IMPL(x,y ) x##y

/**
    Concatenate two objects
*/
#define METAREF_CONCAT(x,y) METAREF_CONCAT_IMPL(x,y)

/**
    The function pointer for the annotation with a 
    function value instead of string. The function 
    accept a void* parameter and returns void*.
*/
typedef void *(*func_ptr_)(void *);

typedef enum metaref_annoptation_type_ {
    METAREF_ANNOTATION_STRING,
    METAREF_ANNOTATION_FUNCTION,
    METAREF_ANNOTATION_TERMINATOR
} AnnotationType;

/**
    
**/
typedef struct annotation_struct_ {
    const size_t line_num;
    const AnnotationType type;
    const char *name;
    const void *str_value;
    func_ptr_ func_ptr;
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
} Field;

/**
    
*/
typedef struct struct_struct_ {
    const char *name;
    const char *file_name;
    size_t line_num;
} Struct;
#endif

/* FIRST EXAPNSION
  -------------------

  Declare the struct meta fields for 
  introspection.
*/
#ifdef STRUCT
    #undef STRUCT
    #undef FIELD
    #undef _S
    #undef _F
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
    Create a string value annotation for 
    a struct. 
    
    Example:
    
    \code
    _S(DATABASE_table, "user")
    STRUCT(User,
        FIELD(char *, name)
    )
    \endcode
    
    \param annotation_name the name of the annotation
    \param annotation_value the string value of the annotation
*/   
#define _S(annotation_name, annotation_value)
    
/**
    Create a function value annotation for 
    a struct. 
    
    Example:
    
    \code
    _F(TO_STRING, user_to_string)
    STRUCT(User,
        FIELD(char *, name)
    )
    
    #ifndef _DCLR
    #define _DCLR
    void *user_to_string(User *user) {
        return "Name=libmetaref";
    }
    #endif
    \endcode
    
    \param annotation_name the name of the annotation
    \param annotation_value the string value of the annotation
*/   
#define _F(annotation_name, annotation_value)

#include __STRUCT_FILE__

/* SECOND EXAPNSION
  -------------------

  Store the annotations for the struct 
  in a static const array.
*/

#undef STRUCT
#undef FIELD
#undef _S
#undef _F

#define STRUCT(struct_name, ...)     

#define FIELD(type_v, identifier)

#define _S(annotation_name, annotation_value)\
        {__LINE__, METAREF_ANNOTATION_STRING, #annotation_name, annotation_value, NULL},

#define _F(annotation_name, annotation_value)\
        {__LINE__, METAREF_ANNOTATION_FUNCTION, #annotation_name, NULL, annotation_value},
        
const static Annotation METAREF_CONCAT(METAREF_, METAREF_CONCAT(__STRUCT_NAME__, _annotations))[] = {
#include __STRUCT_FILE__
{0, METAREF_ANNOTATION_TERMINATOR, NULL, NULL, NULL}
};

/* THIRD EXAPNSION
  -------------------

  Store the name of each fields in the 
  struct in a static array for introspection.
*/
#undef STRUCT
#undef FIELD
#undef _S
#undef _F

#define STRUCT(struct_name, ...) \
    Annotation METAREF_##struct_name##_get_annotation(const char *name) {\
        for(size_t i = 0; METAREF_##struct_name##_annotations[i].type != METAREF_ANNOTATION_TERMINATOR; ++i) {\
            if (METAREF_##struct_name##_annotations[i].name == name) {\
                return METAREF_##struct_name##_annotations[i];\
            }\
        }\
        Annotation METAREF_sub_fields__ = {0, METAREF_ANNOTATION_TERMINATOR, NULL, NULL, NULL};\
        return METAREF_sub_fields__;\
    }\
    
#define FIELD(type_v, identifier)

#define _S(annotation_name, annotation_value)

#define _F(annotation_name, annotation_value)

#include __STRUCT_FILE__

/* FOURTH EXAPNSION
  -------------------

  Store the name of each fields in the 
  struct in a static array for introspection.
*/

#undef STRUCT
#undef FIELD
#undef _S
#undef _F

#define STRUCT(struct_name, ...) \
    const static char *METAREF_##struct_name##_fields[] = { \
        __VA_ARGS__ \
        NULL  \
    };\
    
    
#define FIELD(type_v, identifier) \
    #identifier,

#define _S(annotation_name, annotation_value)

#define _F(annotation_name, annotation_value)

#ifdef __STRUCT_FILE__
#include __STRUCT_FILE__
#undef __STRUCT_FILE__
#undef __STRUCT_NAME__
#endif

/* FINAL EXAPNSION
  -------------------

  Store the name of each fields in the 
  struct in a static array for introspection.
*/
#undef STRUCT
#undef FIELD
#undef _S
#undef _F

#define STRUCT(struct_name, ...) \
    Field METAREF_##struct_name##_get_field(const struct_name *the_meta_struct, const char *name) \
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

#define _S(annotation_name, annotation_value)

#define _F(annotation_name, annotation_value)
 
#ifndef METAREF_HELPER_MACROS
#define METAREF_HELPER_MACROS 

/* inspection helper macros */

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
    
/**
    Get a struct annotation using the annotation name

    \param struct_name the struct name (not variable name)
    \param annotation_name the annotation name (string)
*/
#define STRUCT_GET_ANNOTATION(struct_name, annotation_name)\
    METAREF_##struct_name##_get_annotation(annotation_name)
    
/**
    Check if the struct contains an annotation
    
    \param struct_name the struct name (not variable name)
    \param annotation_name the annotation name (string)
*/
#define STRUCT_HAS_ANNOTATION(struct_name, annotation_name)\
    (STRUCT_GET_ANNOTATION(struct_name, annotation_name).type != METAREF_ANNOTATION_TERMINATOR)
    
/**
    Check if the struct annotation type is string. 
    That is the annotation is declared using the macro 
    **_S(x,y)**
    
    \param struct_name the struct name (not variable name)
    \param annotation_name the annotation name (string)
*/
#define STRUCT_ANNOTATION_IS_STRING(struct_name, annotation_name)\
    (STRUCT_GET_ANNOTATION(struct_name, annotation_name).type == METAREF_ANNOTATION_STRING)
    
/**
    Get the string value of annotation declared with 
    the macro **_S(x,y)**
    
    \param struct_name the struct name (not variable name)
    \param annotation_name the annotation name (string)
*/
#define STRUCT_ANNOTATION_STR_VALUE(struct_name, annotation_name)\
    (STRUCT_GET_ANNOTATION(struct_name, annotation_name).type == METAREF_ANNOTATION_STRING ? \
    STRUCT_GET_ANNOTATION(struct_name, annotation_name).str_value\
    : NULL)
    
/**
    Check if the struct annotation type is function. 
    That is the annotation is declared using the macro 
    **_F(x,y)**
    
    \param struct_name the struct name (not variable name)
    \param annotation_name the annotation name (string)
*/
#define STRUCT_ANNOTATION_IS_FUNCTION(struct_name, annotation_name)\
    (STRUCT_GET_ANNOTATION(struct_name, annotation_name).type == METAREF_ANNOTATION_FUNCTION)
    
/**
    Get the string value of annotation declared with 
    the macro **_F(x,y)**
    
    \param struct_name the struct name (not variable name)
    \param annotation_name the annotation name (string)
*/
#define STRUCT_ANNOTATION_FUNC_VALUE(struct_name, annotation_name)\
    (STRUCT_GET_ANNOTATION(struct_name, annotation_name).type == METAREF_ANNOTATION_FUNCTION ? \
    STRUCT_GET_ANNOTATION(struct_name, annotation_name).func_ptr\
    : NULL)
    
/**
    Iterate through all the struct annotation
    
    \param struct_name the struct name (not variable name)
    \param annotation the annotation object (string)
    \param body the for loop body
*/
#define FOREACH_STRUCT_ANNOTATION(struct_name, annotation, body)\
    for(size_t i = 0; METAREF_##struct_name##_annotations[i].type != METAREF_ANNOTATION_TERMINATOR; ++i) {\
        Annotation annotation = METAREF_##struct_name##_annotations[i];    \
        body   \
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
