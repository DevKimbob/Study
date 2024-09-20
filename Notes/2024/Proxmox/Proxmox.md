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