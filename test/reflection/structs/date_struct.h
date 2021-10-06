
#define __STRUCT_FILE__ "date_struct.h"
#define __STRUCT_NAME__ Date
#include <exotic/metaref.h>

STRUCT(Date,
    FIELD({}, char *, time)
    FIELD({}, int, day)
    FIELD({}, int, month)
)
