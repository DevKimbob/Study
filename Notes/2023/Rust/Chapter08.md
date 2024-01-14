Crate and Module <!-- omit in toc -->
===

**Table of Conents**
- [1. Crate](#1-crate)
  - [1.1. 사용방법](#11-사용방법)
  - [1.2. 에디션](#12-에디션)
- [2. Module](#2-module)
  - [2.1. 중첩된 모듈](#21-중첩된-모듈)
    - [2.1.a 범위](#21a-범위)
  - [2.2. 모듈 포함시키기](#22-모듈-포함시키기)
  - [2.3. 경로와 가져오기](#23-경로와-가져오기)
  - [2.4. 표준 프렐류드](#24-표준-프렐류드)
  - [2.5. 어트리뷰트](#25-어트리뷰트)
  - [2.7. 문서화](#27-문서화)
- [3. Passed](#3-passed)


# 1. Crate
러스트 프로그램의 구성 단위.

러스트 라이브러리 또한 크레이트 형태로 배포된다. `cargo build --verbose`를 통해 의존성을 가진 프로그램을 빌드해보면 여러 크레이트를 다운로드 하는 것을 볼 수 있다.

## 1.1. 사용방법
코드 내에 `use`선언문으로 필요한 크레이트 사용한다.
```rust
use num::Complex;
use image::ColorType;
```
Cargo.toml파일에 각 크레이트의 원하는 버전을 지정한다. 
```toml
[dependencies]
num = "0.4"
image = "0.13"
```

## 1.2. 에디션
러스트는 지원이 필요하다고 판된되는 경우에 대해서 새로운 에디션을 출시한다.
> 2015, 2018, 2021 ...

# 2. Module
크레이트가 프로젝트 간의 코드공유에 관한 것인데 비해 모듈은 프로젝트 내부의 코드 구성을 담당한다. 모듈은 러스트의 네임스페이스로 일종의 컨테이너 역할을 한다.
```rust
mod name {
    use CreateName;

    pub struct StName {
        ...
    }

    pub fn function(arg: type) -> Type {
        ...
    }

    pub(crate) fn crate_function(arg: type) -> Type {
        ...
    }

    fn protected_function(arg: type) -> Type {
        ...
    }
    
    ...
}
```
모듈은 아이템의 집합체로, 아이템은 위 코드에서 구조체와 세 함수처럼 이름이 있는 기능을 말한다.  
* pub 키워드는 아이템을 모듈 바깥에서 접근할 수 있도록 공개한다. 아이템 내보내기라고도 한다.  
* pub(crate)는 이 크레이트 내부 어디서든 사용할 수 있으나 외부 인터페이스로는 노출하지 않아, 다른 크레이트에서는 사용할 수 없도록 하겠다는 의미이다.  
* pub으로 표시되지 않은 것은 모두 비공개이며, 자신이 정의된 모듈이나 자식 모듈에서만 사용할 수 있다.

|키워드\범위|크레이트|모듈|
|---|---|---|
|pub|public|public|
|pub(crate)|private|public|
|(생략)|protected|protected|
> C++ Keyword 기준

## 2.1. 중첩된 모듈
```rust
mod parent {
    pub mod child1 {
        ...
    }
    pub mod child2 {
        ...
    }
}
```
```rust
mod child1;
mod child2;

mod parent {
    ...
}
```

### 2.1.a 범위
```rust
mod parent {
    pub mod child1 {
        ...
    }
    pub mod child2 {
        pub mod grand {
            pub(super) struct A {  // 부모 모듈(parent::child2)만 접근 가능
                ...
            }
            pub(in crate::parent::child1) struct B {  // 경로에 해당하는 모듈(parent::child1)만 접근 가능
            // crate : 절대경로
            // self, super : 상대경로
                ...
            }
        }
    }
}
```

## 2.2. 모듈 포함시키기
<!--
│   hi
├── hi
└── debug
-->
```
project/
├── Cargo.toml
└── src/
    ├── main.rs
    ├── submod.rs
    └── submodules/
        ├── mod.rs
        └── grandsub.rs
```
`main.rs`에서 `mod module;`이라고 하면 `module.rs`가 있거나 `module/mods.rs`가 있는지 확인한다. 둘 다 없거나 둘 다 있으면 오류이다. 위 예시에서 `main.rs`에서 `mod submod;`라고 하면 같은 디렉터리의 `submod.rs`를, `mod submodules;`라고 하면 `submodules/mod.rs`를 가리킨다.

## 2.3. 경로와 가져오기
`::`연산자를 통해 모듈의 하위모듈이나 기능을 접근할 수 있다.
```rust
use std::mem;
use std::collections::{HashMap, HashSet};  // 둘 다 가져오기
use std::io::prelude::*;  // 전부 가져오기
use std::io::Result as IOResult  // 별칭으로 가져오기
```

## 2.4. 표준 프렐류드
모든 프로젝트에는 표준 라이브러리 `std`가 자동으로 연결된다. 또한 `Vec`과 `Result`처럼 자주 쓰이는 이름 몇 가지가 표준 프렐류드에 들어있어서 자동으로 포함된다.

## 2.5. 어트리뷰트
컴파일러에 내리는 각종 지시와 권고를 작성하기 위한 러스트의 범용 문법이다.
```rust
#[test]
fn function() {
    ...
}

#[cfg(unix)]
fn func_for_unix() {
    ...
}
```

## 2.7. 문서화
라이브러리를 위한 HTML문서를 생성
```bash
cargo doc --no-deps --open  // 의존하는 크레이트에 대한 내용은 제외, 생성된 문서를 브라우저에 열기
```

# 3. Passed
use 선언을 pub으로 만들기  
스트럭트 필드를 pub으로 만들기  
스태틱과 상수  
프로그램을 라이브러리로 만들기  
src/bin 디렉터리  
cargo.lock  
crates.io 게시  
워크스페이스