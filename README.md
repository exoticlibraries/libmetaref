# libmetaref
Extends struct for reflection and runtime analysis. Allows (string like) annotation for struct fields.

# Why?

Well I want a situation whereby I can assign the values of struct fields without the need to know what field is declared or not. For example to deserialize a json object into a struct in the traditional manner I will be aware of the JSON object structure and the struct fields so I iterate the JSON object and assign match with the struct fields, this requires me to know both the JSON structure and the struct fields, but with this library there is no need to be aware of either of the two a json library that support libmetaref can just simply take your JSON object, struct and assign where appropriate and possibly set non matching field to NULL. 

An example is described below.

*location.json*

```json
{
    "longitude": 123.45,
    "latitude": 678.90
}
```

The Location struct file:

*location_struct.h*

```h
#define __STRUCT_FILE__ "location_struct.h"
#include <exotic/metaref.h>

STRUCT(Location,
    FIELD(long, longitude)
    FIELD(long, latitude)
)
```

Assume a JSON library that add support for libmetaref 

*json_to_struct.c*
```c
#include "location_struct.h"
#include <exotic/xson.h>
#include <stdio.h>

int main(int argc, char **argv) {
    xson_object* json;
    Location *location = malloc(sizeof(Location));

    if (xson_obj_from_file(&json, "location.json") != XSON_OK || 
        xson_deserialize(json, location) != XSON_OK) {

        return 1;
    }
    printf("Longitude %.3f", location->longitude);
    printf("Latitude %.3f", location->latitude);


    return 0;
}
```

In the example above the json library handles the struct field assignment, the json values validation.
The example above is a pseudocode it not expected to compile.