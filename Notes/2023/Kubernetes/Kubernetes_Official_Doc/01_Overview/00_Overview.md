<p float="left">
    <img src="../image/PIN.png" alt="PINLAB" height="100">
    <img src="../image/docker.png" alt="docker" height="100">
</p>

Overview
===

**Table of Contents**
- [Overview](#overview)
- [Offical Documentation](#offical-documentation)
  - [Going back in time](#going-back-in-time)
  - [Why you need Kubernetes and what it can do](#why-you-need-kubernetes-and-what-it-can-do)
  - [What Kubernetes is not](#what-kubernetes-is-not)

# Offical Documentation
[https://kubernetes.io/docs/concepts/overview/](https://kubernetes.io/docs/concepts/overview/ "https://kubernetes.io/docs/concepts/overview/")

## Going back in time
<img src="../image/container_evolution.svg" alt="conatiner_evolution" width="500">

> Traditional : physical servers\
> Virtualized : VMs\
> Container : Containers

Containers are similar to VMs, but they are considerd lightweight

## Why you need Kubernetes and what it can do
Kubernetes can do:
- Service discovery and load balancing
- Storage orchestration
- Automated rollouts and rollbacks
- Automatic bin packing
- Self-healing
- Secret and configuration management

## What Kubernetes is not
Kubernetes:
- Does not build your application
- Does not provide application-level services; middleware, data-processing framework, DB, ...
- Is not a mere orchestration system
  > Additionally, Kubernetes is not a mere orchestration system. In fact, it eliminates the need for orchestration. The technical definition of orchestration is execution of a defined workflow: first do A, then B, then C. In contrast, Kubernetes comprises a set of independent, composable control processes that continuously drive the current state towards the provided desired state. It shouldn't matter how you get from A to C. Centralized control is also not required. This results in a system that is easier to use and more powerful, robust, resilient, and extensible.