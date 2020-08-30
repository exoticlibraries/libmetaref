/*!g++ {0} -I../../libcester/include/ -I. -I./structs -I../include/ -o out.exe; ./out.exe */

#include <exotic/cester.h>
#ifndef INCLUDE_STRUCTS
#define INCLUDE_STRUCTS
#include "structs/date_struct.h"
#endif

CESTER_BEFORE_ALL(inst,
    Date *date = (Date *) malloc(sizeof(Date));
    date->time = (char *) "01:44 AM";
    date->day = 5;
    inst->arg = date;
)

CESTER_TEST(check_date_struct_fields_values, inst,
    Date *date = (Date *) inst->arg;
    cester_assert_str_equal(date->time, "01:44 AM");
    cester_assert_int_ne(date->day, 0);
    cester_assert_int_eq(date->day, 5);
)

CESTER_TEST(check_date_struct_fields_values_introspection, inst,
    Date *date = (Date *) inst->arg;
    Field time_field = METAREF_GET_FIELD(Date, date, "time");
    Field day_field = METAREF_GET_FIELD(Date, date, "day");
    
    cester_assert_ptr_equal(&(date->time), time_field.ptr_address);
    cester_assert_str_equal(date->time, (char*)(*time_field.ptr_address));
    cester_assert_str_equal((char*)(*time_field.ptr_address), "01:44 AM");
    
    cester_assert_ptr_equal(&(date->day), day_field.ptr_address);
    cester_assert_int_eq(date->day, *((int*)day_field.ptr_address));
    cester_assert_int_ne(*((int*)(day_field.ptr_address)), 0);
    cester_assert_int_eq(*((int*)day_field.ptr_address), 5);
)

CESTER_TEST(check_date_struct_fields_values_introspection_macro, inst,
    Date *date = (Date *) inst->arg;
    Field time_field = METAREF_GET_FIELD(Date, date, "time");
    Field day_field = METAREF_GET_FIELD(Date, date, "day");
    int day2 = *(METAREF_FIELD_VALUE_PTR_AS(int, day_field));
    char *time1 = (char*)METAREF_FIELD_VALUE_PTR(time_field);
    
    int day1 = *((int*)(day_field.ptr_address));
    char *time2 = (char*)(*time_field.ptr_address);  
    
    cester_assert_ptr_equal(&(date->time), &METAREF_FIELD_VALUE_PTR(time_field));
    cester_assert_ptr_equal(&(date->time), &((*time_field.ptr_address)));
    cester_assert_str_equal(date->time, time1);
    cester_assert_str_equal(date->time, time2);
    cester_assert_str_equal(time1, time2);
    cester_assert_str_equal(time1, "01:44 AM");
    cester_assert_str_equal(time2, "01:44 AM");
    
    cester_assert_ptr_equal(&(date->day), &METAREF_FIELD_VALUE_PTR(day_field));
    cester_assert_ptr_equal(&(date->day), &(*day_field.ptr_address));
    cester_assert_int_eq(date->day, day1);
    cester_assert_int_eq(date->day, day2);
    cester_assert_int_eq(day1, day2);
    cester_assert_int_ne(day1, 0);
    cester_assert_int_ne(day2, 0);
    cester_assert_int_eq(day1, 5);
    cester_assert_int_eq(day2, 5);
)

CESTER_TEST(check_date_struct_fields_values_intercession, inst,
    Date *date = (Date *) inst->arg;
    Field time_field = METAREF_GET_FIELD(Date, date, "time");
    Field day_field = METAREF_GET_FIELD(Date, date, "day");
    
    *time_field.ptr_address = (char *) "02:30 PM";
    *day_field.ptr_address = (void*)20; // BAD
)

CESTER_TEST(check_date_struct_fields_values_after_fails, inst,
    Date *date = (Date *) inst->arg;
    cester_assert_str_equal(date->time, "01:44 AM");
    cester_assert_int_ne(date->day, 0);
    cester_assert_int_eq(date->day, 5);
)

CESTER_TEST(check_date_struct_fields_values_after, inst,
    Date *date = (Date *) inst->arg;
    cester_assert_str_equal(date->time, "02:30 PM");
    cester_assert_int_ne(date->day, 5);
    cester_assert_int_eq(date->day, 20);
)

CESTER_TEST(check_date_struct_fields_values_intercession_macro, inst,
    Date *date = (Date *) inst->arg;
    Field time_field = METAREF_GET_FIELD(Date, date, "time");
    Field day_field = METAREF_GET_FIELD(Date, date, "day");
    
    METAREF_SET_FIELD_VALUE(time_field, "01:44 AM");
    METAREF_SET_FIELD_VALUE(day_field, 5);
)

CESTER_TEST(check_date_struct_fields_values_after_fails_macro, inst,
    Date *date = (Date *) inst->arg;
    cester_assert_str_equal(date->time, "02:30 PM");
    cester_assert_int_ne(date->day, 5);
    cester_assert_int_eq(date->day, 20);
)

CESTER_TEST(check_date_struct_fields_values_after_macro, inst,
    Date *date = (Date *) inst->arg;
    cester_assert_str_equal(date->time, "01:44 AM");
    cester_assert_int_ne(date->day, 0);
    cester_assert_int_eq(date->day, 5);
)

CESTER_AFTER_ALL(inst,
    free(inst->arg);
)

CESTER_OPTIONS(
    CESTER_MINIMAL();
    CESTER_VERBOSE();
    CESTER_TEST_SHOULD_FAIL(check_date_struct_fields_values_after_fails);
    CESTER_TEST_SHOULD_FAIL(check_date_struct_fields_values_after_fails_macro);
)

