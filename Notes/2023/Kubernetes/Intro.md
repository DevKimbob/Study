Introduction to K8s via Minikube
===

# 0. Comparison

Minikube : simple, min. single node  
Kubeadm : hard, min. two nodes  
Kind : node is in docker container  
K3s : light, no docker default

kops  
kubespray  
tk8  
tarmak  
rancher kube engine  
puppet module  

## Kubeadam
ref : [padok.fr](https://www.padok.fr/en/blog/minikube-kubeadm-kind-k3s "https://www.padok.fr/en/blog/minikube-kubeadm-kind-k3s")  
* pros : use docker containers
* cons : heavy & one master authorized?

# 1. Installation
## set environment
OS : VMware ubuntu 22.04LTS 64bit
1. install docker engine  
```
https://docs.docker.com/engine/install/ubuntu/#install-using-the-repository
```
2. install minikube  
```
https://minikube.sigs.k8s.io/docs/start/
```
3. install kubectl  
```
https://kubernetes.io/docs/tasks/tools/install-kubectl-linux/
```
4. install helm
```
https://helm.sh/docs/intro/install/
```

# 2. Run demo file
## download files
```
https://github.com/cloudnativedevops/demo
```

## file fixes
```bash
#k8s/sevices.yaml $ port 8888->9999 # code is correct
```

# 3. Commands
## ch04
```bash
$ kubectl delete all --selector app=demo
$ kubectl apply -f k8s/deployment.ymal
$ kubectl apply -f k8s/service.ymal
$ kubectl port-forward service/demo 9999:8888
$ kubectl get pods --selector app=demo
$ kubectl delete pods --seelctor app=demo
$ kubectl get deployments
$ kubectl get nodes
$ kubectl describe deployments/demo
$ kubectl describe pod/<pod_NAME>
$ kubectl delete -f k8s/
```