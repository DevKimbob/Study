<p float="left">
    <img src="images/PIN.png" alt="PINLAB" height="100">
    <img src="images/docker.png" alt="docker" height="100">
</p>

# K8s Perfect Guide

**Table of Contents**
- [K8s Perfect Guide](#k8s-perfect-guide)
- [3. Kubernetes Environments](#3-kubernetes-environments)
    - [Three main types](#three-main-types)
  - [Local Kubernetes](#local-kubernetes)
    - [Minikube](#minikube)
    - [Docker Desktop for Mac/Windows](#docker-desktop-for-macwindows)
    - [Kind](#kind)
  - [Kubetnetes Build Tools](#kubetnetes-build-tools)
    - [SLI/SLO](#slislo)
    - [Kubeadm](#kubeadm)
    - [Rancher](#rancher)
  - [Public Cloud K8s](#public-cloud-k8s)
    - [GKE](#gke)
    - [AKS](#aks)
    - [EKS](#eks)
  - [Kubernetes Playground](#kubernetes-playground)

# 3. Kubernetes Environments
### Three main types
* 로컬 쿠버네티스
  * 물리 머신 한 대에 구축
  * Minikube
  * Docker Desktop for Mac/Windows
  * kind
* 쿠버네티스 구축 도구
  * 도구를 사용하여 온프레미스/클라우드에 클러스터를 구축하여 사용
  * kubeadm
  * Rancher
* 관리형 쿠버네티스 서비스
  * 퍼블릭 클라우드의 관리형 서비스로 제공하는 클러스터를 사용
  * GKE (Google)
  * AKS (Azure)
  * EKS (Elastic)

## Local Kubernetes
### Minikube
물리머신에 단일 노드 구성 로컬 쿠버네티스를 쉽게 구축하고 실행가능\
하이퍼바이저 필요
* 리눅스 : docker, podman, KVM, Baremetal
* 윈도우 : docker, VBox, Hyper-V
* 맥 : docker, Hyperkit driver, VBox, Podman, ...

### Docker Desktop for Mac/Windows
```bash
kubectl config use-context docker-desktop
```

### Kind
Kubernetes in Docker\
로컬 환경에서 멀티 노드 클러스터를 구현할 수 있음\
도커 컨테이너를 여러 개 기동하고, 그 컨테이너를 쿠버네티스 노드로 사용\
내부적으로 kubeamd을 사용
```bash
kubectl config use-context <kind_cluster_name>
```

## Kubetnetes Build Tools
### SLI/SLO
Service Level Indicator / Service Level Objective\
쿠버네티스 서비스 수준 목표\
이를 만족하는 클러스터 최대 구성 범위 존재

### Kubeadm
쿠버네티스에서 제공하는 공식 구축 도구\
책의 예시에서는 플라넬을 사용하여 Pod간의 통신 구현\

### Rancher
랜처 랩에서 개발하는 오픈소스 컨테이너 플랫폼\
중앙에서 랜처 서버를 기동시키고 관리자는 랜처 서버를 통해 클러스터를 구축하고 관리\

## Public Cloud K8s
### GKE
여러 기능이 포함되어 있어 클러스터 자체의 운용 부하를 낮출 수 있음\
GCE를 쿠버네티스 노드로 사용\
가동시간이 24시간으로 제약된 선점형 인스턴스(Preemptible Instance)로 노드 구성 가능 (preemptible-killer 사용 검토)\
노드 내부에 레이블을 부여하여 그룹핑하는 NodePool기능 존재\

### AKS
Microsoft Azure에서 동작하는 쿠버네티스 서비스\
버스팅 하기 전 까지는 비용이 발생하지 않음\

### EKS
Amazon에서 제공하는 쿠버네티스 서비스\
AWS 서비스와 통합된 기능들이 기대되는 특징\

## Kubernetes Playground
도커에서 제공하는 [쿠버네티스 플레이그라운드](https://labs.play-with-k8s.com/, "labs.play-with-k8s.com")\
최대 다섯대의 인스턴스 기동 가능\
연속 사용 시간이 최대 4시간으로 정해지고 기능이 제한됨