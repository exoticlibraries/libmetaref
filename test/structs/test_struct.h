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