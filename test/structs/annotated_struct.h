
#define __STRUCT_FILE__ "annotated_struct.h"
#include <exotic/metaref.h>

STRUCT(Date,
    FIELD(char *, time)
    FIELD(char *, day)
    ANNOTATED_FIELD(
        ANNOTATIONS(
            COLUMN("project"),
            JSON_VALUE("Project"),
            KONFIGER_VALUE("project"),
        ),
        FIELD(char *, project)
    )
)

COLUMN(

)

FIELD_HAS_ANNOTATION(KONFIGER_VALUE)
GET_ANNOTATION_VALUE(KONFIGER_VALUE)