<p float="left">
    <img src="./image/PIN.png" alt="PINLAB" height="100">
    <img src="./image/docker.png" alt="docker" height="100">
</p>

Chapter04 <!-- omit in toc -->
===
쿠버네티스 아키텍처

**Table of Contents**
- [Kubernetes Cluster Architecture](#kubernetes-cluster-architecture)
- [Main Components](#main-components)
  - [Master](#master)
    - [etcd](#etcd)
    - [kube-apiserver](#kube-apiserver)
    - [kube-scheduler](#kube-scheduler)
    - [kube-controller-manager](#kube-controller-manager)
    - [cloud-controller-manager](#cloud-controller-manager)
  - [Node](#node)
    - [kubelet](#kubelet)
    - [kube-proxy](#kube-proxy)
    - [container runtime](#container-runtime)
  - [Addons](#addons)
    - [networking addon](#networking-addon)
    - [DNS addon](#dns-addon)
    - [dashboard addon](#dashboard-addon)
    - [conatainer resource monitoring](#conatainer-resource-monitoring)
    - [cluster logging](#cluster-logging)
- [Ojbect and Controller](#ojbect-and-controller)
  - [Namespace](#namespace)
    - [kubedns](#kubedns)
  - [Template](#template)


# Kubernetes Cluster Architecture
마스터와 노드의 구조로 이루어짐\
마스터는 고가용성을 위해 3대 정도에서 운영\
노드에서는 실제 사용하는 컨테이너 실행, 초기에는 미니언이라고 불림

# Main Components
## Master
### etcd
고가용성을 제공하는 키-값 저장소\
분산 시스템에서 노드 사이의 상태를 공유하는 합의 알고리즘 중 하나인 raft 알고리즘 구현\
쿠버네티스에서 필요한 모든 데이터를 저장하는 데이터베이스 역할을 함

### kube-apiserver
쿠버네티스 클러스터의 API를 사용할 수 있도록 하는 컴포넌트\
클러스터로 온 요청이 유효한지 검증\
수평적으로 확장할 수 있도록 설계

### kube-scheduler
자원 할당이 가능한 노드 중 알맞은 노드를 선택해서 새롭게 만든 파드를 실행

### kube-controller-manager
쿠버네티스에는 파드들을 관리하는 컨트롤러가 존재\
컨트롤러 각각을 실행하는 컴포넌트\
go언어로 개발

### cloud-controller-manager
클라우드 서비스와 연결해 관리하는 컴포넌트

## Node
### kubelet
클러스터 안 모든 노드에서 실행되는 에이전트\
파드 컨테이너들의 실행을 직접 관리\
헬스 체크 진행

### kube-proxy
클러스터 안에 별도의 가상 네트워크를 설정하고 관리

### container runtime
컨테이너를 실행시키는 런타임\
containerd가 kubernetes와 같은 클라우드 컴퓨팅 재단(CNCF) 소속이라 기본 런타임으로 사용 가능

## Addons
클러스터 안에서 필요한 기능을 실행하는 파드\
kube-system을 네임스페이스로 사용

### networking addon
클러스터 안에 가상 네트워크를 구성해 사용할 때 사용\
ex: flannel

### DNS addon
DNS 레코드 제공

### dashboard addon
클러스터 현황이나 파드 상태를 파악하기 쉬움

### conatainer resource monitoring
kubelet안에 포함된 cAdvisor라는 컨테이너 모니터링 도구 사용(?)

### cluster logging
개별 컨테이너의 로그와 클러스터 구성 요소의 로그들을 중앙화된 로그 수집 시스템에 모아서 보는 애드온

# Ojbect and Controller
오브젝트, 그를 관리하는 컨트롤러\
오브젝트 : pod, service, volume, namespace 등\
컨트롤러 : ReplicaSet, deployment, StatefulSet, DaemonSet, job 등

## Namespace
클러스터 하나를 여러 개 논리적인 단위로 나눠서 사용하는 것\
실행하는 앱을 구분하거나 사용량을 제한할 수 있음\
기본적으로 생성되는 네임스페이스:
- default : 기본 네임스페이스
- kube-system : 쿠버네티스 시스템에서 관리. 관리용 파드나 설정 등
- kube-public : 모든 사용자가 읽을 수 있는 네임스페이스. 클러스터 사용량 같은 정보 관리
- kube-node-lease : 각 노드의 임대 오브젝트들을 관리하는 네임스페이스
```bash
kubectl get namespaces
kubectl config current-context
kubectl config get-contexts minikube
kubectl config set-context minikube --namespace=kube-system
kubectl config get-contexts $(kubectl config current-context) --namespace=kube-system
kubectl config view | grep namespace
kubectl get pods --all-namespaces
kubectl config set-context $(kubectl config current-context) --namespace=default
kubectl config get-contexts $(kubectl config current-context)
kubectl config set-context $(kubectl config current-context) --namespace=""
kubectl config get-contexts $(kubectl config current-context)
```

### kubedns
네임스페이스 변경을 쉽게 해주는 도구
```bash
kubens kube-system
```

## Template
YAML 형식의 템플릿 사용\
Scalars(strings/numbers), Sequences(arrays/lists), Mappings(hashes/dictionaries)의 세 가지 기초 요소로 표현\
주석은 # 로 시작, 성격이 다른 YAML 형식의 구분자 혹은 YAML의 시작을 알리는 용도로 --- 사용
> **Scalars**\
> Name: kim
> 
> **Sequences**\
> ProgrammingSkills:\
> &nbsp;&nbsp;\- java\
> &nbsp;&nbsp;\- python
>
> **Mappings**\
> Data:\
> &nbsp;&nbsp;Height: 170\
> &nbsp;&nbsp;Weight: 80

템플릿의 기본 형식:
```yaml
---
apiVersion: v1
kind: Pod
metadata:
spec:
```
> apiVersion : 사용하려고 하는 쿠버네티스 API 버전 명시, `$ kubectl api-versions`로 확인 가능\
> kind : 오브젝트 혹은 컨트롤러의 종류 명시\
> metadata : 오브젝트의 이름이나 레이블 등 설정\
> spec : 컨테이너를 실행할 때의 동작

`$ kubectl explain <object>`로 조회 가능\
<> 안에 명시된 데이터 타입이 \<Object\>인 경우 `$ kubectl explain pods.metadata`와 같이 하위 필드를 조회 가능\
혹은 `--recursive`옵션을 통해 하위 필드를 한꺼번에 조회 가능