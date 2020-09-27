

# Macros

Most macros in the library starts with `METAREF_`.

## METAREF_FIELD_PTR_ADDRESS_TYPE

The macro declares the type in which the address to the field value pointer is cast to, the default value is `void **`. 

The value can be overriden by declaring the macro before including metaref.h in the source. E.g. to change the type to size_t

```c
#define METAREF_FIELD_PTR_ADDRESS_TYPE size_t **
```

##  STRUCT

The macro is used to create a struct. This macro is important for libmetaref to expand a struct and create all the neccesary functions and fields needed for annotations and reflection at runtime. 

The first parameter is the name of the struct which should also be defined at the top of the struct file as `__STRUCT_NAME__`, the following parameter is variadic which accept the [FIELD](#field) macros. The example below illustrate how C struct is traditionally created and how to use the STRUCT macro to create a C struct.

Regular

```c
typedef struct date_struct {
    //...
} Date;
```

Using libmetaref

```c
STRUCT(Date, 
    //...
)
```

The libmetaref method above will generate the Regular struct at the macro expansion phases and add all the required functions and fields needed for runtime reflection.

## FIELD

The field macro is used to create struct fields with support for annotation and reflection. The first parameter is the list of annotation for the field see [field annotations](./field_annotation.html) for documentation of creating field annotations, the second parameter is the field type, `char *`, int, e.t.c. the third parameter is the field identifier. 

Regular

```c
typedef struct date_struct {
    unsigned hours;
    unsigned minutes;
    unsigned seconds;
    char *day_of_the_week;
    char *month_of_the_year;
} Date;
```

Using libmetaref

```c
STRUCT(Date, 
    FIELD({}, unsigned, hours)
    FIELD({}, unsigned, minutes)
    FIELD({}, unsigned, seconds)
    FIELD({}, char *, day_of_the_week)
    FIELD({}, char *, month_of_the_year)
)
```

The annotation still generates the regular valid struct field during the macro expansion phase.

## _S

Use the macro to add char array type annotation to a struct.

```c
_S(DATABASE_table, "date")
STRUCT(Date, 
    //...
)
```

## _I

Use the macro to add int type annotation to a struct.

```c
_I(FIELD_count, 1)
STRUCT(Date, 
    //...
)
```

## _L

Use the macro to add long type annotation to a struct.

```c
_L(DEFAULT_number, 764763746734673674)
STRUCT(Date, 
    //...
)
```

## _F

Use the macro to add a function type annotation to a struct. The function must be declared at the source global scope, it can be before or after the struct.

The function signature is:

```c
typedef void *(*func_ptr_)(const void *, void *)
```

Example:

```c
_F(TO_STRING, date_to_string)
STRUCT(Date, 
    //...
)

#ifndef DATE_ANNOTATION_FUNCTIONS
#define DATE_ANNOTATION_FUNCTIONS
void *date_to_string(const void *date, void *arg) {
    Date *date = (Date *)date;
    return (void *)"Name=libmetaref";
}
#endif
```

## _FS

Use the macro to add char array type annotation to a struct field.

```c
STRUCT(Date, 
    FIELD({
        _FS(CERXOS_value, "day_of_week")
    }, char *, week_day)
)
```

## _FI

Use the macro to add int type annotation to a struct field.

```c
STRUCT(Date, 
    STRUCT(Date, 
    FIELD({
        _FI(CERXOS_read, 0)
    }, char *, week_day)
)
```

## _FL

Use the macro to add long type annotation to a struct field.

```c
STRUCT(Date, 
    STRUCT(Date, 
    FIELD({
        _FL(RANDOM_number, 7612766523656256)
    }, char *, week_day)
)
```

## _FF

Use the macro to add a function type annotation to a struct field. The function must be declared at the source global scope, it can be before or after the struct.

The function signature is:

```c
typedef void *(*func_ptr_)(const void *, void *)
```

Example:

```c
STRUCT(Date, 
    STRUCT(Date, 
    FIELD({
        _FF(PROPERTY_get, get_week_day)
        _FF(PROPERTY_set, set_week_day)
    }, char *, week_day)
)

#ifndef DATE_ANNOTATION_FUNCTIONS
#define DATE_ANNOTATION_FUNCTIONS
void *get_week_day(const void *date, void *arg) {
    return (void *)((Date *)date)->week_day;
}
void *set_week_day(const void *date, void *arg) {
    ((Date *)date)->week_day = arg;
    return NULL;
}
#endif
```

## METAREF_GET_NAME

Get the name of the struct used internally by libmetaref. `METAREF_GET_NAME(Date)` result to `METAREF_Date`

## METAREF_GET_OBJECT

Get the Struct object for a struct, if it null that means it has not been initialized of it has been freed.. `METAREF_GET_OBJECT(Date)` result to `METAREF_Date_Struct`. Do not attempt to use the result directly to prevent isses in case libmetaref internals changes.

## METAREF_GET_STRUCT

Get the `Struct` object of the struct for reflection. This requires the struct name and the defined struct variable. 

```c
Date *my_date = calloc(1, sizeof(Date));
Struct *date_struct = METAREF_GET_STRUCT(Date, my_date);
```

The `date_struct` can be used for the reflection as it contains all the Struct metadatas, annotations, fields e.t.c.

This macro internally make a call to a function created at expansion phase that set a global variable for the struct. Calling the macro multiple time will not keep allocating memory for the global variable. You can call the METAREF_FREE_STRUCT macro to fee the memory allocated to that struct global variable after the struct usage is complete.

## METAREF_FREE_STRUCT

Free the memory allocated to a struct internal global variable which was allocated on the macro call `METAREF_GET_STRUCT`.

```c
Date *my_date = calloc(1, sizeof(Date));
Struct *date_struct = METAREF_GET_STRUCT(Date, my_date);
//...
METAREF_FREE_STRUCT(date_struct);
```

It good practice to indicate at the end of the scope that the Struct object has been freed so it can be reinitialized if it to be used after that scope. 

```c
bool my_custom_serializer(Date *my_date) {
    if (my_date == NULL) {
        return FALSE;
    }
    
    Struct *date_struct = METAREF_GET_STRUCT(Date, my_date);
    //...
    METAREF_FREE_STRUCT(Date);
    return TRUE;
}

```

After that function call if it returns TRUE that means the logic was complete and the Struct object was freed.

## METAREF_STRUCT_GET_ANNOTATION

Get a struct annotation by struct and the annotation name `METAREF_STRUCT_GET_ANNOTATION(Date, "DATABASE_table")`.

## METAREF_STRUCT_GET_ANNOTATION2 

Get a struct annotation by struct and the annotation name without quote `METAREF_STRUCT_GET_ANNOTATION2(Date, DATABASE_table)`.

## METAREF_STRUCT_HAS_ANNOTATION

Check if a struct has an annotation before getting it. `METAREF_STRUCT_GET_ANNOTATION(Date, "DATABASE_table")`, return 1 if the annotation exists and 0 if it does not exists.

## METAREF_STRUCT_ANNOTATION_IS_STRING

Check if the type of the annotation is char array, if the annotation is defined with the macro [_S](#s) it returns 1 else 0.

## METAREF_STRUCT_ANNOTATION_STR_VALUE

Get the char array value of a struct annotation declared with the [_S](#s) macro, `METAREF_STRUCT_ANNOTATION_STR_VALUE(Date, "DATABASE_table")`.

## METAREF_STRUCT_ANNOTATION_IS_INT

Check if the type of the annotation is an integer, if the annotation is defined with the macro [_I](#i) it returns 1 else 0.

## METAREF_STRUCT_ANNOTATION_INT_VALUE

Get the char array value of a struct annotation declared with the [_I](#i) macro, `METAREF_STRUCT_ANNOTATION_INT_VALUE(Date, "FIELD_count")`.

## METAREF_STRUCT_ANNOTATION_IS_LONG

Check if the type of the annotation is a long, if the annotation is defined with the macro [_L](#l) it returns 1 else 0.

## METAREF_STRUCT_ANNOTATION_LONG_VALUE

Get the char array value of a struct annotation declared with the [_L](#l) macro, `METAREF_STRUCT_ANNOTATION_LONG_VALUE(Date, "DEFAULT_number")`.

## METAREF_STRUCT_ANNOTATION_IS_FUNCTION

Check if the type of the annotation is a function, if the annotation is defined with the macro [_F](#f) it returns 1 else 0.

## METAREF_STRUCT_ANNOTATION_FUNC_VALUE

Get the char array value of a struct annotation declared with the [_F](#f) macro, `METAREF_STRUCT_ANNOTATION_FUNC_VALUE(Date, "TO_STRING")`.

## FOREACH_STRUCT_ANNOTATION

Iterate through all the annotation of a struct object. The first parameter is the struct name, the second parameter is the annotation variable, followed by the loop body.

```c
FOREACH_STRUCT_ANNOTATION(Date, annotation, {
    printf("Name=%s\n", annotation.name);
    //...
})
```

## FOREACH_STRUCT_ANNOTATION_INDEX

Iterate through all the annotation of a struct object. The first parameter is the struct name, the second parameter is the current index of the annotation in the iteration, the third parameter is the annotation variable, followed by the loop body.

```c
FOREACH_STRUCT_ANNOTATION_INDEX(Date, index, annotation, {
    printf("Name=%s, At=%d\n", annotation.name, index);
    //...
})
```

## FOREACH_ANNOTATION

Iterate through all the annotation of a struct object. The first parameter is the Struct object of the struct, the second parameter is the annotation variable, followed by the loop body.

```c
Struct *date_struct = METAREF_GET_STRUCT(Date, NULL);
FOREACH_ANNOTATION(date_struct, annotation, {
    printf("Name=%s\n", annotation.name);
    //...
})
METAREF_FREE_STRUCT(Date);
```

## FOREACH_ANNOTATION_INDEX

Iterate through all the annotation of a struct object. The first parameter is the Struct value of the struct, the second parameter is the current index of the annotation in the iteration, the third parameter is the annotation variable, followed by the loop body.

```c
Struct *date_struct = METAREF_GET_STRUCT(Date, NULL);
FOREACH_ANNOTATION_INDEX(date_struct, index, annotation, {
    printf("Name=%s, At=%d\n", annotation.name, index);
    //...
})
METAREF_FREE_STRUCT(Date);
```

## METAREF_STRUCT_FIELD_COUNT

Get the number of fields in the struct `METAREF_STRUCT_FIELD_COUNT(Date)`.

## METAREF_GET_STRUCT_FIELD

Get a field from a struct by it name, the Field returned will have a NULL value for it ptr_address field `METAREF_GET_STRUCT_FIELD(Date, "hours")`.  

## METAREF_HAS_FIELD

Check if a struct has a field declared `METAREF_HAS_FIELD(Date, "hours")`.

## FOREACH_STRUCT_FIELD

Iterate through all the field of a struct object. The first parameter is the Struct object of the struct, the second parameter is the field variable, followed by the loop body.

```c
FOREACH_STRUCT_FIELD(Date, field, {
    //...
})
```

## FOREACH_STRUCT_FIELD_INDEX

Iterate through all the field of a struct. The first parameter is the struct name value of the struct, the second parameter is the current index of the field in the iteration, the third parameter is the field variable, followed by the loop body.

```c
FOREACH_STRUCT_FIELD_INDEX(Date, index, field, {
    //...
})
```

## METAREF_FIELD_IS_CHAR_ARRAY

Check if the field type is char array. This simply compare the type literal as it declared in the source file, it not a sure way to determine the type of a field. 

```c
Field field = METAREF_GET_STRUCT_FIELD(Date, "name_of_field");
if (METAREF_FIELD_IS_CHAR_ARRAY(field)) {
    //...
}
```

This compares the type literal with the following values

- char *
- char*

Returns 1 if the type matches any of the above values.

## METAREF_FIELD_IS_CHAR

Check if the field type is char. This simply compare the type literal as it declared in the source file, it not a sure way to determine the type of a field. 

```c
Field field = METAREF_GET_STRUCT_FIELD(Date, "name_of_field");
if (METAREF_FIELD_IS_CHAR(field)) {
    //...
}
```

This compares the type literal with the following values

- char
- signed char

Returns 1 if the type matches any of the above values.

## METAREF_FIELD_IS_UCHAR

Check if the field type is unsigned char. This simply compare the type literal as it declared in the source file, it not a sure way to determine the type of a field. 

```c
Field field = METAREF_GET_STRUCT_FIELD(Date, "name_of_field");
if (METAREF_FIELD_IS_UCHAR(field)) {
    //...
}
```

This compares the type literal with the following values

- unsigned char

Returns 1 if the type matches any of the above values.

## METAREF_FIELD_IS_INT

Check if the field type is int. This simply compare the type literal as it declared in the source file, it not a sure way to determine the type of a field. 

```c
Field field = METAREF_GET_STRUCT_FIELD(Date, "name_of_field");
if (METAREF_FIELD_IS_INT(field)) {
    //...
}
```

This compares the type literal with the following values

- int
- signed
- signed int

Returns 1 if the type matches any of the above values.

## METAREF_FIELD_IS_UINT

Check if the field type is unsigned int. This simply compare the type literal as it declared in the source file, it not a sure way to determine the type of a field. 

```c
Field field = METAREF_GET_STRUCT_FIELD(Date, "name_of_field");
if (METAREF_FIELD_IS_UINT(field)) {
    //...
}
```

This compares the type literal with the following values

- unsigned
- unsigned int

Returns 1 if the type matches any of the above values.

## METAREF_FIELD_IS_SHORT

Check if the field type is short. This simply compare the type literal as it declared in the source file, it not a sure way to determine the type of a field. 

```c
Field field = METAREF_GET_STRUCT_FIELD(Date, "name_of_field");
if (METAREF_FIELD_IS_SHORT(field)) {
    //...
}
```

This compares the type literal with the following values

- short
- short int
- signed short
- signed short int

Returns 1 if the type matches any of the above values.

## METAREF_FIELD_IS_USHORT

Check if the field type is unsigned short. This simply compare the type literal as it declared in the source file, it not a sure way to determine the type of a field. 

```c
Field field = METAREF_GET_STRUCT_FIELD(Date, "name_of_field");
if (METAREF_FIELD_IS_USHORT(field)) {
    //...
}
```

This compares the type literal with the following values

- unsigned short
- unsigned short int

Returns 1 if the type matches any of the above values.

## METAREF_FIELD_IS_LONG

Check if the field type is long. This simply compare the type literal as it declared in the source file, it not a sure way to determine the type of a field. 

```c
Field field = METAREF_GET_STRUCT_FIELD(Date, "name_of_field");
if (METAREF_FIELD_IS_LONG(field)) {
    //...
}
```

This compares the type literal with the following values

- long
- long int
- signed long
- signed long int

Returns 1 if the type matches any of the above values.

## METAREF_FIELD_IS_ULONG

Check if the field type is unsigned long. This simply compare the type literal as it declared in the source file, it not a sure way to determine the type of a field. 

```c
Field field = METAREF_GET_STRUCT_FIELD(Date, "name_of_field");
if (METAREF_FIELD_IS_ULONG(field)) {
    //...
}
```

This compares the type literal with the following values

- unsigned long
- unsigned long int

Returns 1 if the type matches any of the above values.

## METAREF_FIELD_IS_FLOAT

Check if the field type is float. This simply compare the type literal as it declared in the source file, it not a sure way to determine the type of a field. 

```c
Field field = METAREF_GET_STRUCT_FIELD(Date, "name_of_field");
if (METAREF_FIELD_IS_FLOAT(field)) {
    //...
}
```

This compares the type literal with the following values

- float

Returns 1 if the type matches any of the above values.

## METAREF_FIELD_IS_DOUBLE

Check if the field type is double. This simply compare the type literal as it declared in the source file, it not a sure way to determine the type of a field. 

```c
Field field = METAREF_GET_STRUCT_FIELD(Date, "name_of_field");
if (METAREF_FIELD_IS_DOUBLE(field)) {
    //...
}
```

This compares the type literal with the following values

- double

Returns 1 if the type matches any of the above values.

## METAREF_FIELD_IS_LONG_DOUBLE

Check if the field type is long double. This simply compare the type literal as it declared in the source file, it not a sure way to determine the type of a field. 

```c
Field field = METAREF_GET_STRUCT_FIELD(Date, "name_of_field");
if (METAREF_FIELD_IS_LONG_DOUBLE(field)) {
    //...
}
```

This compares the type literal with the following values

- long double

Returns 1 if the type matches any of the above values.

## METAREF_GET_FIELD_ANNOTATIONS

Get the static list of annotations for the field `METAREF_GET_FIELD_ANNOTATIONS(field)`.

## FOREACH_FIELD_ANNOTATION

Iterate through all the field annotations. The first parameter is the field object, the second parameter is the annotation variable, followed by the loop body.

```c
Field field = METAREF_GET_STRUCT_FIELD(Date, "name_of_field");
FOREACH_FIELD_ANNOTATION(field, annotation, {
    //...
})
```

## FOREACH_FIELD_ANNOTATION_INDEX

Iterate through all the field annotations. The first parameter is the field object, the second parameter is the index of the current annotation in the iteration, the third parameter is the annotation variable, followed by the loop body.

```c
Field field = METAREF_GET_STRUCT_FIELD(Date, "name_of_field");
FOREACH_FIELD_ANNOTATION_INDEX(field, index, annotation, {
    //...
})
```

## METAREF_FIELD_GET_ANNOTATION

Get a field annotation using it name, `METAREF_FIELD_GET_ANNOTATION(field, "CERXOS_value")`.

## METAREF_FIELD_GET_ANNOTATION2

Get a field annotation using it name without quote, `METAREF_FIELD_GET_ANNOTATION2(field, CERXOS_value)`.

## METAREF_FIELD_HAS_ANNOTATION

Check if a field has an annotation before performing an operation.

```c
if (METAREF_FIELD_HAS_ANNOTATION(field, "CERXOS_value"))) {
    //...
}
```

## METAREF_FIELD_ANNOTATION_IS_STRING

Check if the type of the field annotation is char array, if the annotation is defined with the macro [_FS](#fs) it returns 1 else 0.

## METAREF_FIELD_ANNOTATION_STR_VALUE

Get the char array value of a field annotation declared with the [_FS](#fs) macro, `METAREF_FIELD_ANNOTATION_STR_VALUE(field, "CERXOS_value")`.

## METAREF_FIELD_ANNOTATION_IS_INT

Check if the type of the field annotation is an integer, if the annotation is defined with the macro [_FI](#fi) it returns 1 else 0.

## METAREF_FIELD_ANNOTATION_INT_VALUE

Get the char array value of a field annotation declared with the [_FI](#fi) macro, `METAREF_FIELD_ANNOTATION_INT_VALUE(field, "SIZE_min")`.

## METAREF_FIELD_ANNOTATION_IS_LONG

Check if the type of the field annotation is a long, if the annotation is defined with the macro [_FL](#fl) it returns 1 else 0.

## METAREF_FIELD_ANNOTATION_LONG_VALUE

Get the char array value of a field annotation declared with the [_FL](#fl) macro, `METAREF_FIELD_ANNOTATION_LONG_VALUE(field, "SIZE_max")`.

## METAREF_FIELD_ANNOTATION_IS_FUNCTION

Check if the type of the field annotation is a function, if the annotation is defined with the macro [_FF](#ff) it returns 1 else 0.

## METAREF_FIELD_ANNOTATION_FUNC_VALUE

Get the char array value of a field annotation declared with the [_FF](#ff) macro, `METAREF_FIELD_ANNOTATION_FUNC_VALUE(field, "get_prefix")`.

## METAREF_GET_FIELD

Get a field using it name from the meta Struct object. Using this will guarantee the value of the ptr_address of the field to be set. 

```c
Date *date = (Date *) inst->arg;
Struct *date_struct = METAREF_GET_STRUCT(Date, date);
Field time_field = METAREF_GET_FIELD(date_struct, "time");
```

## FOREACH_FIELD

Iterate through all the field in the struct object. The first parameter is the struct object, the second parameter is the field variable, followed by the loop body.

```c
Date *date = (Date *) inst->arg;
Struct *the_struct = METAREF_GET_STRUCT(Date, date);
FOREACH_FIELD(the_struct, field, {
    //...
})
```

## FOREACH_FIELD_INDEX

Iterate through all the field in the struct object. The first parameter is the struct object, the second parameter is the index of the current field in the iteration, the third parameter is the field variable, followed by the loop body.

```c
Date *date = (Date *) inst->arg;
Struct *the_struct = METAREF_GET_STRUCT(Date, date);
FOREACH_FIELD_INDEX(the_struct, index, field, {
    //...
})
```

## METAREF_FIELD_VALUE_IS_NULL

Check if the pointer to the address of the field value is NULL `METAREF_FIELD_VALUE_IS_NULL(field)`.

## METAREF_FIELD_VALUE_PTR

Get the pointer to the address of the field value `METAREF_FIELD_VALUE_PTR(field)`. Returns the `void *` value.

## METAREF_FIELD_VALUE_PTR_AS

Get the pointer to the address of the field value `METAREF_FIELD_VALUE_PTR(int, field)` cast to th type. Returns the `type *` value.

```c
Field field = METAREF_GET_STRUCT_FIELD(Date, "name_of_field");
int *int_ptr = METAREF_FIELD_VALUE_PTR(int, field);
int int_value = *METAREF_FIELD_VALUE_PTR(int, field);
int int_value2 = *int_ptr;
```

## METAREF_SET_FIELD_VALUE

Set the value of a field by changing the value at the address of the previous value.

```c
Field day_field = METAREF_GET_FIELD(date_struct, "day");
METAREF_SET_FIELD_VALUE(day_field, 5);
```
































