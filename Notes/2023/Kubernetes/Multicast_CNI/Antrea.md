Antrea CNI <!-- omit in toc -->
===

**Table of Contents**
- [1. Prerequisites](#1-prerequisites)
- [2. Installation](#2-installation)
- [3. OpenDDS](#3-opendds)

# 1. Prerequisites
[Open vSwitch install](https://gist.github.com/natyoliveira/5108584 "https://gist.github.com/natyoliveira/5108584")  
Apparently Open-VSwitch (already installed in kernel module?)

# 2. Installation
[IPAM](https://antrea.io/docs/v1.14.0/docs/antrea-ipam/ "https://antrea.io/docs/v1.14.0/docs/antrea-ipam/")
> not need but saved for later usage

[pod-network-cidr](https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/create-cluster-kubeadm/#pod-network "https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/create-cluster-kubeadm/#pod-network")
> When using kubeadm to create the Kubernetes cluster, passing --pod-network-cidr=<CIDR Range for Pods> to kubeadm init will enable NodeIpamController
```bash
sudo kubeadm init --pod-network-cidr=<range> ...
```

[installation](https://antrea.io/docs/v1.14.0/ "https://antrea.io/docs/v1.14.0/")  
[enable multicast](https://antrea.io/docs/v1.12.1/docs/multicast-guide/ "https://antrea.io/docs/v1.12.1/docs/multicast-guide/")
```bash
wget https://raw.githubusercontent.com/antrea-io/antrea/main/build/yamls/antrea.yml
vim antrea.yml
# antrea-agent.conf: |
#     multicast:
#       enable: true
kubectl apply -f antrea.yml

kubectl get multicastgroups
# No resources found
kubectl get multicastgroups  # after iperf
# GROUP         PODS
# 239.255.5.1   default/ubuntu-5f77dd47f7-vcm79
```

# 3. OpenDDS
config.ini reference
```ini
[common]
DCPSBitTransportIPAddress=172.100.1.3
DCPSBitTransportPort=3899
DCPSGlobalTransportConfig=myconfig
[config/myconfig]
transports=mytcp
[transport/mytcp]
transport_type=multicast
#local_address=172.100.1.3:3898
pub_address=172.100.1.3:3898
group_address=239.255.5.1:49000
```