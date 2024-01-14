GitLab Installation <!-- omit in toc -->
===

**Table of Contents**
- [1. Hardware Spec](#1-hardware-spec)
- [2. Installation](#2-installation)
  - [2.1. Docker](#21-docker)
  - [2.2. GitLab](#22-gitlab)
- [3. Post Jobs](#3-post-jobs)
  - [3.1. Container Registry](#31-container-registry)
  - [3.2. HTTPS / Registry setup](#32-https--registry-setup)
    - [3.2.1. Separate Gitlab/Registry : open](#321-separate-gitlabregistry--open)
- [4. Additional Stuff](#4-additional-stuff)
  - [4.1. Change Password](#41-change-password)

# 1. Hardware Spec
* 2013 mac pro
  > mac trashcan

# 2. Installation
## 2.1. Docker
```bash
brew search docker
brew install --cask docker

# on mac launch docker via GUI
```

## 2.2. GitLab
* [official doc](https://docs.gitlab.com/ee/install/docker.html "https://docs.gitlab.com/ee/install/docker.html")
```bash
# export .zshrc
export GITLAB_HOME=$HOME/gitlab

./run_gitlab.sh
# run_gitlab.sh
#!/bin/bash
# sudo docker run --detach \
#   --hostname <hostname> \  # or ipaddress
#   --publish 8443:443 --publish 880:80 --publish 822:22 \
#   --name gitlab \
#   --restart always \
#   --volume $GITLAB_HOME/config:/etc/gitlab:Z \
#   --volume $GITLAB_HOME/logs:/var/log/gitlab:Z \
#   --volume $GITLAB_HOME/data:/var/opt/gitlab:Z \
#   --shm-size 256m \
#   gitlab/gitlab-ce:latest

# mount path references
# $GITLAB_HOME/data       /var/opt/gitlab         For storing application data.
# $GITLAB_HOME/logs       /var/log/gitlab         For storing logs.
# $GITLAB_HOME/config     /etc/gitlab             For storing the GitLab configuration files.

# check for logs using
sudo docker logs -f gitlab

# view password : valid for first 24h
sudo docker exec -it gitlab grep 'Password:' /etc/gitlab/initial_root_password

# exec  using
sudo docker exec -it gitlab /bin/bash
```

# 3. Post Jobs
## 3.1. Container Registry
[Official Doc](https://docs.gitlab.com/ee/administration/packages/container_registry.html "https://docs.gitlab.com/ee/administration/packages/container_registry.html")


## 3.2. HTTPS / Registry setup
```bash
# set Domain from 내도메인.한국
pinlab.kro.kr -> xxx.xxx.34.176

# change settings : gitlab.rb
external_url "https://pinlab.kro.kr"
registry_external_url "https://pinlab.kro.kr"

# create certs
openssl req -newkey rsa:2048 -nodes -keyout pinlab.kro.kr.key -subj "/C=KR/ST=Seoul/O=PinLab/CN=pinlab.kro.kr" -out pinlab.kro.kr.csr
openssl x509 -req -extfile <(printf "subjectAltName=DNS:pinlab.kro.kr") -days 3650 -in pinlab.kro.kr.csr -signkey pinlab.kro.kr.key -out pinlab.kro.kr.crt

# add certs to server
mkdir -p $GITLAB_HOME/config/ssl
cd $GITLAB_HOME/config/ssl
cp ~/gitlab-setup/ssl-pinlab.kro.kr/pinlab.kro.kr.{crt,key} .

# add cert to docker : from user, not server
mkdir -p /etc/docker/certs.d/pinlab.kro.kr
cd /etc/docker/certs.d/pinlab.kro.kr
vim pinlab.kro.kr.crt
# copy from pinlab.kro.kr.crt

# docker login
docker login pinlab.kro.kr
```

### 3.2.1. Separate Gitlab/Registry : open
```bash
# change settings : gitlab.rb
external_url "https://gitlab.pinlab.kro.kr"
registry_external_url "https://registry.pinlab.kro.kr"

# create certs
openssl req -newkey rsa:2048 -nodes -keyout gitlab.pinlab.kro.kr.key -subj "/C=KR/ST=Seoul/O=PinLab/CN=gitlab.pinlab.kro.kr" -out gitlab.pinlab.kro.kr.csr
openssl x509 -req -extfile <(printf "subjectAltName=DNS:gitlab.pinlab.kro.kr") -days 3650 -in gitlab.pinlab.kro.kr.csr -signkey gitlab.pinlab.kro.kr.key -out gitlab.pinlab.kro.kr.crt

openssl req -newkey rsa:2048 -nodes -keyout registry.pinlab.kro.kr.key -subj "/C=KR/ST=Seoul/O=PinLab/CN=registry.pinlab.kro.kr" -out registry.pinlab.kro.kr.csr
openssl x509 -req -extfile <(printf "subjectAltName=DNS:registry.pinlab.kro.kr") -days 3650 -in registry.pinlab.kro.kr.csr -signkey registry.pinlab.kro.kr.key -out registry.pinlab.kro.kr.crt

# add certs to server
mkdir -p $GITLAB_HOME/config/ssl
cd $GITLAB_HOME/config/ssl
cp ~/gitlab-setup/ssl-gitlab.pinlab.kro.kr/gitlab.pinlab.kro.kr.{crt,key} .
cp ~/gitlab-setup/ssl-registry.pinlab.kro.kr/registry.pinlab.kro.kr.{crt,key} .

# add cert to docker : from user, not server
mkdir -p /etc/docker/certs.d/registry.pinlab.kro.kr
cd /etc/docker/certs.d/registry.pinlab.kro.kr

### state open...
```

# 4. Additional Stuff
## 4.1. Change Password
[Official Doc](https://docs.gitlab.com/ee/security/reset_user_password.html#reset-your-root-password "https://docs.gitlab.com/ee/security/reset_user_password.html#reset-your-root-password")