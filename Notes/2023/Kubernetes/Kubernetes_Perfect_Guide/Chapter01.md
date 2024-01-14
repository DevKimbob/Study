<p float="left">
    <img src="images/PIN.png" alt="PINLAB" height="100">
    <img src="images/docker.png" alt="docker" height="100">
</p>

# K8s Perfect Guide

**Table of Contents**
- [K8s Perfect Guide](#k8s-perfect-guide)
- [1. Docker](#1-docker)
    - [Docker image를 생성할 때 주의할 점](#docker-image를-생성할-때-주의할-점)
    - [Dockerfile 명령어](#dockerfile-명령어)
    - [Dockerfile -\> Docker image build](#dockerfile---docker-image-build)
    - [MultiStage Build (+a : BuildKit)](#multistage-build-a--buildkit)
    - [Using scratch images](#using-scratch-images)
    - [Pushing to Docker Hub](#pushing-to-docker-hub)
    - [Running Docker Container](#running-docker-container)


# 1. Docker
### Docker image를 생성할 때 주의할 점
1. 1컨테이너당 1프로세스
2. 변경불가 인프라 & 경량 이미지 (경량 기반이미지, apt 캐시파일 삭제, 레이어 줄이기, squash)
3. 실행은 root 이외의 사용자 (Dockerfile : USER 검색)

### Dockerfile 명령어
* LABEL : 메타데이터를 K:V 형식으로 지정
* USER / WORKDIR : 실행 계정 / 디렉터리(없을 시 생성)
* EXPOSE : Listen할 포트 지정
* RUN : build 시 실행 명령어
* ADD / COPY
  * COPY : 단순 복사
  * ADD : tar.gz 압축해제 후 복사
* ENTRYPOINT / CMD : container 실행 시, `$ENTRYPOINT $CMD`가 실행된다고 생각
  * ENTRYPOINT : 실행 명령어
  * CMD : 실행 명령어 인수

### Dockerfile -> Docker image build  
```bash
docker image build -t <REPOSITORY>:<TAG> <dockerfile_dir>
  # build -f <dockerfile_name> 으로 명시 가능
docker image ls
```

### MultiStage Build (+a : BuildKit)
```dockerfile
# Stage 1
FROM golang:1.14.1-alpine3.11 as builder
COPY ./main.go ./
RUN go build -o /go-app ./main-go

# Stage 2
FROM alpine:3.11
COPY --from=builder /go-app .
ENTRYPOINT ["./go-app"]
```

### Using scratch images
```dockerfile
FROM scratch ...
```

### Pushing to Docker Hub
```bash
# <Registry_host_name>/<namespace>/<repository>:<tag>
# Registry_host_name 은 생략 가능
# ex docker.io/DOCKERHUB_USER/sample-image:0.1

docker login
docker image tag simple-image:0.1 DOCKERHUB_USER/sample-image:0.1
docker image push DOCKERHUB_USER/sample-image:0.1
docker logout
```

### Running Docker Container
```bash
docker container run -d -p 12345:8080 sample-image:0.1
curl http://localhost:12345
```
