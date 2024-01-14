Struct <!-- omit in toc -->
===

**Table of Contents**
- [1. Struct](#1-struct)


# 1. Struct
## 1.1. 이름있는 필드로 된 스트럭트
```rust
struct StName {  // CamelCase
    fld_name1: type,  // snake_case
    fld_name2: type
}
```
```rust
struct GrayscaleMap {
    pixels: Vec<u8>,
    size: (usize, usize)
}
```
```rust
let width = 1280;
let height = 720;
let image = GrayscaleMap {
    pixels: vec![0; width * height],
    size: (width, height)
};  // key: value 표현식

fn new_map(pixels: Vec<u8>, size: (usize, usize)) -> GrayscaleMap {
    GrayscaleMap { pixels, size }
}  // 필드를 같은 이름으로 된 지역변수나 인수로 채우는 축약 표기
```
> 하나의 스트럭트 표현식에서 key: value 표현식과 축약 표기를 섞어 쓸 수 있다.

---
원소들은 `.`연산자를 통해 접근할 수 있다. 다른 아이템과 마찬가지로 스트럭트는 비공개가 기본이며, 선언된 모듈과 하위 모듈 안에서만 볼 수 있다. 스트럭트 정의 앞에 `pub`을 붙여 모듈 바깥에서도 볼 수 있게 할 수 있다. 스트럭트의 각 필드도 비공개가 기본이며, 같은 내용이 적용된다.
```rust
pub struct GrayscaleMap {
    pub pixels: Vec<u8>,
    pub size: (usize, usize)
}
```

---
이름있는 필드로 된 스트럭트 값을 만들 때는 같은 타입의 다른 스트럭트를 써서 생략된 필드의 값을 채울 수 있다. 스트럭트 표현식에서 이름 있는 필드 다음에 `.. EXPR`이 오면 언급되지 않은 모든 필드의 값을 `EXPR`에서 가져오게 된다.
```rust
struct SimpleStruct {
    name: String,
    height: u32,
    width: u32
}

let a = SimpleStruct { name:"A".to_string(), height:10, width: 20 };
let b = SimpleStruct { name:a.name.clone(), height:30, width:40 };
let c = SimpleStruct { name:a.name.clone(), .. b };
let d = SimpleStruct { .. a };

println!("{}, {}, {}", a.name, a.height, a.width);  // 컴파일 에러. let d 에서 name 이동
println!("{}, {}, {}", b.name, b.height, b.width);  // A, 30, 40
println!("{}, {}, {}", c.name, c.height, c.width);  // A, 30, 40
println!("{}, {}, {}", d.name, d.height, d.width);  // A, 10, 20
```

## 1.2. 튜플형 스트럭트
튜플을 닮은 스트럭트이다.
```rust
struct StName(type, type);

struct Bounds(usize, usize);
let image_bounds = Bounds(1280, 720);

pub struct Bounds(pub usize, pub usize);  // 각 요소 공개 가능
```
위와 같이 타입을 정의하면 다음과 같은 함수가 암묵적으로 정의된다.
```rust
fn Bounds(elem0: usize, elem1: usize) -> Bounds { ... }
```

튜플형 스트럭트는 뉴타입에 적합하다. 뉴타입이란 타입 검사를 보다 엄격히 하기 위해서 정의하는 구성 요소가 하나인 스트럭트를 말한다.
```rust
struct Ascii(Vec<u8>)
```

## 1.3. 유닛형 스트럭트
요소를 전혀 갖지 않는 스트럭트 타입으로 메모리를 차지하지 않는다. 타입만 가지고 할 수 있는 일들에 사용된다. 논리적으로 볼 땐, 하나의 값만 있는 타입이다.
```rust
struct Onesuch;
```

# 2. Advanced Concepts
## 2.1. 스트럭트 레이아웃
이름 있는 필드로 된 스트럭트와 튜플형 스트럭트는 메모리 관점에서 동일하다. C/C++과 달리 스트럭트의 필드나 요소를 메모리에 어떤 순서로 배치할지에 관해서 아무것도 규정하고 있지 않으나, 필드의 값을 직접 스트럭트의 메모리 블록 안에 저장한다.

## 2.2. impl로 메서드 정의하기
사용자 정의 스트럭트 타입에도 메서드를 정의할 수 있다. `impl`블록은 단순한 fn 정의의 집합체로, 각 정의는 블록 맨 위에 지정된 이름을 가진 스트럭트 타입의 메서드가 된다.
```rust
pub struct Queue {
    older: Vec<char>,
    younger: Vec<char>
}

impl Queue {
    pub fn push(&mut self, c: char) {
        self.younger.push(c);
    }

    pub fn pop(&mut self) -> Option<char> {
        if self.older.is_empty() {
            if self.younger.is_empty() {
                return None;
            }

            use std::mem::swap;
            swap(&mut self.older, &mut self.younger);
            self.older.reverse();
        }

        self.older.pop()
    }
}
```
`impl`블록 안에 정의된 함수는 특정 타입과 연관되어 있다고 해서 `연관 함수`라고 하고 그렇지 않은 함수들(지금까지 생성한 함수들)은 `자유 함수`라고 한다.  
호출 대상이 되는 값을 메서드의 첫 번째 인수로 전달하는데, 이 인수는 `self`라는 이름을 가져야 한다. 이 인수는 `impl`블록 맨 위에 지정된 이름을 가진 타입이거나, 그의 레퍼런스일 수밖에 없으므로, `self: Queue, self: &Queue, self: &mut Queue`를 타입을 생략해서 `self, &self, &mut self`로 적을 수 있게 해준다.

위 코드는 Queue를 수정해야 하기 때문에 `&mut self`로 받았지만 경우에 따라 아래와 같이 받을 수도 있다.
```rust
impl Queue {
    pub fn is_empty(&self) -> bool {  // 수정할 필요 없음
        self.older.is_empty() && self.younger.is_empty()
    }

    pub fn split(self) -> (Vec<char>, Vec<char>) {  // 소유권을 가져와야 함
        (self.older, self.younger)
    }
}
```

## 2.3. 타입 연관 함수
impl블록 안에서 self를 인수로 받지 않아도 되는 함수이다.
```rust
impl Queue {
    pub fn new() -> Queue {
        Queue { older: Vec::new(), younger: Vec::new() }
    }
}
```
또한 자신의 대상이 된느 타입을 특별한 타입 매개변수 `Self`로 정의한다.
```rust
impl Queue {
    pub fn new() -> Self {  // Self!!
        Queue { older: Vec::new(), younger: Vec::new() }
    }
}
```

## 2.4. 연관 상수
타입 자체와 연관된 값이다.
```rust
pub struct MyVector {
    x: f32,
    y: f32
}

impl MyVector {
    const ZERO: MyVector = MyVector { x: 0.0, y:0.0 };
    const UNIT: MyVector = MyVector { x: 1.0, y:0.0 };
    const ID: u32 = 10;
}

let scaled = MyVector::UNIT.scaled_by(2.0);
println("{}", MyVector::ID);  // 10
```

## 2.5. 제네릭 스트럭트
해당 정의가 템플릿으로 되어있어서 원하는 타입을 끼워넣을 수 있다.
```rust
pub struct Queue {
    older: Vec<char>,
    younger: Vec<char>
}

pub struct Queue<T> {  // 제네릭 스트럭트
    older: Vec<T>,
    younger: Vec<T>
}

impl<T> Queue<T> {  // impl 블록에서도 타입 매개변수(T)를 넣어준다
    ...
}

impl Queue<f64> {  // 특정 타입에 대해서만 사용하는 impl 블록은 다음과 같이 작성한다
    ...
}
```

연관 함수 호출의 경우 터보피시(`::<>`) 표기법을 써서 타입 매개변수를 명시적으로 지정하지만, 사실 러스트에게 처리를 맡기는 경우가 대부분이다.
```rust
let mut q = Queue::<char>::new();  // Queue<char>

let mut r = Queue::new();
let mut s = Queue::new();

r.push("CAD");  // Queue<&'static str>
s.push(0.74);  // Queue<f64>
```

## 2.6. 상수 매개변수를 갖는 제네릭 스트럭트
제네릭 스트럭트는 상숫값으로 된 매개변수를 받을 수도 있다.
```rust
struct Polyomial<const N: usize> {
    coefficients: [f64; N]
}

impl<const N: usize> Polyomial<N> {
    fn new(coefficients: [f64; N]) -> Polyomial<N> {
        Polyomial { coefficients }
    }

    fn eval(&self, x: f64) -> f64 {
        let mut sum = 0.0;
        for i in (0..N).rev() {
            sum = self.coefficients[i] + x * sum;
        }

        sum
    }
}
```


# 3. Passed
Self를 Box, Rc, Arc로 넘기기  
수명 매개변수를 갖는 제네릭 스트럭트  
내부가변성 (Cell)