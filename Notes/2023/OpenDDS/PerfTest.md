Simple Test for PerfTest : OpenDDS <!-- omit in toc -->
===

**Table of Contents**
- [1. Abstract](#1-abstract)
- [2. Compile and Run](#2-compile-and-run)
  - [2.1. CMakeLists.txt](#21-cmakeliststxt)
- [3. Perftest idl](#3-perftest-idl)
- [4. Publisher](#4-publisher)
- [5. Subscriber](#5-subscriber)

# 1. Abstract
Simple test
1. make idl
2. copy pub/sub code using messenger example

# 2. Compile and Run
```bash
cp $DDS_ROOT/DevGuideExamples/DCPS/Messenger/{DataReaderListenerImpl.cpp,DataReaderListenerImpl.h,Publisher.cpp,Subscriber.cpp} .
nvim PerfTest.idl
nvim CMakeLists.txt
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH="$INSTALL_PREFIX" ..
# cmake -DCMAKE_PREFIX_PATH="$INSTALL_PREFIX" -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
cd build
./subscriber -DCPSConfigFile ../rtps.ini
./publisher -DCPSConfigFile ../rtps.ini
```

## 2.1. CMakeLists.txt
```cmake
project(opendds_devguide_messenger CXX)
cmake_minimum_required(VERSION 3.3)
# enable_testing()

find_package(OpenDDS REQUIRED)

# Make sure the MPC-generated headers are gone so the CMake build will use the
# right ones. This is not needed in a real project.
file(GLOB headers "*.h")
file(GLOB listener_header "DataReaderListenerImpl.h")
list(REMOVE_ITEM headers ${listener_header})
list(LENGTH headers header_count)
if(header_count GREATER 0)
  file(REMOVE ${headers})
endif()

# IDL TypeSupport Library
add_library(perftest_idl)
OPENDDS_TARGET_SOURCES(perftest_idl PUBLIC "PerfTest.idl")
target_link_libraries(perftest_idl PUBLIC OpenDDS::Dcps)

set(opendds_libs
  OpenDDS::Dcps # Core OpenDDS Library
  OpenDDS::InfoRepoDiscovery OpenDDS::Tcp # For run_test.pl
  OpenDDS::Rtps OpenDDS::Rtps_Udp # For run_test.pl --rtps
  perftest_idl
)

# Publisher
add_executable(publisher
  Publisher.cpp
  # PubMessage.cpp
)
target_link_libraries(publisher ${opendds_libs})

# Subscriber
add_executable(subscriber
  Subscriber.cpp
  DataReaderListenerImpl.cpp
)
target_link_libraries(subscriber ${opendds_libs})
```

# 3. Perftest idl
```idl
@topic
struct PerfTest {
    unsigned long index;
    string message;
}
```

# 4. Publisher
```cpp
pass
```

# 5. Subscriber
```cpp
pass
```