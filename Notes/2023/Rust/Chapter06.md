Expression <!-- omit in toc -->
===

**Table of Contents**
- [1. Expression](#1-expression)
  - [1.1. 표현식 vs 실행문](#11-표현식-vs-실행문)
  - [1.2. 블록과 세미콜론](#12-블록과-세미콜론)
  - [1.3. 선언](#13-선언)
  - [1.4. Shadowing](#14-shadowing)
  - [1.5. If](#15-if)
  - [1.6. Match](#16-match)
  - [1.7. if let](#17-if-let)
  - [1.8. Loop](#18-loop)
    - [1.8.a Loop's Flow Control](#18a-loops-flow-control)
  - [1.9. Return](#19-return)
  - [1.10. Range](#110-range)
- [2. Passed Stuff](#2-passed-stuff)


# 1. Expression
## 1.1. 표현식 vs 실행문
표현식은 값을 가지는 반면 실행문은 값을 갖지 않는다.

C언어는 if, switch가 실행문이기 때문에 표현식 중간에 쓰일 수 없다.
```c
int status;
if (temp) {
    status = 1
} else {
    status = -1
}
```

Rust는 표현식 언어로 모든 일을 표현식으로 해내는 오랜 전통을 따른다. 따라서 if와 match가 값을 산출하는 것이 가능하다. 같은 이유로 Rust에서는 if문을 그대로 사용하면 되기 때문에, C언어의 삼항 연산자를 가지지 않는다.
```rust
let status =
    if temp {
        HttpStatus::Ok
    } else {
        HttpStatus::ServerError
    }
```

## 1.2. 블록과 세미콜론
블록은 값을 산출하는 표현식이며, 값이 필요한 모든 곳에 쓰일 수 있다.
```rust
let a = {
    let b = 10;
    let c = 20;
    b + c
};

println!("{}", a);
```
블록 마지막 줄의 세미콜론을 생략하면 마지막 표현식의 값을 자신의 값으로 산출한다.  
블록은 `fn`, `struct`, `use`와 같은 `아이템 선언`도 포함할 수 있다.

## 1.3. 선언
```rust
let name: type = expr;
let mut name: type = expr;
```
`type`과 `expr`은 옵션이지만 세미콜론은 필수

## 1.4. Shadowing
자신이 속한 블록이 끝날 때 까지 첫 번째 변수의 정의를 대체한다.
```rust
for line in file.lines() {
    let line = line;  // shadowing
}
```

## 1.5. If
값 산출 시 모든 블록이 같은 타입의 값을 산출해야 한다.
```rust
if condition1 {
    block1
} else if condition2 {
    block2
} else {
    block_n
}
```

## 1.6. Match
match는 value가 가능한 모든 값을 다루어야한다.  
값 산출 시 모든 블록이 같은 타입의 값을 산출해야 한다.
```rust
match value {
    pattern => expr,
    ...
}
```
```rust
match code {
    0 => println!("OK"),
    1 => println!("NO"),
    _ => println!("DEF")
}

match Option {
    Some(v) => println!("{}", v),
    None => println!("None")
}
```

## 1.7. if let
`expr`이 `pattern`과 매칭되면 block1을, 매칭되지 않으면 block2를 실행한다.
```rust
if let pattern = expr {
    block1
} else {
    block2
}
```
굳이 if let이 아니라 match로도 같은 표현을 할 수 있다.
```rust
match expr {
    pattern => { block1 }
    _ => { block2 }
}
```

## 1.8. Loop
```rust
while condition {
    block
}

while let pattern = expr {  // if let과 비슷함
    block
}

loop {  // 무한루프를 작성할 때 사용. 필요한 경우 산출할 값 지정 가능
    block
}

for pattern in iterable {
    block
}
```
```rust
for i in 0..20 {  // 0..20 = std::ops::Range { start: 0, end: 20 }, 이상 미만관계
    block
}
```

### 1.8.a Loop's Flow Control
```rust
while condition {
    if cond {
        continue;
    }
    break;
}
```

`loop`의 본문에서는 break에 루프의 값을 산출하는 표현식을 쓸 수 있다.
```rust
let a = loop {
    break 10;
};
```

루프는 수명과 함께 레이블을 가질 수 있다.
```rust
'outer:
for i in 0..20 {
    for j in 0..20 {
        if i + j > 30 {
            break 'outer;
        } else {
            println!("{}, {}", i, j);
        }
    }
}
```

## 1.9. Return
```rust
fn f() {
    return;
}
```
```rust
let output = File::create(filename)?;

let output = match File::create(filename) {
    Ok(f) => f,
    Err(err) => return Err(err)
};
```

## 1.10. Range
```rust
// 기본적으로 이상, 미만관계
..  // RangeFull
a ..  // RangeFrom { start: a }
.. b  // RangeTo { end: b }
a .. b  // Range { start: a, end: b }

a ..= b  // RangeInclusive::new(a, b), 끝을 포함
```

# 2. Passed Stuff
일탈함수 ( -> ! )  
터보피시 ( ::<...> )  
필드, 요소  
레퍼런스 연산자  
산술, 비트별, 비교, 논리 연산자  
배정  
타입 캐스팅 ( as )  
클로저  
