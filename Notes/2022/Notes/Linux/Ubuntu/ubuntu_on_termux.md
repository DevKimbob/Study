Ubuntu on Termux
===
# 1. Termux setup
* download termux  
[f-droid.org](https://github.com/MFDGaming/ubuntu-in-termux "https://github.com/MFDGaming/ubuntu-in-termux")
[github.com](https://github.com/MFDGaming/ubuntu-in-termux "https://github.com/MFDGaming/ubuntu-in-termux")

* basic setup
```bash
~ $ termux-change-repo
~ $ pkg update && pkg upgrade -y
~ $ termux-setup-storage
~ $ ssh-keygen -t rsa
```

# 2. Install Ubuntu
MFDGaming : [github.com](https://github.com/MFDGaming/ubuntu-in-termux "https://github.com/MFDGaming/ubuntu-in-termux")  
tuanpham-dev : [github.com](https://github.com/tuanpham-dev/termux-ubuntu "https://github.com/tuanpham-dev/termux-ubuntu")  
proot-distro : [github.com](https://github.com/termux/proot-distro "https://github.com/termux/proot-distro")  
andronix : [andronix.app](https://andronix.app/ "https://andronix.app/")  

# 3. Install VNC server
* 1 ~ 5 : gnome 하고 싶은데..., andronix : 그냥 xfce로 하자...
[1](https://www.answertopia.com/ubuntu/ubuntu-remote-desktop-access-with-vnc/)  
[2](https://almost-a-technocrat.blogspot.com/2010/06/how-to-start-up-vnc-session-with-gnome.html)  
[3](https://ko.linux-console.net/?p=438)  
[4](https://www.teknotut.com/en/install-vnc-server-with-gnome-display-on-ubuntu-18-04/)  
[5](https://technical-bot.blogspot.com/2021/10/how-to-install-ubuntu-gnome-desktop-on.html)  
[andronix.app](https://andronix.app/ "https://andronix.app/")  

# 4. Additional Settings
* Android 12 Termux fix
[reddit.com](https://www.reddit.com/r/termux/comments/ru61y4/any_fix_for_android_12_and_termux_process/ "https://www.reddit.com/r/termux/comments/ru61y4/any_fix_for_android_12_and_termux_process/")  
[gist.github.com](https://gist.github.com/agnostic-apollo/dc7e47991c512755ff26bd2d31e72ca8#commands-to-disable-phantom-process-killing-and-tldr "https://gist.github.com/agnostic-apollo/dc7e47991c512755ff26bd2d31e72ca8#commands-to-disable-phantom-process-killing-and-tldr")  
```bash
$ adb shell "/system/bin/device_config set_sync_disabled_for_tests persistent; /system/bin/device_config put activity_manager max_phantom_processes 2147483647"
```

* WhiteSur Custom : based on aarch
[youtube.com](https://www.youtube.com/watch?v=oQ8RWtD3MTQ "https://www.youtube.com/watch?v=oQ8RWtD3MTQ")  
[youtube.com](https://www.youtube.com/watch?v=uvvoJU69uNo "https://www.youtube.com/watch?v=uvvoJU69uNo")  

# 5. All at Once..?
* 어차피 andronix로 할거면 얘로 바로하는거도 나쁘진 않아보이긴 하는데...(andronix ubuntu20 xfce, add normal user)  
[github.com](https://github.com/tuanpham-dev/termux-ubuntu "https://github.com/tuanpham-dev/termux-ubuntu")  

* group fix
```bash
~$ cat /etc/group
~$ sudo groupadd --gid <group_num> <empty_group>
```

* customs  
[youtube.com](https://www.youtube.com/watch?v=uvvoJU69uNo&ab_channel=LinuxScoop "https://www.youtube.com/watch?v=uvvoJU69uNo&ab_channel=LinuxScoop")  
```
gtk whitesur
panel custom
plank
ulauncher
nautilus
vscode
```
[1](https://www.clien.net/service/board/cm_linux/16641914 "https://www.clien.net/service/board/cm_linux/16641914")  
[2](https://findnew.tistory.com/22 "https://findnew.tistory.com/22")  
-> ibus preferences