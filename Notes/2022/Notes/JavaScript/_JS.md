JavaScript
===
Reference : [javascript.info](javascript.info "javascript.info")  

# 1. An Introduction
## 1.1. 
* 자바스크립트 : 웹페이지에 생동감을 붙여넣기 위해 만들어진 프로그래밍 언어  
    * 작성한 프로그램 : 스크립트, HTML 안에 작성 가능, 특별한 컴파일 없이 문자형태로 작성 가능  
    서버에서도 실행가능  
    자바스크립트 엔진이 들어있는 모든 디바이스에서도 동작  
    브라우저에는 자바스크립트 가상 머신이라는 엔진이 내장  
        * V8(Chrome, Opera), SpiderMonkey(Firefox), IE(Microsoft Edge, Safari) 등등  
        작동과정 : 스크립트 읽기(파싱) -> 기계어 전환(컴파일) -> 코드실행  
    
* 브라우저에서 할 수 있는 일 :  
    * 메모리나 cpu같은 저수준 영역의 조작을 허용하지 않음  
    자바스크립트의 능력은 실행 환경에 상당한 영향을 받음  
        * ex : Node.js 환경에서는 임의의 파일을 읽거나 쓰고, 네트워크 요청을 수행하는 함수 지원  
    등등  

* 브라우저에서 할 수 없는 일 :  
    * 디스크 관련  
    탭과 창간의 정보 공유  
    타 사이트, 도메인과 정보공유  
    등등  
    
* 강점 :  
    * HTML/CSS 와 완전히 통합  
    간단한 일은 간단하게  
    모든 주요 브라우저에서 지원, 기본언어  

* 추가 언어 :  
    * CoffeScript : syntactic suger, Ruby 개발자들이 좋아함  
    TypeScript : strict data typing에 집중, Microsoft에서 개발  
    Flow : TypeScript와 다른 방식의 자료형 강제, Facebook이 개발  
    Dart : 브라우저가 아닌 환경에서 동작하는 고유의 엔진을 가진 독자적 언어, Googl이 개발  

## 1.2.
* 명세서  
    * ECMA-262 specification  

* 매뉴얼  
    * MDN JavaScript Reference  

* 호환성 표  
    * ...  

## 1.3.
* 통합 개발 환경 : IDE  
    * Visual Studio Code  
    WebStorm  
    등등  

* 경량 에디터  
    * Atom  
    Visual Studio Code  
    Sublime Text  
    Nodepad++  
    Vim, Emacs  
    등등  

## 1.4.
* Chrome :  
    * F12  
    ex : bug.html:12  
        * bug.html : 에러가 난 파일  
        :12 : 에러가 난 라인  

# 2. JavaScript Fundamentals
## 2.1.
* <script> 태그를 이용하여 HTML 문서 대부분의 위치에 삽입 가능  
```html
<!DOCTYPE HTML>
<html>
    <body>
        <p>스크립트 전</p>

        <script>
            alert('Hello, world!');
        </script>

        <p>스크립트 후</p>
    <body>
</html>
```

* 모던 마크업  
    * type속성 : <script type=...>  
        * 이젠 타입명시가 필수가 아니고, 속성의 의미가 바뀜  
    * language속성 : <script language=...>  
        * 현재 사용중인 스크립트 언어를 나타냄. 의미가 퇴화  
    * 스크립트 전후 주석  
        * <script>를 태그처리 할 수 있으므로, 요즘은 사용하지 않음  

* 외부 스크립트  
src 속성을 사용하여 HTML에 삽입
```html
<script src="/path/to/script.js"></script>
```

* URL전체를 속성으로 사용가능
```html
<script src="https://example.com/example.js"></script>
```

* 복수의 스크립트 삽입
```html
<script src="/example1.js"></script>
<script src="/example2.js"></script>
```

* 주의 :  
    * src 속성이 있으면 태그 내부의 코드는 무시  
    HTML 안에 직접 스크립트 코드를 작성하는 방식은 코드가 간단할때만 사용

## 2.2.
* 암시적 세미콜론, 세미콜론 자동 삽입을 지원하지만 가능하면 C처럼 줄마다 세미콜론
* no error
```js
alert('Hello')
alert('World')
```
* error
```js
alert("error")
[1, 2].forEach(alert)
```

* 주석  
```js
// single line

/*
multiple lines
*/
```

## 2.3.
* "use strict" or 'use strict'
    * ES5에서 기존 기능을 변경한 효과가 활성화되게 함  
    클래스나 모듈에 기본탑재 되어있어 둘 다 안쓰는 경우에만 사용해도 됨

## 2.4.
* 변수 : let 으로 정의  
```js
let message;
message = 'Hello';

let message2 = 'world';
let message3 = 'yo', message4 = 'yoyo';  // 가능은 하지만 권장하지는 않음

var old = 'old';  // 오래된 방식으로 오래된 스크립트에서 보이기도 함

let message = 'yoyoyo';  // 에러 : 선언을 두번이상 할경우 에러발생
```

* 변수명
```js
let abc123;  // 문자, 숫자
let $, _;  // 기호 $ _ 까지만 사용가능
let 1abc;  // 숫자로는 시작 불가
```

* 상수
```js
const myBirthday = '41.13.5213';  // let 대신 const 사용
const COLOR_RED = '#F00';  // 대문자 상수는 대문자와 밑줄로 구성
```

## 2.5.
* 동적 타입 : 변수의 타입을 언제든지 바꿀 수 있음  

* 숫자형 : 정수, 부동소수점 숫자, 특수 숫자 값
```js
// 특수 숫자 값들
alert(1 / 0);  // Infinity
alert(Infinity);  // also Infinity
alert("text" / 2);  // NaN, Not a Number : 부정확하거나 정의되지 않은 수학연산결과
```

* BigInt : 길이 상관없이 정수를 나타냄
```js
const bigInt = 1234567890n;  // 끝에 n을 붙임
```

* 문자형
```js
let str = "Hello";  // " "
let str2 = 'World';  // ' '
let phrase = `text and embed ${str}`;  // ` ` 엠베드를 포함가능
```

* Boolean형
```js
let amIHungry = true;
let yo = false;
```

* null : 별도의 자료형  
    * 타 언어의 null과 성격이 다름
    값이 비어있다, 알 수 없다, 존재하지 않는다 를 나타내는데에 사용
```js
let age = null;
```

```js
어차피 웹사이트에 있는 내용을 토대로 공부를 하는거고
사실상 내용 복붙이랑 큰 차이가 없는데
텍스트로 정리할 이유가 있나..?

그냥 ./codes/_notes/ 에 코드화 해서 정리해놓고
정확하거나 자세한게 궁금하면 레퍼런스로 찾아가거나 검색하는 방식으로 전환하는게 어떤지 고민중
```





# 3. Code Quality
# 4. Objects: The Basics
# 5. Data Types
# 6. Advanced Working With Functions
# 7. Object Properties Configuration
# 8. Prototypes, Inheritance
# 9. Classes
# 10. Error Handling
# 11. Promises, async/await
# 12. Generators, Advanced Iteration
# 13. Modules
# 14. Miscellaneous