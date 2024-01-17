Micro Service Architecture <!-- omit in toc -->

**Table of Contents**
- [4. React](#4-react)
  - [4.1. Web](#41-web)
  - [4.2. Install React](#42-install-react)
  - [4.3. Create React App](#43-create-react-app)
  - [4.4. HTML](#44-html)
  - [node's property: "value"](#nodes-property-value)
  - [4.5. Webpack](#45-webpack)
  - [4.6. Svelte : Awesome Awesome Awesome](#46-svelte--awesome-awesome-awesome)
  - [4.7. MUI](#47-mui)
  - [4.8. JSX](#48-jsx)
  - [4.9. Components](#49-components)
- [5. Application](#5-application)
  - [5.1. B2C, B2B](#51-b2c-b2b)
  - [5.2. Props](#52-props)
  - [5.2. Hook](#52-hook)
  - [5.3. 데이터 반응형](#53-데이터-반응형)
  - [5.4. JS vs Window](#54-js-vs-window)
  - [5.5. useEffect](#55-useeffect)
  - [5.6. Network](#56-network)
  - [5.7. Google Docs](#57-google-docs)
  - [5.8. GraphQL](#58-graphql)


# 4. React
> Intended to make web applications

## 4.1. Web
인터넷을 통해 문서를 주고 받기 위해서 등장

* Web Page : 웹을 통해 문서를 제공
* Web Application : 웹을 통해 다양한 애플리케이션을 제공
* Mark Up : 텍스트에 구조, 스타일 등을 추가한 문서

## 4.2. Install React
[reference](https://github.com/nodesource/distributions "https://github.com/nodesource/distributions")
```bash
curl -fsSL https://deb.nodesource.com/setup_lts.x | sudo -E bash - &&\
sudo apt-get install -y nodejs
```

## 4.3. Create React App
```bash
npx create-react-app <project_name>
cd <project_name>
npm start  # or npm run start
```

## 4.4. HTML
* in HTML  
\<tag attribute="value">

* in DOM  
node's property: "value"
---
Nodes:
1. element node
2. text node
3. comment node
4. etc.
> only element node can have attributes
---
from console  
```console
document.getElementById('root')
const root = document.querySelector('#root')
console.dir(root)
```

## 4.5. Webpack
bundler 중 현재 가장 유명한애긴 한데, 최근에는 Byte(?)가 뜨는 중  
소스코드를 수정하면 페이지를 새로고침하지 않아도 자동으로 업데이트 해주는 역할도 해줌

## 4.6. Svelte : Awesome Awesome Awesome
2019년에 등장  
한번 빌드 되고나면 순수 자바스크립트 언어로 구성되어 있음  
(React, Vue 등의 경우 : 따로 라이브러리를 호출하는 부분이 존재)

## 4.7. MUI
React version of Material UI framework

## 4.8. JSX
react uses JSX(JS + XML)  
XML과 HTML의 상위 부모가 존재...!  
한때는 XML과 HTML을 합친 XHTML의 붐이 일어나기도 했음

## 4.9. Components
Header, Main, Footer
GNB, LNB : in header, Global/Local Navigation Bar

# 5. Application
## 5.1. B2C, B2B
저런 포탈같은건 은근 B2B로 많이 쓰임

## 5.2. Props
단방향으로 데이터 전달
부모->자식

## 5.2. Hook
순수함수 : 같은 인자를 넣어 실행하면 무조건 같은 결과가 도출되는 함수  
순수함수에서 stateful한 다른 부분을 사용하는 걸 Hook으로 사용하게 했음(?)  

## 5.3. 데이터 반응형
데이터에 변화가 생기면 루프를 통해서 계속 보고있는게 아니라 이벤트 처리마냥 동작...

## 5.4. JS vs Window
setInterval, alert, localStorage 등의 메소드는 js core가 아니라 윈도우에 포함된 메서드
```js
setInterval()  # is same as
window.setInterval()
```

## 5.5. useEffect
index.js에서 `<React.StrictMode>` : 잘 동작하는지 한번 더 실행해서 확인..?  
```js
useEffect(() => {
  // 1초마다 시각을 업데이트하는 함수
  const intervalId = setInterval(() => {
    setTime(new Date().toLocaleTimeString());
  }, 1000);

  console.log('hi' + time)

  return () => {
    console.log('hello');
  };
}, []);
// 위에서 hi가 두번뜨는 이유라고는 하는데 왜 hello는 한번이고
// hi랑 hello 순서도 궁금
// useEffect return문 추가 검색

// 아니면 한번 실행하고나면 hi만 뜨고
// 다시 한번 실행할 때 hello 뜨고 다시 hi떠서, hi/hello/hi 인건가?
```

## 5.6. Network
network -> throttling -> slow 3g

## 5.7. Google Docs
캔버스로 셀 화면 렌더링

## 5.8. GraphQL
쓰는 이유중에 내가 FE에 적용할 데이터 구조를 그대로 BE에 요청하면 그 응답을 그대로 "쏟아버리기"만 하면 되는 이유도 있음