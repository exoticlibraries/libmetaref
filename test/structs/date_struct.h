
#define __STRUCT_FILE__ "date_struct.h"
#include <exotic/metaref.h>

#define _A(name, ...)

STRUCT(XSON,
    FIELD(char*, serializer)
    FIELD(char*, deserializer)
)


STRUCT(Date,
    _A(XSON, F(serializer, "string_to_date"), F(deserializer, "date_to_string"))

    FIELD(char *, time)
    FIELD(char *, day)
)

