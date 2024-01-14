Enum and Pattern <!-- omit in toc -->
===

**Table of Contents**
- [1. Enum](#1-enum)
  - [1.1. C 스타일 이늄](#11-c-스타일-이늄)
  - [1.2. 데이터를 갖는 이늄](#12-데이터를-갖는-이늄)
  - [1.3. 제네릭 이늄](#13-제네릭-이늄)
- [2. Pattern](#2-pattern)
  - [2.1. 와일드카드](#21-와일드카드)
  - [2.2. 레퍼런스 패턴](#22-레퍼런스-패턴)
  - [2.3. 매치 가드](#23-매치-가드)
  - [2.4. 여러 가능성](#24-여러-가능성)
  - [2.5. @ 패턴 바인딩](#25--패턴-바인딩)
- [3. Passed](#3-passed)


# 1. Enum
## 1.1. C 스타일 이늄
```rust
enum Ordering {
    Less,  // 각 후보값을 베리언트 또는 생성자라고 한다.
    Equal,
    Greater,
}

use std::cmp::Ordering;
let order = Ordering::Less;

use std::cmp::Ordering::{self, *};  // 자식들을 전부 가져오지만, 가능하면 안쓰는게
let order = Less;

use self::Ordering;  // 현재 모듈에 선언된 이늄의 생성자를 가져올 때는 self사용
```
```rust
enum HttpStatus {  // 0부터 수를 배정하는것이 아니라 임의의 정수 지정 가능
    Ok = 200,
    NotModified = 304,
    NotFound = 404,
    ...
}

let ok = HttpStatus::Ok as i32;  // 정수 캐스팅 가능
// 반대는 안되지만, match를 통해 직접 코드 작성 가능
```
```rust
impl HttpStatus {  // enum에 대한 메서드 정의 가능
    fn status(self) -> &'static str {
        match self {
            HttpStatus::Ok => "Ok",
            HttpStatus::NotModified => "NotModified",
            HttpStatus::NotFound => "NotFound",
        }
    }
}
```

## 1.2. 데이터를 갖는 이늄
```rust
enum Shape {
    Point,  // 데이터를 갖지 않는 베리언트
    Rect(Point3d, Point3d),  // 튜플 베리언트
    Sphere { center: Point3d, radius: f32 },  // 스트럭트 베리언트
}

let s1 = Shape::Rect(ORIGIN, ORIGIN);
let s2 = Shape::Sphere { center: ORIGIN, radius: 1.0, };
```

## 1.3. 제네릭 이늄
```rust
enum Option<T> {
    None,
    Some(T),
}

enum Result<T, E> {
    Ok(T),
    Err(E),
}
```
타입 T가 레퍼런스이거나 Box이거나 기타 스마트 포인터 타입일 경우 러스트가 Option\<T>의 태그 필드를 제거할 수 있다. 예시로 `Option<Box<i32>>`를 1 머신워드로 표현할 수 있다.
```rust
enum BinaryTree<T> {
    Empty,
    NonEmpty(Box<TreeNode<T>>),
}

struct TreeNode<T> {
    element: T,
    left: BinaryTree<T>,
    right: BinaryTree<T>,
}
```

# 2. Pattern
러스트에서 이늄의 필드에는 직접적으로 접근할 수 없다. 따라서 `match`의 패턴 매칭을 통해 필드에 접근한다.
```rust
enum MyEnum {
    Empty,
    NonEmpty(u32, u32),
}

let me = MyEnum::NonEmpty(10, 20);
match me {
    MyEnum::Empty => {
        println!("EMPTY");
    },
    MyEnum::NonEmpty(val1, val2) => {
        println!("{}, {}", val1, val2);
    },
};  // 10, 20
```
`=>`기호 앞에 오는 부분이 `패턴`이다. 위 부터 패턴이 매칭되는지를 확인하면서 내려오는데, 패턴이 매칭되는 경우 패턴에 해당하는 지역변수로 값이 복사되거나 이동된다.

## 2.1. 와일드카드
```rust
match value {
    _ => println!("everything");
}
```

## 2.2. 레퍼런스 패턴
```rust
match value {
    ExampleStruct { ref f1, ref f2, .. } => println!("reference"),
}
```

## 2.3. 매치 가드
```rust
match value {
    Some(v) if v == 1 => println!("match gaurd"),
}
```

## 2.4. 여러 가능성
```rust
match value {
    Some(&'\r' | &'\n') | None => true,
    _ => false,
}
```

## 2.5. @ 패턴 바인딩
```rust
match value {
    var @ Expr => println!("var"),  // Expr과 패턴이 맞으면 var변수로 이동
}
```

# 3. Passed
이늄의 메모리 구조  
이늄을 이용한 리치 데이터 구조  
패턴을 쓸 수 있는 곳  