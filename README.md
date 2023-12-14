# LLCL

A helper to build your own Low Level Core Layer.

## Introduction

For every low level cpp application, it is very common to define lots of macros, data types, function pointers, const/constexpr variables across compiler/hardware/platform at first. People can also write their own STL/Math/... functions and classes based it. Then you get a set of files called Core.

This project doesn't want to add application-specified parts of Core such as STL/Math/... Keep simple and thin to be convenient for developers to build Core layer.

## Usages

Just add this repo to your project's include directory. Then you will get lots of abstraction constexpr variables by detecting compiler/hardware/platform. By default, no namespace wrapped.

```
#include "LLCL/Core.h"
```

If you would like to include these variables in a customized named namespace, it is required to define `LLCL_NAME` before including `LLCL/Core.h` or just define it in project settings.

```
#define LLCL_NAME llcl
#include "LLCL/Core.h"
```
