#define __STRUCT_FILE__ "user_table_struct.h"
#define __STRUCT_NAME__ User
#include <exotic/metaref.h>
    
_S(DATABASE_table, "user")
_S(KONFIGER_file, "#{rsc}/user.conf")
_F(TO_STRING, user_to_string)
STRUCT(User,
    
    //_S(DATABASE_column, "id")
    FIELD(long, user_id)
    
    FIELD(char *, first_name)
    FIELD(char *, middle_name)
    FIELD(char *, last_name)
)

#ifndef USER_ANNOTATION_FUNCTION
#define USER_ANNOTATION_FUNCTION
void *user_to_string(void *user) {
    return "Name=libmetaref";
}
#endif