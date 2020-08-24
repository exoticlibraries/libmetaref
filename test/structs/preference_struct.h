#define __STRUCT_FILE__ "preference_struct.h"
#define __STRUCT_NAME__ Preference
#include <exotic/metaref.h>
    
STRUCT(Preference,
    FIELD({
    _FS(KONFIGER_value, "IpAddress")
    }, char *, ip_address)
    
    FIELD({}, int, MainPort)
    
    FIELD({
    _FF(URL_prefix, get_map_prefix)
    }, char *, google_map_link)
    
    FIELD({
    _FS(DATABASE_column, "fullname")
    _FS(JSON_value, "full_name")
    _FS(KONFIGER_value, "FullName")
    _FI(SIZE_min, 10)
    _FI(SIZE_max, 150)
    _FS(SIZE_msg, "The length of the name must be between 10 and 50")
    }, char *, fullname)
)

#ifndef PREFERENCE_STRUCT_FUNCTION
#define PREFERENCE_STRUCT_FUNCTION
void *get_map_prefix(const void *arg) {
    return (void *)"https://www.google.ng/maps/place/";
}
#endif