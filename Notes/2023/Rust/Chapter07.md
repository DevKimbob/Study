Error Handling <!-- omit in toc -->
===

**Table of Contents**
- [1. Panic](#1-panic)
  - [1.1. 중단](#11-중단)
- [2. Result](#2-result)
  - [2.1. 오류 잡기](#21-오류-잡기)
  - [2.2. Result 타입 별칭](#22-result-타입-별칭)
  - [2.3. 오류 출력](#23-오류-출력)
  - [2.4. 오류 전파](#24-오류-전파)
  - [2.5. 여러개의 오류](#25-여러개의-오류)
  - [2.6. 발생할 수 없는 오류](#26-발생할-수-없는-오류)
  - [3. Passed](#3-passed)


# 1. Panic
프로그램 자체에 있는 버그로 인해 문제가 생겼을 때 패닉에 빠진다.
* 배열의 범위 밖에 있는 요소에 접근
* 정수를 0으로 나누는 행위
* Err이 된 Result에 .expect()를 호출
* 단언문 실패 (ex. expect, assert)
* panic!() 매크로 호출

패닉에 빠지면 보통 다음 절차를 진행한다.
1. 터미널에 오류 메시지가 출력
2. 스택 해제
   1. 현재 함수가 쓰던 임시 값, 지역변수, 인수는 모두 생성한 순서와 반대로 드롭
   2. 현재 함수 호출이 정리되고 나면, 그의 호출부로 이동해서 같은방법으로 변수와 인수 드롭
   3. 스택 끝에 닿을 때까지 계속해서 정리
3. 스레드 종료

패닉은 크래시도 아니고 미정의 동작도 아니다. 오히려 자바의 RuntimeException이나 C++의 std::logic_error에 가깝다.
> C/C++의 `core dumped`와 비교

패닉은 스레드별로 발생한다. 스택 해제를 잡아서 스레드를 죽지 않고 계속 실행되게 만드는 방법도 있다(`std::panic::catch_unwind()`).

## 1.1. 중단
다음 두가지 상황에서는 러스트가 스택 해제를 시도하지 않는다.
1. 러스트가 첫 번째 패닉을 정리하고 있는 상황에서 `.drop()`메소드가 두 번째 패닉을 유발하면 이는 치명적인 상황으로 간주하고 전체 프로세스 중단
2. 컴파일 옵션으로 패닉 처리 방식을 명시
   > `-C panic=abort`옵션으로 컴파일할 시 첫 번째 패닉이 발생하는 즉시 프로세스 중단

# 2. Result
러스트는 예외가 없는 대신 실패할 수 있는 함수가 다음과 같은 반환 타입을 갖는다.
```rust
fn function(arg: type) -> Result<TYPE, io::Error>
```
* Reuslt 타입 : 실패 가능성을 암시
* 해당 함수는 성공 결과 `Ok(ret)`나 실패 결과`Err(err_val)` 둘 중 하나를 반환
  * `ret`은 `TYPE`값이며, `err_val`은 무엇이 잘못됐는지를 설명하는 `io::Error`값
* 위 함수를 호출할 때마다 모종의 오류 처리 코드 작성을 요구

## 2.1. 오류 잡기
가장 철저한 방법으로 match 표현식을 사용한다. 이는 다른 언어의 try/catch에 해당하는 방식이다. 오류를 호출부에 넘기지 않고 직접 처리하고자 할 때 사용한다.
```rust
match function(arg) {
    Ok(ret) => {
        println!("{}", ret);
    }
    Err(err) {
        println!("Error: {}", err);
    }
}
```
match는 코드를 구구절절 늘어놓게 되는 경향이 있어 `Result<T, E>`는 유용하게 쓸 수 있는 메서드를 모아 제공한다.
```rust
result.is_ok(), result.is_err()
// result가 성공결과인지 오류결과인지 말해주는 bool 반환

result.ok()
// 성공값이 있을 경우 그것을 Option<T>로 반환
// 성공결과이면 Some(success_value)반환, 그렇지 않으면 None을 반환하며 오륫값은 버린다.

result.err()
// 오륫값이 있을 경우 그것을 Option<E>로 반환

result.unwrap()
// result가 성공결과일 경우 성공값을 반환
// 오류결과일 경우 패닉에 빠짐

result.expect(message)
// .unwrap()과 동일하나, 패닉에 빠졌을 때 출력할 메시지 지정

result.as_ref(), result.as_mut()
// Result<T, E>를 각각 Result<&T, &E>, Result<&mut T, &mut E>로 반환

// 등등...
```

## 2.2. Result 타입 별칭
다음과 같이 오류 타입이 생략된 경우, Result 타입 별칭을 쓰고 있는 것으로, 모듈의 함수들이 공통적으로 사용하는 오류 타입을 반복해서 적지 않아도 되도록 한다.
```rust
fn function(arg: type) -> Result<()>
```

## 2.3. 오류 출력
```rust
println!("{}", err);
println!("{:?}", err);  // 해당 오류의 Debug 뷰를 보는 방법
err.to_string()
err.source()  // err의 원인이 되는 오류가 있을 경우 Option으로 반환
```
```rust
fn print_error(mut err: &dyn Error) {
    let _ = writeln!(stderr(), "error: {}", err);
    while let Some(source) == err.source() {
        let _ = writeln!(stderr(), "caused by: {}", err);
        err = source;
    }
}
```

## 2.4. 오류 전파
```rust
let ret = function(arg)?;
```
1. 함수가 성공한 경우 `Result`를 풀어서 그 안에 있는 성공값을 꺼낸다. 이 때 `let`의 타입은 `Result<TYPE, io::Error>`가 아니라 단순히 `TYPE`이 된다.
2. 오류가 발생한 경우에는 즉시 바깥쪽 함수에서 복귀하고 오류 결과를 호출 체인 위로 전달한다. 이 때문에 `?`는 반환 타입이 `Result`인 함수에서만 쓸 수 있다.

> Result가 아니라 Option에도 ?를 적용할 수 있다. Option을 반환하는 함수 안에서 ?로 값을 풀면 None일 경우에 조기 복귀할 수 있다.  
> `let ret = function(arg).ok()?;`

## 2.5. 여러개의 오류
한 함수가 여러개의 오류 타입을 발생시킬 수 있는 경우, 그에 대한 해결방법이 두 가지가 있다.
1. 발생할 수 있는 오류 타입들을 어우르는 오류 타입 정의
2. `Box<dyn std::error::Error + Send + Sync + 'static>` 타입으로 오류 타입을 변환하여 반환값으로 사용.
    ```rust
    type GenericError = Box<dyn std::error::Error + Send + Sync + 'static>;
    type GenericResult = Result<T, GenericError>;

    fn function(arg: type) -> GenericResult<Vec<i64>> { ... }
    ```

## 2.6. 발생할 수 없는 오류
오류가 절대 발생할 수 없다고 확신할 수 있는 상황에서는 `.unwrap()`메서드를 사용하여 처리할 수 있다.
> 결과가 Ok이면 성공값을 반환하고, Err이면 패닉에 빠짐

## 3. Passed
오류 무시하기  
main()에서 오류 처리하기  
사용자 정의 오류 타입 선언하기