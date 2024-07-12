Proxmox Setup  <!-- omit in toc -->
===

**Table of Contents**
- [01. Proxmox](#01-proxmox)
  - [SDN](#sdn)
  - [node](#node)
- [02. VM](#02-vm)
  - [hw](#hw)
  - [netplan](#netplan)
  - [setup](#setup)
  - [copy](#copy)
  - [/etc/hosts](#etchosts)
- [03. LB](#03-lb)
  - [haproxy](#haproxy)
  - [keepalived](#keepalived)
- [04. K8s](#04-k8s)
  - [master](#master)
  - [worker](#worker)
  - [cni : Antrea](#cni--antrea)


# 01. Proxmox
## SDN
* VZnoe
  * VNet
    * 192.168.0.0/24
    * 192.168.0.1
* SZnoe
  * SNet
    * 192.168.100.0/24
    * 192.168.100.1
    * SNAT on

## node
firewall : off

# 02. VM
## hw
* ens18 : VNet
  * firewall : off
* ens19 : SNet
  * firewall : off

## netplan
```yaml
# This is the network config written by 'subiquity'
network:
  ethernets:
    ens18:
      addresses:
      - 192.168.0.251/24
      nameservers:
        addresses: []
        search: []
    ens19:
      addresses:
      - 192.168.100.251/24
      routes:
        - to: default
          via: 192.168.100.1
      nameservers:
        addresses:
          - 168.126.63.1
          - 8.8.8.8
        search: []
  version: 2
```

## setup
```bash
sudo apt update
sudo apt install ssh
sudo apt install net-tools
scp kubernetes.tar.gz
```

## copy
copy and set cpu/mem

## /etc/hosts
```
127.0.0.1 localhost
127.0.1.1 ubuntu

# The following lines are desirable for IPv6 capable hosts
::1     ip6-localhost ip6-loopback
fe00::0 ip6-localnet
ff00::0 ip6-mcastprefix
ff02::1 ip6-allnodes
ff02::2 ip6-allrouters

# 192.168.0.100 vip
192.168.0.101 lb01
192.168.0.102 lb02

192.168.0.111 master01
192.168.0.112 master02
192.168.0.113 master03

192.168.0.121 worker01
192.168.0.122 worker02
192.168.0.123 worker03
```

# 03. LB
1. copy vm and set cpu/mem
    * (2 core / 2GB memory)
2. setup ipaddress
3. setup hostname
    ```bash
    hostnamectl set-hostname lb01
    # or hostnamectl set-hostname lb02
    ```
4. install haproxy keepalived  
    [ref](https://kubesphere.io/docs/v3.3/installing-on-linux/high-availability-configurations/set-up-ha-cluster-using-keepalived-haproxy/ "https://kubesphere.io/docs/v3.3/installing-on-linux/high-availability-configurations/set-up-ha-cluster-using-keepalived-haproxy/")

## haproxy
/etc/haproxy/haproxy.cfg
```conf
global
        log /dev/log    local0
        log /dev/log    local1 notice
        chroot /var/lib/haproxy
        stats socket /run/haproxy/admin.sock mode 660 level admin expose-fd listeners
        stats timeout 30s
        user haproxy
        group haproxy
        daemon

        # Default SSL material locations
        ca-base /etc/ssl/certs
        crt-base /etc/ssl/private

        # See: https://ssl-config.mozilla.org/#server=haproxy&server-version=2.0.3&config=intermediate
        ssl-default-bind-ciphers ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:DHE-RSA-AES128-GCM-SHA256:DHE-RSA-AES256-GCM-SHA384
        ssl-default-bind-ciphersuites TLS_AES_128_GCM_SHA256:TLS_AES_256_GCM_SHA384:TLS_CHACHA20_POLY1305_SHA256
        ssl-default-bind-options ssl-min-ver TLSv1.2 no-tls-tickets

defaults
        log     global
        mode    http
        option  httplog
        option  dontlognull
        timeout connect 5000
        timeout client  50000
        timeout server  50000
        errorfile 400 /etc/haproxy/errors/400.http
        errorfile 403 /etc/haproxy/errors/403.http
        errorfile 408 /etc/haproxy/errors/408.http
        errorfile 500 /etc/haproxy/errors/500.http
        errorfile 502 /etc/haproxy/errors/502.http
        errorfile 503 /etc/haproxy/errors/503.http
        errorfile 504 /etc/haproxy/errors/504.http

frontend loadbalancer-frontend
        bind *:6443
        mode tcp
        option tcplog
        default_backend kube-apiserver-backend

backend kube-apiserver-backend
        mode tcp
        option tcplog
        option tcp-check
        balance roundrobin
        #default-server inter 10s downinter 5s rise 2 fall 2 slowstart 60s maxconn 250 maxqueue 256 weight 100
        server kube-apiserver-1 192.168.0.111:6443 check
        #server kube-apiserver-2 192.168.0.112:6443 check
        #server kube-apiserver-3 192.168.0.113:6443 check
```
```bash
sudo systemctl restart haproxy
sudo systemctl enable haproxy
```

## keepalived
```conf
global_defs {
  notification_email {
  }
  router_id LVS_DEVEL
  vrrp_skip_check_adv_addr
  vrrp_garp_interval 0
  vrrp_gna_interval 0
}

vrrp_script chk_haproxy {
  script "killall -0 haproxy"
  interval 2
  weight 2
}

vrrp_instance haproxy-vip {
  state BACKUP
  priority 100                  # Priority
  interface ens18               # NIC
  virtual_router_id 60
  advert_int 1
  authentication {
    auth_type PASS
    auth_pass 1111
  }
  unicast_src_ip 192.168.0.102  # Local IP
  unicast_peer {
    192.168.0.101               # Peer IP
  }

  virtual_ipaddress {
    192.168.0.100/24            # VIP
  }

  track_script {
    chk_haproxy
  }
}
```
```bash
sudo systemctl restart keepalived
sudo systemctl enable keepalived
```

# 04. K8s
1. copy vm and set cpu/mem
    * (4 core / 4GB memory)
2. setup ipaddress
3. setup hostname
    ```bash
    hostnamectl set-hostname master01
    # or hostnamectl set-hostname worker01
    ```
4. run kube.sh
    ```bash
    sudo ./kube.sh 1.7.0 1.1.10 1.3.0 1.28.11-1.1
    ```
5. download images
    ```bash
    sudo kubeadm config images pull
    ```

## master
1. kubeadm init for each masters
2. reset all
3. set default interface to ens18
    * gateway : 192.168.0.1
4. init first master and join others

## worker
join cluster (without switching the gateway? for now...)

## cni : Antrea
turn on multicast for dds discovery
