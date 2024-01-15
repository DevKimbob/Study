Micro Service Architecture <!-- omit in toc -->

**Table of Contents**
- [4. React](#4-react)
  - [4.1. Web](#41-web)
  - [4.2. Install React](#42-install-react)
  - [4.3. Create React App](#43-create-react-app)


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