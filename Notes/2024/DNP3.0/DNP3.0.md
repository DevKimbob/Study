DNP3.0  <!-- omit in toc -->
===
> Simplified

**Table of Contents**
- [Yeah...](#yeah)
  - [Point](#point)
  - [Groups](#groups)
  - [Variations](#variations)
  - [DNP3 objects](#dnp3-objects)
  - [Static](#static)
  - [Events](#events)
  - [Classes](#classes)
- [Message structure](#message-structure)
  - [Application Layer fragments](#application-layer-fragments)
    - [Application Header](#application-header)
    - [Object Headers](#object-headers)


# Yeah...
## Point
uniquely identifiable physical or logical entity

## Groups
provide a means of classifying the type or types of data within a message

## Variations
choice of encoding formats for many of the data types

## DNP3 objects
encoded representation of data from a point, or other structure, that is formatted according to its group and variation number for transport in a message

## Static
the point's current value, which is the most recently measured

## Events
something of significance happening. state changes, ...

## Classes
organize static data and events into several categories
* 0 : static data
* 1, 2, 3 : events

# Message structure
## Application Layer fragments
* Request Fragment
    | Application Request Header | First Object Header | DNP3 Ojbects | ... | Last Object Header | DNP3 Objects |
    |---|---|---|---|---|---|
* Response Fragment
    | Application Response Header | First Object Header | DNP3 Ojbects | ... | Last Object Header | DNP3 Objects |
    |---|---|---|---|---|---|

### Application Header
* Application Request Header
    |Application Control|Function Code|
    |---|---|
    |(1 octet)|(1 octet)|
* Application Response Header
    |Application Control|Function Code|Internal Indications|
    |---|---|---|
    |(1 octet)|(1 octet)|(2 octets)
---
* Application Control octet
    |7|6|5|4|3|2|1|0|
    |:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
    |FIR|FIN|CON|UNS|SEQ|"|"|"|
    * FIR : first fragment
    * FIN : final message
    * CON : return confirm message?
    * UNS : contains unsolicited response or a confirmation of it
    * SEQ : verify fragment order
* Function Code octet
  * identifies the purpose of the message
  * Request : 0 ~ 128
  * Response : 129 ~ 255
* Internal Indications
    |First Octet|Second Octet|
    |---|---|
    * IINx.b : x(1 for first, 2 for second), b(bit number)
    * indicate certain states and error conditions within the outstation

### Object Headers
* Object Header
    |Object Type Field|"|Qualifier Field|Range Field|
    |---|---|---|---|
    |Group (1 octet)|Variation (1 octet)|(1 octet)|(dependent upon qualifier)|
    * Qualifier and Range fields
        |7|6|5|4|3|2|1|0|
        |:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
        |Res|OPC*|"|"|RSC*|"|"|"|
        > OPC : Object Prefix Code  
        > RSC : Range Specifier Code
        * RES : reserved for future use
        * OPC : index number or an object size
            > (what, if any, prefix value appers before each of the DNP3 objects that follow the object header)
        * RSC : whether a range field is used and, if so, what it contains and how large it is
            > 0x5B : 0b_0101_1011  
            > 5 : Objects are prefixed with an object size  
            > B : Variable format qualifier, range field contains 1-octet count of objects
        * Preferred qualifier codes
          * 00, 01, 06, 07, 08, 17, 28, 5B