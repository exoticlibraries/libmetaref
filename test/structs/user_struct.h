#define __STRUCT_FILE__ "user_struct.h"
#define __STRUCT_NAME__ User
#include <exotic/metaref.h>

_S(DATABASE_table, "user")
_I(SIZE_min, 10)
STRUCT(User,
    FIELD({}, char *, fullname)
    FIELD({}, char *, email)
)