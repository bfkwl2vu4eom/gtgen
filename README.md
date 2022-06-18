
# gtgen

![GitHub Workflow Status](https://img.shields.io/github/workflow/status/Torimune29/gtgen/CI)
[![codecov](https://codecov.io/gh/Torimune29/gtgen/branch/main/graph/badge.svg)](https://codecov.io/gh/Torimune29/gtgen)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/4ab150dd86c44db9ba17df846aa309a3)](https://www.codacy.com/gh/Torimune29/gtgen/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Torimune29/dev-cpp-oss-template&amp;utm_campaign=Badge_Grade)
![CodeQL](https://github.com/Torimune29/gtgen/workflows/CodeQL/badge.svg)
<br>[Github Repo](https://github.com/Torimune29/gtgen)

## Features

- googlemock mock class generating
  - for legacy
    - MOCK_METHODn for general functions
    - MOCK_CONST_METHOD for const member functions
    - overloaded operator functions workaround support
    - noexcept functions workaround support

## Examples

- googlemock mock class generating
  - [gtgen mock codes for unittestng](https://github.com/Torimune29/gtgen/tree/main/tests/units/mocks) are generated by gtgen !

## How to Build

- Requirement
  - Build
    - cmake >=3.14
    - [cppast](https://github.com/foonathan/cppast) (fetching as cmake external)
    - [CLI11](https://github.com/CLIUtils/CLI11) (fetching as cmake external)
    - [jsoncons](https://github.com/danielaparker/jsoncons) (fetching as cmake external)
  - Runtime
    - libclang (like libclang-dev on Ubuntu20.04) for [cppast](<https://github.com/foonathan/cppast>)
  - Unit Testing
    - googletest (fetching as cmake external)
- Build

```bash
> mkdir build
> cd build
> cmake .. -DCMAKE_BUILD_TYPE=Release
> make
> make install
> ls ../release/bin/
gtgen

```

## How to Use

### options

```
$ ./gtgen --help
gtgen 0.0.1
Usage: ./gtgen [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -f,--files TEXT ...         Analyze file paths. If empty, parse all files using compile database.
  -p,--compile-database TEXT REQUIRED
                              Compile database directory path
  --verbose                   Verbose parse result
  --mock{0},--view-functions{10},--view-scopes{11},--view-includes{12} [0]
                              Mode
  --mock-label TEXT           Mock Label for class. (--mock only)

```

### Generate mock

```

~/gtgen/build$ cat ../include/CodeAnalyzerInterface.h
#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "FunctionInfo.h"
#include "IncludeInfo.h"
#include "ScopeInfo.h"

/**
 * @brief Abstract Code Parser Class
 *
 */
class CodeAnalyzerInterface {
 public:
  virtual ~CodeAnalyzerInterface() = default;

  virtual std::vector<std::shared_ptr<FunctionAttributeInterface>> GetFunctions() {
    return {};
  }

  virtual std::vector<ScopeInfo> GetScopes() {
    return {};
  }

  virtual std::vector<IncludeInfo> GetIncludes() {
    return {};
  }

 protected:
  CodeAnalyzerInterface() = default;
};

~/gtgen/build$ ls
CMakeCache.txt  Makefile              _deps  cmake_install.cmake    gtgen
CMakeFiles      ProjectInformation.h  cmake  compile_commands.json  install_manifest.txt

~/gtgen/build$ ./gtgen -f ../include/CodeAnalyzerInterface.h -p . --mock --mock-label=mock_ > ../tests/mock/mock_CodeAnalyzerInterface.h

~/gtgen/build$ cat ../tests/mock/mock_CodeAnalyzerInterface.h
// This code was generated by gtgen 0.0.1
#pragma once

#include <gmock/gmock.h>

#include "FunctionInfo.h"
#include "IncludeInfo.h"
#include "ScopeInfo.h"
#include <string>
#include <unordered_map>
#include <vector>


class mock_CodeAnalyzerInterface : public CodeAnalyzerInterface {
 public:
  MOCK_METHOD0(GetFunctions, std::vector<std::shared_ptr<FunctionAttributeInterface>>());
  MOCK_METHOD0(GetScopes, std::vector<ScopeInfo>());
  MOCK_METHOD0(GetIncludes, std::vector<IncludeInfo>());
};


```

## How to Develop

This uses a OSS Development Template for C++ projects based on [cpp-project](https://github.com/bsamseth/cpp-project), and [dev-cpp-oss-template](https://github.com/Torimune29/dev-cpp-oss-template).
