reference : [wnw1005.tistory.com](https://wnw1005.tistory.com/425 "https://wnw1005.tistory.com/425")

# 1. Pre setting
현재 사용중이거나 마운트되어있는 파일 시스템 확인
```console
user_name@Device_name:~$ df -h
Filesystem  Size  Used  Avail  Use%  Mounted on
/dev/sda2    30G   20G    10G   66%  /
/dev/sda1   500M   10M   490M    2%  /boot/efi
```

현재 연결된 모든(?) 장치들의 상태 확인
```console
user_name@Device_name:~$ sudo fdisk -l
Device     Start  End       Sectors    Size  Type
/dev/sdb1  2048   30527374  30525327  14.6G  Microsoft basic data
```

장치 마운트 및 언마운트
```console
user_name@Device_name:~$ sudo mount /dev/sdb1 /media/user_name/Label
user_name@Device_name:~$ umount /dev/sdb1
```

디스크 포맷\
FAT32
```console
user_name@Device_name:~$ sudo mkfs.fat -F 32 -n [Label] -v [Device_dir]
```
NTFS
```console
user_name@Device_name:~$ sudo mkntfs -f -L [Label] -v [Device_dir]
```
ext4
```console
user_name@Device_name:~$ sudo mke2fs -t ext4 -L [Label] -v [Device_dir]
```

# 2. Backup using tar command
Single line version
```console
user_name@Device_name:~$ cd /
user_name@Device_name:/$ sudo tar cvpzf /media/user_name/Label/backup_$(date +%y%m%d).tar.gz --exclude=/proc/* --exclude=/lost+found/* --exclude=/media/* --exclude=/mnt/* --exclude=/sys/* /
```

Line breaked version : shift+enter after \
```console
user_name@Device_name:~$ cd /
user_name@Device_name:/$ sudo tar cvpzf /media/user_name/Label/backup_$(date +%y%m%d).tar.gz \
>--exclude=/proc/* \
>--exclude=/lost+found/* \
>--exclude=/media/* \
>--exclude=/mnt/* \
>--exclude=/sys/* \
/
```

# 3. Restore backup file
```console
user_name@Device_name:~$ sudo tar xvpzf /dir_of_backupfile/backup.tar.gz -C /
```

```console
# on ubuntu try

$ sudo add-apt-repository ppa:yannubuntu/boot-repair && sudo apt update
$ sudo apt install -y boot-repair && boot-repair

$ cd <devkimbob's />
$ blkid
$ sudo vi ./etc/fstab
```

# 4. Additional : HDD ownership
```console
$ sudo chown user_name:user_name .
```
