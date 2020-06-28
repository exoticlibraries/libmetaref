
#define __STRUCT_FILE__ "annotated_struct.h"
#include <exotic/metaref.h>

ANNOTATIONS(
    TABLE("date")
)
STRUCT(Date,
    FIELD(char *, time)
    FIELD(char *, day)
    ANNOTATED_FIELD(
        ANNOTATIONS(
            COLUMN("project"),
            JSON_VALUE("Project"),
            KONFIGER_VALUE("project"),
            SIZE(10, 50, "The length must be between 10 and 50"),
        ),
        FIELD(char *, project)
    )
)

COLUMN(value) { "COLUMN", value }
SIZE(min, max, message) { "SIZE", min, max, message }

FIELD_HAS_ANNOTATION(KONFIGER_VALUE)
GET_ANNOTATION_VALUE(KONFIGER_VALUE)