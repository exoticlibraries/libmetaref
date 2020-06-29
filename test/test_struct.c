/*!gcc {0} -I. -I./structs -I../include/ -o out; ./out --cester-verbose */

#include <exotic/cester.h>
#ifndef INCLUDE_STRUCTS
#define INCLUDE_STRUCTS
#include "structs/friend_struct.h"
#include "structs/date_struct.h"
#endif

CESTER_TEST(test_friend_model, _,
    /*Friend *friend = malloc(sizeof(Friend));
    
    METAREF_SET_FIELD(Friend, friend, "name", "Dr. Dre");
    METAREF_SAFELY_SET_STRUCT_FIELD(Friend, friend, "picture", "/mnt/images/dre.png");
    METAREF_SAFELY_SET_STRUCT_FIELD(Friend, friend, "location", "Nigeria");
    
    FOREACH_FIELDS(Friend, friend, field,
        printf("Field Name: %s, Value: %p ", field.name, field.ptr_address);
        printf("%s", *field.ptr_address);
        printf("\n");
    )
    
    free(friend);*/
)

CESTER_TEST(test_date_model, _,
    /*Date *date = malloc(sizeof(Date));
    
    METAREF_SAFELY_SET_FIELD(Date, date, "time", "00:00 PM 00:00");
    METAREF_SAFELY_SET_FIELD(Date, date, "day", "Sunday");
    
    FOREACH_FIELDS(Date, date, field,
        printf("Field Name: %s, Value: %p ", field.name, field.ptr_address);
        printf("%s", *field.ptr_address);
        printf("\n");
    )
    
    free(date);*/
)

