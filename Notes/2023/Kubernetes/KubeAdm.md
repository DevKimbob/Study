KubeAdmin <!-- omit in toc -->
===

**Table of Contents**
- [Version Check](#version-check)
- [References to Check](#references-to-check)
- [Installation](#installation)
  - [Container Runtime](#container-runtime)
  - [Setup Container Runtime](#setup-container-runtime)
  - [Install kubeadm, kubelet, kubectl](#install-kubeadm-kubelet-kubectl)
  - [Helm](#helm)
- [Creating Cluster](#creating-cluster)
- [Kustomize](#kustomize)
- [Jenkins](#jenkins)

# Version Check
- Ubuntu : 20.04
    > 22.04 has problem installing proxy?\
    > https://forum.linuxfoundation.org/discussion/862809/lab-3-1-kubeadm-init-error-creating-kube-proxy-service-account
- containerd : 1.6.12
    > most recent version from apt 23.06.07\
    > moved from 1.5.11\
    > cri v1 runtime api is not implemented for endpoint unix:///var/run/containerd/containerd.sock
- runc : 1.1.7
- CNI Plugins : 1.3.0
- kubernetes : 1.24.14-00
  - kubeadm, kubelet, kubectl
- Helm : 3.11.3
  > hmm...

# References to Check
Links
- [cri-dockerd](https://passwd.tistory.com/entry/kubeadmcri-dockerd-Kubernetes-%EC%84%A4%EC%B9%98-%ED%81%B4%EB%9F%AC%EC%8A%A4%ED%84%B0-%EC%83%9D%EC%84%B1 "https://passwd.tistory.com/entry/kubeadmcri-dockerd-Kubernetes-%EC%84%A4%EC%B9%98-%ED%81%B4%EB%9F%AC%EC%8A%A4%ED%84%B0-%EC%83%9D%EC%84%B1")

Commands
```bash
sudo apt list -a <package_name>
sudo apt install <package_name>=<version>
sudo apt show <package_name>
sudo apt-cache depends <package_name>
sudo dpkg-reconfigure tzdata
```

# Installation
- [Official Documentation](https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/install-kubeadm/ "https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/install-kubeadm/")

make unique hostname
```bash
sudo vi /etc/hostname
sudo vi /etc/hosts
sudo systemctl reboot
```

configure ip address
```bash
sudo vim /etc/netplan/01-network-manager-all.yaml
# network:
#   version: 2
#   renderer: networkd
#   ethernets:
#     ens33:
#       addresses: [192.168.1.200/24]
#       gateway4: 192.168.1.2
#       nameservers:
#         addresses: [168.126.63.1, 168.126.63.2]
sudo netplan apply 
```

check open port
```bash
nc -l <port>
# open new terminal
nc <ip> <port>
```

## Container Runtime
install container runtime
- Must implement CRI
- containerd or cri-dockerd(for docker) for example
- gonna use [containerd](https://github.com/containerd/containerd/blob/main/docs/getting-started.md "https://github.com/containerd/containerd/blob/main/docs/getting-started.md") [v1.5.11](https://github.com/containerd/containerd/tree/main#:~:text=Hello%20Kubernetes%20v1.24,for%20Kubernetes%20v1.24. "https://github.com/containerd/containerd/tree/main#:~:text=Hello%20Kubernetes%20v1.24,for%20Kubernetes%20v1.24.") for now
  - update : moved to 1.6.12
```bash
# install containerd
# https://github.com/containerd/containerd/releases?q=%221.6.12%22&expanded=true
wget https://github.com/containerd/containerd/releases/download/v1.6.12/containerd-1.6.12-linux-amd64.tar.gz
# wget https://github.com/containerd/containerd/releases/download/v1.6.12/containerd-1.6.12-linux-amd64.tar.gz.sha256sum
# sha256sum -c containerd-1.6.12-linux-amd64.tar.gz.sha256sum
sudo tar Cxzvf /usr/local containerd-1.6.12-linux-amd64.tar.gz
curl https://raw.githubusercontent.com/containerd/containerd/main/containerd.service -O
sudo install -D containerd.service /usr/local/lib/systemd/system/containerd.service
sudo systemctl daemon-reload
sudo systemctl enable --now containerd

# install runc
# https://github.com/opencontainers/runc/releases
wget https://github.com/opencontainers/runc/releases/download/v1.1.7/runc.amd64
sudo install -m 755 runc.amd64 /usr/local/sbin/runc

# install CNI plugin
# https://github.com/containernetworking/plugins/releases
wget https://github.com/containernetworking/plugins/releases/download/v1.3.0/cni-plugins-linux-amd64-v1.3.0.tgz
# wget https://github.com/containernetworking/plugins/releases/download/v1.3.0/cni-plugins-linux-amd64-v1.3.0.tgz.sha256
# sha256sum -c cni-plugins-linux-amd64-v1.3.0.tgz.sha256
sudo mkdir -p /opt/cni/bin
sudo tar Cxzvf /opt/cni/bin cni-plugins-linux-amd64-v1.3.0.tgz
```

## Setup Container Runtime
```bash
cat <<EOF | sudo tee /etc/modules-load.d/k8s.conf
overlay
br_netfilter
EOF

sudo modprobe overlay
sudo modprobe br_netfilter

cat <<EOF | sudo tee /etc/sysctl.d/k8s.conf
net.bridge.bridge-nf-call-iptables  = 1
net.bridge.bridge-nf-call-ip6tables = 1
net.ipv4.ip_forward                 = 1
EOF

sudo sysctl --system
# lsmod | grep br_netfilter
# lsmod | grep overlay
# sysctl net.bridge.bridge-nf-call-iptables net.bridge.bridge-nf-call-ip6tables net.ipv4.ip_forward

sudo mkdir -p /etc/containerd
containerd config default | sudo tee /etc/containerd/config.toml
sudo systemctl restart containerd

sudo swapoff -a
sudo sed -i 's/^\/swapfile/#\/swapfile/' /etc/fstab
```

## Install kubeadm, kubelet, kubectl
version 1.24.14-00

```bash
sudo apt-get update
sudo apt-get install -y apt-transport-https ca-certificates curl
sudo mkdir /etc/apt/keyrings
curl -fsSL https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo gpg --dearmor -o /etc/apt/keyrings/kubernetes-archive-keyring.gpg
echo "deb [signed-by=/etc/apt/keyrings/kubernetes-archive-keyring.gpg] https://apt.kubernetes.io/ kubernetes-xenial main" | sudo tee /etc/apt/sources.list.d/kubernetes.list
sudo apt-get update
sudo apt-get install -y kubelet=1.24.14-00 kubeadm=1.24.14-00 kubectl=1.24.14-00
sudo apt-mark hold kubelet kubeadm kubectl
```

kubectl auto completion
```bash
echo '' >>~/.zshrc
echo 'source <(kubectl completion zsh)' >>~/.zshrc
echo 'alias k=kubectl' >>~/.zshrc
echo 'complete -F __start_kubectl k' >>~/.zshrc
source ~/.zshrc

echo '' >>~/.bashrc
echo 'source <(kubectl completion bash)' >>~/.bashrc
echo 'alias k=kubectl' >>~/.bashrc
echo 'complete -F __start_kubectl k' >>~/.bashrc
source ~/.bashrc
```

## Helm
```bash
# https://github.com/helm/helm/releases
wget https://get.helm.sh/helm-v3.11.3-linux-amd64.tar.gz
tar -zxvf helm-v3.11.3-linux-amd64.tar.gz
mv linux-amd64/helm /usr/local/bin/helm
```

# Creating Cluster
```bash
# master
kubeadm init --control-plane-endpoint=192.168.1.200 --upload-certs --pod-network-cidr=10.244.0.0/16 --cri-socket=unix:///var/run/containerd/containerd.sock
# output example
# kubeadm join 192.168.1.200:6443 --token 1jupff.bxv6msrqvqzizv8t \
#	--discovery-token-ca-cert-hash sha256:e52e6cccda271654e9989569aae6d5d9dd5ed0e8e313f83f3ca1d5018bef2cb6 \
#	--control-plane --certificate-key 502f59e0a542578920881d107a210a6c886c7203de5efef2a76b5414cbc483b4
# kubeadm init phase upload-certs --upload-certs

# non root
mkdir -p $HOME/.kube
sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
sudo chown $(id -u):$(id -g) $HOME/.kube/config
# root
export KUBECONFIG=/etc/kubernetes/admin.conf

kubectl apply -f https://github.com/flannel-io/flannel/releases/latest/download/kube-flannel.yml
# sudo scp /etc/kubernetes/admin.conf pinkimbob@192.168.17.140:/home/pinkimbob/admin.conf

# worker
sudo kubeadm join 192.168.1.100:6443 --token 1jupff.bxv6msrqvqzizv8t --discovery-token-ca-cert-hash sha256:e52e6cccda271654e9989569aae6d5d9dd5ed0e8e313f83f3ca1d5018bef2cb6
# can give option to change node's name : --node-name?

# kubeadm join --token <token> <control-plane-host>:<control-plane-port> --discovery-token-ca-cert-hash sha256:<hash>
# kubeadm token create
# kubeadm token list
# openssl x509 -pubkey -in /etc/kubernetes/pki/ca.crt | openssl rsa -pubin -outform der 2>/dev/null | openssl dgst -sha256 -hex | sed 's/^.* //'
```

reset
- [Clean up](https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/create-cluster-kubeadm/#tear-down "https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/create-cluster-kubeadm/#tear-down")

dashboard
> https://kubernetes.io/docs/tasks/access-application-cluster/web-ui-dashboard/
> https://github.com/kubernetes/dashboard/blob/master/docs/user/access-control/creating-sample-user.md

# Kustomize

# Jenkins
```bash
docker run -d -p 8080:8080 -p 50000:50000 -v /home/jenkins:/var/jenkins_home -v /var/run/docker.sock:/var/run/docker.sock -u root jenkins/jenkins:lts
# install docker
# install kubectl
# get admin.conf
# install jq
# install ngrok
cat /var/jenkins_home/secrets/initialAdminPassword
```
