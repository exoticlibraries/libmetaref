/*!gcc {0} -I../../libcester/include/ -I. -I./structs -I../include/ -o out.exe; ./out.exe */

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