<p float="left">
    <img src="./image/PIN.png" alt="PINLAB" height="100">
    <img src="./image/docker.png" alt="docker" height="100">
</p>

Chapter05 <!-- omit in toc -->
===
파드

**Table of Contents**
- [파드 개념](#파드-개념)
- [파드 사용하기](#파드-사용하기)
- [파드 생명 주기](#파드-생명-주기)
- [kubelet](#kubelet)
- [초기화 컨테이너](#초기화-컨테이너)
- [파드 인프라 컨테이너](#파드-인프라-컨테이너)
- [스태틱 파드](#스태틱-파드)
- [파드에 CPU와 메모리 자원 할당](#파드에-cpu와-메모리-자원-할당)
- [파드에 환경 변수 설정하기](#파드에-환경-변수-설정하기)
- [파드 환경 설정 내용 적용하기](#파드-환경-설정-내용-적용하기)
- [파드 구성 패턴](#파드-구성-패턴)

# 파드 개념
쿠버네티스는 파드라는 단위로 컨테이너를 묶어서 관리\
파드가 여러 노드에 흩어져서 실행되는 일은 없음\
파드의 역할 중 하나는 컨테이너들이 같은 목적으로 자원을 공유하는 것

# 파드 사용하기
템플릿 설정 예:
```yaml
apiVersion: v1
kind: Pod
metadata:
  name: kubernetes-simple-pod  # 파드 이름
  labels:
    app: kubernetes-simple-pod  # 오브젝트 식별 레이블
spec:
  containers:
  - name: kubernetes-simple-pod  # 컨테이너 이름, - 는 하위 필드를 배열로 묶는다는 뜻
    image: arisu1000/simple-container-app:latest  # 컨테이너 이미지
    ports:
    - containerPort: 8080  # 컨테이너 접속 포트 (명시적, 역할은 없음?)
```

# 파드 생명 주기
`$ kubectl describe pods <podname>`에서 `Status`항목으로 확인 가능
- Pending : 파드 생성 중
- Running : 모든 컨테이너 실행 중
- Succeeded : 모든 컨테이너 정상 실행 종료, 재시작 x
- Failed : 모든 컨테이너 중 정상 실행 종료하지 않은 컨테이너 존재
- Unknown : 파드의 상태를 확인할 수 없음. 보통 파드가 있는 노드와 통신할 수 없을 때

파드의 현재 상태를 나타내는 `Conditions`항목에서 `Type`은 다음과 같다
- Initialized : 모든 [초기화 컨테이너](#초기화-컨테이너)가 성공적으로 시작 완료
- Ready : 파드는 요청 실행 가능, 연결된 모든 서비스의 로드밸런싱 풀에 추가되어야 함
- ContainersReady : 모든 컨테이너가 준비 상태
- PodScheduled : 파드가 하나의 노드로 스케줄 완료
- Unschedulable : 스케줄러가 지금 당장 파드를 스케줄할 수 없음

# kubelet
컨테이너 실행 후 주기적으로 진단\
이때 필요한 Probe에는 다음 세가지가 있음:
- livenessProbe : 컨테이너가 실행됐는지 확인. 실패시 kubelet이 컨테이너를 종료시키고, 재시작 정책을 따름. 기본 상태값은 Success
- readinessProbe : 컨테이너 실행 후 서비스 요청에 응답할 수 있는지 진단. 실패시 endpoint controller는 해당 파드에 연결된 모든 서비스를 대상으로 엔드포인트 정보 제거. 첫 번쨰 readinessProbe를 하기 전까지의 기본 상태값은 Failure, 지원하지 않는 컨테이너의 기본 상태 값은 Success
- startupProbe : 컨테이너 안 애플리케이션이 시작되었는지 나타냄. 진단 성공 전까지 다른 프로브 활성 x, 실패시 kubelet이 컨테이너를 종료시키고, 재시작 정책을 따름. startupProbe가 없으면 기본 상태값은 Success

컨테이너 진단은 컨테이너가 구현한 핸들러를 kubelet이 호출해서 실행\
핸들러에는 세 가지가 있음:
- ExecAction : 컨테이너 안에 지정된 명령을 싫행하고 종료 코드가 0일떄 Success라고 진단
- TCPSocketAction : 컨테이너 안에 지정된 IP와 포트로 TCP상태를 확인하고 포트가 열려있으면 Success라고 진단
- HTTPGetAction : 컨테이너 안에 지정된 IP, 포트, 경로로 HTTP GET 요청을 보냄. 응답코드가 200에서 400사이면 Success라고 진단

진단 결과도 세 가지가 있음:
- Success : 컨테이너 진단 성공
- Failure : 컨테이너 진단 실패
- Unknown : 진단 자체가 실패, 컨테이너 상태를 알 수 없음

# 초기화 컨테이너
앱 컨테이너가 실행되기 전 파드를 초기화\
보안상 이유로 앱 컨테이너 이미지와 같이 두면 안되는 앱의 소스 코드를 별도로 관리할 떄 유용
- 여러개 구성 가능, 템플릿에 명시한 순서대로 실행
- 실행에 실패하면 성공할 때까지 재시작. 쿠버네티스의 선언적이라는 특징에서 벗어날 수 있음
- 초기화 컨테이너가 모두 실행된 후 앱 컨테이너 실행 시작
- 프로브 지원하지 않음. 파드가 모두 준비되기 전에 실행한 후 종료되기 때문

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: kubernetes-simple-pod
  labels:
    app: kubernetes-simple-pod
spec:
  initContainers:
  - name: init-myservice  # 컨테이너 이름
    image: arisu1000/simple-container-app:latest  # 컨테이너 이미지
    command: ['sh', '-c', 'sleep 2; echo helloworld01;']  # 실행 명령
  - name: init-mydb
    image: arisu1000/simple-container-app:latest
    command: ['sh', '-c', 'sleep 2; echo helloworld02;']
  containers:
  - name: kubernetes-simple-pod 
    image: arisu1000/simple-container-app:latest
    command: ['sh', '-c', 'echo The app is running! && sleep 3600']
```

# 파드 인프라 컨테이너
모든 파드에서 항상 실행되는 pause라는 컨테이너를 파드 인프라 컨테이너라고 함\
pause는 파드 안 기본 네트워크로 실행되며, 프로세스 식별자(PID)가 1로 설정되므로 다른 컨테이너의 부모 컨테이너 역할을 함\
파드 안 다른 컨테이너는 pause 컨테이너가 제공하는 네트워크를 공유해서 사용하기 때문에 파드 안 다른 컨테이너가 재시작됐을 때는 파드의 IP를 유지하지만, pause 컨테이너가 재시작되면 파드 안 모든 컨테이너도 재시작\
kubelet에는 명령 옵션으로 `--pod-infra-container-image`를 통해 pause가 아닌 다른 컨테이너를 파드 인프라 컨테이너로 지정할 수 있음

# 스태틱 파드
kube-apiserver를 통하지 않고 kubelet이 직접 실행하는 파드들\
kubelet 설정의 `--pod-maniffest-path`옵션에 지정한 디렉터리에 있는 파드들을 kubelet이 감지하여 파드로 실행\
kubelet이 직접 관리하여 이상시 재시작, kubelet이 실행중인 노드에서만 실행, kube-apiserver로 조회만 가능\
보통 kube-apiserver나 etcd와 같은 시스템 파드를 실행하는 용도로 많이 사용
> ex : static pod -> kube-apiserver -> kubernetes pods

쿠버네티스 시스템용 파드들의 템플릿 확인
```bash
minikube ssh
cd /etc/kubernetes/manifests
```

# 파드에 CPU와 메모리 자원 할당
파드를 설정할 때 각 컨테이너가 CPU나 메모리 사용량의 조건 지정
- .spec.containers[].resources.limits.cpu
- .spec.containers[].resources.limits.memory
- .spec.containers[].resources.requests.cpu
- .spec.containers[].resources.requests.memory

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: kubernetes-simple-pod
  labels:
    app: kubernetes-simple-pod
spec:
  containers:
  - name: kubernetes-simple-pod
    image: arisu1000/simple-container-app:latest
    resources:
      requests:
        cpu: 0.1
        memory: 200M
      limits:
        cpu: 0.5
        memory: 1G
    ports:
    - containerPort: 8080
```
요구하는 만큼의 자원이 있는 노드가 없다면 파드는 Pending 상태로 실행되지 않음\
- CPU자원 : 코어 개수로 표시. 0.1 = 코어 하나 연산능력의 10% 
- Memory자원 : 바이트 단위로 측정

# 파드에 환경 변수 설정하기
```yaml
apiVersion: v1
kind: Pod
metadata:
  name: kubernetes-simple-pod
  labels:
    app: kubernetes-simple-pod
spec:
  containers:
  - name: kubernetes-simple-pod
    image: arisu1000/simple-container-app:latest
    ports:
    - containerPort: 8080
    env:
    - name: TESTENV01
      value: "testvalue01"
    - name: HOSTNAME
      valueFrom:
        fieldRef:
          fieldPath: spec.nodeName
    - name: POD_NAME
      valueFrom:
        fieldRef:
          fieldPath: metadata.name
    - name: POD_IP
      valueFrom:
        fieldRef:
          fieldPath: status.podIP
    - name: CPU_REQUEST
      valueFrom:
        resourceFieldRef:
          containerName: kubernetes-simple-pod
          resource: requests.cpu
    - name: CPU_LIMIT
      valueFrom:
        resourceFieldRef:
          containerName: kubernetes-simple-pod
          resource: limits.cpu
```
> name : 사용할 환경변수 이름\
> value : 문자열이나 숫자 형식의 값\
> valueFrom : 값을 다른 곳에서 참조\
> fieldRef : 파드의 현재 설정 내용을 값으로 설정\
> fieldPath : .fieldRef에서 값을 참조하는 항목의 위치 지정\
> resourceFieldRef : 컨테이너에 할당한 자원 정보\
> contaerName : 환경 변수 설정을 가져올 컨테이너 이름\
> resource : 가져올 자원의 종류

# 파드 환경 설정 내용 적용하기
```bash
kubectl apply -f pod-all.yaml
kubectl exec -it kubernetes-simple-pod -- sh
env
exit
```

# 파드 구성 패턴
구글에서 공개한 [Design patterns for container-based distributed system](https://www.usenix.org/system/files/conference/hotcloud16/hotcloud16_burns.pdf "https://www.usenix.org/system/files/conference/hotcloud16/hotcloud16_burns.pdf") : 단일 노드에서 여러 개 컨테이너를 구성할 때의 패턴들이 소개됨
- 사이드카 패턴 : 원래 사용하던 기본 컨테이너의 기능을 확장하거나 강화하는 요도의 컨테이너 추가
- 앰배서더 패턴 : 파드 안에서 프록시 역할을 하는 컨테이너를 추가
- 어댑터 패턴 : 파드 외부로 노출되는 정보를 표준화하는 어댑터 컨테이너 사용