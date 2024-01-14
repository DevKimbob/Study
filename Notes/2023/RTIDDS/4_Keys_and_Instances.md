# 4. Keys and Instances <!-- omit in toc -->

continue in [official link](https://community.rti.com/static/documentation/connext-dds/6.1.0/doc/manuals/connext_dds_professional/getting_started_guide/cpp98/intro_keys_instances.html "https://community.rti.com/static/documentation/connext-dds/6.1.0/doc/manuals/connext_dds_professional/getting_started_guide/cpp98/intro_keys_instances.html")

> gonna come back to writing notes when there's something important to write down for later use.

> Somtimes, we wamt to use one Topic to publish samples of data for several different objects, such as flights or sensors. Connext DDS uses "instances" to represent these real-world objects.

> When you need to represent multiple objects within a DDS Topic, you use a key to establish instances. An instance is the object identified by the key.

> Key fields can be specified by annotating them with `@key` in the IDL file.

**Table of Contents**
- [4.1.1. Writing an Instance](#411-writing-an-instance)
- [4.1.2. Reading an Instance](#412-reading-an-instance)
- [4.1.3. Instance Lifecycle](#413-instance-lifecycle)


## 4.1.1. Writing an Instance
```idl
// Temperature data type
struct Temperature {

    // Unique ID of the sensor sending the temperature. Each time a sample is
    // written with a new ID, it represents a new sensor instance.
    @key
    string<256> sensor_id;

    // Degrees in Celsius
    long degrees;

};
```
A DataWriter can write multiple instances just by setting the key fields to unique values.

<img src=images/Instance.png alt="Instance" width=500>

## 4.1.2. Reading an Instance
When the application gets the data_available notification from an instance lifecycle event, retrieving an instance is identical to retrieving a sample (except that you have some additional options).

## 4.1.3. Instance Lifecycle
* Alive
* Not alive, disposed(we don't need to track it anymore)
* Not alive, no writers

 