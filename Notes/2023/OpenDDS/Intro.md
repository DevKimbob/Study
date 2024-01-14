Intro to OpenDDS w/ java <!-- omit in toc -->
===

**Table of Contents**
- [1. Installation](#1-installation)
  - [1.1. prerequisite](#11-prerequisite)
  - [1.2. OpenDDS](#12-opendds)
- [2. Using OpenDDS](#2-using-opendds)
- [3. Example : Cpp](#3-example--cpp)
- [4. Example : Java](#4-example--java)
  - [4.1. Code generation](#41-code-generation)


# 1. Installation
```
Env : VMware Ubuntu 22.04LTS 64bit
OpenDDS : 3.23.1
SDK : 5.18.0/0.1.3 (SDKMAN)
JDK : 17.0.6-oracle
```
## 1.1. prerequisite
1. SDK(optional)
```bash
$ curl -s "https://get.sdkman.io" | bash
$ source "/home/$USER/.sdkman/bin/sdkman-init.sh"
$ sdk version
```

2. JDK
```bash
$ sdk list java
$ sdk install java <version>
$ java --version
$ sdk use java <version>
$ sdk default java <version>
```

## 1.2. OpenDDS
download link : [https://github.com/OpenDDS/OpenDDS/releases](https://github.com/OpenDDS/OpenDDS/releases "https://github.com/OpenDDS/OpenDDS/releases")
```bash
$ tar -xvzf OpenDDS-x.xx.x.tar.gz
```

install readme : [https://github.com/OpenDDS/OpenDDS/blob/master/java/INSTALL](https://github.com/OpenDDS/OpenDDS/blob/master/java/INSTALL "https://github.com/OpenDDS/OpenDDS/blob/master/java/INSTALL")  
install doc : [https://opendds.readthedocs.io/en/dds-3.25/building/index.html#building-and-installing](https://opendds.readthedocs.io/en/dds-3.25/building/index.html#building-and-installing "https://opendds.readthedocs.io/en/dds-3.25/building/index.html#building-and-installing")  
```bash
$ export INSTALL_PREFIX=<install_dir>
$ ./configure --verbose --doc-group3 --java --prefix=<install_dir> [--tests --qt]
# $ ./setenv.sh
# $ ./configure --verbose --doc-group3 --java --prefix=<install_dir>
$ make -j 4
$ make install
$ cd ACE_wrappers
$ make install
```

# 2. Using OpenDDS
[Official Doc](https://opendds.readthedocs.io/en/dds-3.25/building/index.html#using-an-installed-opendds "https://opendds.readthedocs.io/en/dds-3.25/building/index.html#using-an-installed-opendds")
```bash
# Set env
<prefix>/share/dds/dds-devel.sh
<prefix>/share/ace/ace-devel.sh
<prefix>/share/tao/tao-devel.sh
```
> The <prefix> tree does not contain a tool for makefile generation. To use MPC to generate application makefiles, the MPC_ROOT subdirectory from the OpenDDS source tree can be used either in-place or copied elsewhere.

# 3. Example : Cpp
* compile
```bash
./configure --verbose --doc-group3 --prefix=$INSTALL_PREFIX --qt --tests
make -j 12 && make install
```

# 4. Example : Java
OpenDDS Developer's Guide : [http://download.ociweb.com/OpenDDS/OpenDDS-latest.pdf](http://download.ociweb.com/OpenDDS/OpenDDS-latest.pdf "http://download.ociweb.com/OpenDDS/OpenDDS-latest.pdf")  
* CHAPTER 10 : Java Bindings  

## 4.1. Code generation
```bash
$ACE_ROOT/bin/generate_export_file.pl Foo > Foo_Export.h
# NEW : Foo_Export.h

nvim Foo.mpc
# NEW : Foo.mpc
# project: dcps_java {
#
#   idlflags += -Wb,stub_export_include=Foo_Export.h \
#               -Wb,stub_export_macro=Foo_Export
#
#   dcps_ts_flags += -Wb,export_macro=Foo_Export
#
#   idl2jniflags += -Wb,stub_export_include=Foo_Export.h \
#                   -Wb,stub_export_macro=Foo_Export
#
#   dynamicflags += FOO_BUILD_DLL
#
#   specific {
#     jarname = DDS_Foo_types  
#     # can be left out if there's no need for jar file. use class files instead
#   }
#
#   TypeSupport_Files {
#     Foo.idl
#   }
#
#   # libout = $(PROJECT_ROOT)/lib
#   # can be added to export libraries(.so, .jar) to another location
# }

$ACE_ROOT/bin/mwc.pl -type gnuace
# NEW : GNUmakefile GNUmakefile.Foo

nvim Foo.idl
# NEW : Foo.idl
# module Baz {
#   @topic
#   struct Bar {
#     long x;
#   };
# };

cd $JAVA_HOME/include
cp linux/* .

make
# NEW : everything

# Add the directory containing libFoo.so to the LD_LIBRARY_PATH
```