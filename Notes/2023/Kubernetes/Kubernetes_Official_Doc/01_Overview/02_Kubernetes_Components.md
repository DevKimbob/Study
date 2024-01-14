<p float="left">
    <img src="../image/PIN.png" alt="PINLAB" height="100">
    <img src="../image/docker.png" alt="docker" height="100">
</p>

Kubernetes Components
===

**Table of Contents**
- [Kubernetes Components](#kubernetes-components)
- [Offical Documentation](#offical-documentation)
  - [Overview](#overview)
  - [Control Plane Components](#control-plane-components)
    - [kube-apiserver](#kube-apiserver)
    - [etcd](#etcd)
    - [kube-scheduler](#kube-scheduler)
    - [kube-controller-manager](#kube-controller-manager)
    - [cloud-controller-manager](#cloud-controller-manager)
  - [Node Components](#node-components)
    - [kubelet](#kubelet)
    - [kube-proxy](#kube-proxy)
    - [Container runtime](#container-runtime)
    - [Addons](#addons)
    - [DNS](#dns)
    - [Web UI (Dashboard)](#web-ui-dashboard)
    - [Container Resource Monitoring](#container-resource-monitoring)
    - [Cluster-level Logging](#cluster-level-logging)

# Offical Documentation
[https://kubernetes.io/docs/concepts/overview/components/](https://kubernetes.io/docs/concepts/overview/components/ "https://kubernetes.io/docs/concepts/overview/components/")

## Overview
<img src="../image/components-of-kubernetes.svg" alt="components-of-kubernetes" width=500>

> Components of a Kubernetes cluster

Basic Terms:
- Node : a worker machine
- Pod : a set of running containers
- Control plane : container orchestration layer that exposes the API
- Controller : a control loop that watches the shared state of the cluster through the apiserver and makes changes attempting to move the current state towords the desired state
- DaemonSet : Ensures a copy of a Pod is running acroos a set of nodes in a cluster
- Deployment : Manages a replicated application on your cluster

## Control Plane Components
Control plane's components make global decisions about the cluster, as well as detecting and responding to cluster events

Control plane components can be run on any machine in the cluster. However, for simplicity, set up scripts typically start all control plane components on the same machine, and do not run user containers on this machine. (= master node?)

### kube-apiserver
exposes the Kubernetes API. The API server is the front end for the Kubernetes control plane. The main implementation kube-apiserver is designed to scale horizontally. You can run several instances of kube-apiserver and balance traffic between them.

### etcd
> ["/etc" + "d"istributed](https://etcd.io/docs/v3.1/learning/why/ "https://etcd.io/docs/v3.1/learning/why/")

Key-value store used as Kubernetes' backing store for all cluster data. If Kubernetes cluster uses etcd as its backing store, make sure to have a back up plan for the data.

### kube-scheduler
Wathces for newly created Pods whit no assigned node, and selects a node for them to run on.

### kube-controller-manager
Runs controller processes. Logically, each controller is a separate process, but to reduce complexity, they are all compiled into a single binary and run in a single process.

Some types of these controllers are:
- Node controller: Responsible for noticing and responding when nodes go down.
- Job controller: Watches for Job objects that represent one-off tasks, then creates Pods to run those tasks to completion.
- EndpointSlice controller: Populates EndpointSlice objects (to provide a link between Services and Pods).
- ServiceAccount controller: Create default ServiceAccounts for new namespaces.

### cloud-controller-manager
Embeds cloud-specific control logic. It lets you link your cluster into your cloud provider's API, and separates out the components that interact with that cloud platform from components that only interact with your cluster.

The cloud-controller-manager only runs controllers that are specific to your cloud provider. If you're running Kubernetes on your own premises for example, the cluster does not have a cloud controller manager.

As with the kube-controller-manager, cloud-controller-manager is compiled into a single binary.

The following controllers can have cloud provider dependencies:
- Node controller: For checking the cloud provider to determine if a node has been deleted in the cloud after it stops responding
- Route controller: For setting up routes in the underlying cloud infrastructure
- Service controller: For creating, updating and deleting cloud provider load balancers

## Node Components
### kubelet
An agent that runs on each node in the cluster to make sure that containers are running in a pod.

kubelet takes a set of PodSpecs and ensure that the containers described in those PodSpecs are running and healthy.

### kube-proxy
A network proxy that runs on each node in your cluster, maintaining network rules on nodes. Enables your Pods from network sessions in/outside of your cluster. kube-proxy uses the operating system packet filtering layer if there is one and it's available. Otherwise, kube-proxy forwards the traffic itself.

### Container runtime
Software that is responsible for running containers. Supports any implementation of the [Kubernetes CRI](https://github.com/kubernetes/community/blob/master/contributors/devel/sig-node/container-runtime-interface.md "https://github.com/kubernetes/community/blob/master/contributors/devel/sig-node/container-runtime-interface.md").

### Addons
Uses Kubernetes resources to implement cluster features. Namespaced resources for addons belong within the `kube-system` namespace.

### DNS
Cluster DNS is a DNS server which serves DNS records for Kubernetes services. All Kubernetes cluster should have cluster DNS as many examples rely on it. Containers started by Kubernetes automatically include DNS server in their DNS serches.

### Web UI (Dashboard)
General purpose web-based UI for Kubernetes clusters.

### Container Resource Monitoring
Records generic time-series metrics about containers in a central DB, and provides a UI for browsing that data.

### Cluster-level Logging
Reponsible for saving container logs to a central log store with search/browsing interface.