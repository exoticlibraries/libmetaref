#define __STRUCT_FILE__ "user_table_struct.h"
#define __STRUCT_NAME__ User
#include <exotic/metaref.h>
    
_S(DATABASE_table, "user")
_S(KONFIGER_file, "#{rsc}/user.conf")
_L(SIZE_max, 2000)
_I(SIZE_min, 10)
_F(TO_STRING, user_to_string)
STRUCT(User,
    FIELD({}, long, user_id)
    FIELD({}, char *, first_name)
    FIELD({}, char *, middle_name)
    FIELD({}, char *, last_name)
)

#ifndef USER_ANNOTATION_FUNCTION
#define USER_ANNOTATION_FUNCTION
void *user_to_string(const void *user) {
    return (void *)"Name=libmetaref";
}
#endif