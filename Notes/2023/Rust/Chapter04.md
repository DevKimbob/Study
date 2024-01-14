Ownership and Move <!-- omit in toc -->
===

**Table of Contents**
- [1. Ownership](#1-ownership)
  - [1.1. 소유](#11-소유)
- [2. Move](#2-move)
  - [2.1. 이동](#21-이동)
  - [2.2. 이동으로 처리되는 연산들](#22-이동으로-처리되는-연산들)
  - [2.3. 이동에서 주의점](#23-이동에서-주의점)
- [3. 이동과 제어흐름](#3-이동과-제어흐름)
  - [3.1. 기본 원칙](#31-기본-원칙)
  - [3.2. 인덱싱을 써서 접근할 때 이동](#32-인덱싱을-써서-접근할-때-이동)
  - [3.3. 이동의 예외 : Copy 타입](#33-이동의-예외--copy-타입)
- [4. Rc, Arc](#4-rc-arc)


# 1. Ownership
## 1.1. 소유
소유한다 : 소유 객체가 피소유 객체의 해제 시점을 결정한다. 즉, 소유자가 소멸될 때 그의 소유물도 함께 소멸된다.  
드롭(Drop) : C/C++ 에서의 해제와 같은 개념. 변수는 자신이 선언된 블록을 벗어날 때 드롭되어 소멸된다.
```cpp
int main() {
    int *array = new int(10);  // 할당, 생성

    delete array;  // 해제, 소멸
    // 해제를 명시적으로 해주지 않으면 메모리 누수가 일어남
}
```
```rust
fn my_own() {
    let array = vec![1, 2, 3];  // 할당, 소유
}  // 드롭, 소멸

fn my_drop() {
    let array = vec![1, 2, 3];  // 할당, 소유

    drop(array);  // 드롭, 소멸
}
```

# 2. Move
## 2.1. 이동
```rust
let s = vec![1, 2, 3];
let t = s;  // t로 소유권 이동, s는 미초기화 상태
let u = s;  // 컴파일 에러
```
배정을 이동으로 처리할 때의 장점
1. 비용이 거의 들지 않는다.
2. 객체에 대한 소유권이 확실하다.
3. 복사본이 필요한 경우에는 명시해주기만 하면 된다.
    ```rust
    let s = vec![1, 2, 3];
    let t = s.clone();  // 이동 없이 복사본 생성(깊은복사)
    let u = s.clone();  // 에러없이 컴파일
    ```

## 2.2. 이동으로 처리되는 연산들
* 값을 이미 초기화된 변수에 옮기는 경우
    ```rust
    let mut s = "One".to_string();
    s = "Two".to_string();  // "One"이 드롭됨
    ```
    ```rust
    let mut s = "One".to_string();
    let t = s;  // "One"이 t로 이동
    s = "Two".to_string();  // "One"이 드롭되지 않음
    ```
* 짬뽕 예시
    ```rust
    struct Person { name: String, birth: i32 }  // 구조체 정의

    let mut people = Vec::new();  // Vec::new()에서 people로의 이동
    people.push(
        Person {name: "James".to_string(), birth: 1525 }  // "James"에서 name으로 이동
    );  // Person 객체에서 people로의 이동. people은 Person의 소유권을 가지며, name이 가진 String의 간접 소유자가 됨
    ```

## 2.3. 이동에서 주의점
이동의 적용 대상은 **값 자체**이지, 그가 소유한 **힙 저장소**가 아니다. 벡터와 문자열의 경우 값 자체는 3워드로 된 헤더 뿐이며, 잠재적으로 크기가 늘어날 수 있는 `요소 배열`과 `텍스트 버퍼`는 힙에 저장된다.
> 가변크기를 가진 정보는 힙에 그대로 저장. 크기가 고정적인 정보가 이동

# 3. 이동과 제어흐름
## 3.1. 기본 원칙
어떤 변수의 값이 이동될 가능성이 있고, 이동 이후에 값이 새로 주어지지 않는다면, 그 변수는 미초기화 상태로 간주한다.
```rust
let x = vec![1, 2, 3];
if c {
    f(x);  // 이동될 가능성
    // 이동 후 값이 새로 주어지지 않음
} else {
    g(x);  // 이동될 가능성
    // 이동 후 값이 새로 주어지지 않음
}
// 이동 후 값이 새로 주어지지 않음
h(x);  // x는 미초기화 상태로 간주, 따라서 컴파일 에러
```
```rust
let x = vec![1, 2, 3];
if c {
    f(x);  // 이동될 가능성
    // 이동 후 값이 새로 주어지지 않음
} else {
    println!("Hello");  // 이동될 가능성 없음
}
h(x);  // x는 미초기화 상태로 간주, 따라서 컴파일 에러
```
```rust
let x = vec![1, 2, 3];
while f() {
    g(x);  // x는 첫 반복 시에 이동되기 때문에 두 번째 반복 부터는 미초기화상태, 컴파일 에러
}
```
```rust
let mut x = vec![1, 2, 3];  // mut keyword 추가됨에 주의
while f() {
    g(x);  // x 이동
    x = h();  // 새 값 주어짐
}
e(x);  // 컴파일 에러 없음
```

## 3.2. 인덱싱을 써서 접근할 때 이동
* 몇 가지의 경우에 대해서는 이동이 금지되어 할당 자체가 컴파일 에러를 일으키는 경우도 존재한다.
```rust
let mut v = Vec::new();
for i in 101 .. 106 {
    v.push(i.to_string());
}

let thrid = v[2];  // 컴파일 에러. 레퍼런스를 사용하거나 다른 방법 사용
```
> 다른방법 예시 : pop, 다른 값과 교체, 마지막 요소와 교체 후 pop 등

* for 루프로 Vector를 전달할 때
```rust
let v = vec!["1".to_string(), "2".to_string(), "3".to_string()];

for mut s in v {  // loop 내부코드가 v의 소유권을 넘겨받고, v는 미초기화 상태
                  // 벡터를 요소 단위로 분해하여 반복마다 s로 옮김
    println!("{}", s);
    let c = s;
    println!("{}", s);  // 컴파일 에러. s의 소유권은 c로 이동하고 미초기화 상태
}

let new_v = v;  // 컴파일 에러. v의 소유권은 for 루프로 이동하고 미초기화 상태
```

* Option에 대한 `take`메서드 존재
    > Option의 값을 함수 호출부에 전달하고 None저장(?)

## 3.3. 이동의 예외 : Copy 타입
`i32`와 같이 러스트가 Copy 타입으로 지정해둔 타입들은 갑 배정시 값이 이동하지 않고 복사된다. 표쥰 Copy 타입에는 `모든 머신 정수`와 `부동소수점`수치 타입, `char`와 `bool`타입, 그리고 기타 몇가지가 포함되며, Copy 타입으로 된 `튜플`이나 `고정 길이 배열`도 Copy타입이다.  

간단한 비트 단위 복사로 복사본을 만들 수 있는 타입만 Copy가 될 수 있다. `String`은 힙에 할당된 버퍼를 소유하므로 Copy 타입이 아니다. 따라서 값을 드롭할 때 특별한 처리가 필요한 타입은 Copy가 될 수 없다고도 볼 수 있다.  

사용자 정의 타입인 `struct`와 `enum`타입은 기본적으로는 Copy가 아니다. 하지만 Copy타입만을 필드로 가지는 경우에 `#[derive(Copy, Clone)]`어트리뷰트를 통해 타입을 Copy로 만들 수 있다.
```rust
#[derive(Copy, Clone)]
struct Label { number: u32 }

fn print(l: Label) { println!("Stamp: {}", l.number); }

let l = Label { number: 3 };
print(l);
print(l);
```

# 4. Rc, Arc
동일한 객체에 대한 여러개의 포인터를 가지고 싶을 때 사용할 수 있는 Arc와 Rc는 다음 특징을 제외하면 동일하다. Arc의 경우 스레드 간에 직접 공유해도 안전하고, Rc는 스레드 안전성은 없는 대신 코드 속도가 더 빠르다.
> Rc : Reference Count  
> ARC : Atomic Reference Count

```rust
use std::rc::Rc;

let s = Rc::new("hi".to_string());
let t = s.clone();  // clone을 사용해도 힙을 복사하는 것이 아니라, reference count만 증가
let u = s.clone();
println!("{}", s);  // hi
println!("{}", u);  // hi
```

Rc(Arc도 동일하지만 생략)포인터가 소유한 값은 변경할 수 없다.
```rust
use std::rc::Rc;

let s = Rc::new("hi".to_string());
s.push('!');  // 컴파일 에러
s.push_str("Push");  // 컴파일 에러
```

Rc에 대한 이동
```rust
let s = Rc::new("hi".to_string());
println!("{}", Rc::strong_count(&s));  // 1
let t = s.clone();
println!("{}", Rc::strong_count(&s));  // 2
let u = s.clone();
println!("{}", Rc::strong_count(&s));  // 3
let mv = s;  // s만 mv로 이동
println!("{}", Rc::strong_count(&mv));  // 3
```