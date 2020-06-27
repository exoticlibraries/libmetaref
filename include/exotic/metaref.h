
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

#ifndef METAREF_FIELD_STRUCT
#define METAREF_FIELD_STRUCT
typedef struct field_struct {
    char *name;
    char *type;
    void **ptr_address;
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

#define METAREF_FIELD_EXISTS(struct_name, obj, meta_name) (METAREF_##struct_name##_get_field(obj, meta_name).name != "")

#define METAREF_GET_FIELD(struct_name, obj, name) METAREF_##struct_name##_get_field(obj, name)

#define METAREF_GET_FIELDS(struct_name) METAREF_##struct_name##_fields

#define FOREACH_FIELDS(struct_name, obj, field, body) \
    for(size_t i = 0; METAREF_GET_FIELDS(struct_name)[i] != NULL; ++i) {\
        Field field = METAREF_GET_FIELD(struct_name, obj, METAREF_GET_FIELDS(struct_name)[i]);    \
        body   \
    }          \

#define METAREF_SET_FIELD(struct_name, obj, name, value)\
    *(METAREF_##struct_name##_get_field(obj, name)).ptr_address = value;

#define METAREF_SAFELY_SET_FIELD(struct_name, obj, name, value) \
    if (METAREF_FIELD_EXISTS(struct_name, obj, name)) { \
        *(METAREF_##struct_name##_get_field(obj, name)).ptr_address = value; \
    }

#define METAREF_SET_FIELD_CAST(struct_name, obj, name, type, value)\
    *((type*)(METAREF_##struct_name##_get_field(obj, name)).ptr_address) = value;
    
#endif

#define METAREF_PREPROCESSING_DONE
#undef EXOTIC_METAREF_STRUCT

#ifdef __cplusplus
}
#endif

#endif
#endif
