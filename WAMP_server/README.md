# Evaluation 2 - WAMP Server

### Install from WAMP
https://sourceforge.net/projects/wampserver/files/WampServer%203/WampServer%203.0.0/wampserver3.3.0_x64.exe/download
<hr>

### http://localhost/phpmyadmin/

```
CREATE DATABASE ir_data;
USE ir_data;

CREATE TABLE readings (
  id INT AUTO_INCREMENT PRIMARY KEY,
  value INT NOT NULL,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

<hr>

### file:///C:/wamp64/bin/apache/apache2.4.54.2/conf/extra/httpd.vhosts

```
# Virtual Hosts
#
<VirtualHost *:80>
  ServerName localhost
  ServerAlias localhost
  DocumentRoot "${INSTALL_DIR}/www"
  <Directory "${INSTALL_DIR}/www/">
    Options +Indexes +Includes +FollowSymLinks +MultiViews
    AllowOverride All
    Require all granted
  </Directory>
</VirtualHost>
```

<hr>

### Windows Defender Firewall with Advanced Security -> Inbound Rules -> New port -> Port -> 80 -> iot -> finish

> restart WAMP server
