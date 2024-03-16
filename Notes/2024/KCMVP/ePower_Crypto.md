ePower Crypto  <!-- omit in toc -->
===

**Table of Contents**
- [1. ePower Crypto](#1-epower-crypto)
- [2. Used Methods](#2-used-methods)
  - [2.1. Block Cipher](#21-block-cipher)
    - [2.1.1. ARIA](#211-aria)
    - [2.1.2. LEA](#212-lea)
  - [2.2. Authorization](#22-authorization)
    - [2.2.1. HMAC](#221-hmac)
  - [2.3. Hash](#23-hash)
    - [2.3.1. SHA-256/384/512](#231-sha-256384512)
  - [2.4. Random](#24-random)
    - [2.4.1. CTR\_DRBG](#241-ctr_drbg)
  - [2.5. Signature](#25-signature)
    - [2.5.1. ECDSA](#251-ecdsa)
    - [2.5.2. EC-KCDSA](#252-ec-kcdsa)
  - [2.6. Key Exchange](#26-key-exchange)
    - [2.6.1. ECDH](#261-ecdh)


# 1. ePower Crypto
[Reference from NCSC](https://www.ncsc.go.kr:4018/main/cop/bbs/selectBoardArticle.do?bbsId=CryptoModule_main&nttId=13962&pageIndex=1 "https://www.ncsc.go.kr:4018/main/cop/bbs/selectBoardArticle.do?bbsId=CryptoModule_main&nttId=13962&pageIndex=1")

# 2. Used Methods
## 2.1. Block Cipher
### 2.1.1. ARIA
* Cipher
  *  ECB, CBC, CTR, CCM, GCM
* Key Length
  * 128, 192, 256(bit)
* Block Length
  * 128, 192, 256(bit)

### 2.1.2. LEA
* Cipher
  *  ECB, CBC, CTR, CCM, GCM
* Key Length
  * 128, 192, 256(bit)
* Block Length
  * 128, 192, 256(bit)

## 2.2. Authorization
### 2.2.1. HMAC
SHA-256/384/512 Based

## 2.3. Hash
### 2.3.1. SHA-256/384/512

## 2.4. Random
### 2.4.1. CTR_DRBG
Block Cipher : ARIA-128

## 2.5. Signature
### 2.5.1. ECDSA
* Curve
  * FIPS P-256
* Hash
  * SHA-256

### 2.5.2. EC-KCDSA
* Curve
  * FIPS P-256
* Hash
  * SHA-256

## 2.6. Key Exchange
### 2.6.1. ECDH
* Curve
  * FIPS P-256