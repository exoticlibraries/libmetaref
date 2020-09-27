#define __STRUCT_FILE__ "test_struct.h"
#define __STRUCT_NAME__ Test
#include <exotic/metaref.h>

_S(DATABASE_table, "test")
_I(SIZE_min, 10)
_F(TO_STRING, test_to_string)
STRUCT(Test,
    FIELD({}, char *, fullname)
    FIELD({}, char *, email)
)

#ifndef TEST_ANNOTATION_FUNCTION
#define TEST_ANNOTATION_FUNCTION
void *test_to_string(const void *test, void *arg) {
    return (void *)"Name=test";
}
#endif