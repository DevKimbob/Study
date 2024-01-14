<p float="left">
    <img src="./image/PIN.png" alt="PINLAB" height="100">
    <img src="./image/docker.png" alt="docker" height="100">
</p>

Chapter03 <!-- omit in toc -->
===
컨테이너 실행하기

**Table of Contents**
- [kubectl](#kubectl)
  - [설치](#설치)
  - [사용법](#사용법)
  - [kubeconfig](#kubeconfig)
- [Deployment](#deployment)
- [Service](#service)

# kubectl
## 설치
binary 혹은 package manager로 설치 가능

## 사용법
자세한 사용법은 공식 문서의 kubectl Cheat Sheet 참고

```bash
kubectl [command] [TYPE] [NAME] [flags]
# ex:
# kubectl get pods
# kubectl get services
# kubectl port-forward svc/echoserver 8080:8080
```
> command : 자원에 실행하려는 동작\
> TYPE : 자원 타입\
> NAME : 자원 이름\
> FLAG : 부가적으로 실행할 옵션

```bash
kubectl run echoserver --image="k8s.gcr.io/echoserver:1.10" --port=8080
kubectl expose po echoserver --type=NodePort
kubectl get pods
kubectl get services
kubectl port-forward svc/echoserver 8080:8080
curl http://localhost:8080
kubectl logs -f echoserver
kubectl delete pod echoserver
kubectl get pods

echo 'source <(kubectl completion bash)' >>~/.bashrc
echo 'source <(kubectl completion zsh)' >>~/.zshrc
```

## kubeconfig
kubectl은 기본적으로 \$HOME/.kube/config 파일에서 클러스터, 인증, 컨텍스트 정보를 읽어들임. 이러한 클러스터 구성 정보를 kubeconfig라고 하고, `$ kubectl config use-context <context>`를 실행해 사용하거나, `--kubeconfig`옵션으로 다른 설정 파일을 지정할 수 있다.
```bash
kubectl get nodes -o wide --no-headers | awk '{print $6}'
kubectl get nodes -o json | jq -r '.items[].status.addresses[] | select(.type=="InternalIP") | .address'
kubectl get nodes -o jsonpath='{.items[*].status.addresses[?(@.type=="InternalIP")].address}'
kubectl get nodes -o json | vim -c 'set ft=json' -
kubectl get pods <podname> -o json | gron
kubectl get nodes -o go-template --template="{{range .items}}{{printf "%s\n" .metadata.name}}{{end}}" 
```

# Deployment
kubectl run으로 파드를 실행시킬 때 사용되는 기본 컨트롤러\
명령이나 템플릿(.yaml)으로 생성 및 수정할 수 있다.
```bash
kubectl create deployment nginx-app --image nginx --port=80
kubectl get pods
kubectl get deployments
kubectl scale deploy nginx-app --replicas=2
kubectl get pods
kubectl get deployments
kubectl delete deployments nginx-app
kubectl get deployments
kubectl get pods
```

# Service
클러스터 외부에서 내부로 접근하는 방법\
ClusterIP, NodePort, LoadBalancer, ExternalName의 타입이 존재\
아래의 예시에서는 서비스 하나에 모든 노드의 지정된 포트를 할당하는 NodePort를 설정
```bash
kubectl apply -f nginx-app.yaml
kubectl get pods
kubectl get deployments

kubectl expose deployment nginx-app --type=NodePort
kubectl get service
# kubectl get nodes -o wide
kubectl describe service nginx-app
# curl http://<node-IP>:<service NodePort>
kubectl delete deployment nginx-app
```