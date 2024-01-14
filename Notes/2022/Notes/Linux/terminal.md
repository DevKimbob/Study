Terminal Commands
===
references  
[kinsta.com](https://kinsta.com/blog/linux-commands/ "https://kinsta.com/blog/linux-commands/")  
[ubuntu.com](https://ubuntu.com/tutorials/command-line-for-beginners#8-hidden-files "https://ubuntu.com/tutorials/command-line-for-beginners#8-hidden-files")  

# 1. Directory n Files
## pwd  
shows current directory  
```bash
~ $ pwd
/home/ubuntu
```

## ls  
shows directorys  
-a : shows hidden files  
```bash
~ $ ls
documents downloads
~ $ ls -a
. .. .ssh .config documents downloads
~ $ ls -al
total ---
Permissions Size User DateModified Name
drwxr-x---  13   ubuntu            .
drwxr-x-r-x 4    ubuntu            ..
...
```

## cd
change directory  
```bash
~ $ cd documents  # dir inside cur folder
~/documents $ cd /home/ubuntu/documents/github  # absolute path
~/documents/github $ cd  # cd to home
~ $ cd -  # previous path
/home/ubuntu/documents/github
~/documents/github $ cd ..  # upper path
~/documents $ cd .  # cur path
~/documents $ cd ~  # home
~ $
```

## mv
move file/dir
```bash
~ $ mv <src> <dst_dir>
~ $ mv <src> <dst>  # change name
~ $ mv <src> <dst_dir/dst>  # mv and change name
```

## cp
copy file/dir
```bash
~ $ cp <src> <dst>
~ $ cp -r <src_dir/> <dst_dir/>  # forders ends with a forward slash, r = recursive
```

## rm
remove file/dir
```bash
~ $ rm <src>  # file
~ $ rm -r <src_dir/>  # empty dir
~ $ rm -rf <src_dir/>  # dir with file
```

## mkdir
make dir
```bash
~ $ mkdir test/
~ $ mkdir -p another/subdir  # p : parent
```

## touch
make file
```bash
~ $ ls
documents downloads
~ $ touch test.sh
~ $ ls
documents downloads test.sh
```

## chmod
change mode of a file  
r(read), w(write), x(execute)  
```bash
~ $ chmod +x script  # make executable
~ $ chmod 755 shcript  # r = 1, w = 2, x = 4 | User, Group, Others
```

## tar
```bash
~ $ tar -cvf dir1.tar dir1/  # c : create .tar , v : verbose , f : filename
~ $ tar -cvzf dir2.tar.gz dir2/  # z : gzip

~ $ tar -xvf dir1.tar   # x : extract
~ $ tar -xvf dir1.tar -C /home/ubuntu/downloads/  # C : different directory
~ $ tar -xvf dir1.tar script1.sh  # extract single file
~ $ tar -xvf dir1.tar "script1.sh" "script2.sh"  # extarct multiple files
~ $ tar -xvf dir1.tar --wildcards '*.sh'  # extrace multiple file via wildcard
~ $ tar -rvf dir1.tar script3.sh  # add file or dirs
~ $ tar -xvzf dir2.tar.gz
~ $ tar -xvzf dir2.tar.gz script2.sh

~ $ tar -tvf dir1.tar  # t : list content
```

# 2. Others
## alias / unalias  
testging

## man
displays manual page
```bash
~ $ man mkdir
...
~ $ man man
...
```

## exit
exit terminal

## sudo 
superuser do

## htop
interactive process viewer

## package manager
```bash
Debian : apt
Red Hat : yum
Arch : pacman
```

## echo
displays
```bash
~ $ echo hello
hello
~ $ echo $DISPLAY
localhost:10
~ $ echo $PATH
...
```

## cat
concatenate
```bash
~ $ cat script.sh
#! /bin/bash
script
~ $
```

## ps / kill
processers
```bash
~ $ ps
PID   TTY   TIME     CMD
12345 pts/2 00:00:00 program
~ $ kill 12345  # or
~ $ kill program  # this
```

## history
shows command history
```bash
~ $ history
...
346 history
```