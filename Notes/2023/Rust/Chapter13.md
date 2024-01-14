Utility Trait <!-- omit in toc -->
===

**Table of Contents**
- [1. Utility Traits](#1-utility-traits)


# 1. Utility Traits
1. 언어 확장 트레이트
   * Drop, Deref, DerefMut 등과 같이 러스트의 연장점 역할을 함
2. 마커 트레이트
   * Sized, Copy로 주로 제네릭 타입 변수의 바운드 부분에 알려 두어야 할 제약 조건을 표현하기 위한 용도로 쓰임
3. 공용 어휘 트레이트
   * AsRef, AsMut, Borrow, BorrorMut 등과 같이 다른 크레이트의 기능을 바로 연결해 쓸 수 있게 함

|트레이트|설명|
|---|---|
|Drop|소멸자, 값이 드롭될 때마다 러스트가 자동으로 실행|
|Sized|컴파일 시점에 알 수 있는 고정된 크기를 갖는 타입임을 표시|
|Clone|값 복제를 지원하는 타입|
|Copy|단순 메모리 복사가 곧 복제인 타입|
|Deref, DerefMut|스마트 포인터 타입. 역참조 연산자의 동작 방식을 명시 가능|
|Default|합리적인 '기본값'이 있는 타입|
|AsRef, AsMut|현 타입에서 다른 타입의 레퍼런스를 빌려오기 위한 변환 트레이트|
|Borrow, BorrowMut|위와 비슷한 변환 트레이트. 여러 일관성을 보장|
|From, Into|현 타입의 값을 다른 타입으로 바꾸기 위한 변환 트레이트|
|TryFrom, TryInto|위와 같으나 실패할 수도 있는 변환에 사용|
|ToOwned|레퍼런스를 소유권이 있는 값으로 바꾸기 위한 변환 트레이트|