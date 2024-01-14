Operator Overloading <!-- omit in toc -->
===

**Table of Contents**
- [1. Operator Overloading](#1-operator-overloading)


# 1. Operator Overloading
러스트는 연산자 오버로딩을 위해 여러개의 트레이트를 정의해놓았다.
|범주|트레이트|표현식|동등한 표현식|
|---|---|---|---|
|산술 연산자|std::ops::Add|x + y|x.add(y)|
|산술 연산자|std::ops::Sub|x - y|x.sub(y)|
|산술 연산자|std::ops::Mul|x * y|x.mul(y)|
|산술 연산자|std::ops::Div|x / y|x.div(y)|
|...|...|...|...|

```rust
struct Point {
    x: u8,
    y: u8,
}

impl Add for Point {
    type Output = Point;
    fn add(self, rhs: Self) -> Self {
        Point {
            x: self.x + rhs.x,
            y: self.y + rhs.y,
        }
    }
}

let p1 = Point { x: 10, y: 20 };
let p2 = Point { x: 30, y: 40 };
let p3 = p1 + p2;
println!("{}, {}", p3.x, p3.y);  // 40, 60
```