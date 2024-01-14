RTIDDS <!-- omit in toc -->
===

- [Installation](#installation)
- [Licensing](#licensing)
- [Pub/Sub example](#pubsub-example)

# Installation
[official link](https://community.rti.com/static/documentation/connext-dds/6.1.0/doc/manuals/connext_dds_professional/getting_started_guide/cpp98/before.html#installing-connext-dds "https://community.rti.com/static/documentation/connext-dds/6.1.0/doc/manuals/connext_dds_professional/getting_started_guide/cpp98/before.html#installing-connext-dds")
> If you have installed a “license-managed” bundle (usually used for evaluation purposes), you do not need to install a target. License-managed bundles combine both the host and target in one package. They have `lm` in their name, such as `rti_connext_dds-6.1.0-lm-x64Win64VS2017.exe`. The `lm` bundle already installed the SDK libraries, so you can go straight to [Setting Up a License](https://community.rti.com/static/documentation/connext-dds/6.1.0/doc/manuals/connext_dds_professional/getting_started_guide/cpp98/before.html#section-gsg-license "https://community.rti.com/static/documentation/connext-dds/6.1.0/doc/manuals/connext_dds_professional/getting_started_guide/cpp98/before.html#section-gsg-license").

install via gui or command line

# Licensing
[official link](https://community.rti.com/static/documentation/connext-dds/6.1.0/doc/manuals/connext_dds_professional/getting_started_guide/cpp98/before.html#setting-up-a-license "https://community.rti.com/static/documentation/connext-dds/6.1.0/doc/manuals/connext_dds_professional/getting_started_guide/cpp98/before.html#setting-up-a-license")

# Pub/Sub example
[official link](https://community.rti.com/static/documentation/connext-dds/6.1.0/doc/manuals/connext_dds_professional/getting_started_guide/cpp98/intro_pubsub_cpp.html "https://community.rti.com/static/documentation/connext-dds/6.1.0/doc/manuals/connext_dds_professional/getting_started_guide/cpp98/intro_pubsub_cpp.html")
run code generator (ex .idl -> .cxx)
```bash
cd 2_hello_world
rtiddsgen -language c++ -platform <architecture> -create makefiles -create typefiles -d c++98 hello_world.idl
```
change some code -> compile -> run
```bash
# compile
make -f makefile_hello_world_x64Linux4gcc7.3.0
```