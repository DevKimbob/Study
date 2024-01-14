VSCode Server
===
* references  

[github.com](https://github.com/coder/code-server "https://github.com/coder/code-server")  
[tistory.com](https://luke-tofu.tistory.com/entry/code-server-%EA%B5%AC%EB%8F%99%ED%95%98%EA%B8%B0-with-Oracle-Cloud-Infrastructure "https://luke-tofu.tistory.com/entry/code-server-%EA%B5%AC%EB%8F%99%ED%95%98%EA%B8%B0-with-Oracle-Cloud-Infrastructure")  
[tistory.com](https://iamiet.tistory.com/20 "https://iamiet.tistory.com/20")  
[hoing.io](https://hoing.io/archives/4615 "https://hoing.io/archives/4615")  
[medium.com](https://medium.com/guleum/oracle-cloud%EC%97%90-code-server-%EC%84%A4%EC%B9%98%ED%95%98%EA%B8%B0-d7226c77be3a "https://medium.com/guleum/oracle-cloud%EC%97%90-code-server-%EC%84%A4%EC%B9%98%ED%95%98%EA%B8%B0-d7226c77be3a")  


# 1. Install and setup
```bash
~ $ curl -fsSL https://code-server.dev/install.sh | sh  # install
~ $ sudo systemctl enable --now code-server@$USER  # background, startup
~ $ vim ~/.config/code-server/config.yaml  # set ip, port, passwd

bind-addr: 0.0.0.0:<port>
auth: password
password : <password>
cert: false

~ $ sudo systemctl start/stop/restart/status code-server@$USER
```

# 2. Ports
OCI : open subnet port  

open port on os
```bash
~ $ Sudo iptables -I INPUT 5 -i ens3 -p tcp --dport 80 -m state --state NEW,ESTABLISHED -j ACCEPT
~ $ sudo iptables -I INPUT 5 -i ens3 -p tcp --dport 443 -m state --state NEW,ESTABLISHED -j ACCEPT
~ $ Sudo iptables -I INPUT 5 -i ens3 -p tcp --dport <port> -m state --state NEW,ESTABLISHED -j ACCEPT
```