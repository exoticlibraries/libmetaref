
#ifndef INCLUDE_OTHER_STRUCTS
#define INCLUDE_OTHER_STRUCTS
#include "friend_struct.h"
#include "date_struct.h"
#endif

#define __STRUCT_FILE__ "types_struct.h"
#define __STRUCT_NAME__ Types
#include <exotic/metaref.h>

STRUCT(Types,
    FIELD({}, char*, field00)
    FIELD({}, char *   , field0)
    FIELD({}, char *, field1)
    FIELD({}, int, field2)
    FIELD({}, signed int, field3)
    FIELD({}, unsigned, field4)
    FIELD({}, unsigned int, field5)
    FIELD({}, unsigned       int, field6)
    FIELD({}, unsigned int , field7)
    FIELD({}, short, field8)
    FIELD({}, signed short, field9)
    FIELD({}, unsigned short, field10)
    FIELD({}, short int, field11)
    FIELD({}, signed short int, field12)
    FIELD({}, unsigned short int, field13)
    FIELD({}, long, field14)
    FIELD({}, signed long, field15)
    FIELD({}, unsigned long, field16)
    FIELD({}, long int, field17)
    FIELD({}, signed long int, field18)
    FIELD({}, unsigned long int, field19)
    
    FIELD({}, float, field20)
    FIELD({}, double, field21)
    FIELD({}, long double, field22)
    
    FIELD({}, char, field23)
    FIELD({}, signed char, field24)
    FIELD({}, unsigned char, field25)
    
    FIELD({
    _FI(IS_STRUCT, 1)
    }, Date *, field26)
    
    FIELD({
    _FI(IS_STRUCT, 1)
    }, Friend *, field27)
)
