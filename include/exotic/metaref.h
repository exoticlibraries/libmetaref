
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

#ifndef EXOTIC_METAREF
#define EXOTIC_METAREF

/* Globals */

/**
    Concatenate two objects implicitly

	\param x the first token to concat with y
	\param y the second token to concat with x
*/
#define METAREF_CONCAT_IMPL(x,y ) x##y

/**
    Concatenate two objects

	\param x the first token to concat with y
	\param y the second token to concat with x
*/
#define METAREF_CONCAT(x,y) METAREF_CONCAT_IMPL(x,y)

/**
    Double two tokens by concating the token with itself

	\param token the token to double
*/
#define METAREF_DOUBLE_TOKEN(token) METAREF_CONCAT_IMPL(token,token)

/**
    Duplicate the parameter that is passed, e.g.
	`METAREF_DUPLICATE_VALUE(unsigned)` expands 
	to `unsigned unsigned`

	\param value the value to duplicate
*/
#define METAREF_DUPLICATE_VALUE(value) value value

/**
    Dupplicate the parameter that is passed with a delimeter 
	e.g. `METAREF_DUPLICATE_VALUE_WITH_DELIMITER(unsigned, :)` 
	expands to `unsigned: unsigned`

	\param value the value to duplicate
	\param delimiter the delimiter to sperate the duplicate values
*/
#define METAREF_DUPLICATE_VALUE_WITH_DELIMITER(value, delimiter) value delimiter value

/**
    Convert a token to a string literal
	e.g. `METAREF_VALUE_TO_STR(unsigned)` 
	expands to `"unsigned"`

	\param token the token to convert to string literal
*/
#define METAREF_VALUE_TO_STR(token) #token

/**
    Convert a token to a string literal, seperated by 
	the specified delimiter.
	e.g. `METAREF_VALUE_CONCAT_STR_WITH_DELIMITER(unsigned, :)` 
	expands to `unsigned : "unsigned"`

	\param token the token to convert to concat
*/
#define METAREF_VALUE_CONCAT_STR_WITH_DELIMITER(token, delimeter) token delimeter METAREF_VALUE_TO_STR(token)

/**
    Get the type of a variable, uses the C11 _Generic 
	expression to determine the variable type.

	The following types are currently recognized.
	- short
	- unsigned short
	- int
	- unsigned int
	- long int
	- unsigned long int
	- long long int
	- unsigned long long int
	- char
	- signed char
	- unsigned char
	- float
	- double
	- long double

	\param value the variable to get it type
*/
#define METAREF_GENERIC_TYPE_STR(value) _Generic(value,                     \
		METAREF_VALUE_CONCAT_STR_WITH_DELIMITER(short, :),                  \
		METAREF_VALUE_CONCAT_STR_WITH_DELIMITER(unsigned short, :),         \
		METAREF_VALUE_CONCAT_STR_WITH_DELIMITER(int, :),                    \
		METAREF_VALUE_CONCAT_STR_WITH_DELIMITER(unsigned int, :),           \
		METAREF_VALUE_CONCAT_STR_WITH_DELIMITER(long int, :),               \
		METAREF_VALUE_CONCAT_STR_WITH_DELIMITER(unsigned long int, :),      \
		METAREF_VALUE_CONCAT_STR_WITH_DELIMITER(long long int, :),          \
		METAREF_VALUE_CONCAT_STR_WITH_DELIMITER(unsigned long long int, :), \
		METAREF_VALUE_CONCAT_STR_WITH_DELIMITER(char, :),                   \
		METAREF_VALUE_CONCAT_STR_WITH_DELIMITER(signed char, :),            \
		METAREF_VALUE_CONCAT_STR_WITH_DELIMITER(unsigned char, :),          \
		METAREF_VALUE_CONCAT_STR_WITH_DELIMITER(float, :),                  \
		METAREF_VALUE_CONCAT_STR_WITH_DELIMITER(double, :),                 \
		METAREF_VALUE_CONCAT_STR_WITH_DELIMITER(long double, :),            \
		METAREF_VALUE_CONCAT_STR_WITH_DELIMITER(char *, :),                 \
		default: "void *"                                                   \
	)

/**
    Get the format specifier of a variable according 
	to type, uses the C11 _Generic expression to 
	determine the variable type.

	\param value the variable to get it format specifier
*/
#define METAREF_GENERIC_FORMAT_SPECIFIER(value) _Generic(value,  \
		short: "%hd",                                    \
		unsigned short: "%hu",                           \
		int: "%d",                                       \
		unsigned int: "%u",                              \
		long int: "%ld",                                 \
		unsigned long int: "%lu",                        \
		long long int: "%lld",                           \
		unsigned long long int: "%llu",                  \
		char: "%c",                                      \
		signed char: "%c",                               \
		unsigned char: "%c",                             \
		float: "%f",                                     \
		double: "%lf",                                   \
		long double: "%Lf",                              \
		char *: "%s",                                    \
		default: "%p"                                    \
	)

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

#ifndef METAREF_FIELD_PTR_ADDRESS_TYPE
#define METAREF_FIELD_PTR_ADDRESS_TYPE void **
#endif

#ifndef METAREF_STRUCTS_DECLARED
#define METAREF_STRUCTS_DECLARED

/**
    The function pointer for the annotation with a 
    function value instead of string. The function 
    accept a void* parameter and returns void*.
*/
typedef void *(*func_ptr_)(const void *);

typedef enum metaref_annotation_type_ {
    METAREF_ANNOTATION_STRING,
    METAREF_ANNOTATION_INT,
    METAREF_ANNOTATION_LONG,
    METAREF_ANNOTATION_FUNCTION,
    METAREF_ANNOTATION_TERMINATOR
} AnnotationType;

// TODO Use union for the multiple value instead of fields
/**
    
**/
typedef struct annotation_struct_ {
    const size_t line_num;
    const AnnotationType type;
    const char *name;
    const char *str_value;
    int int_value;
    long long long_value;
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
        FIELD({}, int, num)
        FIELD({}, char *, str)
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
        Field *num = METAREF_GET_STRUCT_FIELD(the_struct, "num");
        METAREF_SET_FIELD_CAST();
        return 0;
    }
    \endcode
*/
typedef struct field_struct_ {
    const size_t line_num;
    const char *type;                /**< The type of of the field in `char *` */
    const char *name;                /**< The identifier of of the field */
    METAREF_FIELD_PTR_ADDRESS_TYPE ptr_address;   /**< The field location in memory, dereferenced value of ptr_address can be used to set the field value */
    const Annotation annotations[10]; /**< The size of the field annotation, 10 by default */
} Field;

/**
    
*/
typedef struct metaref_struct_ {
    const char *name;
    const char *file_name;
    size_t line_num;
    const Field *fields_array;
    const Annotation *annotations_array;
} Struct;
    
/**

*/  
static unsigned metaref_str_equals(const char* arg, const char* arg1) {
    unsigned i = 0;
    if (arg == NULL || arg1 == NULL) {
        return 0;
    }
    while (1) {
        if (arg[i] == '\0' && arg1[i] == '\0') {
            break;
        }
        if (arg[i] != arg1[i]) {
            return 0;
        }
        ++i;
    }
    return 1;
}

static Annotation inline metaref_get_field_annotation(Field field, const char *name) {
    for(int _iter_index = 0; field.annotations[_iter_index].line_num != 0; ++_iter_index) {
        if (metaref_str_equals(field.annotations[_iter_index].name, name)) {
            return field.annotations[_iter_index];
        }
    }
    Annotation METAREF_sub_annotation__ = {0, METAREF_ANNOTATION_TERMINATOR, NULL, NULL, -1, -1, NULL};
    return METAREF_sub_annotation__ ;
}

static Field metaref_struct_get_field(Struct *the_struct, const char *name) {
    for(size_t i = 0; the_struct->fields_array[i].type != NULL; ++i) {
        if (metaref_str_equals(the_struct->fields_array[i].name, name)) {
            return the_struct->fields_array[i];
        }
    }
    Field METAREF_sub_fields1__ = {0, NULL, NULL, NULL, {}};
    return METAREF_sub_fields1__;
}
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
    #undef _I
    #undef _L
    #undef _F
    #undef _FS
    #undef _FI
    #undef _FL
    #undef _FF
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
        Struct *metaref_obj; \
    } struct_name;\
   
/**

*/   
#define FIELD(annotations, type_v, identifier) \
    type_v identifier;
    
/**
    Create a string value annotation for 
    a struct. 
    
    Example:
    
    \code
    _S(DATABASE_table, "user")
    STRUCT(User,
        FIELD({
            _S(JSON_value, "Name")
        }, char *, name)
    )
    \endcode
    
    \param annotation_name the name of the annotation
    \param annotation_value the string value of the annotation
*/   
#define _S(annotation_name, annotation_value)
    
/**
    Create an integer value annotation for 
    a struct. 
    
    Example:
    
    \code
    _I(SIZE_min, 1)
    _I(SIZE_max, 10)
    STRUCT(User,
        FIELD({
            _S(JSON_value, "Name")
        }, char *, name)
    )
    \endcode
    
    \param annotation_name the name of the annotation
    \param annotation_value the integer value of the annotation
*/   
#define _I(annotation_name, annotation_value)
    
/**
    Create a long value annotation for 
    a struct. 
    
    Example:
    
    \code
    _L(SIZE_min, 1)
    _L(SIZE_max, 10)
    STRUCT(User,
        FIELD({
            _S(JSON_value, "Name")
        }, char *, name)
    )
    \endcode
    
    \param annotation_name the name of the annotation
    \param annotation_value the long value of the annotation
*/   
#define _L(annotation_name, annotation_value)
    
/**
    Create a function value annotation for 
    a struct. 
    
    Example:
    
    \code
    _F(TO_STRING, user_to_string)
    STRUCT(User,
        FIELD({
            _S(JSON_value, "Name")
        }, char *, name)
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

#define _FS(annotation_name, annotation_value)
#define _FI(annotation_name, annotation_value)
#define _FL(annotation_name, annotation_value)
#define _FF(annotation_name, annotation_value)

#include __STRUCT_FILE__

/* SECOND EXAPNSION
  -------------------

  Store the annotations for the struct 
  in a static const array.
*/

#undef STRUCT
#undef FIELD
#undef _S
#undef _I
#undef _L
#undef _F
#undef _FS
#undef _FI
#undef _FL
#undef _FF

#define STRUCT(struct_name, ...)     

#define FIELD(annotations, type_v, identifier)

#define _S(annotation_name, annotation_value)\
    {__LINE__, METAREF_ANNOTATION_STRING, #annotation_name, annotation_value, -1, -1, NULL},

#define _I(annotation_name, annotation_value)\
    {__LINE__, METAREF_ANNOTATION_INT, #annotation_name, NULL, annotation_value, -1, NULL},

#define _L(annotation_name, annotation_value)\
    {__LINE__, METAREF_ANNOTATION_LONG, #annotation_name, NULL, -1, annotation_value, NULL},

#define _F(annotation_name, annotation_value)\
    {__LINE__, METAREF_ANNOTATION_FUNCTION, #annotation_name, NULL, -1, -1, annotation_value},

#define _FS(annotation_name, annotation_value)

#define _FI(annotation_name, annotation_value)

#define _FL(annotation_name, annotation_value)

#define _FF(annotation_name, annotation_value)
     
#ifdef __cplusplus
}
#endif     
const static Annotation METAREF_CONCAT(METAREF_, METAREF_CONCAT(__STRUCT_NAME__, _annotations))[] = {
#include __STRUCT_FILE__
{0, METAREF_ANNOTATION_TERMINATOR, NULL, NULL, -1, -1, NULL}
};
#ifdef __cplusplus
extern "C" {
#endif

/* THIRD EXAPNSION
  -------------------

  Store the name of each fields in the 
  struct in a static array for introspection.
*/

#undef STRUCT
#undef FIELD
#undef _S
#undef _I
#undef _L
#undef _F
#undef _FS
#undef _FI
#undef _FL
#undef _FF

#define STRUCT(struct_name, ...) \
    static Field METAREF_##struct_name##_fields[] = { \
        __VA_ARGS__ \
        {0, NULL, NULL, NULL, {}},  \
    };    
    
#define FIELD(annotations, type_v, identifier) \
    {__LINE__, #type_v, #identifier, NULL, annotations},

#define _S(annotation_name, annotation_value)

#define _I(annotation_name, annotation_value)

#define _L(annotation_name, annotation_value)

#define _F(annotation_name, annotation_value)

#define _FS(annotation_name, annotation_value)\
    {__LINE__, METAREF_ANNOTATION_STRING, #annotation_name, annotation_value, -1, -1, NULL},

#define _FI(annotation_name, annotation_value)\
    {__LINE__, METAREF_ANNOTATION_INT, #annotation_name, NULL, annotation_value, -1, NULL},

#define _FL(annotation_name, annotation_value)\
    {__LINE__, METAREF_ANNOTATION_LONG, #annotation_name, NULL, -1, annotation_value, NULL},

#define _FF(annotation_name, annotation_value)\
    {__LINE__, METAREF_ANNOTATION_FUNCTION, #annotation_name, NULL, -1, -1, annotation_value},

#include __STRUCT_FILE__

/* FOURTH EXAPNSION
  -------------------

  Store the name of each fields in the 
  struct in a static array for introspection.
*/
#undef STRUCT
#undef FIELD
#undef _S
#undef _I
#undef _L
#undef _F
#undef _FS
#undef _FI
#undef _FL
#undef _FF

#define STRUCT(struct_name, ...) \
    Annotation METAREF_##struct_name##_get_annotation(const char *name) {\
        for(size_t i = 0; METAREF_##struct_name##_annotations[i].type != METAREF_ANNOTATION_TERMINATOR; ++i) {\
            if (metaref_str_equals(METAREF_##struct_name##_annotations[i].name, name)) {\
                return METAREF_##struct_name##_annotations[i];\
            }\
        }\
        Annotation METAREF_sub_fields__ = {0, METAREF_ANNOTATION_TERMINATOR, NULL, NULL, -1, -1, NULL};\
        return METAREF_sub_fields__;\
    }\
    Field METAREF_##struct_name##_get_field_name(const char *name) {\
        for(size_t i = 0; METAREF_##struct_name##_fields[i].type != NULL; ++i) {\
            if (metaref_str_equals(METAREF_##struct_name##_fields[i].name, name)) {\
                return METAREF_##struct_name##_fields[i];\
            }\
        }\
        Field METAREF_sub_fields1__ = {0, NULL, NULL, NULL, {}};\
        return METAREF_sub_fields1__;\
    }\
    
#define FIELD(annotations, type_v, identifier)

#define _S(annotation_name, annotation_value)

#define _I(annotation_name, annotation_value)

#define _L(annotation_name, annotation_value)

#define _F(annotation_name, annotation_value)

#define _FS(annotation_name, annotation_value)

#define _FI(annotation_name, annotation_value)

#define _FL(annotation_name, annotation_value)

#define _FF(annotation_name, annotation_value)

#include __STRUCT_FILE__

/* FIFTH EXAPNSION
  -------------------

  Store the name of each fields in the 
  struct in a static array for introspection.
*/
#undef STRUCT
#undef FIELD
#undef _S
#undef _I
#undef _L
#undef _F
#undef _FS
#undef _FI
#undef _FL
#undef _FF

#define STRUCT(struct_name, ...) \
    Struct *METAREF_##struct_name##_Struct; \
    Struct *METAREF_##struct_name##_Struct_init(const struct_name *the_meta_struct) { \
        if (METAREF_##struct_name##_Struct == NULL) {\
            for(size_t i = 0; METAREF_##struct_name##_fields[i].type != NULL && the_meta_struct != NULL; ++i) {\
                Field metaref_field___ = METAREF_##struct_name##_fields[i];\
                __VA_ARGS__\
                METAREF_##struct_name##_fields[i].ptr_address = metaref_field___.ptr_address;\
            }\
            METAREF_##struct_name##_Struct = (Struct *) malloc(sizeof(Struct));\
            METAREF_##struct_name##_Struct->name = #struct_name;\
            METAREF_##struct_name##_Struct->file_name = __FILE__;\
            METAREF_##struct_name##_Struct->line_num = __LINE__;\
            METAREF_##struct_name##_Struct->fields_array = METAREF_##struct_name##_fields;\
            METAREF_##struct_name##_Struct->annotations_array = METAREF_##struct_name##_annotations;\
        }\
        return METAREF_##struct_name##_Struct;\
    }
    
#define FIELD(annotations, type_v, identifier) \
    if (metaref_str_equals(metaref_field___.name, #identifier) == 1) {\
        metaref_field___.ptr_address = (METAREF_FIELD_PTR_ADDRESS_TYPE)&the_meta_struct->identifier;\
    }

#define _S(annotation_name, annotation_value)

#define _I(annotation_name, annotation_value)

#define _L(annotation_name, annotation_value)

#define _F(annotation_name, annotation_value)

#define _FS(annotation_name, annotation_value)

#define _FI(annotation_name, annotation_value)

#define _FL(annotation_name, annotation_value)

#define _FF(annotation_name, annotation_value)

#include __STRUCT_FILE__

/* SIXTH EXAPNSION
  -------------------

  Suplement expansion templates
*/
#undef STRUCT
#undef FIELD
#undef _S
#undef _I
#undef _L
#undef _F
#undef _FS
#undef _FI
#undef _FL
#undef _FF

#define STRUCT(struct_name, ...)
    
#define FIELD(annotations, type_v, identifier)

#define _S(annotation_name, annotation_value)

#define _I(annotation_name, annotation_value)

#define _L(annotation_name, annotation_value)

#define _F(annotation_name, annotation_value)

#define _FS(annotation_name, annotation_value)

#define _FI(annotation_name, annotation_value)

#define _FL(annotation_name, annotation_value)

#define _FF(annotation_name, annotation_value)

#ifdef __STRUCT_FILE__
#include __STRUCT_FILE__
#undef __STRUCT_FILE__
#undef __STRUCT_NAME__
#endif

#ifdef METAREF_FIELD_PTR_ADDRESS_TYPE
#undef METAREF_FIELD_PTR_ADDRESS_TYPE
#endif
 
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
        FIELD({}, long, longitude)
        FIELD({}, long, latitude)
    )
    \endcode
    
    \code
    Struct my_struct = METAREF_Location_Struct_init();
    \endcode
    
    After using the object in the a code block it should be 
    freed to avoid dangling in memory. Free the object with 
    the macro `METAREF_FREE_STRUCT`.
    
    If the second parameter (struct_object) is NULL the values 
    of each fields of the struct will not be set. 
*/
#define METAREF_GET_STRUCT(struct_name, struct_object)\
    METAREF_##struct_name##_Struct_init(struct_object);
    
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
#define METAREF_STRUCT_GET_ANNOTATION(struct_name, annotation_name)\
    METAREF_##struct_name##_get_annotation(annotation_name)
    
/**
    Get a struct annotation using the annotation name

    \param struct_name the struct name (not variable name)
    \param annotation_name the annotation name (string)
*/
#define METAREF_STRUCT_GET_ANNOTATION2(struct_name, annotation_name)\
    METAREF_STRUCT_GET_ANNOTATION(struct_name, #annotation_name)
    
/**
    Check if the struct contains an annotation
    
    \param struct_name the struct name (not variable name)
    \param annotation_name the annotation name (string)
*/
#define METAREF_STRUCT_HAS_ANNOTATION(struct_name, annotation_name)\
    (METAREF_STRUCT_GET_ANNOTATION(struct_name, annotation_name).type != METAREF_ANNOTATION_TERMINATOR)
    
/**
    Check if the struct annotation type is string. 
    That is the annotation is declared using the macro 
    **_S(x,y)**
    
    \param struct_name the struct name (not variable name)
    \param annotation_name the annotation name (string)
*/
#define METAREF_STRUCT_ANNOTATION_IS_STRING(struct_name, annotation_name)\
    (METAREF_STRUCT_GET_ANNOTATION(struct_name, annotation_name).type == METAREF_ANNOTATION_STRING)
    
/**
    Get the string value of annotation declared with 
    the macro **_S(x,y)**
    
    \param struct_name the struct name (not variable name)
    \param annotation_name the annotation name (string)
*/
#define METAREF_STRUCT_ANNOTATION_STR_VALUE(struct_name, annotation_name)\
    (METAREF_STRUCT_GET_ANNOTATION(struct_name, annotation_name).type == METAREF_ANNOTATION_STRING ? \
    METAREF_STRUCT_GET_ANNOTATION(struct_name, annotation_name).str_value\
    : "")
    
/**
    Check if the struct annotation type is an integer. 
    That is the annotation is declared using the macro 
    **_I(x,y)**
    
    \param struct_name the struct name (not variable name)
    \param annotation_name the annotation name (string)
*/
#define METAREF_STRUCT_ANNOTATION_IS_INT(struct_name, annotation_name)\
    (METAREF_STRUCT_GET_ANNOTATION(struct_name, annotation_name).type == METAREF_ANNOTATION_INT)
    
/**
    Get the int value of annotation declared with 
    the macro **_I(x,y)**
    
    \param struct_name the struct name (not variable name)
    \param annotation_name the annotation name (string)
*/
#define METAREF_STRUCT_ANNOTATION_INT_VALUE(struct_name, annotation_name)\
    (METAREF_STRUCT_GET_ANNOTATION(struct_name, annotation_name).type == METAREF_ANNOTATION_INT ? \
    METAREF_STRUCT_GET_ANNOTATION(struct_name, annotation_name).int_value\
    : -1)
    
/**
    Check if the struct annotation type is long. 
    That is the annotation is declared using the macro 
    **_L(x,y)**
    
    \param struct_name the struct name (not variable name)
    \param annotation_name the annotation name (string)
*/
#define METAREF_STRUCT_ANNOTATION_IS_LONG(struct_name, annotation_name)\
    (METAREF_STRUCT_GET_ANNOTATION(struct_name, annotation_name).type == METAREF_ANNOTATION_LONG)
    
/**
    Get the long value of annotation declared with 
    the macro **_L(x,y)**
    
    \param struct_name the struct name (not variable name)
    \param annotation_name the annotation name (string)
*/
#define METAREF_STRUCT_ANNOTATION_LONG_VALUE(struct_name, annotation_name)\
    (METAREF_STRUCT_GET_ANNOTATION(struct_name, annotation_name).type == METAREF_ANNOTATION_LONG ? \
    METAREF_STRUCT_GET_ANNOTATION(struct_name, annotation_name).long_value\
    : -1)
    
/**
    Check if the struct annotation type is function. 
    That is the annotation is declared using the macro 
    **_F(x,y)**
    
    \param struct_name the struct name (not variable name)
    \param annotation_name the annotation name (string)
*/
#define METAREF_STRUCT_ANNOTATION_IS_FUNCTION(struct_name, annotation_name)\
    (METAREF_STRUCT_GET_ANNOTATION(struct_name, annotation_name).type == METAREF_ANNOTATION_FUNCTION)
    
/**
    Get the string value of annotation declared with 
    the macro **_F(x,y)**
    
    \param struct_name the struct name (not variable name)
    \param annotation_name the annotation name (string)
*/
#define METAREF_STRUCT_ANNOTATION_FUNC_VALUE(struct_name, annotation_name)\
    (METAREF_STRUCT_GET_ANNOTATION(struct_name, annotation_name).type == METAREF_ANNOTATION_FUNCTION ? \
    METAREF_STRUCT_GET_ANNOTATION(struct_name, annotation_name).func_ptr\
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
    
/**
    Iterate through all the struct annotations
    
    \param the_struct the struct object 
    \param annotation the annotation object (string)
    \param body the for loop body
*/
#define FOREACH_ANNOTATION(the_struct, annotation, body)\
    for(size_t i = 0; the_struct->annotations_array[i].type != METAREF_ANNOTATION_TERMINATOR; ++i) {\
        Annotation annotation = the_struct->annotations_array[i];    \
        body   \
    }
    
/**
    Iterate through all the struct annotation
    
    \param struct_name the struct name (not variable name)
    \param index the annotation object index (size_t)
    \param annotation the annotation object (string)
    \param body the for loop body
*/
#define FOREACH_STRUCT_ANNOTATION_INDEX(struct_name, index, annotation, body)\
    for(size_t i = 0; METAREF_##struct_name##_annotations[i].type != METAREF_ANNOTATION_TERMINATOR; ++i) {\
        size_t index = i;\
        Annotation annotation = METAREF_##struct_name##_annotations[index];    \
        body   \
    }
    
/**
    Iterate through all the struct annotation
    
    \param the_struct the struct object 
    \param index the annotation object index (size_t)
    \param annotation the annotation object (string)
    \param body the for loop body
*/
#define FOREACH_ANNOTATION_INDEX(the_struct, index, annotation, body)\
    for(size_t i = 0; the_struct->annotations_array[i].type != METAREF_ANNOTATION_TERMINATOR; ++i) {\
        size_t index = i;\
        Annotation annotation = the_struct->annotations_array[index];    \
        body   \
    }
    
/**
    Get the number of fields the struct.
    
    \param struct_name the struct name (not variable name)
*/
#define METAREF_STRUCT_FIELD_COUNT(struct_name)\
    ((sizeof(METAREF_##struct_name##_fields) / sizeof(METAREF_##struct_name##_fields[0])) - 1)
    
/**
    Get the field object using the field identifier.
    
    \param struct_name the struct name (not variable name)
    \param field_name the identifier of a field
*/
#define METAREF_GET_STRUCT_FIELD(struct_name, field_name)\
    METAREF_##struct_name##_get_field_name(field_name)
    
/**
    Check if the struct contains a field
    
    \param struct_name the struct name (not variable name)
    \param field_name the identifier of a field
*/
#define METAREF_HAS_FIELD(struct_name, field_name)\
    (METAREF_GET_STRUCT_FIELD(struct_name, field_name).type != NULL)
    
/**
    Iterate through all the struct fields
    
    \param struct_name the struct name (not variable name)
    \param field the field variable to use in the loop
    \param body the for loop body
*/
#define FOREACH_STRUCT_FIELD(struct_name, field, body)\
    for(size_t i = 0; METAREF_##struct_name##_fields[i].type != NULL; ++i) {\
        Field field = METAREF_##struct_name##_fields[i];    \
        body   \
    }
    
/**
    Iterate through all the struct fields
    
    \param struct_name the struct name (not variable name)
    \param index the index of the field in the array
    \param field the field variable to use in the loop
    \param body the for loop body
*/
#define FOREACH_STRUCT_FIELD_INDEX(struct_name, index, field, body)\
    for(size_t i = 0; METAREF_##struct_name##_fields[i].type != NULL; ++i) {\
        size_t index = i; \
        Field field = METAREF_##struct_name##_fields[index];    \
        body   \
    }
    
/**
    Check whether a field is string. 
    
    This macro is non efficient at all in determining 
    the type of the field, it simply compare the field 
    type used in declaration which might cause failure 
    if the field is declared with it type in a format 
    not taken care of. 
    
    This macro simply compare a field type with the 
    following values 
    
    - char *
    - char*
    
    You should possibly make your own rule on how fields 
    should be declared and check for possible matching 
    types.
    
    \param field the field variable to check it type
    
    \return true if the field is char *
*/
#define METAREF_FIELD_IS_CHAR_ARRAY(field)\
    (metaref_str_equals(field.type, "char *") == 1 || \
    metaref_str_equals(field.type, "char*") == 1)
    
#define METAREF_STRUCT_FIELD_IS_CHAR_ARRAY(struct_name, field_name)\
    (METAREF_FIELD_IS_CHAR_ARRAY(METAREF_GET_STRUCT_FIELD(struct_name, field_name)))
    
/**
    Check whether a field is char. 
    
    This macro is non efficient at all in determining 
    the type of the field, it simply compare the field 
    type used in declaration which might cause failure 
    if the field is declared with it type in a format 
    not taken care of. 
    
    This macro simply compare a field type with the 
    following values 
    
    - char
    - signed char
    
    You should possibly make your own rule on how fields 
    should be declared and check for possible matching 
    types.
    
    \param field the field variable to check it type
    
    \return true if the field is signed
*/
#define METAREF_FIELD_IS_CHAR(field)\
    (metaref_str_equals(field.type, "char") == 1 || \
      metaref_str_equals(field.type, "signed char") == 1)
      
#define METAREF_STRUCT_FIELD_IS_CHAR(struct_name, field_name)\
    (METAREF_FIELD_IS_CHAR(METAREF_GET_STRUCT_FIELD(struct_name, field_name)))
    
/**
    Check whether a field is unsigned char. 
    
    This macro is non efficient at all in determining 
    the type of the field, it simply compare the field 
    type used in declaration which might cause failure 
    if the field is declared with it type in a format 
    not taken care of. 
    
    This macro simply compare a field type with the 
    following values 
    
    - unsigned char
    
    You should possibly make your own rule on how fields 
    should be declared and check for possible matching 
    types.
    
    \param field the field variable to check it type
    
    \return true if the field is char
*/
#define METAREF_FIELD_IS_UCHAR(field)\
    (metaref_str_equals(field.type, "unsigned char") == 1)
    
#define METAREF_STRUCT_FIELD_IS_UCHAR(struct_name, field_name)\
    (METAREF_FIELD_IS_UCHAR(METAREF_GET_STRUCT_FIELD(struct_name, field_name)))
    
/**
    Check whether a field is int. 
    
    This macro is non efficient at all in determining 
    the type of the field, it simply compare the field 
    type used in declaration which might cause failure 
    if the field is declared with it type in a format 
    not taken care of. 
    
    This macro simply compare a field type with the 
    following values 
    
    - int
    - signed
    - signed int
    
    You should possibly make your own rule on how fields 
    should be declared and check for possible matching 
    types.
    
    \param field the field variable to check it type
    
    \return true if the field is int
*/
#define METAREF_FIELD_IS_INT(field)\
    (metaref_str_equals(field.type, "int") == 1 || \
      metaref_str_equals(field.type, "signed") == 1 || \
      metaref_str_equals(field.type, "signed int") == 1)
      
#define METAREF_STRUCT_FIELD_IS_INT(struct_name, field_name)\
    (METAREF_FIELD_IS_INT(METAREF_GET_STRUCT_FIELD(struct_name, field_name)))
    
/**
    Check whether a field is unsigned int. 
    
    This macro is non efficient at all in determining 
    the type of the field, it simply compare the field 
    type used in declaration which might cause failure 
    if the field is declared with it type in a format 
    not taken care of. 
    
    This macro simply compare a field type with the 
    following values 
    
    - unsigned int
    - unsigned
    
    You should possibly make your own rule on how fields 
    should be declared and check for possible matching 
    types.
    
    \param field the field variable to check it type
    
    \return true if the field is unsigned int
*/
#define METAREF_FIELD_IS_UINT(field)\
    (metaref_str_equals(field.type, "unsigned") == 1 || \
     metaref_str_equals(field.type, "unsigned int") == 1)
     
#define METAREF_STRUCT_FIELD_IS_UINT(struct_name, field_name)\
    (METAREF_FIELD_IS_UINT(METAREF_GET_STRUCT_FIELD(struct_name, field_name)))
    
/**
    Check whether a field is short. 
    
    This macro is non efficient at all in determining 
    the type of the field, it simply compare the field 
    type used in declaration which might cause failure 
    if the field is declared with it type in a format 
    not taken care of. 
    
    This macro simply compare a field type with the 
    following values 
    
    - short
    - short int
    - signed short
    - signed short int
    
    You should possibly make your own rule on how fields 
    should be declared and check for possible matching 
    types.
    
    \param field the field variable to check it type
    
    \return true if the field is short
*/
#define METAREF_FIELD_IS_SHORT(field)\
    (metaref_str_equals(field.type, "short") == 1 || \
      metaref_str_equals(field.type, "short int") == 1 || \
      metaref_str_equals(field.type, "signed short") == 1 || \
      metaref_str_equals(field.type, "signed short int") == 1)
      
#define METAREF_STRUCT_FIELD_IS_SHORT(struct_name, field_name)\
    (METAREF_FIELD_IS_SHORT(METAREF_GET_STRUCT_FIELD(struct_name, field_name)))
    
/**
    Check whether a field is unsigned short. 
    
    This macro is non efficient at all in determining 
    the type of the field, it simply compare the field 
    type used in declaration which might cause failure 
    if the field is declared with it type in a format 
    not taken care of. 
    
    This macro simply compare a field type with the 
    following values 
    
    - unsigned short
    - unsigned short int
    
    You should possibly make your own rule on how fields 
    should be declared and check for possible matching 
    types.
    
    \param field the field variable to check it type
    
    \return true if the field is unsigned short
*/
#define METAREF_FIELD_IS_USHORT(field)\
    (metaref_str_equals(field.type, "unsigned short") == 1 || \
     metaref_str_equals(field.type, "unsigned short int") == 1)
     
#define METAREF_STRUCT_FIELD_IS_USHORT(struct_name, field_name)\
    (METAREF_FIELD_IS_USHORT(METAREF_GET_STRUCT_FIELD(struct_name, field_name)))
    
/**
    Check whether a field is long. 
    
    This macro is non efficient at all in determining 
    the type of the field, it simply compare the field 
    type used in declaration which might cause failure 
    if the field is declared with it type in a format 
    not taken care of. 
    
    This macro simply compare a field type with the 
    following values 
    
    - long
    - short int
    - signed long
    - signed long int
    
    You should possibly make your own rule on how fields 
    should be declared and check for possible matching 
    types.
    
    \param field the field variable to check it type
    
    \return true if the field is long
*/
#define METAREF_FIELD_IS_LONG(field)\
    (metaref_str_equals(field.type,"long") == 1 || \
      metaref_str_equals(field.type,"long int") == 1 || \
      metaref_str_equals(field.type,"signed long") == 1 || \
      metaref_str_equals(field.type,"signed long int") == 1)
      
#define METAREF_STRUCT_FIELD_IS_LONG(struct_name, field_name)\
    (METAREF_FIELD_IS_LONG(METAREF_GET_STRUCT_FIELD(struct_name, field_name)))
    
/**
    Check whether a field is unsigned long. 
    
    This macro is non efficient at all in determining 
    the type of the field, it simply compare the field 
    type used in declaration which might cause failure 
    if the field is declared with it type in a format 
    not taken care of. 
    
    This macro simply compare a field type with the 
    following values 
    
    - unsigned long
    - unsigned long int
    
    You should possibly make your own rule on how fields 
    should be declared and check for possible matching 
    types.
    
    \param field the field variable to check it type
    
    \return true if the field is unsigned long
*/
#define METAREF_FIELD_IS_ULONG(field)\
    (metaref_str_equals(field.type, "unsigned long") == 1 || \
     metaref_str_equals(field.type, "unsigned long int") == 1)
     
#define METAREF_STRUCT_FIELD_IS_ULONG(struct_name, field_name)\
    (METAREF_FIELD_IS_ULONG(METAREF_GET_STRUCT_FIELD(struct_name, field_name)))
    
/**
    Check whether a field is float. 
    
    This macro is non efficient at all in determining 
    the type of the field, it simply compare the field 
    type used in declaration which might cause failure 
    if the field is declared with it type in a format 
    not taken care of. 
    
    This macro simply compare a field type with the 
    following values 
    
    - float
    
    You should possibly make your own rule on how fields 
    should be declared and check for possible matching 
    types.
    
    \param field the field variable to check it type
    
    \return true if the field is float
*/
#define METAREF_FIELD_IS_FLOAT(field)\
    (metaref_str_equals(field.type,"float") == 1)
    
#define METAREF_STRUCT_FIELD_IS_FLOAT(struct_name, field_name)\
    (METAREF_FIELD_IS_FLOAT(METAREF_GET_STRUCT_FIELD(struct_name, field_name)))
    
/**
    Check whether a field is double. 
    
    This macro is non efficient at all in determining 
    the type of the field, it simply compare the field 
    type used in declaration which might cause failure 
    if the field is declared with it type in a format 
    not taken care of. 
    
    This macro simply compare a field type with the 
    following values 
    
    - double
    
    You should possibly make your own rule on how fields 
    should be declared and check for possible matching 
    types.
    
    \param field the field variable to check it type
    
    \return true if the field is double
*/
#define METAREF_FIELD_IS_DOUBLE(field)\
    (metaref_str_equals(field.type,"double") == 1)
    
#define METAREF_STRUCT_FIELD_IS_DOUBLE(struct_name, field_name)\
    (METAREF_FIELD_IS_DOUBLE(METAREF_GET_STRUCT_FIELD(struct_name, field_name)) == 1)
    
/**
    Check whether a field is long double. 
    
    This macro is non efficient at all in determining 
    the type of the field, it simply compare the field 
    type used in declaration which might cause failure 
    if the field is declared with it type in a format 
    not taken care of. 
    
    This macro simply compare a field type with the 
    following values 
    
    - long double
    
    You should possibly make your own rule on how fields 
    should be declared and check for possible matching 
    types.
    
    \param field the field variable to check it type
    
    \return true if the field is long doubel
*/
#define METAREF_FIELD_IS_LONG_DOUBLE(field)\
    (metaref_str_equals(field.type,"long double") == 1)
    
#define METAREF_STRUCT_FIELD_IS_LONG_DOUBLE(struct_name, field_name)\
    (METAREF_FIELD_IS_LONG_DOUBLE(METAREF_GET_STRUCT_FIELD(struct_name, field_name)))
    
/**
    Get all field annotations

    \param field the field value
*/
#define METAREF_GET_FIELD_ANNOTATIONS(field) field.annotations
    
/**
    Iterate through all the field annotations
    
    \param struct_name the struct name (not variable name)
    \param field the field object to get it annotations
    \param annotation the active annotation value
    \param body the for loop body
*/
#define FOREACH_FIELD_ANNOTATION(field, annotation, body)\
    for(size_t mr_i_ = 0; field.annotations[mr_i_].line_num != 0; ++mr_i_) {\
        Annotation annotation = field.annotations[mr_i_];    \
        body   \
    }
    
/**
    Get a field annotation using the annotation name

    \param field the field object
    \param annotation_name the annotation name (string)
*/
#define METAREF_FIELD_GET_ANNOTATION(field, annotation_name)\
    metaref_get_field_annotation(field, annotation_name)
    
/**
    Get a string annotation using the annotation name

    \param field the field object
    \param annotation_name the annotation name (unquoted string)
*/
#define METAREF_FIELD_GET_ANNOTATION2(field, annotation_name)\
    METAREF_FIELD_GET_ANNOTATION(field, #annotation_name)
    
/**
    Check if the field has an annotation
    
    \param field the field object
    \param annotation_name the annotation name (string)
*/
#define METAREF_FIELD_HAS_ANNOTATION(field, annotation_name)\
    (METAREF_FIELD_GET_ANNOTATION(field, annotation_name).type != METAREF_ANNOTATION_TERMINATOR)
    
/**
    Check if the struct annotation type is string. 
    That is the annotation is declared using the macro 
    **_FS(x,y)**
    
    \param field the field object
    \param annotation_name the annotation name (string)
*/
#define METAREF_FIELD_ANNOTATION_IS_STRING(field, annotation_name)\
    (METAREF_FIELD_GET_ANNOTATION(field, annotation_name).type == METAREF_ANNOTATION_STRING)
    
/**
    Get the string value of annotation declared with 
    the macro **_FS(x,y)**
    
    \param field the field object
    \param annotation_name the annotation name (string)
*/
#define METAREF_FIELD_ANNOTATION_STR_VALUE(field, annotation_name)\
    (METAREF_FIELD_GET_ANNOTATION(field, annotation_name).type == METAREF_ANNOTATION_STRING ? \
    METAREF_FIELD_GET_ANNOTATION(field, annotation_name).str_value\
    : "")
    
/**
    Check if the struct annotation type is an integer. 
    That is the annotation is declared using the macro 
    **_FI(x,y)**
    
    \param field the field object
    \param annotation_name the annotation name (string)
*/
#define METAREF_FIELD_ANNOTATION_IS_INT(field, annotation_name)\
    (METAREF_FIELD_GET_ANNOTATION(field, annotation_name).type == METAREF_ANNOTATION_INT)
    
/**
    Get the int value of annotation declared with 
    the macro **_FI(x,y)**
    
    \param field the field object
    \param annotation_name the annotation name (string)
*/
#define METAREF_FIELD_ANNOTATION_INT_VALUE(field, annotation_name)\
    (METAREF_FIELD_GET_ANNOTATION(field, annotation_name).type == METAREF_ANNOTATION_INT ? \
    METAREF_FIELD_GET_ANNOTATION(field, annotation_name).int_value\
    : -1)
    
/**
    Check if the struct annotation type is long. 
    That is the annotation is declared using the macro 
    **_FL(x,y)**
    
    \param field the field object
    \param annotation_name the annotation name (string)
*/
#define METAREF_FIELD_ANNOTATION_IS_LONG(field, annotation_name)\
    (METAREF_FIELD_GET_ANNOTATION(field, annotation_name).type == METAREF_ANNOTATION_LONG)
    
/**
    Get the long value of annotation declared with 
    the macro **_FL(x,y)**
    
    \param field the field object
    \param annotation_name the annotation name (string)
*/
#define METAREF_FIELD_ANNOTATION_LONG_VALUE(field, annotation_name)\
    (METAREF_FIELD_GET_ANNOTATION(field, annotation_name).type == METAREF_ANNOTATION_LONG ? \
    METAREF_FIELD_GET_ANNOTATION(field, annotation_name).long_value\
    : -1)
    
/**
    Check if the struct annotation type is function. 
    That is the annotation is declared using the macro 
    **_FF(x,y)**
    
    \param field the field object
    \param annotation_name the annotation name (string)
*/
#define METAREF_FIELD_ANNOTATION_IS_FUNCTION(field, annotation_name)\
    (METAREF_FIELD_GET_ANNOTATION(field, annotation_name).type == METAREF_ANNOTATION_FUNCTION)
    
/**
    Get the string value of annotation declared with 
    the macro **_FF(x,y)**
    
    \param field the field object
    \param annotation_name the annotation name (string)
*/
#define METAREF_FIELD_ANNOTATION_FUNC_VALUE(field, annotation_name)\
    (METAREF_FIELD_GET_ANNOTATION(field, annotation_name).type == METAREF_ANNOTATION_FUNCTION ? \
    METAREF_FIELD_GET_ANNOTATION(field, annotation_name).func_ptr\
    : NULL)
    
/**
    Get an allocated struct object field using the field identifier.
    
    This returns the Field object with the ptr_address pointing to 
    the address of the field value. If the field does not exist the 
    type is null.
    
    The field ptr_address can be uncasted to get the value of the 
    returned field. Check if the field is valid first by checking 
    if it type does not equal NULL
    
    \param the_meta_struct the struct object
    \param field_name the identifier of a field
*/
#define METAREF_GET_FIELD(the_meta_struct, field_name)\
    metaref_struct_get_field(the_meta_struct, field_name)
    
/**
    Iterate through all the struct fields, the field value in 
    the iteration has the ptr_address value set. 
    
    Use this loop to get a struct field with it value
    
    \param struct_name the struct name (not variable name)
    \param obj the struct object
    \param field the field variable to use in the loop
    \param body the for loop body
*/
#define FOREACH_FIELD(struct_name, obj, field, body)\
    for(size_t i = 0; the_struct->fields_array[i].type != NULL; ++i) {\
        Field field = the_struct->fields_array[i];    \
        body   \
    }
    
/**
    Iterate through all the struct fields, the field value in 
    the iteration has the ptr_address value set. 
    
    Use this loop to get a struct field with it value
    
    \param struct_name the struct name (not variable name)
    \param obj the struct object
    \param index the index of the field in the array
    \param field the field variable to use in the loop
    \param body the for loop body
*/
#define FOREACH_FIELD_INDEX(the_struct, index, field, body)\
    for(size_t i = 0; the_struct->fields_array[i].type != NULL; ++i) {\
        size_t index = i; \
        Field field = the_struct->fields_array[index];    \
        body   \
    }

/**
    Check if the value of a field is NULL.
    
    This is useful to validate the value of a field 
    before modifying it values to prevent undefined 
    behaviours.

    \field the Field object with a valid ptr_address
*/
#define METAREF_FIELD_VALUE_IS_NULL(field)\
    (field.ptr_address == NULL || *field.ptr_address == NULL)

/**
    Uncast the pointer address of the field value, it returns 
    the value of the field as void pointer.
    
    When type casting to get actual value care is to be taken as 
    segfault can occur with wrong casting.

    \field the Field object with a valid ptr_address
*/
#define METAREF_FIELD_VALUE_PTR(field)\
    (*field.ptr_address)

/**
    Uncast the pointer address of the field value, it returns 
    the value of the field as the specified type pointer.
    
    This is most useful to type like int, long which actual 
    value is not a pointer.

    \type the type to uncast the value pointer addredd into
    \field the Field object with a valid ptr_address
*/
#define METAREF_FIELD_VALUE_PTR_AS(type, field)\
    ((type*)field.ptr_address)
    
/**
    Set the value of a field

    \field the Field object with a valid ptr_address
*/
#define METAREF_SET_FIELD_VALUE(field, value)\
    *field.ptr_address = (void*)value
    
#endif

#define METAREF_PREPROCESSING_DONE
#undef EXOTIC_METAREF_STRUCT

#ifdef __cplusplus
}
#endif

#endif
#endif
