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