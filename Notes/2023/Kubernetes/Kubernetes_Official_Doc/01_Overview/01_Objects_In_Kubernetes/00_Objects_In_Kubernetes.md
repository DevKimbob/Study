<p float="left">
    <img src="../image/PIN.png" alt="PINLAB" height="100">
    <img src="../image/docker.png" alt="docker" height="100">
</p>

Objects In Kubernetes
===

**Table of Contents**
- [Objects In Kubernetes](#objects-in-kubernetes)
- [Offical Documentation](#offical-documentation)
  - [Understanding Kubernetes objects](#understanding-kubernetes-objects)
  - [Object spec and status](#object-spec-and-status)
  - [Describing a Kubernetes object](#describing-a-kubernetes-object)
    - [Required fields](#required-fields)

# Offical Documentation
[https://kubernetes.io/docs/concepts/overview/working-with-objects/](https://kubernetes.io/docs/concepts/overview/working-with-objects/ "https://kubernetes.io/docs/concepts/overview/working-with-objects/")

## Understanding Kubernetes objects
A Kubernetes object is a "record of intent"--once you create the object, the Kubernetes system will constantly work to ensure that object exists. By creating an object, you're effectively telling the Kubernetes system what you want your cluster's workload to look like; this is your cluster's desired state.

To work with Kubernetes objects--whether to create, modify, or delete them--you'll need to use the Kubernetes API. When you use the kubectl command-line interface, for example, the CLI makes the necessary Kubernetes API calls for you. You can also use the Kubernetes API directly in your own programs using one of the Client Libraries.

## Object spec and status
Almost every Kubernetes object includes two nested object fields: *spec* and *status*. The Spec has to be set when you create the object, providing a description of it's *desired state*. The Status describes the *current state* of the object.

## Describing a Kubernetes object
When you create on object you must provide the object spec as well as some basic information about the object.
```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: nginx-deployment
spec:
  selector:
    matchLabels:
      app: nginx
  replicas: 2 # tells deployment to run 2 pods matching the template
  template:
    metadata:
      labels:
        app: nginx
    spec:
      containers:
      - name: nginx
        image: nginx:1.14.2
        ports:
        - containerPort: 80
```

### Required fields
In the .yaml file you'll need to set values for the following fields:
- apiVersion : Which version of the Kubernetes API you're using to create this object
- kind : What kind of object you want to create
- metadata : Data that helps uniquely identify the object, including a `name` string, `UID`, and optional `namespace`
- spec : What state you desire for the object