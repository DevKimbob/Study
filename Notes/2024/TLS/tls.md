Transport Layer Security Protocol <!-- omit in toc -->
===
> Referenced from RFC5246

**Table of Contents**
- [1. Introduction](#1-introduction)
- [2. Goals](#2-goals)
- [3. Goals of This Document](#3-goals-of-this-document)
- [4. Presentation Language](#4-presentation-language)
  - [4.1. Basic Block Size](#41-basic-block-size)
  - [4.2. Miscellaneous](#42-miscellaneous)
  - [4.3. Vectors](#43-vectors)
  - [4.4 Numbers](#44-numbers)
  - [4.5. Enumerateds](#45-enumerateds)
  - [4.5. Constructed Types](#45-constructed-types)
    - [4.6.1. Variants](#461-variants)
  - [4.7. Cryptographic Attributes](#47-cryptographic-attributes)
  - [4.8. Constants](#48-constants)
- [5. HMAC and the Pseudorandom Function](#5-hmac-and-the-pseudorandom-function)
- [6. The TLS Record Protocol](#6-the-tls-record-protocol)
  - [6.1. Connection States](#61-connection-states)
  - [6.2. Record layer](#62-record-layer)
    - [6.2.1. Fragmentation](#621-fragmentation)
    - [6.2.2. Record Compression and Decompression](#622-record-compression-and-decompression)
    - [6.2.3. Record Payload Protection](#623-record-payload-protection)
      - [6.2.3.1. Null of Standard Stream Cipher](#6231-null-of-standard-stream-cipher)
      - [6.2.3.2. CBC Block Cipher](#6232-cbc-block-cipher)
      - [6.2.3.3. AEAD Ciphers](#6233-aead-ciphers)
  - [6.3. Key Calculation](#63-key-calculation)
- [7. The TLS Handshaking Protocols](#7-the-tls-handshaking-protocols)
  - [7.1. Change Cipher Spec Protocols](#71-change-cipher-spec-protocols)
  - [7.2. Alert Protocol](#72-alert-protocol)
    - [7.2.1. Closure Alerts](#721-closure-alerts)
    - [7.2.2. Error Alerts](#722-error-alerts)
  - [7.3. Handshake Protocol Overview](#73-handshake-protocol-overview)
  - [7.4. Handshake Protocol](#74-handshake-protocol)
    - [7.4.1. Hello Messages](#741-hello-messages)
      - [7.4.1.1. Hello Request](#7411-hello-request)
      - [7.4.1.2. Client Hello](#7412-client-hello)
      - [7.4.1.3. Server Hello](#7413-server-hello)
      - [7.4.1.4. Hello Extensions](#7414-hello-extensions)
        - [7.4.1.4.1. Signature Algorithms](#74141-signature-algorithms)
    - [7.4.2. Server Certificate](#742-server-certificate)
    - [7.4.3. Server Key Exchange Message](#743-server-key-exchange-message)
    - [7.4.4. Certificate Request](#744-certificate-request)
    - [7.4.5. Server Hello Done](#745-server-hello-done)
    - [7.4.6. Client Certificate](#746-client-certificate)
    - [7.4.7. Client Key Exchange Message](#747-client-key-exchange-message)
      - [7.4.7.1. RSA-Encrypted Premaster Secret Message](#7471-rsa-encrypted-premaster-secret-message)
      - [7.4.7.2. Client Diffie-Hellman Public Value](#7472-client-diffie-hellman-public-value)
    - [7.4.8. Certificate Verify](#748-certificate-verify)
    - [7.4.9. Finished](#749-finished)
- [8. Passed for later...](#8-passed-for-later)


# 1. Introduction
The primary goal of the TLS protocol is to provide privacy and data integrity between two communicating applications

# 2. Goals
The goals of the TLS protocol, in order of priority, are as follows:
1. Cryptographic security
2. Interoperability
3. Extensibility
4. Relative efficiency

# 3. Goals of This Document
This document is intended primarily for readers who will be implementing the protocol and for those doing cryptographic analysis of it

# 4. Presentation Language
This document deals with the formatting of data in an external representation

## 4.1. Basic Block Size
The basic data block size is `one byte` (i.e., 8 bits). Multiple byte data items are concatenations of bytes, from `left to right`, from `top to bottom`.  
This byte ordering for multi-byte value is the commonplace `network byte order` or `big-endian` format.

## 4.2. Miscellaneous
Comments begin with `/*` and end with `*/`.  
Optional components are denoted by enclosing them in `[[ ]]` double brackets.  
Single-byte entities containing uninterpreted data are of type `opaque`.

## 4.3. Vectors
A vector (single-dimensioned array) is a stream of homogeneous data elements.  
The length declares the `number of bytes`, not the number of elements.
```c
// fixed-length vector
T T'[n];  /* n bytes */
opaque Datum[3];  /* three uninterpreted bytes */
Datum Data[9];  /* 3 consecutive 3 byte vectors */

// variable-length vector
T T'<floor..ceiling>;
opaque mandatory<300..400>;  /* length field is 2 bytes */
uint16 longer<0..800>;  /* zero to 400 16-bit unsigned integers */
```

## 4.4 Numbers
The Basic numeric data type is an unsigned byte(`uint8`). All larger numeric data types are formed from fixed-length series of bytes. The following numeric types are predefined.
```c
uint uint16[2];
uint uint24[3];
uint uint32[4];
uint uint64[8];
```

## 4.5. Enumerateds
An additional sparse data type is available called enum. One may optionally specify a value without its associated tag to force the width definition without defining a superfluous element.
```c
enum { e1(v1), e2(v2), ... , en(vn) [[, (n)]] } Te;
enum { red(3), blue(5), white(7) } Color;
enum { sweet(1), sour(2), bitter(4), (32000) } Taste;  /* Taste will consume two bytes in the data stream but can only assume the values 1, 2, or 4. */

Color color = Color.blue;  /* overspecified, legal */
Color color = blue;  /* correct, type implicit */
```

## 4.5. Constructed Types
Structure types may be constructed from primitive types for convenience.
```c
struct {
    T1 f1;
    T2 f2;
    ...
    Tn fn;
} [[T]];
```
> `T.f2` refers to the second field of the above declaration.

### 4.6.1. Variants
Defined structures may have variants based on some knowledge that is available within the environment. The selector must be an enumerated type that defines the possible variants the structure defines.
```c
struct {
    T1 f1;
    T2 f2;
    ...
    Tn fn;
    select (E) {
        case e1: Te1;
        case e2: Te2;
        case e3: case e4: Te3;
        ...
        case en: Ten;
    } [[fv]];
} [[Tv]];
```
```c
enum { apple, orange, banana } VariantTag;

struct {
    uint16 number;
    opaque string<0..10>; /* variable length */
} V1;

struct {
    uint32 number;
    opaque string[10];    /* fixed length */
} V2;

struct {
    select (VariantTag) { /* value of selector is implicit */
        case apple:
        V1;   /* VariantBody, tag = apple */
        case orange:
        case banana:
        V2;   /* VariantBody, tag = orange or banana */
    } variant_body;       /* optional label on variant */
} VariantRecord;
```

## 4.7. Cryptographic Attributes
The five cryptographic operations are designated as below.
|digital signing|stream cipher encryption|block cipher encryption|authenticated encryption with additional data (AEAD) encryption|public key encryption|
|---|---|---|---|---|
|digitally-signed|stream-ciphered|block-ciphered|aead-ciphered|public-key-encrypted|

A digitally-signed element is encoded as a struct `DigitallySigned`:
```c
struct {
    SignatureAndHashAlgorithm algorithm;
    opaque signature<0..2^16-1>;
} DigitallySigned;
```
> There's a lot more in the document

## 4.8. Constants
Typed constants can be defined for purposes of specification by declaring a symbol of the desired type and assigning values to it.
```c
struct {
    unit8 f1;
    uint8 f2;
} Example1;

Example1 ex1 = {1, 4};  /* assigns f1 = 1, f2 = 4 */
```

# 5. HMAC and the Pseudorandom Function
The TLS record layer uses a keyed Message Authentication Code (MAC) to protect message integrity.  
In addition, a construction is required to do expansion of secrets into blocks of data for the purposes of key generation or validation. This pseudorandom function (PRF) takes as input a secret, a seed, and an identifying label and produces an output of arbitrary length.

# 6. The TLS Record Protocol
The TLS Record Protocol is a layerd protocol. At each layer, messages may include fields for length, description, and content.  
The Record Protocol takes messages to be transmitted, fragments the data into manageable blocks, optionally compresses the data, applies a MAC, encrypts, and transmits the result. Received data is decrypted, verified, decompressed, reassembled, and then delivered to higher-level clients.

Four protocols that use the record protocol are described in this document: the handshake protocol, the alert protocol, the change cipher spec protocol, and the application data protocol.

## 6.1. Connection States
A TLS connection state is the operating environment of the TLS Record Protocol.  It specifies a compression algorithm, an encryption algorithm, and a MAC algorithm.  
Logically, there are always four connection states outstanding: the current read and write states, and the pending read and write states.

The security parameters for a TLS Connection read and write state are set by providing the following values:
* connection end
  * Whether this entity is considered the "client" or the "server" in this connection.
* PRF algorithm
  * An algorithm used to generate keys from the master secret.
* bulk encryption algorithm
  * An algorithm to be used for bulk encryption. This specification includes the key size of this algorithm, whether it is a block, stream, or AEAD cipher, the block size of the cipher (if appropriate), and the lengths of explicit and implicit initialization vectors (or nonces).
* MAC algorithm
  * An algorithm to be used for message authentication. This specification includes the size of the value returned by the MAC algorithm.
* compression algorithm
  * An algorithm to be used for data compression. This specification must include all information the algorithm requires to do compression.
* master secret
  * A 48-byte secret shared between the two peers in the connection.
* client random
  * A 32-byte value provided by the client.
* server random
  * A 32-byte value provided by the server.

These parameters are defined in the presentation language as:
```c
enum { server, client } ConnectionEnd;

enum { tls_prf_sha256 } PRFAlgorithm;

enum { null, rc4, 3des, aes } BulkCipherAlgorithm;

enum { stream, block, aead } CipherType;

enum { null, hmac_md5, hmac_sha1, hmac_sha256, hmac_sha384, hmac_sha512 } MACAlgorithm;

enum { null(0), (255) } CompressionMethod;

/* The algorithms specified in CompressionMethod, PRFAlgorithm,
    BulkCipherAlgorithm, and MACAlgorithm may be added to. */
struct {
    ConnectionEnd          entity;
    PRFAlgorithm           prf_algorithm;
    BulkCipherAlgorithm    bulk_cipher_algorithm;
    CipherType             cipher_type;
    uint8                  enc_key_length;
    uint8                  block_length;
    uint8                  fixed_iv_length;
    uint8                  record_iv_length;
    MACAlgorithm           mac_algorithm;
    uint8                  mac_length;
    uint8                  mac_key_length;
    CompressionMethod      compression_algorithm;
    opaque                 master_secret[48];
    opaque                 client_random[32];
    opaque                 server_random[32];
} SecurityParameters;
```

The record layer will use the security parameters to generate the following six items (some of which are not required by all ciphers, and are thus empty):
```
client write MAC key
server write MAC key
client write encryption key
server write encryption key
client write IV
server write IV
```

---

Once the security parameters have been set and the keys have been generated, the connection states can be instantiated by making them the current states. These current states MUST be updated for each record processed. Each connection state includes the following elements:
* compression state
  * The current state of the compression algorithm.
* cipher state
  * The current state of the encryption algorithm. This will consist of the scheduled key for that connection. For stream ciphers, this will also contain whatever state information is necessary to allow the stream to continue to encrypt or decrypt data.
* MAC key
  * The MAC key for this connection, as generated above.
* sequence number
  * Each connection state contains a sequence number, which is maintained separately for read and write states. The sequence number MUST be set to zero whenever a connection state is made the active state. Sequence numbers are of type uint64 and may not exceed 2^64-1. Sequence numbers do not wrap. If a TLS implementation would need to wrap a sequence number, it must renegotiate instead. A sequence number is incremented after each record: specifically, the first record transmitted under a particular connection state MUST use sequence number 0.

## 6.2. Record layer
The TLS record layer receives uninterpreted data from higher layers in non-empty blocks of arbitrary size.

### 6.2.1. Fragmentation
### 6.2.2. Record Compression and Decompression
### 6.2.3. Record Payload Protection
#### 6.2.3.1. Null of Standard Stream Cipher
#### 6.2.3.2. CBC Block Cipher
#### 6.2.3.3. AEAD Ciphers
## 6.3. Key Calculation

# 7. The TLS Handshaking Protocols
TLS has three subprotocols that are used to allow peers to agree upon security parameters for the record layer, to authenticate themselves, to instantiate negotiated security parameters, and to report error conditions to each other.

The Handshake Protocol is responsible for negotiating a session, which consists of the fallowing items:
* session identifier
  * An arbitrary byte sequence chosen by the server to identify an active or resumable session state.
* peer certificate
  * X509v3 certificate of the peer. This element of the state may be null.
* compression method
  * The algorithm used to compress data prior to encryption.
* cipher spec
  * Specifies the pseudorandom function (PRF) used to generate keying material, the bulk data encryption algorithm (such as null, AES, etc.) and the MAC algorithm (such as HMAC-SHA1). It also defines cryptographic attributes such as the mac_length. (See Appendix A.6 for formal definition.)
* master secret
  * 48-byte secret shared between the client and server.
* is resumable
  * A flag indicating whether the session can be used to initiate new connections.

## 7.1. Change Cipher Spec Protocols
The change cipher spec protocol exists to signal transitions in ciphering strategies. The protocol consists of a single message, which is encrypted and compressed under the current (not the pending) connection state. The message consists of a single byte of value 1.
```c
struct {
    enum { change_cipher_spec(1), (255) } type;
} ChangeCipherSpec;
```

The ChangeCipherSpec message is sent by both the client and the
server to notify the receiving party that subsequent records will be
protected under the newly negotiated CipherSpec and keys.  Reception
of this message causes the receiver to instruct the record layer to
immediately copy the read pending state into the read current state.
Immediately after sending this message, the sender MUST instruct the
record layer to make the write pending state the write active state.

## 7.2. Alert Protocol
### 7.2.1. Closure Alerts
### 7.2.2. Error Alerts
## 7.3. Handshake Protocol Overview
## 7.4. Handshake Protocol
### 7.4.1. Hello Messages
#### 7.4.1.1. Hello Request
#### 7.4.1.2. Client Hello
#### 7.4.1.3. Server Hello
#### 7.4.1.4. Hello Extensions
##### 7.4.1.4.1. Signature Algorithms
### 7.4.2. Server Certificate
### 7.4.3. Server Key Exchange Message
### 7.4.4. Certificate Request
### 7.4.5. Server Hello Done
### 7.4.6. Client Certificate
### 7.4.7. Client Key Exchange Message
#### 7.4.7.1. RSA-Encrypted Premaster Secret Message
#### 7.4.7.2. Client Diffie-Hellman Public Value
### 7.4.8. Certificate Verify
### 7.4.9. Finished

# 8. Passed for later...