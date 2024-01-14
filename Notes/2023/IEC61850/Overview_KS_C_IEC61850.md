# Overview from KS C IEC 61850 <!-- omit in toc -->

**Table of Contents**
- [IEC 61850](#iec-61850)
- [Levels](#levels)
- [Communication Service](#communication-service)
- [SCL](#scl)
- [Interface](#interface)

# IEC 61850
여러 제조사에서 공급한 IED들이 서로 상호 운용성을 가질 수 있도록 하기 위한 프레임워크를 제공하는 목적을 가짐.

# Levels
* Station Level : 일반적인 원격 입출력, 지능형 센서 및 액츄에이터들
* Bay Level : 각 베이의 제어, 보호 또는 감시 장치 포함
* Process Level : 데이터베이스, 운영자의 작업장, 원격 통신 인터페이스를 갖춘 스테이션 컴퓨터 포함

or...

변전소 내 설치 구조가 아닌 통신만을 고려한 계층 구조
* Station Level : 시스템의 중앙 서버 역할 부분
* Bay Level : 변전소에 있는 보호기기들의 부분
* Process Level : 계측 설비들의 부분

# Communication Service
* Client-Server : MMS
* Publisher-Subscriber : GOOSE
* Multicast Sample Value(?) : SV

# SCL
* 시스템 기능 명세
* IED 기능 설명
* 전력 유틸리티 자동화 시스템 설명

# Interface
* Station Bus : 전체 변전소를 상호 연결하고, 중앙 관리 장치와 개별 베이 간의 연결성 제공
* Process Bus : 1차 계측 및 제어 장비를 IED에 연결

<img src=images/Levels.png alt=Levels.png width=500>