Closer <!-- omit in toc -->
===

**Table of Contents**
- [1. Closer](#1-closer)
  - [1.1. 변수 캡쳐](#11-변수-캡쳐)
  - [1.2. 빌리는 클로저](#12-빌리는-클로저)
  - [1.3. 훔치는 클로저](#13-훔치는-클로저)
  - [1.4. 함수와 클로저 타입](#14-함수와-클로저-타입)
  - [1.5. 클로저의 종류](#15-클로저의-종류)
    - [1.5.1. Fn](#151-fn)
    - [1.5.1. FnOnce](#151-fnonce)
    - [1.5.2. FnMut](#152-fnmut)
- [2. Passed](#2-passed)


# 1. Closer
익명의 함수 표현식으로 함수를 선언하지 않고 바로 사용할 수 있다는 장점이 있다.

## 1.1. 변수 캡쳐
```rust
fn sort_by_stat(cities: &mut Vec<City>, stat: Stat) {
    cities.sort_by_key(|city| city.get_stat(stat));
}
```
클로저는 바깥쪽 함수에 속한 데이터를 사용할 수 있다. 이를 클로저가 `stat`을 `캡쳐`한다고 한다.

## 1.2. 빌리는 클로저
```rust
fn sort_by_stat(cities: &mut Vec<City>, stat: Stat) {
    cities.sort_by_key(|city| city.get_stat(stat));
}
```
위 예시에서 러스트가 클로저를 생성할 때 `stat`의 레퍼런스를 자동으로 차용한다. 위 클로저는 `stat`의 레퍼런스를 가지고 있으므로 `stat`보다 더 오래 지속될 수 없지만, 위 예시에서는 클로저가 정렬하는 동안에만 쓰이무로 문제가 되지 않는다.

## 1.3. 훔치는 클로저
```rust
use std::thread;

fn sort_by_stat(cities: &mut Vec<City>, stat: Stat) -> thread::JoinHandle<Vec<City>> {
    let key_fn = move |city: &City| -> i64 { city.get_stat(stat) };

    thread::spawn(move || {
        cities.sort_by_key(key_fn);
        cities
    })
}
```
수명에 관한 문제가 있을 경우 `move`키워드를 통해 변수의 레퍼런스를 빌리지 않고, `옮기는`것으로 해결할 수 있다.
1. `city`의 안전한 사용을 보장할 수 없다.
2. `cities`와 `stat`이 소멸되기 전에 스레드가 자신의 일을 끝낼 것이라고 기대할 수 없다.
> 복사할 수 있는 타입의 값을 `move`할 경우 이동이 아니라 복사가 일어난다.

## 1.4. 함수와 클로저 타입
```rust
fn city_pop_desc(city: &City) -> i64 {  // type : fn(&City) -> i64
    city.pop
}

let my_key_fn: fn(&City) -> i64 =  // 함수를 변수에 저장할 수 있다.
    if cond {
        city_pop_desc
    } else {
        coty_risk_desc
    }
cities.sort_by_key(my_key_fn);  // 함수는 다른 함수를 인수로 받을 수 있다.
```
```rust
fn bool_function(city: &City) -> bool {
    ...
}

fn function1(test_fn: fn(&City) -> bool) -> usize {
    ...
}
fn function2<F>(test_fn: F) -> usize
    where F: Fn(&City) -> bool {
    ...
}
```
일반 함수를 함수의 인수로 넘기려면 `function1`처럼 작성하면 되지만, 클로저를 함수의 인수로 넘기려면 `function2`처럼 작성해야한다. `function2`는 특수 트레이트 `Fn(&City) -> bool`을 구현하고 있는 임의의 타입 `F`로 된 `test_fn`을 받는다.
```rust
fn(&City) -> bool  // fn타입 (함수만 받는다)
Fn(&City) -> bool  // Fn트레이트 (함수와 클로저를 모두 받는다)
```
```rust
pub fn sort_by_key<K, F>(&mut self, mut f: F)
where
    F: FnMut(&T) -> K,
    K: Ord,  // Order, 비교 및 최대, 최소 등을 구현한 트레이트
{
    stable_sort(self, |a, b| f(a).lt(&f(b)));
}
```

## 1.5. 클로저의 종류
모든 클로저는 자기만의 고유한 타입을 가진다. 또한 클로저의 종류에 따라 구현하는 트레이트가 다른데 그 종류는 세 가지로, 다음과 같다.
* `Fn` ⊂ `FnMut` ⊂ `FnOnce`
> `Fn()`은 `FnMut()`의 서브트레이트고, `FnMut()`는 `FnOnce()`의 서브트레이트다.

```rust
trait Fn() -> R {
    fn call(&self) -> R;
}

trait FnOnce() -> R {
    fn call_once(self) -> R;
}

trait FnMut() -> R {
    fn call_mut(&mut self) -> R;
}
```

### 1.5.1. Fn
제한 없이 여러 번 호출 할 수 있는 클로저와 함수군이다.
```rust
let f = || println!("hi");
```

### 1.5.1. FnOnce
`FnOnce`클로저는 호출부가 클로저를 소유한 경우에 한 번만 호출될 수 있는 클로저로, 처음 호출될 때 클로저 자체가 소모된다.
```rust
let my_str = "hello".to_string();
let f = || drop(my_str);

f();
f();  // 컴파일 에러
```

### 1.5.2. FnMut
값의 mut 접근권한을 필요로 하지만 아무런 값도 드롭하지 않는 클로저이다. 클로저 자체를 mut로 선언한 경우에 여러 번 호출할 수 있는 클로저군이다.
```rust
let mut i = 0;
let mut f = || i += 1;  // f클로저 자체가 i에 대한 mut 접근권한을 가진다.

f();
f();
println!("{}", i);  // 2
```
<!-- ```rust
let mut i = 0;
let mut f = || i += 1;

f();
println!("{}", &mut i);  // 컴파일 에러
f();
``` -->

# 2. Passed
클로저를 위한 Copy와 Clone  
콜백  
효율적인 클로저 사용법  