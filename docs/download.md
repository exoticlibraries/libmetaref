
# Download

The library is compliant with C99 and C++11 any lesser version is not supported, Also the compiler must support the variadic parameter in the macro declaration and the macro constant `__VA_ARGS__`.

## From Source

Simply download the header file libmetaref.h from the repo into your project source folder and include it in your project. Download the file from https://github.com/exoticlibraries/libmetaref/releases or from any of the branches. Then you can include it in your project relatively like `#include "libmetaref.h"`.

## Using irorun

Install irorun from https://exoticlibraries.github.io/irorun

Installing directly from the repo

```
irorun install libmetaref --github=https://github.com/exoticlibraries/libmetaref
```

Installing from vcpkg directory

```
irorun install libmetaref
```

The library will be installed for the following compilers and others installed compilers recognized by irorun.

- GCC
- CMAKE
- Visual C++

## Using Microsoft vcpkg

```
vcpkg install libmetaref
```

To use the library after installation with vcpkg with your build system, continue with [vcpkg documentation](https://github.com/microsoft/vcpkg/blob/master/docs/index.md) and [integration with build systems](https://github.com/microsoft/vcpkg/blob/master/docs/users/integration.md)

<div class="admonition note">
<p class="admonition-title">Note</p>
<p>Always add the relative or absolute path to the struct file(s) during compilation e.g. <code>-I./structs</code></p>
</div>

	