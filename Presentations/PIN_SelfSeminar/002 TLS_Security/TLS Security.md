TLS Security  <!-- omit in toc -->
===

**Table of Contents**
- [1. Attack vs Defense](#1-attack-vs-defense)
  - [1.1. 보안 CIA 3요소](#11-보안-cia-3요소)
  - [1.2. 보안에 대한 공격](#12-보안에-대한-공격)
  - [1.2.1. 네트워크 통신상의 공격](#121-네트워크-통신상의-공격)
- [2. Encryption](#2-encryption)
  - [2.1. 대칭키 암호화](#21-대칭키-암호화)
  - [2.1.1. 블록암호 알고리즘](#211-블록암호-알고리즘)
    - [2.1.2. 블록암호 모드](#212-블록암호-모드)
  - [2.2. 비대칭키 암호화](#22-비대칭키-암호화)
- [3. Key Exchange](#3-key-exchange)
- [4. Authentication](#4-authentication)
  - [4.1. MAC](#41-mac)
  - [4.2. Hash](#42-hash)
- [5. Digital Signature](#5-digital-signature)
- [6. Certificate](#6-certificate)
- [7. TLS Protocol](#7-tls-protocol)
- [8. OpenSSL](#8-openssl)


# 1. Attack vs Defense
Reference : [InfoSec](https://www.microsoft.com/en-us/security/business/security-101/what-is-information-security-infosec "https://www.microsoft.com/en-us/security/business/security-101/what-is-information-security-infosec")
## 1.1. 보안 CIA 3요소
1. 기밀성(Confidentiality)
   * 승인되지 않은 사람은 정보 열람 불가
2. 무결성(Integrity)
   * 승인되지 않은 사람은 정보 수정 불가
3. 가용성(Availability)
   * 승인된 사람이 정보가 필요할 때 사용 가능
   > 필요할 때 언제나  
   > High-Availability : 고가용성

## 1.2. 보안에 대한 공격
1. 도청
   * 암호화
   > 기밀성
2. 위장
   * 인증
   > 무결성
3. 변형
   * 무결성
   > 기밀성, 가용성
4. 중단
   * 가용성

## 1.2.1. 네트워크 통신상의 공격
1. 노출
2. 트래픽 분석
3. 위장
4. 내용수정
5. 순서수정
6. 시간수정
7. 송신처부인
8. 수신처부인
> 1, 2 : 기밀성  
> 3 ~ 6 : 인증  
> 7 : 전자 서명  
> 8 : 전자 서명, 보안 프로토콜  

# 2. Encryption
* 평문
* 암호문
* 암호화
* 복호화
* 비밀키

## 2.1. 대칭키 암호화
암/복호화 : 비밀키

## 2.1.1. 블록암호 알고리즘
AES, DES, ARIA, LEA, etc.
> 128, 192, 256 : Key 길이

### 2.1.2. 블록암호 모드
* ECB
* CBC
  * IV : Initial Vector
  * XOR -> Encrypt -> Use cipher as Vector
  * Use cipher as Vector(>1) -> Decrypt -> XOR
* CFB
* OFB
* CTR
* GCM
* OCB

## 2.2. 비대칭키 암호화
암호화 : 공개키(Public key)  
복호화 : 개인키(Private key)

소인수분해, 이산대수의 2가지 분류
> RSA, ECC  
> 보통 암호화보다 전자서명 및 키 교환에서 사용

공개키, 개인키 생성 후 공개키만 전달

# 3. Key Exchange
송신자와 수신자가 보안 통신을 위한 키를 공유하는 알고리즘
> used as Pre-Master Secret(?)  
> DH, ECDH

**DH Example**
> for ECDH change `^` to `x`

A : `x`로 `Ax = G^x` 를 만들어서 전달  
B : `y`로 `By = G^y` 를 만들어서 전달  
A : `K = By^x = G^y^x`를 통해 키 생성  
B : `K = Ax^y = G^x^y`를 통해 키 생성  

# 4. Authentication
인증 : 메시지의 무결성을 검증하는데 이용하는 기법  
수신받은 데이터가 전송된 것과 정확히 동일하며, 송신자의 신원이 알려진 것과 일치함을 보장
* Hash
* Enc
* MAC

## 4.1. MAC
Message Authentication Code
메시지의 비밀키를 입력으로 하여 고정된 작은 크기의 데이터 블록 생성  
* CMAC : Cipher based MAC
* HMAC : Hash based MAC
* CCM : Counter with Cipher Block Chaining MAC
* GMC : Galois/Counter Mode

## 4.2. Hash
Hashing에 의해 만들어진 요약이나 지문  
CRC와 같이 해당 메시지의 무결성을 보장하기 위해 사용  
단방향성, 충돌 방지
* MD5
* SHA-{0, 1, 256, 512}

# 5. Digital Signature
본인만이 가진 전자적인 정보를 전자 문서에 포함하여 자신이 만들었다는 것을 증명
* 공개키, 해싱을 사용
* 비밀키 암호화를 사용 
* 해싱을 사용

알고리즘 : 개인키로 암호화, 공개키로 복호화
* RSA
* ECDSA

# 6. Certificate
인증서 : 네트워크 상에서 온라인 신분을 인증하는데 사용되는 전자 자격 증명  
공개키가 첨부된 공개키 인증서를 사용  
X.509 인증서 : 공개키 인증서의 표준 규격  
CA Certificate, Root Certificate, Self-Signed Certificate  
PKI

# 7. TLS Protocol
```
Client                                        Server

ClientHello          -------->
                                         ServerHello
                                        Certificate*
                                  ServerKeyExchange*
                                 CertificateRequest*
                     <--------       ServerHelloDone
Certificate*
ClientKeyExchange
CertificateVerify*
[ChangeCipherSpec]
Finished             -------->
                                  [ChangeCipherSpec]
                     <--------              Finished
Application Data     <------->      Application Data
```

# 8. OpenSSL
