Proxmox with backup
===

**Table of Contents**

# 1. Proxmox
install pve 8.2-2

## basic setup
1. post install
   1. install vim
2. install desktop environment
    > maybe not install xfce at all?
    > https://pve.proxmox.com/wiki/Developer_Workstations_with_Proxmox_VE_and_X11

    1. install nvidia-driver : install failed. skip for now
    ```
    apt install -y dkms pve-headers wget
    wget https://us.download.nvidia.com/XFree86/Linux-x86_64/550.78/NVIDIA-Linux-x86_64-550.78.run
    (Or whatever version you want)
    chmod +x NVIDIA-Linux-x86_64-550.78.run
    ./NVIDIA-Linux-x86_64-550.78.run --dkms
    ```
   2. install barrier, tmux, i3wm
   3. install wpasupplicant, net-tools

3. install theme
   1. zorin. failed, skip for now
   ```
   sudo apt-get install software-properties-common
   sudo apt-get install python3-launchpadlib
   ```
   2. xfce custom
   ```
   
   ```
   
4. setup i3
```
https://cravencode.com/post/essentials/enable-tap-to-click-in-i3wm/
/etc/X11/xorg.conf.d/90-touchpad.conf

https://itsfoss.com/i3-customization/

https://yoonchang.tistory.com/56
```


#
DK Proxmox Setup
===

# 1. VMID
|VMID #1|VMID #2|VMID #3|VMIP|VMType|
|:-:|:-:|:-:|:-:|---|
|1xx||||**System**|
|||111|11|PBS|
|2xx||||**Personal**|
||21x||2x|Main Development|
|||211|21|Ubuntu 20.04 Server|
|3xx||||**PINLab**|
||31x||3x|Daea/Osong DDS|
|||314|34|Osong Interface|
|||315|35|Osong Rtsms|
|||316|36|Osong Rtrms Interface|
|8xx||||**Test-Bed**|
||81x||15x|K8s Enterprise LB/Control|
|||811|151|Load Balancer #1|
|||812|152|Load Balancer #2|
|||815|155|K8s Master #1|
|||816|156|K8s Master #2|
|||817|157|K8s Master #3|
||82x|16x||K8s Enterprise Worker|
|||821|161|K8s Worker #1|
|||822|162|K8s Worker #2|
|||823|163|K8s Worker #3|
||83x|17x||K8s Simple|
|||831|171|K8s Master|
|||832|172|K8s Worker|
|9xx||||**Templates**|
||91x||21x|Ubuntu|
|||911|211|Ubuntu 20.04.06 LTS 64bit Server|
||92x||22x|Windows|
|||921|221|Windows 10 64bit Desktop|
||93x||23x|RedHat|
|||931|231|RHEL 6.9 kernel 3.10.0|
