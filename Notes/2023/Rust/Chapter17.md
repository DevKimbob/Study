String and Text <!-- omit in toc -->
===

**Table of Contents**
- [1. Unicode](#1-unicode)
  - [1.1. UTF-8](#11-utf-8)
- [2. 문자(char)](#2-문자char)
  - [2.1. 문자 분류하기](#21-문자-분류하기)
  - [2.2. 숫자 다루기](#22-숫자-다루기)
  - [2.3. 대소문자 변환](#23-대소문자-변환)
  - [2.4. 문자와 정수 간의 변환](#24-문자와-정수-간의-변환)
- [3. String과 str](#3-string과-str)
  - [3.1. String 생성](#31-string-생성)
  - [3.2. 간단한 점검](#32-간단한-점검)
  - [3.3. 텍스트 덧붙이기와 끼워 넣기](#33-텍스트-덧붙이기와-끼워-넣기)
  - [3.4. 텍스트 제거하기와 맞바꾸기](#34-텍스트-제거하기와-맞바꾸기)
  - [3.5. 검색하기와 맞바꾸기](#35-검색하기와-맞바꾸기)
  - [3.6. 반복 처리하기](#36-반복-처리하기)
  - [3.7. 다듬기](#37-다듬기)
  - [3.8. 대소문자 변환](#38-대소문자-변환)
  - [3.9. 다른 타입으로 파싱](#39-다른-타입으로-파싱)
- [4. 값 형식화하기](#4-값-형식화하기)
  - [4.1. 디버깅용으로 값 형식화하기](#41-디버깅용으로-값-형식화하기)
  - [4.2. 디버깅용으로 포인터 형식화하기](#42-디버깅용으로-포인터-형식화하기)
- [5. Passed](#5-passed)


# 1. Unicode
러스트의 문자와 문자열 타입은 유니코드를 중심으로 설계됐다.
|인코딩|비트 수|특징|
|---|---|---|
|ASCII|7bit|제어문자와 출력가능문자 128개로 구성|
|ISO/IEC 8859-1 (Latin-1)|8bit(1Byte)|ASCII의 8비트 확대집합|
|Unicode|32bit(4Byte)|라틴-1의 확대집합|

```rust
fn latin1_to_char(latin1: u8) -> char {
    latin1 as char
}

fn char_to_latin1(c: char) -> Option<u8> {
    if c as u32 <= 0xff {
        Some(c as u8)
    } else {
        None
    }
}
```

## 1.1. UTF-8
러스트의 `String`과 `str`타입은 텍스트를 UTF-8 인코딩 형식으로 표현한다. UTF-8은 한 문자를 1에서 4바이트 길이로 된 시퀀스로 인코딩한다. 적격한 UTF-8 시퀀스에는 두 가지 제약이 있다.
1. 주어진 코드 포인트에 대해서 가장 짧은 인코딩만 적격한 것으로 간주한다.
2. 0xd800에서 0xdfff사이에 있는 수나 0x10ffff보다 큰 수를 절대로 인코딩 하지 않는다.

|UTF-8 인코딩|표현하는 코드 포인트|범위|
|---|---|---|
|0xxxxxxx|0bxxxxxxx (7)|0 ~ 0x7f|
|110xxxxx 10yyyyyy|0bxxxxxyyyyyy (11)|0x80 ~ 0x7ff|
|1110xxxx 10yyyyyy 10zzzzzz|0bxxxxyyyyyyzzzzzz (16)|0x800 ~ 0xffff|
|11110xxx 10yyyyyy 10zzzzzz 10wwwwww|0bxxxyyyyyyzzzzzzwwwwww (21)|0x10000 ~ 0x10ffff|
> 0b1_1111_1111_1111_1111_1111 = 0x1f_ffff

따라서 UTF-8은 여러가지의 특성을 가진다.
* 0에서 0x7f 사이의 코드 포인트는 아스키코드와 완전하게 동일하다
* 어떤 바이트의 상위 비트를 보면 그것이 어떤 문자의 인코딩이 시작되는 부분인지, 한가운데 있는 부분인지 알 수 있다

# 2. 문자(char)
러스트의 `char`는 유니코드 코드 포인트를 쥐고 있는 32비트 값이다. `char`는 항상 0에서 0xd7ff사이나 0xe000에서 0x10ffff사이의 값만 갖는다는 것이 보장된다.
> 0xd800에서 0xdfff사이에 있는 수나 0x10ffff보다 큰 수를 절대로 인코딩 하지 않는다.

문자열 슬라이스는 `slice.chars()`를 써서 자기가 가진 문자들을 반복 처리하는 이터레이터를 산출할 수 있다.

## 2.1. 문자 분류하기
```rust
ch.is_numeric()
ch.is_alphabetic()

ch.is_ascii()
ch.is_ascii_digit()
ch.is_ascii_alphabetic()
32u8.is_ascii_whitespace()  // ch.is_ascii_... 메서드는 u8 바이트 타입에 대고 쓸 수 있다.
```

## 2.2. 숫자 다루기
```rust
ch.to_digit(radix)
std::char::from_digit(num, radix)
```

## 2.3. 대소문자 변환
```rust
ch.is_lowercase(), ch.is_uppercase()
ch.to_lowercase(), ch.to_uppercase()
```

## 2.4. 문자와 정수 간의 변환
```rust
let c = 'C' as u32;  // 상위 비트들은 잘린다

// u8 -> char
let b1 = char::from(66);
// u32 -> Option<char>
let b2 = std::char::from_u32(0x9942);  // Some('饂')
let b3 = std::char::from_u32(0xd800);  // None
```

# 3. String과 str
`str`은 수정할 수 없는 문자열을 나타낸다. `String`은 `Vec<u8>`의 래퍼 형태로 구현되어 길이와 내용을 변경할 수 있는 문자열을 나타낸다. `String`은 `&str`로 역참조된다. 따라서 `str`에 정의된 모든 메소드를 `String`에 대고 바로 사용할 수 있다.

## 3.1. String 생성
```rust
String::new()
str_slice.to_string()
iter.collect()
```

## 3.2. 간단한 점검
```rust
slice[range]  // 슬라이스에서 주어진 범위에 해당하는 부분을 빌려와 슬라이스로 반환
slice.split_at(i)  // 슬라이스에서 빌려온 두 개의 공유된 슬라이스를 요소로 갖는 튜플을 반환
```

## 3.3. 텍스트 덧붙이기와 끼워 넣기
```rust
string.push(ch)
string.push_str(slice)
string.extend(iter)
string.insert(i, ch)
string.insert_str(i, slice)

let addstr = "hello".to_string() + " world";  // Add<&str> 구현
```

## 3.4. 텍스트 제거하기와 맞바꾸기
```rust
string.pop()
string.remove(i)
string.replace_range(range, replacement)
```

## 3.5. 검색하기와 맞바꾸기
```rust
slice.contains(pattern)
slice.starts_with(pattern), slice.ends_with(pattern)
slice.find(pattern), slice.rfind(pattern)
slice.replace(pattern, replacement)
```

## 3.6. 반복 처리하기
```rust
slice.chars()  // u8
slice.bytes()  // char
slice.split(pattern), slice.rsplit(pattern)
slice.split_whitespace(), slice.split_ascii_whitespace()
```

## 3.7. 다듬기
```rust
slice.trim()
slice.trim_matches(pattern)
slice.strip_prefix(pattern), slice.strip_suffix(pattern)
```

## 3.8. 대소문자 변환
```rust
slice.to_uppercase(), slice.to_lowercase()
```

## 3.9. 다른 타입으로 파싱
어떤 타입이 `std::str::FromStr`트레이트를 구현하고 있다면, 그 타입은 문자열 슬라이스를 값으로 파싱하는 표준 방법을 제공한다.
```rust
let u = usize::from_str("3628800");
let f = f64::from_str("128.5625");
let b = bool::from_str("true");
```

사람이 읽을 수 있는 자연스러운 인쇄 형태를 가진 타입은 `std::fmt::Display`트레이트를 구현할 수 있는데, `format!`매크로에서 `{}`형식 지정자를 쓸 수 있다.
```rust
let s1 = format!("{} world", "hello");  // "hello world"
let s2 = format!("({:.3}, {:.3})", 0.5, f64::sqrt(3.0)/2.0);  // "(0.500, 0.866)"
let s3 = f64::sqrt(3.1).to_string();  // 1.760681686165901
```

# 4. 값 형식화하기
템플릿에 있는 `{...}`는 형식 매개변수로 `{which:how}`형태를 갖는다. 두 부분 다 옵션이라서 `{}`로도 자주 쓰인다.
* `which`값은 템플릿 뒤에 오는 인수 중에서 매개변수의 자리를 차지할 대상을 선택한다. 생략시 단순히 왼쪽에서 오른쪽 순으로 인수와 짝을 이룬다.
* `how`값은 인수의 형식화 방식을 나타낸다.
```rust
println!("number : {}", 10);  // number : 10
println!("{1}, {0}", 0, 1);  // 1, 0
println!("{a}, {b}", b = 10, a = 20);  // 20, 10
println!("{:?}", vec![1, 2, 3]);  // [1, 2, 3]
println!("name = {:?}", "Name");  // name = "Name"

println!("{:.4}", "hello world");    // hell
println!("{:>17}", "hello world");   //       hello world
println!("{:*^17}", "hello world");  // ***hello world***

println!("{:b}", 12);  // 1100
println!("{:#x}", 123);  // 0x7b
println!("{:.2}", 12.34567);  // 12.35
println!("{:e}", 12.34567);  // 1.234567e1
println!("{:.3e}", 12.34567);  // 1.235E1
```

## 4.1. 디버깅용으로 값 형식화하기
디버깅과 로깅을 돕기 위해 마련된 `{:?}`매개변수는 프로그래머에게 유용한 정보를 가득 담아서 러스트 표준 라이브러리에 있는 모든 공개 타입을 형식화한다.
```rust
let mut hm = HashMap::new();
hm.insert(1, (1, 2, 3));
hm.insert(2, (4, 5, 6));
println!("{:?}", hm);  // {2: (4, 5, 6), 1: (1, 2, 3)}
```

## 4.2. 디버깅용으로 포인터 형식화하기
`{:p}`표기법은 레퍼런스, 박스, 기타 유사 포인터 타입을 주소로 형식화한다.
```rust
let a = 10;
let b = 20;
let c = 30;
println!("{:p}, {:p}, {:p}", &a, &b, &c);  // 0x7fff4c0aead4, 0x7fff4c0aead8, 0x7fff4c0aeadc
```

# 5. Passed
텍스트를 UTF-8로 접근하기  
UTF-8 데이터를 가지고 텍스트 생성하기  
할당 미루기  
제네릭 컬렉션으로서의 문자열  
사용자 정의 타입 형식화  
내 코드에서 형식화 언어 사용하기  
정규 표현식  
정규화  