Getting Started <!-- omit in toc -->
===

**Table of Contents**
- [1. Variable](#1-variable)
- [2. Function](#2-function)
- [3. Macro](#3-macro)


# 1. Variable
```rust
let variable: type = Expr;
let variable = Expr;  // 러스트가 타입을 추론하여 적용
```

# 2. Function
```rust
fn function(arg: type) -> return_type {
    ...
}

fn function(arg: type) {  // 반환값 없음
    ...
}
```

# 3. Macro
```rust
println!("Hello World");
let v = vec![10, 20, 30];
```