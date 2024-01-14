<p float="left">
    <img src="./image/PIN.png" alt="PINLAB" height="100">
    <img src="./image/docker.png" alt="docker" height="100">
</p>

Chapter07 <!-- omit in toc -->
===
서비스

**Table of Contents**
- [서비스의 개념](#서비스의-개념)
- [서비스 타입](#서비스-타입)
- [서비스 사용하기](#서비스-사용하기)
  - [ClusterIP 타입 서비스 사용하기](#clusterip-타입-서비스-사용하기)
  - [NodePort 타입 서비스 사용하기](#nodeport-타입-서비스-사용하기)

# 서비스의 개념
여러 노드를 옮기면서 동적으로 실행되는 파드들에 고정적으로 접근할 수 있는 방법\
서비스는 주로 L4영역에서 통신할 때, 인그레스는 주로 L7영역에서 통신할 때 사용

# 서비스 타입
크게 네 가지 존재:
- ClusterIP : 기본 서비스 타입. 클러스터 안에서만 사용.
- NodePort : 서비스 하나에 모든 노드의 지정된 포트를 할당. 클러스터 외부에서 안으로 접근하는 가장 간단한 방법.
    > node1:8080, node2:8080로 지정한다고 가정. 파드가 node1에만 실행되어 있고, node2에는 실행되지 않았더라도 node2:8080으로 접근했을 때 node1에 실행된 파드로 연결
- LoadBalancer : 퍼블릭 클라우드 서비스, 로드밸런서 장비에서 사용.
- ExternalName : .spec.externalName 필드의 값과 연결. 클러스터 안에서 외부에 접근할 때 주로 사용.

# 서비스 사용하기
```yaml
# service example
apiVersion: v1
kind: Service
metadata:
  name: my-service
spec:
  type: ClusterIP  # 서비스 타입. 생략시 기본은 ClusterIP
  clusterIP: 10.0.10.10  # 클러스터 IP 설정 가능. 생략시 자동으로 할당
  selector:
    app: MyApp  # 서비스와 연결할 파드에 설정한 .labels 필드 값
  ports:  # 배열 형태이기 때문에 한번에 여러 포트를 제공할 떄는 .spec.ports[] 하위에 필드 값 설정
  - protocol: TCP
    port: 80
    targetPort: 9376
```
```bash
kubectl create deployment nginx-for-svc --image=nginx --replicas=2 --port=80
```

## ClusterIP 타입 서비스 사용하기
```yaml
# clusterip.yaml
apiVersion: v1
kind: Service
metadata:
  name: clusterip-service
spec:
  type: ClusterIP
  selector:
    app: nginx-for-svc
  ports:
  - protocol: TCP
    port: 80
    targetPort: 80
```
```bash
kubectl apply -f clusterip.yaml
kubectl get svc
kubectl describe service clusterip-service
kubectl get pods -o wide
kubectl run -it --image nicolaka/netshoot testnet -- bash
$ curl 10.244.0.49  # Endpoints from describe
```

## NodePort 타입 서비스 사용하기
```yaml
# nodeport.yaml
apiVersion: v1
kind: Service
metadata:
  name: nodeport-service
spec:
  type: NodePort
  selector:
    app: nginx-for-svc
  ports:
  - protocol: TCP
    port: 80
    targetPort: 80
    nodePort: 30080
```
```bash
kubectl apply -f nodeport.yaml
kubectl get svc
# localhost:30080
# minikube cluster 환경에서는 localhost라 아니라 node IP로 접속
```