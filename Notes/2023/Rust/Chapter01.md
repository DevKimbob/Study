Rust <!-- omit in toc -->
===

**Table of Contents**
- [1. Rust](#1-rust)
- [2. Why](#2-why)


# 1. Rust
러스트가 좋은 이유
* 안전성이 좋다
* 실행 속도가 빠르다

# 2. Why
러스트의 특징
* **런타임에 해야 할 동작이 컴파일타임에 이루어진다**
* 컴파일 언어
  * 컴파일러의 성능이 매우 훌륭하다
  * 각 객체애 대한 수명과 접근권한을 관리할 수 있다
  * 변수의 타입을 추론할 수 있다
* 정적 타입
  * 타입 추론으로 타입을 명시하지 않아도 된다
  * 타입 추론이 런타임이 아니라 컴파일타임에 이루어진다
* GC(Garbage Collector)가 존재하지 않는다
  * 객체를 수명으로 관리한다
  * 객체의 생명주기 관리(?)를 런타임이 아니라 컴파일타임에 진행한다
* Zero-Cost Abstractions
  > adding higher-level programming concepts, like generics, collections and so on 
do not come with a run-time cost, only compile time cost
  * 트레이트, 이터레이터 등의 구현이 타 언어들의 구현과 다르다
    > 모든 타입이 클래스이거나, 호출마다 래퍼클래스로 감싸는 방식을 사용하지 않는다
