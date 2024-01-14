Trait and Generic <!-- omit in toc -->
===

**Table of Contents**
- [1. Trait](#1-trait)
  - [1.1. 트레이트 객체](#11-트레이트-객체)
  - [1.2. 트레이트의 정의와 구현](#12-트레이트의-정의와-구현)
  - [1.3. 서브트레이트](#13-서브트레이트)
- [2. Generic](#2-generic)
- [3. Trait vs Generic](#3-trait-vs-generic)
- [4. Passed](#4-passed)


# 1. Trait
인터페이스나 추상 기본 클래스의 역할을 한다. 임의의 주어진 타입이 지원할 수도 있고 지원하지 않을 수도 있는 기능이다. 트레이트 메서드의 특이한 규칙은 트레이트 자체가 반드시 범위 안에 있어야 한다.

## 1.1. 트레이트 객체
러스트에서 트레이트를 이용해 다형적 코드를 작성하는 방법에는 트레이트 객체와 제네릭 두 가지가 있다.
```rust
dyn Write  // 트레이트 객체
```

트레이트 객체는 팻 포인터로 다음과 같이 구성되어있다.
* 값을 가리키는 포인터
* 그 값의 타입을 나타내는 테이블을 가리키는 포인터
  > V테이블이라고도 하며 컴파일 시점에 한 번만 만들어 진다.

## 1.2. 트레이트의 정의와 구현
`고아 규칙` : 대상이 된느 트레이트나 타입이 현재 크레이트에서 처음 선보이는 것이어야 한다. (ex. `impl Write for u8`은 이미 구현되어 있기 때문에 추가적으로 구현할 수 없다.)
```rust
struct Point {  // 타입 정의
    x: u8,
    y: u8,
}

trait GetDist {  // 트레이트 정의
    fn get_dist_trait(&self) -> f32;
}

impl GetDist for Point {  // 트레이트 구현
    fn get_dist_trait(&self) -> f32 {
        ((self.x.pow(2) + self.y.pow(2)) as f32).sqrt()
    }
}

let p1 = Point { x: 3, y: 4 };
println!("{}", p1.get_dist_trait());  // 메소드 형식 호출
println!("{}", Point::get_dist_trait(&p1));  // 한정자가 붙은 메소드 호출
println!("{}", <Point as GetDist>::get_dist_trait(&p1));  // 한정자가 모두 붙은 메소드 호출
```

## 1.3. 서브트레이트
```rust
trait GetAngle: GetDist {  // 트레이트를 확장하여 새로운 트레이트 생성
    ...
}

// GetAngle을 구현하기 위해서는 GetDist 또한 구현해야 한다
impl GetDist for Point {  // 슈퍼트레이트
    ...
}
impl GetAngle for Point {  // 서브트레이트
    ...
}
```
```rust
trait GetAngle where Self: GetDist {  // 서브트레이트는 다음에 대한 축약표기이며, 슈퍼트레이트의 연관 아이템들을 상속하지 않는다.
    ...
}
```

# 2. Generic
```rust
fn function<T: Trait + Trait2>(arg: &mut T)
// <T: Trait + Trait2> : 타입 T가 트레이트 Trait, Trait2을 구현하고 있다.
// ref: 단형성화

fn function<T>(arg: &mut T)
    where T: Trait + Trait2
```

# 3. Trait vs Generic
트레이트 객체는 다양한 타입으로 된 값들의 집합체가 필요할 때 쓰면 적합하다.
```rust
trait Vegetable {  // 이와 같은 트레이트에 대해서
    ...
}
```

```rust
struct Salad<V: Vegetable> {  // 이 방법 보다는
    veggies: Vec<v>
}

struct Salad {  // 이 방법아 더 좋다
    veggies: Vec<Box<dyn Vegetable>>
}
```

제네릭은 트레이트 객체에 비해서 속도가 더 빠르다. 또한 트레이트 객체에서는 쓸 수 없는 몇가지가 존재한다(ex. 연관함수).

# 4. Passed
타입 연관 함수  
**연관 타입(자신이 산출하는 아이템의 타입 명시)**  
제네릭 트레이트  
**impl 트레이트(반환값의 타입은 지우고 구현하는 트레이트만 지정)**  
연관 상수  
바운드 역설계