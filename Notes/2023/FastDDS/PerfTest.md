Simple Test for PerfTest : FastDDS <!-- omit in toc -->
===

**Table of Contents**
- [1. Abstract](#1-abstract)
- [2. Compile and Run](#2-compile-and-run)
- [3. Perftest idl](#3-perftest-idl)
- [4. Publisher](#4-publisher)
- [5. Subscriber](#5-subscriber)

# 1. Abstract
Simple test
1. make idl
2. started from [official doc](https://fast-dds.docs.eprosima.com/en/latest/fastdds/getting_started/simple_app/simple_app.html "https://fast-dds.docs.eprosima.com/en/latest/fastdds/getting_started/simple_app/simple_app.html")

# 2. Compile and Run
```bash
wget -O HelloWorldPublisher.cpp \
    https://raw.githubusercontent.com/eProsima/Fast-RTPS-docs/master/code/Examples/C++/DDSHelloWorld/src/HelloWorldPublisher.cpp
wget -O HelloWorldSubscriber.cpp \
    https://raw.githubusercontent.com/eProsima/Fast-RTPS-docs/master/code/Examples/C++/DDSHelloWorld/src/HelloWorldSubscriber.cpp
cd build
cmake ..
cmake --build .
./DDSPerfTestSubscriber
./DDSPerfTestPublisher
```

# 3. Perftest idl
```idl
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