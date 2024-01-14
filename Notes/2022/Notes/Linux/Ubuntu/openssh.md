OpenSSH
===

# 1. Open SSH Server
reference : [codechacha.com](https://codechacha.com/ko/ubuntu-install-openssh/ "https://codechacha.com/ko/ubuntu-install-openssh/")

## 1.1. Install OpenSSH
```console
user_name@Device_name:~$ sudo apt update
user_name@Device_name:~$ sudo apt install openssh-server
```

## 1.2. Activate SSH Server
Active: active (running)  // It's curruntly running.
```console
user_name@Device_name:~$ sudo systemctl status ssh

● ssh.service - OpenBSD Secure Shell server
     Loaded: loaded (/lib/systemd/system/ssh.service; enabled; vendor preset: enabled)
     Active: active (running) since Fri 2022-07-08 05:54:02 KST; 8h left
       Docs: man:sshd(8)
             man:sshd_config(5)
   Main PID: 1131 (sshd)
      Tasks: 1 (limit: 18924)
     Memory: 2.3M
     CGroup: /system.slice/ssh.service
             └─1131 sshd: /usr/sbin/sshd -D [listener] 0 of 10-100 startups

Jul 08 05:54:02 <Device_Name> systemd[1]: Starting OpenBSD Secure Shell server...
Jul 08 05:54:02 <Device_Name> sshd[1131]: Server listening on 0.0.0.0 port <port_number>.
Jul 08 05:54:02 <Device_Name> sshd[1131]: Server listening on :: port <port_number>.
Jul 08 05:54:02 <Device_Name> systemd[1]: Started OpenBSD Secure Shell server.
```

If not
```console
user_name@Device_name:~$ sudo systemctl enable ssh  # enable in startup
user_name@Device_name:~$ sudo systemctl start ssh  # start ssh
```

## 1.3. Firewall
Allow ssh in firewall
```console
user_name@Device_name:~$ sudo ufw allow ssh
```

Firewall is disabled by default
```console
user_name@Device_name:~$ sudo ufw status

Status: inactive

user_name@Device_name:~$ sudo ufw enable
user_name@Device_name:~$ sudo ufw disable
```

# 2. Close SSH server
reference : [codechacha.com](https://codechacha.com/ko/ubuntu-install-openssh/ "https://codechacha.com/ko/ubuntu-install-openssh/")

To stop SSH
```console
user_name@Device_name:~$ sudo systemctl stop ssh
```

To disable ssh in startup
```console
user_name@Device_name:~$ sudo systemctl disable ssh
```

# 3. Change port
reference : [jbhs7014.tistory.com](https://jbhs7014.tistory.com/141 "https://jbhs7014.tistory.com/141")

```console
user_name@Device_name:~$ sudo vim /etc/ssh/sshd_config

...
#Port 22
Port <port_number>  # add new line
#AddressFamily any
...

user_name@Device_name:~$ sudo service sshd restart
```

# 4. Connect to SSH
reference : [codechacha.com](https://codechacha.com/ko/ubuntu-install-openssh/ "https://codechacha.com/ko/ubuntu-install-openssh/")

## 4.1. Connect when in a same network
1. Install OpenSSH client
```console
user_name@Device_name:~$ sudo apt-get install openssh-client
```

2. Check logical name : enp3s0
```console
user_name@Device_name:~$ sudo lshw -c network

  *-network DISABLED        
       description: Wireless interface
       ...
  *-network
       description: Ethernet interface
       ...
       logical name: enp3s0  # check!
       ...
```

3. Check IP : <IP_address>
```console
user_name@Device_name:~$ ip a

...
2: enp3s0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc mq state UP group default qlen 1000
    ...
    inet <IP_Address>...
...
```

4. Connect to SSH Server
```console
user_name@Device_name:~$ ssh <user_name>@<IP_Address> -p <port_number>
```

## 4.2. Connect when not in the same network
~~In Progress~~\
~~basically portforward, and use personal ip address. more on that later...~~

# 5. Using Termux
reference : [wiki.termux.com](https://wiki.termux.com/wiki/Main_Page "https://wiki.termux.com/wiki/Main_Page")\
reference(outdated) : [blog.bsmind.co.kr](https://blog.bsmind.co.kr/2180 "https://blog.bsmind.co.kr/2180")\
download link : [f-droid.org](https://f-droid.org/en/packages/com.termux/ "https://f-droid.org/en/packages/com.termux/")

```console
~ $ pkg update
~ $ pkg upgrade
~ $ termux-setup-storage  # gives storage access permission
~ $ pkg install openssh
~ $ sshd  # run ssh
```

# 6. Using SSH Keys
reference : [shanepark.tistory.com](https://shanepark.tistory.com/195 "https://shanepark.tistory.com/195")

## 6.1. Generate SSH key
From : Client
```console
~ $ ssh-keygen -t rsa

# values to type in
# 1. path (default : $HOME/.ssh/id_rsa)
# 2. passphrase (default : none)
# 3. passphrase confirm
```

## 6.2. Registrate SSH key
From : Server
```console
user_name@Device_name:~$ mkdir ~/.ssh  # if not exiting
user_name@Device_name:~$ touch ~/.ssh/authorized_keys
user_name@Device_name:~$ chmod 755 ~/.ssh/authorized_keys  # RW permission
```

Client's ~/.ssh/id_ras.pub : copy\
Server's ~/.ssh/authorized_keys : append
```console
user_name@Device_name:~$ sudo vim ~/.ssh/authorized_keys
```

## 6.3. Save SSH connection info
From : Client
```console
~ $ vim ~/.ssh/config

Host <info_name>
  HostName <IP_Address>
  Port <port_number>
  User <user_name>
```

Connect by
```console
~ $ ssh <info_name>
```