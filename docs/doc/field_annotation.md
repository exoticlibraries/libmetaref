

# Field Annotation

libmetaref provides various macros to add annotation to a field. Each field annotation macro accept different types.

- [_FS](./macros.html#fs)
- [_FI](./macros.html#fi)
- [_Fl](./macros.html#fl)
- [_FF](./macros.html#ff)

## Annotation structure

```c
typedef struct annotation_struct_ {
    const size_t line_num;
    const AnnotationType type;
    const char *name;
    const char *str_value;
    int int_value;
    long long long_value;
    func_ptr_ func_ptr;
} Annotation;
```

The line_num is the line number where the annotation is declared, the type is the type of annotation it will be one of the following values:

- METAREF_ANNOTATION_STRING,
- METAREF_ANNOTATION_INT,
- METAREF_ANNOTATION_LONG,
- METAREF_ANNOTATION_FUNCTION,
- METAREF_ANNOTATION_TERMINATOR

The name is the identifier of the field, str_value is the value of the annotation if defined with _S macro, the int_value i sthe value if defined with _I, long_value when defined with the macro _L and func_ptr is the value if the annotation is a function type.

## Creating annotations

The annotation is declared in the first parameter in the FIELD macro inside the braces {}.

```c
#define __STRUCT_FILE__ "test_struct.h"
#define __STRUCT_NAME__ Test
#include <exotic/metaref.h>

STRUCT(Test,
    FIELD({
        _FS(DATABASE_column, "full_name")
        _FI(SIZE_min, 10)
        _FF(TO_STRING, fullname_to_string)
    }, char *, fullname)
)

#ifndef TEST_ANNOTATION_FUNCTION
#define TEST_ANNOTATION_FUNCTION
void *fullname_to_string(const void *test, void *arg) {
    return (void *)"Column=Full Name";
}
#endif
```

## Using the annotations at runtime

Each declared annotations can be accessed at runtime using one of the macros provided in the library. The example below check if a field has an annotation then get it value.

```c
#include <stdio.h>
#include <structs/test_struct.h>

int main(int argc, char **argv) {
    Field field = METAREF_GET_STRUCT_FIELD(Test, "fullname");
    if (METAREF_FIELD_HAS_ANNOTATION(field, "DATABASE_column")) {
        printf("Column Name: %s\n", 
                METAREF_FIELD_ANNOTATION_STR_VALUE(field, "DATABASE_column"));
    }
    if (METAREF_FIELD_HAS_ANNOTATION(field, "TO_STRING")) {
        func_ptr_ func = METAREF_FIELD_ANNOTATION_FUNC_VALUE(field, "TO_STRING");
        printf("Field to String: %s\n", func(NULL, NULL));
    }
}
```

## Iterating through the annotations 

The macro FOREACH_STRUCT_ANNOTATION can be used to iterate through all the annotations in a field:

```c
#include <stdio.h>
#include <structs/test_struct.h>

int main(int argc, char **argv) {
    Field field = METAREF_GET_STRUCT_FIELD(Test, "fullname");
    FOREACH_FIELD_ANNOTATION(field, annotation, {
        printf("Name=%s\n", annotation.name);
    })
}
```

