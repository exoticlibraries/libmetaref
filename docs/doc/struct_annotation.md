

# Struct Annotation

libmetaref provides various macros to add annotation to a struct. Each struct annotation macro accept different types.

- [_S](./macros.html#s)
- [_I](./macros.html#i)
- [_l](./macros.html#l)
- [_F](./macros.html#f)

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

The name is the identifier of the annotation, str_value is the value of the annotation if defined with _S macro, the int_value i sthe value if defined with _I, long_value when defined with the macro _L and func_ptr is the value if the annotation is a function type.

## Creating annotations

The annotation is declared at the top before the struct.

```c
#define __STRUCT_FILE__ "test_struct.h"
#define __STRUCT_NAME__ Test
#include <exotic/metaref.h>

_S(DATABASE_table, "test")
_I(SIZE_min, 10)
_F(TO_STRING, test_to_string)
STRUCT(Test,
    //...
)

#ifndef TEST_ANNOTATION_FUNCTION
#define TEST_ANNOTATION_FUNCTION
void *test_to_string(const void *test, void *arg) {
    return (void *)"Name=test";
}
#endif
```

## Using the annotations at runtime

Each declared annotations can be accessed at runtime using one of the macros provided in the library. The example below check if a struct has an annotation then get it value.

```c
#include <stdio.h>
#include <structs/test_struct.h>

int main(int argc, char **argv) {
    if (METAREF_STRUCT_HAS_ANNOTATION(Test, "DATABASE_table")) {
        printf("Table Name: %s\n", 
                METAREF_STRUCT_ANNOTATION_STR_VALUE(Test, "DATABASE_table"));
    }
    if (METAREF_STRUCT_HAS_ANNOTATION(Test, "TO_STRING")) {
        func_ptr_ func = METAREF_STRUCT_ANNOTATION_FUNC_VALUE(Test, "TO_STRING");
        printf("Test to String: %s\n", func(NULL, NULL));
    }
}
```

## Iterating through the annotations 

The macro FOREACH_STRUCT_ANNOTATION can be used to iterate through all the annotations in a struct:

```c
#include <stdio.h>
#include <structs/test_struct.h>

int main(int argc, char **argv) {
    FOREACH_STRUCT_ANNOTATION(Test, annotation, {
        printf("Name=%s\n", annotation.name);
    })
}
```

