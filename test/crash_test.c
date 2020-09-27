/*!gcc {0} -I../../libcester/include/ -I. -I./structs -I../include/ -o out.exe; ./out.exe */

#include <stdio.h>
#include <structs/test_struct.h>

int main(int argc, char **argv) {
    FOREACH_STRUCT_ANNOTATION(Test, annotation, {
        printf("Name=%s\n", annotation.name);
    })
}