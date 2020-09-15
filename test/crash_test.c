/*!gcc {0} -I../../libcester/include/ -I. -I./structs -I../include/ -o out.exe; ./out.exe */

#include <stdio.h>
#include <stdlib.h>

typedef struct Struct_Field { 
    int number; 
    char *type;
} Field;

const static Field METAREF_Date_fields[] = {
    {1, "time"},
    {1, "day"},
    {1, "month"},
    {0, NULL},
};

typedef struct metaref_obj__ { 
    const Field* field_array; 
} MetarefStruct;

typedef struct METAREF_Date { 
    char * time; 
    int day; 
    int month; 
    MetarefStruct* metaref_obj; 
} Date;

void print_(MetarefStruct *the_struct) {
    for(size_t i = 0; the_struct->field_array[i].type != NULL; ++i) {
        Field field = the_struct->field_array[i]; 
        printf("    %s\n", field.type);
    }
}

int main(int argc, char **argv) {
    Date *date = malloc(sizeof(Date));
    date->metaref_obj = malloc(sizeof(MetarefStruct));
    date->metaref_obj->field_array = METAREF_Date_fields;
    printf("%p\n", date->metaref_obj->field_array[0]);
    print_(date->metaref_obj);
    
    return 0;
}