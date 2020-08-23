
#define __STRUCT_FILE__ "annotated_struct.h"
#include <exotic/metaref.h>

STRUCT(Date,
    FIELD(char *, time)
    FIELD(char *, day)
    ANNOTATED_FIELD(
        _S(DATABASE_column, "project")
        _S(JSON_value, "project_data")
        _S(KONFIGER_value, "project")
        _I(SIZE_min, 10)
        _I(SIZE_max, 50")
        _S(SIZE_msg, "The length must be between 10 and 50")
        FIELD(char *, project)
    )
)

COLUMN(value) { "COLUMN", value }
SIZE(min, max, message) { "SIZE", min, max, message }

FIELD_HAS_ANNOTATION(Date, "project", KONFIGER_VALUE)
GET_ANNOTATION_VALUE(Date, "project", KONFIGER_VALUE)