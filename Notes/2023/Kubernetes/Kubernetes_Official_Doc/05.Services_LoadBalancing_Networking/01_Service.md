<p float="left">
    <img src="../image/PIN.png" alt="PINLAB" height="100">
    <img src="../image/docker.png" alt="docker" height="100">
</p>

Service
===

**Table of Contents**
- [Service](#service)
- [Offical Documentation](#offical-documentation)
  - [Overview](#overview)
  - [Services in Kubernetes](#services-in-kubernetes)
  - [Defining a Service](#defining-a-service)
    - [Port definitions](#port-definitions)
    - [Services without selectors](#services-without-selectors)
  - [Service type](#service-type)

# Offical Documentation
[https://kubernetes.io/docs/concepts/services-networking/service/](https://kubernetes.io/docs/concepts/services-networking/service/ "https://kubernetes.io/docs/concepts/services-networking/service/")

## Overview
Service is a method for exposing a network application that is running as one or more Pods in your cluster. Each Pod gets its own IP address. If some set of Pods(call them backends) provides functionality to other Pods(call them frontends) inside your cluster, frontends can keep track of the backends using Services.

## Services in Kubernetes
The set of Pods targeted by a Service is usually determined by a selector that you define. If your workload speaks HTTP, you might choose to use an Ingress to control how web traffic reaches that workload. Ingress is not a Service type, but it acts as the entry point for your cluster.

## Defining a Service
A Service is an object like a Pod or a ConfigMap.

For example, suppose you have a set of Pods that each listen on TCP port 9376 and are labelled as `app.kubernetes.io/name=MyApp`. You can define a Service to publish that TCP listener:
```yaml
apiVersion: v1
kind: Service
metadata:
  name: my-service
spec:
  selector:
    app.kubernetes.io/name: MyApp
  ports:
    - protocol: TCP
      port: 80
      targetPort: 9376
```

Applying this manifest creates a new Service named "my-service", and assigns IP address to its self; the *cluster IP*. The controller for that Service continuously scans for Pods that match its selector, and then makes any necessary updates to the set of EndpointSlices for the Service.
> A Service can map any incoming port to a targetPort. By default and for convenience, the targetPort is set to the same value as the port field.

### Port definitions
Port definitions in Pods have names, and you can reference these names in the targetPort attribute of a Service. For example, we can bind the targetPort of the Service to the Pod port in the following way:
```yaml
apiVersion: v1
kind: Pod
metadata:
  name: nginx
  labels:
    app.kubernetes.io/name: proxy
spec:
  containers:
  - name: nginx
    image: nginx:stable
    ports:
      - containerPort: 80
        name: http-web-svc

---
apiVersion: v1
kind: Service
metadata:
  name: nginx-service
spec:
  selector:
    app.kubernetes.io/name: proxy
  ports:
  - name: name-of-service-port
    protocol: TCP
    port: 80
    targetPort: http-web-svc
```

### Services without selectors
To be Continued...

## Service type
The available `type` values and their behaviors are:
- [Cluster IP](https://kubernetes.io/docs/concepts/services-networking/service/#type-clusterip "https://kubernetes.io/docs/concepts/services-networking/service/#type-clusterip") : Exposes the Service on a cluster-internal IP. Choosing this value makes the Service only reachable from within the cluster. This is the default that is used if you don't explicitly specify a type for a Service. You can expose the Service to the public internet using an Ingress or a Gateway.
- [NodePort](https://kubernetes.io/docs/concepts/services-networking/service/#type-nodeport "https://kubernetes.io/docs/concepts/services-networking/service/#type-nodeport") : Exposes the Service on each Node's IP at a static port (the NodePort). To make the node port available, Kubernetes sets up a cluster IP address, the same as if you had requested a Service of type: ClusterIP.
- [LoadBalancer](https://kubernetes.io/docs/concepts/services-networking/service/#loadbalancer "https://kubernetes.io/docs/concepts/services-networking/service/#loadbalancer") : Exposes the Service externally using an external load balancer. Kubernetes does not directly offer a load balancing component; you must provide one, or you can integrate your Kubernetes cluster with a cloud provider.
- [ExternalName](https://kubernetes.io/docs/concepts/services-networking/service/#externalname "https://kubernetes.io/docs/concepts/services-networking/service/#externalname") : Maps the Service to the contents of the externalName field (for example, to the hostname api.foo.bar.example). The mapping configures your cluster's DNS server to return a CNAME record with that external hostname value. No proxying of any kind is set up.