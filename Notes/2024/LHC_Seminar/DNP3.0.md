DNP3.0 Security Authentication  <!-- omit in toc -->
===

**Table of Contents**
- [1. DNP3.0 SA](#1-dnp30-sa)
- [2. AuthN Mechanism](#2-authn-mechanism)
- [3. Sources](#3-sources)
- [Ref](#ref)

# 1. DNP3.0 SA
* Defined at IEEE 1815  
* Located at DNP3 Application Layer
* 암/복호화 방식은 제공하지 않음
* 사전 공유키 사용 가능
* Challange and Response
  * 주고 받기
* Aggressive
  * 그냥 다 주기?
* 키 관리 : 대칭키를 주로 사용(?)
  * 역할에 따라 4가지 종류 존재

# 2. AuthN Mechanism
* Challange and Response
  * OTP 생성
    * ID/PW 문제점 개선
  * Mac을 사용한 ASDU (Hmac, Gmac)
  * Challange : g120v1, Reply : g120v2
* Critical 판단 여부 : from Outstation에서 많이 하긴 하는데, 반대 여부도 있나?
  * Select, Operate : Critical (관리, 수정 등)
  * Read : non-Critical (단순 읽기 등)
  > 꼭 이런건 아니고 약간 예시느낌
* Aggressive Mode
  * Critical ASDU 자체로 MAC 생성해서 보냄

* Key change : g120v5

# 3. Sources
* TMW : SA only
* OpenDNP : TLS only, SA comming soon..?
* KDN Porting : SHA256 part and Rand part?
* defaultUserKey1 : hard codded update key

# Ref
* Boost.Asio