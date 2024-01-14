<p float="left">
    <img src="./image/PIN.png" alt="PINLAB" height="100">
    <img src="./image/docker.png" alt="docker" height="100">
</p>

Chapter06 <!-- omit in toc -->
===
컨트롤러

**Table of Contents**
- [레플리케이션 컨트롤러](#레플리케이션-컨트롤러)
- [레플리카세트](#레플리카세트)
  - [레플리카세트와 파드의 연관 관계](#레플리카세트와-파드의-연관-관계)
- [디플로이먼트](#디플로이먼트)
  - [컨테이너 업데이트](#컨테이너-업데이트)
  - [디플로이먼트 롤백](#디플로이먼트-롤백)
  - [파드 개수 조정하기](#파드-개수-조정하기)
  - [디플로이먼트 배포 정지, 배포 재개, 재시작하기](#디플로이먼트-배포-정지-배포-재개-재시작하기)
  - [디플로이먼트 상태(status)](#디플로이먼트-상태status)
- [데몬세트](#데몬세트)
  - [데몬세트 사용하기 : To be Continued...](#데몬세트-사용하기--to-be-continued)

# 레플리케이션 컨트롤러
지정한 숫자만큼의 파드가 항상 클러스터 안에서 실행되도록 관리\
쿠버네티스 프로젝트 초기부터 있었으나 레플리카세트나 디플로이먼트를 주로 사용

# 레플리카세트
레플리케이션 컨트롤러의 발전형, 같은 동작을 하지만 집합 기반의 셀렉터 지원, rolling-update 사용가능
```yaml
apiVersion: apps/v1
kind: ReplicaSet
metadata:
  name: nginx-replicaset
spec:
  template:  # 실행 파드 정보
    metadata:  # 파드 메타데이터
      name: nginx-replicaset  # 파드 이름
      labels:
        app: nginx-replicaset  # 파드 레이블
    spec:  # 컨테이너 구체 명시
      containers:
      - name: nginx-replicaset  # 컨테이너 이름
        image: nginx  # 컨테이너 이미지
        ports:  # 컨테이너 포트
        - containerPort: 80
  replicas: 3
  selector:
    matchLabels:
      app: nginx-replicaset
```
> template : 레플리카세트가 어떤 파드를 실행할지\
> replicas : 파드 유지 개수. 기본값 1\
> selector : 어떤 레이블의 파드를 선택해서 관리할지 설정. 처음 레플리케이션 컨트롤러를 생성할 때 `.spec.template.metadata.labels`의 하위 필드 설정과 `.spec.selector.matchLabels`의 하위 필드 설정이 같아야 함. 다를 경우 kube-apiserver에서 유효하지 않다고 판단하고 파드 변경 거부. selector 설정이 없으면 metadata.labels.app에 있는 내용을 기본값으로 설정

```bash
kubectl apply -f replicaset-nginx.yaml
kubectl delete pod nginx-replicaset-xxxxx
kubectl get pods
```

## 레플리카세트와 파드의 연관 관계
파드는 레이블 기준으로 관리, 레플리카세트와 파드는 느슨하게 결합되어 있다.\
`--cascade=orphan`옵션을 사용하면 파드에 영향없이 레플리카세트만 삭제가능\
이후 실행중인 파드들을 관리하는 레플리카세트를 추가로 생성 가능\

```bash
kubectl delete replicaset nginx-replicaset --cascade=orphan
kubectl get replicaset,pods
kubectl apply -f replicaset-nginx.yaml
kubectl get replicaset,pods
kubectl delete pod nginx-replicaset-xxxxx
kubectl get replicaset,pods
kubectl edit pod nginx-replicaset-xxxxx
kubectl get replicaset,pods
kubectl get pods -o=jsonpath="{range .items[*]}{.metadata.name}{'\t'}{.metadata.labels}{'\n'}{end}"
```

# 디플로이먼트
상태가 없는 앱을 배포할 때 사용하는 가장 기본적인 컨트롤러\
레플리카세트를 관리하면서 앱 배포를 더 세밀하게 관리
```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: nginx-deployment
  labels:
    app: nginx-deployment
spec:
  replicas: 3
  selector:
    matchLabels:
      app: nginx-deployment
  template:
    metadata:
      labels:
        app: nginx-deployment
    spec:
      containers:
      - name: nginx-deployment
        image: nginx
        ports:
        - containerPort: 80
```
> replicas : 파드를 몇 개 실행할지\
> matchLabels : `.metadata.labels`의 하위 필드와 같은 설정

```bash
kubectl apply -f deployment-nginx.yaml
kubectl get deploy,rs,rc,pods
```

## 컨테이너 업데이트
1. `$ kubectl set`
    ```bash
    kubectl set image deployment/nginx-deployment nginx-deployment=nginx:1.9.1
    kubectl get deploy,rs,rc,pods
    kubectl get deploy nginx-deployment -o=jsonpath="{.spec.template.spec.containers[0].image}{'\n'}"
    ```
    컨테이너 이미지를 업데이트 하면서 새로운 레플리카세트가 생성. 기존 파드는 해당 레플리카세트가 관리하는 형식의 파드들로 변경. 이전에 있던 레플리카세트는 DESIRED가 0이 된 상태로 그대로 존재
2. `$ kubectl edit`
   ```bash
   kubectl edit deploy nginx-deployment
   kubectl get deploy nginx-deployment -o=jsonpath="{.spec.template.spec.containers[0].image}{'\n'}"
   ```
   \* 이 방법도 `$ kubectl set`과 동일하게 레플리카세트가 변경되는 것 같음
3. `$ kubectl apply`
   yaml파일 수정 수 `$ kubectl apply -f <deployment_filepath>`

## 디플로이먼트 롤백
```bash
kubectl rollout history deploy nginx-deployment
kubectl rollout history deploy nginx-deployment --revision=3
kubectl rollout undo deploy nginx-deployment
kubectl get deploy,rs,rc,pods
kubectl get deploy nginx-deployment -o=jsonpath="{.spec.template.spec.containers[0].image}{'\n'}"
kubectl rollout undo deploy nginx-deployment --to-revision=3
kubectl get deploy,rs,rc,pods
```

CHANGE-CAUSE 항목에 내용 추가
```yaml
metadata:
  name: nginx-deployment
  labels:
    app: nginx-deployment
  annotations:
    kubernetes.io/change-cause: version 1.10.1
```
```bash
kubectl apply -f deployment-nginx.yaml
# kubectl apply -f deployment-nginx.yaml --record-false
kubectl rollout history deploy nginx-deployment
```

## 파드 개수 조정하기
```bash
kubectl scale deploy nginx-deployment --replicas=5
kubectl get pods
```

## 디플로이먼트 배포 정지, 배포 재개, 재시작하기
```bash
kubectl rollout pause deployment/nginx-deployment
kubectl set image deploy/nginx-deployment nginx-deployment=nginx:1.11
kubectl patch deployment/nginx-deployment -p "{\"metadata\":{\"annotations\":{\"kubernetes.io/change-cause\":\"version 1.11\"}}}"
kubectl rollout history deploy/nginx-deployment
kubectl rollout resume deploy/nginx-deployment
kubectl rollout history deploy/nginx-deployment
kubectl rollout restart deploy/nginx-deployment
kubectl rollout history deploy/nginx-deployment
```

## 디플로이먼트 상태(status)
배포 중에는 디플로이먼트 상태가 변함\
> Progressing -> Complete or Failed\
`$ kubectl rollout status`명령으로 배포 진행 상태 확인 가능

- Progressing
  - 디플로이먼트가 새로운 레플리카세트를 만들 때
  - 디플로이먼트가 새로운 레플리카세트의 파드 개수를 늘릴 때
  - 디플로이먼트가 예전 레플리카세트의 파드 개수를 줄일 때
  - 새로운 파드가 준비 상태가 되거나 이용 가능한 상태가 되었을 때
- Complete
  - 디플로이먼트가 관리하는 모든 레플리카세트가 업데이트 완료되었을 때
  - 모든 레플리카세트가 사용 가능해졌을 때
  - 예전 레플리카세트가 모두 종료되었을 때
- Failed
  - 쿼터 부족
  - readinessProbe 진단 실패
  - 컨테이너 이미지 가져오기 에러
  - 권한 부족
  - 제한 범위 초과
  - 앱 실행 조건을 잘못 지정

템플릿에 .spec.progressDeadlineSeconds 항목 추가 시 지정된 시간이 지났을 때 상태를 False로 바꿈
```bash
kubectl patch deployment/nginx-deployment -p "{\"spec\":{\"progressDeadlineSeconds\":2}}"
# kubectl patch deployment/nginx-deployment -p '{"spec":{"progressDeadlineSeconds":2}}'
kubectl get deploy nginx-deployment -o=jsonpath="{.spec.progressDeadlineSeconds}{'\n'}"
kubectl set image deploy/nginx-deployment nginx-deployment=nginx:1.14
kubectl describe deploy nginx-deployment
```

# 데몬세트
클러스터 전체 노드에 특정 파드를 실행할 때 사용하는 컨트롤러\
클러스터 안에 새롭게 노드가 추가되었을 때 데몬세트가 자동으로 해당 노드에 파드를 실행\
반대로 노드가 클러스터에서 빠졌을 때는 해당 노드에 있던 파드는 그대로 사라짐\
따라서 데몬세트는 클러스터 전체에서 항상 실행시켜두어야 하는 파드에 사용(ex : 로그 수집, 노드 모니터링)

## 데몬세트 사용하기 : To be Continued...
```yaml
apiVersion: apps/v1
kind: DaemonSet
metadata:
  name: fluentd-elasticsearch
  namespace: kube-system
  labels:
    k8s-app: fluentd-logging
spec:
  selector:
    matchLabels:
      name: fluentd-elasticsearch
  updateStrategy:
    type: RollingUpdate
  template:
    metadata:
      labels:
        name: fluentd-elasticsearch
    spec:
      containers:
      - name: fluentd-elasticsearch
        image: fluent/fluentd-kubernetes-daemonset:elasticsearch
        env:
        - name: testenv
          value: value
        resources:
          limits:
            memory: 200Mi
          requests:
            cpu: 100m
            memory: 200Mi%
```