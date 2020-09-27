
# libmetaref

<div class="header">
    <img src="https://raw.githubusercontent.com/exoticlibraries/libmetaref/main/docs/libmetaref.png" alt="libmetaref logo"><br/><br/>
    <span class="title">libmetaref</span><br/>
    <p class="brief">
        Reflection library for C Struct. Runtime introspection and intercession for struct fields, supports struct and field annotation.
    </p>
    <div class="linksdiv">
        <a class="link" href="./download.html">Download</a>
        <a class="link" href="./doc/index.html">Documentation</a>
        <a class="link" href="./reference/">API Reference</a>
    </div>
</div>
<div style="margin-top:470px;"></div>

# Struct and Field Annotation

Annotate a struct for inspection at runtime. Use 
annotation to extend the struct, add options for various 
libraries that uses libmetaref for extended functionalities.

<div class="highlight-c notranslate">
    <div class="highlight">
        <pre>
#define __STRUCT_FILE__ "user_struct.h"
#define __STRUCT_NAME__ User
#include &lt;exotic/metaref.h>

_S(DATABASE_table, "user")
_I(SIZE_min, 10)
STRUCT(User,
    FIELD({}, char *, fullname)
    FIELD({}, char *, email)
)
        </pre>
    </div>
</div>

# Runtime Reflection

Inspect struct fields and annotation at runtime. Get fields name, 
annotation and modify value using the field address to the value pointer.

<div class="highlight-c notranslate">
    <div class="highlight">
        <pre>
#include &lt;stdio.h>
#include &lt;structs/user_struct.h>

int main(int argc, char **argv) {
    FOREACH_STRUCT_ANNOTATION(User, annotation, {
        printf("Annotation Name=%s\n", annotation.name);
    })    
    FOREACH_STRUCT_FIELD(User, field, {
        printf("Field Name=%s, Type=%s\n", field.name, field.type);
    })
    return 0;
}
        </pre>
    </div>
</div>

# Serialization and Deserialization

A struct created with the macros provided by libmetaref can be easilly 
interface with for serialization and deserialization through composition. 
The struct is declared with an extra variable of type [Struct](#) that can be used in the 
serialization and deserialization functions. 

See this [example](https://github.com/exoticlibraries/libmetaref/blob/main/test/test_serialization.c) that does a simple struct serialization.
