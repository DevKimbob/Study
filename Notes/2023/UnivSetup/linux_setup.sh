#! /bin/bash
# ./linux_setup.sh <id_prefix> <start_num> <end_num> <password>
# sudo apt install dos2unix
# $ dos2unix <script>
# set xrdp remote : ip
# take snapshot?

if [ $EUID != 0 ]; then
	echo '** This script needs sudo privileges **'
	exit 1
fi

if [ $# -ne 4 ]; then
	echo '** Usage : $ ./linux_setup.sh <id_prefix> <start_num> <end_num> <password> **'
	exit 1
fi

id_prefix=$1
start_num=$2
end_num=$3
password=$4

printf "\n=== Installing Basic Components ===\n"
sudo apt update && sudo apt upgrade -y
sudo apt install vim build-essential gedit whois xrdp open-vm-tools-desktop git -y
systemctl enable xrdp
adduser xrdp ssl-cert
systemctl stop ufw
systemctl disable ufw

printf "\n=== Creating Users ===\n"
for i in $(seq $2 $3); do
	if [ $i -lt 0 ] || [ $i -gt 99 ]; then
		continue
	fi

	username=$(printf "%s%02d" $id_prefix $i)
	printf " * invoking %s\n" $username

	# useradd -m -p $(mkpasswd -m sha-512 $password) $username
	adduser --disabled-password --gecos "" $username
	echo "$username:$password" | chpasswd

	#usermod -aG sudo $username
done

printf "\n=== Disabling rsyslog ===\n"
echo ' $ systemctl stop rsyslog'
systemctl stop rsyslog
echo ' $ systemctl disable rsyslog'
systemctl disable rsyslog
