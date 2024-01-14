#! /bin/bash

# check sudo
if [ $EUID != 0 ]; then
	echo '** This script needs sudo privileges **'
	exit 1
fi

# check argc
if [[ $# -ne 4 && $# -ne 5 ]]; then
	echo '** Usage : $ ./KubeAdm.sh <container_runtime_version> <runc_version> <cni_plugin_version> <kubernetes_version>'
	exit 2
fi

# version variable
CONTRTVERSION=$1
RUNCVERSION=$2
CNIPVERSION=$3
KUBEVERSION=$4

# make temp dir
temp_dir=$(mktemp -d)
cd $temp_dir
# mkdir kubeadm_install
# cd kubeadm_install

# containerd
wget https://github.com/containerd/containerd/releases/download/v$CONTRTVERSION/containerd-$CONTRTVERSION-linux-amd64.tar.gz
tar Cxzvf /usr/local containerd-$CONTRTVERSION-linux-amd64.tar.gz
curl https://raw.githubusercontent.com/containerd/containerd/main/containerd.service -O
install -D containerd.service /usr/local/lib/systemd/system/containerd.service
systemctl daemon-reload
systemctl enable --now containerd

# runc
wget https://github.com/opencontainers/runc/releases/download/v$RUNCVERSION/runc.amd64
install -m 755 runc.amd64 /usr/local/sbin/runc

# CNI Plugins
wget https://github.com/containernetworking/plugins/releases/download/v$CNIPVERSION/cni-plugins-linux-amd64-v$CNIPVERSION.tgz
mkdir -p /opt/cni/bin
tar Cxzvf /opt/cni/bin cni-plugins-linux-amd64-v$CNIPVERSION.tgz

# Container Runtime Setup
cat <<EOF | tee /etc/modules-load.d/k8s.conf
overlay
br_netfilter
EOF

modprobe overlay
modprobe br_netfilter

cat <<EOF | tee /etc/sysctl.d/k8s.conf
net.bridge.bridge-nf-call-iptables  = 1
net.bridge.bridge-nf-call-ip6tables = 1
net.ipv4.ip_forward                 = 1
EOF

sudo sysctl --system

mkdir -p /etc/containerd
containerd config default | tee /etc/containerd/config.toml
systemctl restart containerd

swapoff -a
sed -i 's/^\/swapfile/#\/swapfile/' /etc/fstab

# kubernetes
apt-get update
apt-get install -y apt-transport-https ca-certificates curl
mkdir /etc/apt/keyrings
curl -fsSL https://packages.cloud.google.com/apt/doc/apt-key.gpg | gpg --dearmor -o /etc/apt/keyrings/kubernetes-archive-keyring.gpg
echo "deb [signed-by=/etc/apt/keyrings/kubernetes-archive-keyring.gpg] https://apt.kubernetes.io/ kubernetes-xenial main" | tee /etc/apt/sources.list.d/kubernetes.list
apt-get update
apt-get install -y kubelet=$KUBEVERSION kubeadm=$KUBEVERSION kubectl=$KUBEVERSION
apt-mark hold kubelet kubeadm kubectl

# rm temp dir
cd
rm -rf $temp_dir

# finalize installation
echo -e "\nInstallation complete"

# auto completion
echo '''
for enabling auto completion run :

<bash>
echo '' >>~/.bashrc
echo 'source <(kubectl completion bash)' >>~/.bashrc
echo 'alias k=kubectl' >>~/.bashrc
echo 'complete -F __start_kubectl k' >>~/.bashrc
source ~/.bashrc

<zsh>
echo '' >>~/.zshrc
echo 'source <(kubectl completion zsh)' >>~/.zshrc
echo 'alias k=kubectl' >>~/.zshrc
echo 'complete -F __start_kubectl k' >>~/.zshrc
source ~/.zshrc
'''