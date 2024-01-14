Default Types <!-- omit in toc -->
===

**Table of Contents**
- [1. Types (simplyfied)](#1-types-simplyfied)
  - [1.1. Integer](#11-integer)
  - [1.2. Float](#12-float)
  - [1.3. Boolean](#13-boolean)
  - [1.4. Charactor](#14-charactor)
  - [1.5. Tuple](#15-tuple)
  - [1.6. Struct](#16-struct)
  - [1.7. Enum](#17-enum)
  - [1.8. Box](#18-box)
  - [1.9. Reference](#19-reference)
  - [1.10. String](#110-string)
  - [1.11. str Reference](#111-str-reference)
  - [1.12. Array](#112-array)
  - [1.12. Vector](#112-vector)
  - [1.13. Slice Reference](#113-slice-reference)
  - [1.14. Option](#114-option)
  - [1.15. Result](#115-result)
  - [1.16. Trate Objects](#116-trate-objects)
  - [1.17. Function Pointer](#117-function-pointer)
  - [1.18. Closer](#118-closer)
- [2. Type Definition](#2-type-definition)


# 1. Types (simplyfied)
## 1.1. Integer
```rust
i8, i16, i32, i64, i128  // signed
u8, u16, u32, u64, u128  // unsigned

// 32bit or 64bit depending on OS
isize  // signed machine word size
usize  // unsigned machine word size
```
* 8, 16, ... , 128bit
* uses `u8` for Bytes
  <!-- * or you can use `byte literal`, where only ASCII can be used
  ```rust
  b'A'  // equals 65u8
  ``` -->
* can use types for suffixes
  ```rust
  42u8, 128isize
  ```
* can use `0x`, `0o`, `0b`as prefixes for base indication
  ```rust
  0xff, 0b0110
  ```
* can use `_`s
  ```rust
  0xffff_ffff, 127_u8
  ```
* if type is not specified `i32` is the default type among the candidates.
  * causes error if else

## 1.2. Float
```rust
f32  // single presision : float
f64  // double presision : double
```
* includes +infinity, -infinity, +0, -0, NaN

## 1.3. Boolean
```rust
bool  // true, false
```

## 1.4. Charactor
```rust
char  // 32bit unicode, different from u8 or u32 compared to C/C++
```

## 1.5. Tuple
```rust
(char, u8, i32)  // type mixing is possible, access by index
()  // unit tuple
```

## 1.6. Struct
```rust
struct S { x: f32, y: f32 }  // struct with named fields
struct T (i32, char);  // tuple struct
struct E;  // unit struct
```

## 1.7. Enum
```rust
enum Attend { OnTime, Late(u32) }
```

## 1.8. Box
```rust
Box<Attend>  // 힙에 있는 데이터의 소유권을 가지는 포인터
```

## 1.9. Reference
```rust
&i32, &mut i32
```

## 1.10. String
```rust
String  // dynamic range UTF-8 string
```

## 1.11. str Reference
```rust
&str  // UTF-8 text pointer
```

## 1.12. Array
```rust
[f64; 4], [u8; 256]  // [init_value, count]
```

## 1.12. Vector
```rust
Vec<f64>  // dynamic length vector
```
* can create using vec! macro
    > 1. create empty vector using Vec::new()
    > 2. fill-in given values

## 1.13. Slice Reference
```rust
&[u8], &mut [u8]  // implicitly used when arrays are passed(?)
```
* fat pointer : (pointer to slices's first element, count of the elements)

## 1.14. Option
```rust
Option<&str>  // None or Some(v)
```

## 1.15. Result
```rust
Result<u64, Error>  // Ok(v) or Err(e)
```

## 1.16. Trate Objects
```rust
&dyn Any, &mut dyn Read
```

## 1.17. Function Pointer
```rust
fn(&str) -> bool
```

## 1.18. Closer
```rust
// closer
```

# 2. Type Definition
```rust
type Bytes = Vec<u8>;
```