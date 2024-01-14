Simple Test for PerfTest : RTIDDS <!-- omit in toc -->
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
2. generate pub/sub code using rtiddsgen

# 2. Compile and Run
```bash
nvim PerfTest.idl
rtiddsgen -language c++11 -platform x64Linux4gcc7.3.0 -create typefiles Perftest.idl -example x64Linux4gcc7.3.0 -exampleTemplate advanced
make -f makefile_PerfTest_x64Linux4gcc7.3.0
cd objs/x64Linux4gcc7.3.0
./PerfTest_subscriber -d 10 -s 10 -v 0
./PerfTest_publisher -d 10 -s 10 -v 0
```

# 3. Perftest idl
```idl
struct PerfTest {
    unsigned long index;
    string message;
};
```

# 4. Publisher
```cpp
pass
```

# 5. Subscriber
```cpp
pass
```