#define __STRUCT_FILE__ "preference_struct.h"
#define __STRUCT_NAME__ Preference
#include <exotic/metaref.h>
    
STRUCT(Preference,
    /*ANNOTATED_FIELD(
        _S(KONFIGER_value, "IpAddress")
        FIELD(char *, ip_address)
    )*/
    FIELD(int, MainPort)
    /*ANNOTATED_FIELD(
        _S(DATABASE_column, "project")
        _S(JSON_value, "project_data")
        _S(KONFIGER_value, "project")
        _I(SIZE_min, 10)
        _I(SIZE_max, 50)
        _S(SIZE_msg, "The length must be between 10 and 50")
        _F(URL_prefix, get_map_prefix)
        FIELD(char *, google_map_link)
    )*/
)

#ifndef PREFERENCE_STRUCT_FUNCTION
#define PREFERENCE_STRUCT_FUNCTION
void *get_map_prefix(const void *arg) {
    return (void *)"https://www.google.ng/maps/place/";
}
#endif