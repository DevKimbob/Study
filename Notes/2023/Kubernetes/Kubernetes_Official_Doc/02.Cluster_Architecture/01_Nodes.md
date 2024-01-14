<p float="left">
    <img src="../image/PIN.png" alt="PINLAB" height="100">
    <img src="../image/docker.png" alt="docker" height="100">
</p>

Nodes
===
A node may be a virtual or physical machine. Each node is managed by the control plane.

**Table of Contents**
- [Nodes](#nodes)
- [Offical Documentation](#offical-documentation)
  - [Management](#management)
  - [To be Continued...](#to-be-continued)

# Offical Documentation
[https://kubernetes.io/docs/concepts/architecture/nodes/](https://kubernetes.io/docs/concepts/architecture/nodes/ "https://kubernetes.io/docs/concepts/architecture/nodes/")

## Management
Two main ways to have Nodes added to the API server:
1. The kubelet on a node self-registers to the control plane
2. User manually add a Node object

After node is created/self-registers, the control plane checks whether the new Node object is valid.

## To be Continued...