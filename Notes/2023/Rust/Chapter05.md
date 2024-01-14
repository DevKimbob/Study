Reference <!-- omit in toc -->
===

**Table of Contents**
- [1. Reference](#1-reference)
  - [1.1. Usage Example](#11-usage-example)
  - [1.2. Ref of Ref](#12-ref-of-ref)
  - [1.3. 익명변수](#13-익명변수)
  - [1.4. Slice, Trait](#14-slice-trait)
- [2. Lifetime](#2-lifetime)
  - [2.1. 수명 매개변수](#21-수명-매개변수)
- [3. Shared vs Mutable](#3-shared-vs-mutable)


# 1. Reference
레퍼런스 : 소유권을 가지지 않는 포인터 타입으로 자신이 가리키는 대상의 수명에 아무런 영항을 주지 않는다. 오히려 자신이 가리키는 대상보다 더 오래 살아있으면 안된다. 따라서 어떤 값의 레퍼런스를 만드는 걸 두고 값을 **빌려 온다**고 표현한다.

||참조 대상 읽기|참조 대상 수정|레퍼런스 수|표현식|Copy타입|
|---|---|---|---|---|---|
|공유된 레퍼런스(shared reference)|가능|불가능|여러 개|&e|O|
|변경할 수 있는 레퍼런스(mutable reference)|가능|가능|한 개|&mut e|X|
1. shared reference가 존재하는 동안에는 참조하는 값 자체가 잠기므로 소유자라고 해도 값을 수정할 수 없음
2. mutable reference를 가지고 있는 기간동안 참조하는 값의 독점적인 접근 권한을 가지기 때문에 같은 값을 참조하는 다른 모든 종류의 레퍼런스를 사용할 수 없음
3. Multiple Readers or Single Writer 규칙을 시행하기 위해 둘을 나누었다고 할 수 있음  

## 1.1. Usage Example
```rust
// #1
let mut x = 10;
let y = &mut x;
*y = 20;

// #2
struct Label { name: String }

let mut str = Label { name: "Hello".to_string() };
let rstr = &mut str;
println!("{}", (*rstr).name);
println!("{}", rstr.name);  // 암묵적 역참조
```

함수로 레퍼런스를 전달하거나 반환할 수도 있다.
```rust
struct Label { number: u32 }

fn print(l: &Label) { println!("{}", l.number); }

let l = Label { number: 3 };
print(&l);
print(&l);
```

`.`연산자는 메서드 호출 시에 필요할 경우 암묵적으로 자신의 왼쪽에 있는 피연산자의 레퍼런스를 빌려올 수 있다.
```rust
let mut v = vec![10, 20];
v.sort();
(&mut v).sort();
```

러스트는 `&`와 `*`연산자를 써서 레퍼런스를 만들고 따라가야 하며, `.`연산자를 쓸 때만 암묵적인 차용과 역참조가 일어난다.

## 1.2. Ref of Ref
러스트는 레퍼런스의 레퍼런스를 만들 수 있고, `.`연산자를 사용 시 최종적으로 가리키는 대상을 찾을 때까지 거듭해서 연결고리를 따라간다.
```rust
struct Label { number: u32 }

let a = Label { number: 10 };
let b = &a;
let c = &b;
let d = &c;
println!("{}", d.number);
```

레퍼런스 메모리 자체를 비교하고 싶다면 `std::ptr::eq`를 사용한다.
```rust
let a = 10;
let b = 10;
let aa = &a;
let bb = &b;

println!("{}", a == b);  // true
println!("{}", aa == bb);  // true
println!("{}", std::ptr::eq(aa, bb));  // false
```

## 1.3. 익명변수
```rust
let &a = &100;
```
표현식의 값을 보관할 익명 변수를 만들고, 이를 가리키는 레퍼런스를 만든다.

## 1.4. Slice, Trait
러스트는 두 가지 종류의 팻 포인터를 더 가지고 있다.
> 팻 포인터 : 어떤 값의 주소와 그 값을 사용하는데 필요한 추가 정보를 갖는 2워드 크기의 값

# 2. Lifetime
변수의 수명은 자신에게서 차용된 레퍼런스의 수명을 반드시 포함(`contain`)하거나 에워싸야(`enclose`)한다.

## 2.1. 수명 매개변수
```rust
fn f(p: &i32) { ... }
fn f<'a>(p: &'a i32) { ... }  // 수명 'a(틱 A 라고 읽음), 수명이 'a인 i32의 레퍼런스를 받는 함수를 정의. (<'a>는 생략 가능?)
// <`a> : 임의의 수명 'a에 대해서
fn f(p: &'static i32) { ... }  // 'static 수명, 수명이 'static한 i32의 레퍼런스를 받는 함수를 정의
```
함수의 시그니처만을 보고 인수가 함수의 호출 구간보다 더 긴 수명을 가진 어딘가에 보관되는 일이 없다는 것을 알 수 있다.  
시그니처만을 보고서 함수가 인수를 가지고 할 수 있는 일과 할 수 없는 일을 파악할 수 있다.  

컴파일러는 주어진 수명 매개변수들과 변수들의 수명을 보고 모두를 만족하는 수명을 찾기위해 노력한다.

---
1. 하나의 원소에 대한 수명
```rust
fn first<'a>(v: &'a [i32]) -> &'a i32 { &v[0] }

let m;
{
    let v = [1, 2, 3];
    m = first(&v);
    println!("{}", m);
}
println!("{}", m);  // v의 수명과 m의 수명을 동시에 만족하는 수명 'a 찾기 실패. 컴파일 에러
```
```rust
struct S<'a> { r: &'a i32 }  // 스트럭트 타입이 레퍼런스를 갖는 경우에는 반드시 해당 레퍼런스의 수명을 지정해야함

let s;
{
    let x = 10;
    s = S { r: &x };
    println!("{}", s.r);
}
println!("{}", s.r);  // 컴파일 에러
```

---
2. 두개 이상의 원소에 대한 수명
각각의 변수에 다른 수명 매개변수를 할당 가능
```rust
fn f<'a>(r: &'a i32, s: &'a i32) -> &'a i32 { r }
fn f<'a, 'b>(r: &'a i32, s: &'b i32) -> &'a i32 { r }
```
```rust
struct S<'a, 'b> { x: &'a i32, y: &'b i32 }
// 'a는 y의 수명이 되면 되고, 'b는 s의 수명이 되면 됨
// 'b로 y의 수명도 가능하긴 하지만 러스트는 가장 짧은 수명 채택

let x = 10;
let r;
{
    let y = 20;
    {
        let s = S { x: &x, y: &y };
        r = s.x;
    }
}
println!("{}", r);
```

수명이 하나이거나, 코드가 모호하지 않은 선에서는 컴파일러가 자동으로 매개변수의 수명을 배정한다.

# 3. Shared vs Mutable
> passed